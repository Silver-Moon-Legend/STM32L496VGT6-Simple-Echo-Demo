/**
  * @file i2s_driver.c
  * @brief I2S driver implementation for MAX98357
  */

#include "i2s_driver.h"
#include "main.h"

static uint16_t i2s_audio_buffer[I2S_BUFFER_SIZE];

/**
  * @brief Initialize I2S peripheral for MAX98357 amplifier
  */
void MX_I2S3_Init(void)
{
    hi2s3.Instance = SPI3;
    hi2s3.Init.Mode = I2S_MODE_MASTER_TX;
    hi2s3.Init.Standard = I2S_STANDARD_PHILLIPS;
    hi2s3.Init.DataFormat = I2S_DATA_FORMAT;
    hi2s3.Init.MCLKOutput = I2S_MCLKOUTPUT_ENABLE;
    hi2s3.Init.AudioFreq = I2S_AUDIO_FREQ;
    hi2s3.Init.CPOL = I2S_CPOL_LOW;
    hi2s3.Init.ClockSource = I2S_CLOCKSOURCE_SYSCLK;
    hi2s3.Init.FullDuplexMode = I2S_FULLDUPLEXMODE_ENABLE;
    
    if (HAL_I2S_Init(&hi2s3) != HAL_OK)
    {
        Error_Handler();
    }
    
    /* Initialize DMA for I2S */
    hdma_i2s3_tx.Instance = DMA1_Channel4;
    hdma_i2s3_tx.Init.Direction = DMA_MEMORY_TO_PERIPHERAL;
    hdma_i2s3_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_i2s3_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_i2s3_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    hdma_i2s3_tx.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
    hdma_i2s3_tx.Init.Mode = DMA_NORMAL;
    hdma_i2s3_tx.Init.Priority = DMA_PRIORITY_MEDIUM;
    
    HAL_DMA_Init(&hdma_i2s3_tx);
    
    hdma_i2s3_rx.Instance = DMA1_Channel5;
    hdma_i2s3_rx.Init.Direction = DMA_PERIPHERAL_TO_MEMORY;
    hdma_i2s3_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_i2s3_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_i2s3_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    hdma_i2s3_rx.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
    hdma_i2s3_rx.Init.Mode = DMA_NORMAL;
    hdma_i2s3_rx.Init.Priority = DMA_PRIORITY_MEDIUM;
    
    HAL_DMA_Init(&hdma_i2s3_rx);
    
    /* Link DMA to I2S */
    __HAL_LINKDMA(&hi2s3, hdmatx, hdma_i2s3_tx);
    __HAL_LINKDMA(&hi2s3, hdmarx, hdma_i2s3_rx);
}

/**
  * @brief Generate alert sound through I2S
  */
void I2S_PlayAlert(I2S_HandleTypeDef *hi2s)
{
    /* Generate simple alert tone */
    for (int i = 0; i < I2S_BUFFER_SIZE; i++)
    {
        /* Generate sine wave at 800Hz */
        uint16_t sine_value = (uint16_t)(32767 * sin(2 * PI * 800 * i / I2S_AUDIO_FREQ));
        i2s_audio_buffer[i] = sine_value;
    }
    
    /* Send audio data via DMA */
    HAL_I2S_Transmit_DMA(hi2s, (uint16_t *)i2s_audio_buffer, I2S_BUFFER_SIZE);
}

/**
  * @brief Stop I2S playback
  */
void I2S_Stop(I2S_HandleTypeDef *hi2s)
{
    HAL_I2S_Stop(hi2s);
    HAL_I2S_DMAStop(hi2s);
}

/**
  * @brief DMA transfer complete callback
  */
void I2S_DMA_Callback(DMA_HandleTypeDef *hdma)
{
    /* DMA transfer complete - audio playback finished */
    if (hdma->Instance == DMA1_Channel4)
    {
        /* TX DMA complete */
        I2S_Stop(&hi2s3);
    }
    else if (hdma->Instance == DMA1_Channel5)
    {
        /* RX DMA complete */
        // Handle RX data if needed
    }
}

/**
  * @brief Initialize DMA peripherals
  */
void MX_DMA_Init(void)
{
    /* DMA already initialized in DFSDM and I2S drivers */
    /* Enable DMA interrupts */
    HAL_NVIC_SetPriority(DMA1_Channel4_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA1_Channel4_IRQn);
    HAL_NVIC_SetPriority(DMA1_Channel5_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA1_Channel5_IRQn);
    HAL_NVIC_SetPriority(DMA2_Channel1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA2_Channel1_IRQn);
    HAL_NVIC_SetPriority(DMA2_Channel2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA2_Channel2_IRQn);
    HAL_NVIC_SetPriority(DMA2_Channel3_IRNie, 0, 0);
    HAL_NVIC_EnableIRQ(DMA2_Channel3_IRQn);
    HAL_NVIC_SetPriority(DMA2_Channel4_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA2_Channel4_IRQn);
}