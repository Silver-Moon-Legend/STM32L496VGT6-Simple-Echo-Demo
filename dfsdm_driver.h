/**
  * @file dfsdm_driver.h
  * @brief DFSDM driver for STM32L496VGT6 with 8-channel PDM microphone support
  */

#ifndef DFSDM_DRIVER_H
#define DFSDM_DRIVER_H

#include "stm32l4xx_hal.h"

/* DFSDM configuration */
#define DFSDM_CLOCK_FREQ          2000000    /* DFSDM clock frequency: 2 MHz */
#define DFSDM_SAMPLE_RATE         48000      /* Audio sample rate: 48 kHz */
#define DFSDM_DATA_BUFFER_SIZE    256        /* Buffer size for each channel */
#define DFSDM_CHANNEL_COUNT       8          /* Total channels */

/* DFSDM Filter configuration */
typedef struct {
    DFSDM_HandleTypeDef *handle;
    DFSDM_Filter_HandleTypeDef filter;
    uint32_t channel_id;
    uint32_t data_buffer[DFSDM_DATA_BUFFER_SIZE];
} DFSDM_Channel_t;

/* Driver functions */
void MX_DFSDM1_Init(void);
void DFSDM_Start(DFSDM_HandleTypeDef *hdfsdm);
void DFSDM_Stop(DFSDM_HandleTypeDef *hdfsdm);
void DFSDM_ProcessData(DFSDM_HandleTypeDef *hdfsdm, uint32_t *data_buffer);

/* DMA callback functions */
void DFSDM_DMA_Callback(DMA_HandleTypeDef *hdma);

#endif /* DFSDM_DRIVER_H */