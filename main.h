/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

#ifndef MAIN_H
#define MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes -----------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

/* Function prototypes -------------------------------------------------------*/
void Error_Handler(void);

/* Exported variables -------------------------------------------------------*/
extern DFSDM_HandleTypeDef hdfsdm1_filter0;
extern DFSDM_HandleTypeDef hdfsdm1_filter1;
extern DFSDM_HandleTypeDef hdfsdm1_filter2;
extern DFSDM_HandleTypeDef hdfsdm1_filter3;
extern I2S_HandleTypeDef hi2s3;
extern DMA_HandleTypeDef hdma_dfsdm1_flt0;
extern DMA_HandleTypeDef hdma_dfsdm1_flt1;
extern DMA_HandleTypeDef hdma_dfsdm1_flt2;
extern DMA_HandleTypeDef hdma_dfsdm1_flt3;
extern DMA_HandleTypeDef hdma_i2s3_rx;
extern DMA_HandleTypeDef hdma_i2s3_tx;

#ifdef __cplusplus
}
#endif

#endif /* MAIN_H */