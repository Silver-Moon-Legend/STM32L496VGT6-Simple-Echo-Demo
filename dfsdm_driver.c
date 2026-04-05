/**
  * @file dfsdm_driver.c
  * @brief DFSDM driver implementation for STM32L496VGT6
  */

#include "dfsdm_driver.h"
#include "main.h"

static DFSDM_Channel_t dfsdm_channels[DFSDM_CHANNEL_COUNT];

/* Helper function for channel-specific error handling */
void Error_ForChannel(uint8_t channel)
{
    /* Log channel error */
    printf("DFSDM Channel %d configuration failed\n", channel);
    Error_Handler();
}

static DFSDM_Channel_t dfsdm_channels[DFSDM_CHANNEL_COUNT];

/**
  * @brief Initialize DFSDM peripherals for 8-channel PDM microphone input
  */
void MX_DFSDM1_Init(void)
{
    /* Initialize DFSDM Filter 0 */
    hdfsdm1_filter0.Instance = DFSDM1_Filter0;
    hdfsdm1_filter0.Init.SincOrder = DFSDM_FILTER_SINC5_ORDER;
    hdfsdm1_filter0.Init.FilterParam.FOSR = 64;
    hdfsdm1_filter0.Init.FilterParam.IOSR = 4;
    hdfsdm1_filter0.Init.FilterParam.FastMode = DFSDM_FILTER_FASTMODE_DISABLE;
    hdfsdm1_filter0.Init.FilterParam.DmaMode = DFSDM_FILTER_DMA_MODE_ENABLED;
    hdfsdm1_filter0.Init.FilterParam.TriggerMode = DFSDM_FILTER_TRIGGER_SW_START;
    hdfsdm1_filter0.Init.ChannelParam.Input = DFSDM_CHANNEL_0;
    hdfsdm1_filter0.Init.ChannelParam.DataPacking = DFSDM_CHANNEL_STANDARD_MODE;
    hdfsdm1_filter0.Init.ChannelParam.RightBitShift = 0;
    
    if (HAL_DFSDM_FilterInit(&hdfsdm1_filter0) != HAL_OK)
    {
        Error_Handler();
    }
    
    /* Initialize DFSDM Filter 1 */
    hdfsdm1_filter1.Instance = DFSDM1_Filter1;
    hdfsdm1_filter1.Init.SincOrder = DFSDM_FILTER_SINC5_ORDER;
    hdfsdm1_filter1.Init.FilterParam.FOSR = 64;
    hdfsdm1_filter1.Init.FilterParam.IOSR = 4;
    hdfsdm1_filter1.Init.FilterParam.FastMode = DFSDM_FILTER_FASTMODE_DISABLE;
    hdfsdm1_filter1.Init.FilterParam.DmaMode = DFSDM_FILTER_DMA_MODE_ENABLED;
    hdfsdm1_filter1.Init.FilterParam.TriggerMode = DFSDM_FILTER_TRIGGER_SW_START;
    hdfsdm1_filter1.Init.ChannelParam.Input = DFSDM_CHANNEL_1;
    hdfsdm1_filter1.Init.ChannelParam.DataPacking = DFSDM_CHANNEL_STANDARD_MODE;
    hdfsdm1_filter1.Init.ChannelParam.RightBitShift = 0;
    
    if (HAL_DFSDM_FilterInit(&hdfsdm1_filter1) != HAL_OK)
    {
        Error_Handler();
    }
    
    /* Initialize DFSDM Filter 2 */
    hdfsdm1_filter2.Instance = DFSDM1_Filter2;
    hdfsdm1_filter2.Init.SincOrder = DFSDM_FILTER_SINC5_ORDER;
    hdfsdm1_filter2.Init.FilterParam.FOSR = 64;
    hdfsdm1_filter2.Init.FilterParam.IOSR = 4;
    hdfsdm1_filter2.Init.FilterParam.FastMode = DFSDM_FILTER_FASTMODE_DISABLE;
    hdfsdm1_filter2.Init.FilterParam.DmaMode = DFSDM_FILTER_DMA_MODE_ENABLED;
    hdfsdm1_filter2.Init.FilterParam.TriggerMode = DFSDM_FILTER_TRIGGER_SW_START;
    hdfsdm1_filter2.Init.ChannelParam.Input = DFSDM_CHANNEL_2;
    hdfsdm1_filter2.Init.ChannelParam.DataPacking = DFSDM_CHANNEL_STANDARD_MODE;
    hdfsdm1_filter2.Init.ChannelParam.RightBitShift = 0;
    
    if (HAL_DFSDM_FilterInit(&hdfsdm1_filter2) != HAL_OK)
    {
        Error_Handler();
    }
    
    /* Initialize DFSDM Filter 3 */
    hdfsdm1_filter3.Instance = DFSDM1_Filter3;
    hdfsdm1_filter3.Init.SincOrder = DFSDM_FILTER_SINC5_ORDER;
    hdfsdm1_filter3.Init.FilterParam.FOSR = 64;
    hdfsdm1_filter3.Init.FilterParam.IOSR = 4;
    hdfsdm1_filter3.Init.FilterParam.FastMode = DFSDM_FILTER_FASTMODE_DISABLE;
    hdfsdm1_filter3.Init.FilterParam.DmaMode = DFSDM_FILTER_DMA_MODE_ENABLED;
    hdfsdm1_filter3.Init.FilterParam.TriggerMode = DFSDM_FILTER_TRIGGER_SW_START;
    hdfsdm1_filter3.Init.ChannelParam.Input = DFSDM_CHANNEL_3;
    hdfsdm1_filter3.Init.ChannelParam.DataPacking = DFSDM_CHANNEL_STANDARD_MODE;
    hdfsdm1_filter3.Init.ChannelParam.RightBitShift = 0;
    
    if (HAL_DFSDM_FilterInit(&hdfsdm1_filter3) !=  HAL_OK)
    {
        Error_Handler();
    }
    
    /* Configure DFSDM Channels */
    DFSDM_ChannelConfigTypeDef channel_config;
    
    /* Channel 0 configuration */
    channel_config.Input = DFSDM_CHANNEL_EXTERNAL_INPUT;
    channel_config.OutputClock = DFSDM_CHANNEL_OUTPUT_CLOCK_SYS;
    channel_config.SerialInterfaceType = DFSDM_CHANNEL_SPI_FALLING;
    channel_config.InputMode = DFSDM_CHANNEL_DIGITAL_INPUT;
    channel_config.DataPacking = DFSDM_CHANNEL_STANDARD_MODE;
    channel_config.Offset = 0;
    channel_config.RightBitShift = 0;
    
    if (HAL_DFSDM_ChannelConfig(&hdfsdm1_filter0.Instance->Channel0, &channel_config) != HAL_OK)
    {
        Error_Handler();
    }
    
    /* Configure other channels similarly */
    /* Channel 1 */
    if (HAL_DFSDM_ChannelConfig(&hdfsdm1_filter0.Instance->Channel1, &channel_config) != HAL_OK)
    {
        Error_ForChannel(1);
    }
    /* Channel 2 */
    if (HAL_DFSDM_ChannelConfig(&hdfsdm1_filter0.Instance->Channel2, &channel_config) != HAL_OK)
    {
        Error_ForChannel(2);
    }
    /* Channel 3 */
    if (HAL_DFSDM_ChannelConfig(&hdfsdm1_filter0.Instance->Channel3, &channel_config) != HAL_OK)
    {
        Error_ForChannel(3);
    }
    /* Channel 4 */
    if (HAL_DFSDM_ChannelConfig(&hdfsdm1_filter1.Instance->Channel0, &channel_config) != HAL_OK)
    {
        Error_ForChannel(4);
    }
    /* Channel 5 */
    if (HAL_DFSDM_ChannelConfig(&hdfsdm1_filter1.Instance->Channel1, &channel_config) != HAL_OK)
    {
        Error_ForChannel(5);
    }
    /* Channel 6 */
    if (HAL_DFSDM_ChannelConfig(&hdfsdm1_filter1.Instance->Channel2, &channel_config) != HAL_OK)
    {
        Error_ForChannel(6);
    }
    /* Channel 7 */
    if (HAL_DFSDM_ChannelConfig(&hdfsdm1_filter1.Instance->Channel3, &channel_config) != HAL_OK)
    {
        Error_ForChannel(7);
    }
    
    /* Initialize DMA for DFSDM */
    hdma_dfsdm1_flt0.Instance = DMA2_Channel1;
    hdma_dfsdm1_flt0.Init.Direction = DMA_PERIPHERAL_TO_MEMORY;
    hdma_dfsdm1_flt0.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_dfsdm1_flt0.Init.MemInc = DMA_MINC_ENABLE;
    hdma_dfsdm1_flt0.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    hdma_dfsdm1_flt0.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    hdma_dfsdm1_flt0.Init.Mode = DMA_CIRCULAR;
    hdma_ddfsdm1_flt0.Init.Priority = DMA_PRIORITY_HIGH;
    
    HAL_DMA_Init(&hdma_dfsdm1_flt0);
    
    /* Initialize DMA for DFSDM Filter 1 */
    hdma_dfsdm1_flt1.Instance = DMA2_Channel2;
    hdma_dfsdm1_flt1.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_dfsdm1_flt1.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_dfsdm1_flt1.Init.MemInc = DMA_MINC_ENABLE;
    hdma_dfsdm1_flt1.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    hdma_dfsdm1_flt1.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    hdma_dfsdm1_flt1.Init.Mode = DMA_CIRCULAR;
    hdma_ddfsdm1_flt1.Init.Priority = DMA_PRIORITY_HIGH;
    
    HAL_DMA_Init(&hdma_dfsdm1_flt1);
    
    /* Link DMA to DFSDM filters */
    __HAL_LINKDMA(&hdfsdm1_filter0, hdma, hdma_dfsdm1_flt0);
    __HAL_LINKDMA(&hdfsdm1_filter1, hdma, hdma_dfsdm1_flt1);
    __HAL_LINKDMA(&hdfsdm1_filter2, hdma, hdma_dfsdm1_flt0);
    __HAL_LINKDMA(&hdfsdm1_filter3, hdma, hdma_dfsdm1_flt1);
}

