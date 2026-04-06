/**
  ******************************************************************************
  * @file           : sai_driver.c
  * @brief          : SAI驱动文件
  ******************************************************************************
  */

#include "sai_driver.h"

/* SAI句柄 */
SAI_HandleTypeDef hsai1;

/* DMA句柄 */
DMA_HandleTypeDef hdma_sai1_a;

/**
  * @brief SAI初始化
  */
void SAI_Init(void)
{
    /* SAI时钟初始化 */
    __HAL_RCC_SAI1_CLK_ENABLE();
    __HAL_RCC_DMA1_CLK_ENABLE();
    
    /* SAI BlockA配置 */
    hsai1.Instance = SAI1_BlockA;
    hsai1.Init.AudioMode = SAI_MODEMASTER_TX;
    hsai1.Init.Synchro = SAI_ASYNCHRONOUS;
    hsai1.Init.OutputDrive = SAI_OUTPUTDRIVE_DISABLE;
    hsai1.Init.NoDivider = SAI_MASTERDIVIDER_ENABLE;
    hsai1.Init.FIFOThreshold = SAI_FIFOTHRESHOLD_1QF;
    hsai1.Init.AudioFrequency = SAI_AUDIO_FREQUENCY_48K;
    hsai1.Init.SynchroExt = SAI_SYNCEXT_DISABLE;
    hsai1.Init.MonoStereoMode = SAI_MONOMODE;
    hsai1.Init.CompandingMode = SAI_NOCOMPANDING;
    hsai1.Init.TriState = SAI_OUTPUT_NOTRELEASED;
    
    /* SAI Frame配置 */
    hsai1.FrameInit.FrameLength = 64;
    hsai1.FrameInit.ActiveFrameLength = 32;
    hsai1.FrameInit.FSDefinition = SAI_FS_CHANNEL_IDENTIFICATION;
    hsai1.FrameInit.FSPolarity = SAI_FS_ACTIVE_LOW;
    hsai1.FrameInit.FSOffset = SAI_FS_FIRST_BIT;
    
    /* SAI Slot配置 */
    hsai1.SlotInit.FirstBitOffset = 0;
    hsai1.SlotInit.SlotSize = SAI_SLOT_SIZE_16B;
    hsai1.SlotInit.SlotNumber = 2;
    hsai1.SlotInit.SlotActive = SAI_SLOTACTIVE_ALL;
    
    HAL_SAI_Init(&hsai1);
    
    /* DMA配置 */
    hdma_sai1_a.Instance = DMA1_Channel1;
    hdma_sai1_a.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_sai1_a.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_sai1_a.Init.MemInc = DMA_MINC_ENABLE;
    hdma_sai1_a.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    hdma_sai1_a.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
    hdma_sai1_a.Init.Mode = DMA_NORMAL; 
    hdma_sai1_a.Init.Priority = DMA_PRIORITY_HIGH;
    
    HAL_DMA_Init(&hdma_sai1_a);
    
    /* 连接DMA到SAI */
    __HAL_LINKDMA(&hsai1, hdmaTx, hdma_sai1_a);
    
    /* 启用DMA中断 */
    HAL_DMA_RegisterCallback(&hdma_sai1_a, HAL_DMA_XFER_CPLT_CB_ID, SAI_DMA_Callback);
}

/**
  * @brief 启动SAI
  */
void SAI_Start(void)
{
    HAL_SAI_Transmit_DMA(&hsai1, NULL, 0);
}

/**
  * @brief 停止SAI
  */
void SAI_Stop(void)
{
    HAL_SAI_DeInit(&hsai1);
    HAL_DMA_DeInit(&hdma_sai1_a);
}

/**
  * @brief SAI传输数据
  */
void SAI_Transmit(uint32_t *data, uint32_t size)
{
    HAL_SAI_Transmit_DMA(&hsai1, (uint8_t *)data, size / 2);
}

/**
  * @brief DMA传输完成回调
  */
void SAI_DMA_Callback(DMA_HandleTypeDef *hdma)
{
    if (hdma->Instance == DMA1_Channel1)
    {
        speaker_samples_count++;
    }
}