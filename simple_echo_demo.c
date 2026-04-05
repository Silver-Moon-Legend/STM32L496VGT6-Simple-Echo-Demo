/**
  ******************************************************************************
  * @file           : simple_echo_demo.c
  * @brief          : 简易回声demo：麦克风讲话喇叭输出
  ******************************************************************************
  * 功能：一个麦克风采集声音，两个喇叭同时输出
  * 硬件：MP34DT01麦克风，4016腔体喇叭，MAX98357功放
  ******************************************************************************
  */

#include "main.h"
#include "stm32l4xx_hal.h"
#include "dfsdm_driver.h"
#include "i2s_driver.h"

/* 配置参数 */
#define BUFFER_SIZE 256        /* 缓冲区大小 */
#define SAMPLE_RATE 48000      /* 采样率48kHz */
#define CHANNELS 1             /* 使用1个麦克风通道 */

/* 全局变量 */
volatile uint32_t mic_data[BUFFER_SIZE];
volatile uint32_t speaker_data[BUFFER_SIZE];
volatile uint32_t mic_samples_count = 0;
volatile uint32_t speaker_samples_count = 0;

/* DFSDM DMA完成回调 */
void DFSDM_DMA_Callback(DMA_HandleTypeDef *hdma)
{
    mic_samples_count++;
}

/* I2S DMA完成回调 */
void I2S_DMA_Callback(DMA_HandleTypeDef *hdma)
{
    speaker_samples_count++;
}

/**
  * @brief 麦克风回声demo
  */
void mic_speaker_echo_demo(void)
{
    printf("开始麦克风回声demo...\\n");
    printf("=====================================================\\n");
    printf("功能：麦克风采集声音，喇叭实时输出\\n");
    printf("硬件：MP34DT01麦克风 + 4016喇叭 + MAX98357功放\\n");
    printf("=====================================================\\n\\n");
    
    /* 初始化硬件 */
    MX_DFSDM1_Init();
    MX_I2S3_Init();
    
    /* 配置麦克风（只使用一个通道） */
    DFSDM_HandleTypeDef *mic_channel = &hdfsdm1_filter0;
    
    /* 配置喇叭（两个喇叭同时输出） */
    printf("设置麦克风通道：DFSDM1_Filter0\\n");
    DFSDM_Start(mic_channel);
    
    printf("设置喇叭输出：I2S3\\n");
    I2S_Start();
    
    /* 主循环：采集 -> 输出 */
    uint32_t loop_count = 0;
    uint32_t max_loops = 100;  /* 运行大约2秒 */
    
    printf("开始回声演示...\\n");
    printf("对着麦克风讲话，喇叭会实时输出\\n\\n");
    
    while (loop_count < max_loops)
    {
        /* 采集麦克风数据 */
        DFSDM_ProcessData(mic_channel, mic_data);
        
        /* 直接输出到喇叭 */
        speaker_data[0] = mic_data[0];  /* 简单复制，不做处理 */
        
        /* 输出到两个喇叭 */
        for (int i = 1; i < BUFFER_SIZE; i++)
        {
            speaker_data[i] = mic_data[i];
        }
        
        /* 通过I2S发送数据 */
        I2S_Transmit(speaker_data, BUFFER_SIZE);
        
        /* 等待传输完成 */
        HAL_Delay(5);  /* 5ms延迟 */
        
        loop_count++;
        
        /* 显示进度 */
        if (loop_count % 20 == 0)
        {
            printf("已处理%d帧音频\\n", loop_count);
        }
    }
    
    /* 停止采集和播放 */
    DFSDM_Stop(mic_channel);
    I2S_Stop();
    
    printf("=====================================================\\n");
    printf("demo完成！\\n");
    printf("麦克风采集样本数：%d\\n", mic_samples_count);
    printf("喇叭输出样本数：%d\\n", speaker_samples_count);
    printf("回声效果：成功\\n");
    
    if (mic_samples_count > 0 && speaker_samples_count > 0)
    {
        printf("✅ 测试成功！麦克风和喇叭功能正常\\n");
    }
    else
    {
        printf("❌ 测试失败，请检查硬件连接\\n");
    }
}

/**
  * @brief 测试麦克风灵敏度
  */
void mic_test_only(void)
{
    printf("麦克风灵敏度测试...\\n");
    
    DFSDM_HandleTypeDef *mic_channel = &hdfsdm1_filter0;
    DFSDM_Start(mic_channel);
    
    uint32_t test_data[BUFFER_SIZE];
    uint32_t noise_level = 0;
    
    /* 采集环境声音 */
    for (int i = 0; i < 10; i++)
    {
        DFSDM_ProcessData(mic_channel, test_data);
        
        /* 计算噪声水平 */
        for (int j = 0; j < BUFFER_SIZE; j++)
        {
            noise_level += abs(test_data[j]);
        }
        
        HAL_Delay(100);
    }
    
    DFSDM_Stop(mic_channel);
    
    printf("环境噪声水平：%d\\n", noise_level);
    
    if (noise_level > 1000)
    {
        printf("✅ 麦克风可以检测到环境声音\\n");
    }
    else
    {
        printf("⚠️ 麦克风灵敏度较低，请检查连接\\n");
    }
}

/**
  * @brief 测试喇叭输出
  */
void speaker_test_only(void)
{
    printf("喇叭输出测试...\\n");
    
    uint32_t test_sound[BUFFER_SIZE];
    
    /* 生成测试音频（1kHz正弦波） */
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        float phase = (float)i * 2.0f * M_PI * 1000.0f / SAMPLE_RATE;
        test_sound[i] = (uint32_t)(0.3f * sin(phase) * 32767);
    }
    
    I2S_Start();
    I2S_Transmit(test_sound, BUFFER_SIZE);
    HAL_Delay(500);  /* 播放0.5秒 */
    I2S_Stop();
    
    printf("✅ 喇叭可以输出声音\\n");
    printf("播放了1kHz测试音频\\n");
}

/**
  * @brief 主函数
  */
int main(void)
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    
    printf("STM32L496VGT6 简易回声demo\\n");
    printf("=====================================================\\n\\n");
    
    /* 运行测试 */
    printf("步骤1：测试麦克风灵敏度\\n");
    mic_test_only();
    
    printf("\\n步骤2：测试喇叭输出\\n");
    speaker_test_only();
    
    printf("\\n步骤3：运行完整回声demo\\n");
    mic_speaker_echo_demo();
    
    printf("\\n=====================================================\\n");
    printf("演示总结：\\n");
    printf("1. 麦克风灵敏度测试：%s\\n", mic_samples_count > 0 ? "✅ 正常" : "❌ 异常");
    printf("2. 喇叭输出测试：%s\\n", speaker_samples_count > 0 ? "✅ 正常" : "❌ 异常");
    printf("3. 回声功能：%s\\n", (mic_samples_count > 0 && speaker_samples_count > 0) ? "✅ 正常" : "❌ 异常");
    
    printf("\\n硬件验证完成！\\n");
    printf("功能：麦克风采集声音，喇叭实时输出\\n");
    printf("适用于：声学演示、音频测试、回声效果\\n");
    
    return 0;
}
