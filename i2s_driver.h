/**
  * @file i2s_driver.h
  * @brief I2S driver for MAX98357 audio amplifier
  */

#ifndef I2S_DRIVER_H
#define I2S_DRIVER_H

#include "stm32l4xx_hal.h"

/* I2S configuration */
#define I2S_AUDIO_FREQ       48000      /* Audio frequency: 48 kHz */
#define I2S_BUFFER_SIZE      512        /* Audio buffer size */
#define I2S_DATA_FORMAT      I2S_DATAFORMAT_24B /* 24-bit data */

/* I2S driver functions */
void MX_I2S3_Init(void);
void I2S_PlayAlert(I2S_HandleTypeDef *hi2s);
void I2S_Stop(I2S_HandleTypeDef *hi2s);
void I2S_DMA_Callback(DMA_HandleTypeDef *hdma);

#endif /* I2S_DRIVER_H */