/**
  * @brief Start DFSDM data acquisition
  */
void DFSDM_Start(DFSDM_HandleTypeDef *hdfsdm)
{
    /* Start DFSDM filter */
    if (HAL_DFSDM_FilterStart(hdfsdm) != HAL_OK)
    {
        Error_Handler();
    }
    
    /* Start DMA transfer */
    if (HAL_DFSDM_FilterStart_DMA(hdfsdm, dfsdm_channels[0].data_buffer, DFSDM_DATA_BUFFER_SIZE) != HAL_OK)
    {
        Error_Handler();
    }
}

/**
  * @brief Stop DFSDM data acquisition
  */
void DFSDM_Stop(DFSDM_HandleTypeDef *hdfsdm)
{
    HAL_DFSDM_FilterStop(hdfsdm);
    HAL_DFSDM_FilterStop_DMA(hdfsdm);
}

/**
  * @brief Process DFSDM data from buffer
  */
void DFSDM_ProcessData(DFSDM_HandleTypeDef *hdfsdm, uint32_t *data_buffer)
{
    /* Process audio data - convert from DFSDM format to standard audio */
    for (int i = 0; i < DFSDM_DATA_BUFFER_SIZE; i++)
    {
        /* Convert DFSDM data to PCM */
        int32_t raw_data = data_buffer[i];
        int32_t pcm_data = (raw_data >> 8) & 0xFFFF; /* Extract 16-bit PCM */
        
        /* Store processed data */
        data_buffer[i] = pcm_data;
    }
}

/**
  * @brief DMA transfer complete callback
  */
void DFSDM_DMA_Callback(DMA_HandleTypeDef *hdma)
{
    /* DMA transfer complete - data ready for processing */
    if (hdma->Instance == DMA2_Channel1)
    {
        /* Process DFSDM Filter 0 data */
        DFSDM_ProcessData(&hdfsdm1_filter0, dfsdm_channels[0].data_buffer);
    }
    else if (hdma->Instance == DMA2_Channel2)
    {
        /* Process DFSDM Filter 1 data */
        DFSDM_ProcessData(&hdfsdm1_filter1, dfsdm_channels[1].data_buffer);
    }
    else if (hdma->Instance == DMA2_Channel3)
    {
        /* Process DFSDM Filter 2 data */
        DFSDM_ProcessData(&hdfsdm1_filter2, dfsdm_channels[2].data_buffer);
    }
    else if (hdma->Instance == DMA2_Channel4)
    {
        /* Process DFSDM Filter 3 data */
        DFSDM_ProcessData(&hdfsdm1_filter3, dfsdm_channels[3].data_buffer);
    }
}