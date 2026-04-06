/**
  ******************************************************************************
  * @file           : sai_driver.h
  * @brief          : SAI驱动头文件
  ******************************************************************************
  */

#ifndef __SAI_DRIVER_H__
#define __SAI_DRIVER_H__

#include "stm32l4xx_hal.h"

/* 外部SAI句柄 */
extern SAI_HandleTypeDef hsai1;

/* 函数声明 */
void SAI_Init(void);
void SAI_Start(void);
void SAI_Stop(void);
void SAI_Transmit(uint32_t *data, uint32_t size);
void SAI_DMA_Callback(DMA_HandleTypeDef *hdma);

/* SAI配置 */
#define SAI_BLOCK_A           SAI1_BlockA
#define SAI_FRAME_SYNC        SAI_FrameSyncActiveLow
#define SAI_CLOCK_STROBING    SAI_ClockStrobingRisingEdge
#define SAI_AUDIO_FREQUENCY  48000

#endif /* __SAI_DRIVER_H__ */