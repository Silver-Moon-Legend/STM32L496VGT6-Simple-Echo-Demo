/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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

#include "main.h"
#include "stm32l4xx_hal.h"
#include "dfsdm_driver.h"
#include "i2s_driver.h"
#include "power_manager.h"
#include "snore_detection_optimized.h"
#include "noise_filter_fixed.h"

/* Private variables ---------------------------------------------------------*/
DFSDM_HandleTypeDef hdfsdm1_filter0;
DFSDM_HandleTypeDef hdfsdm1_filter1;
DFSDM_HandleTypeDef hdfsdm1_filter2;
DFSDM_HandleTypeDef hdfsdm1_filter3;
I2S_HandleTypeDef hi2s3;
DMA_HandleTypeDef hdma_dfsdm1_flt0;
DMA_HandleTypeDef hdma_dfsdm1_flt1;
DMA_HandleTypeDef hdma_dfsdm1_flt2;
DMA_HandleTypeDef hdma_dfsdm1_flt3;
DMA_HandleTypeDef hdma_i2s3_rx;
DMA_HandleTypeDef hdma_i2s3_tx;

/* Audio buffers optimized for fixed-point processing */
uint32_t dfsdm_data[8][256]; /* DFSDM data buffer */
uint32_t filtered_data[256]; /* Filtered audio buffer */
uint32_t audio_buffer[512]; /* I2S output buffer */

/* Optimization parameters */
#define OPTIMIZED_BUFFER_SIZE 256 /* Reduced buffer size */
#define OPTIMIZED_SAMPLE_RATE 16000 /* Lower sample rate */
#define OPTIMIZED_FRAME_SIZE 128 /* Frame size for incremental processing */

/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
static void MX_GPIO_Init(void);

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* MCU Configuration--------------------------------------------------------*/
  HAL_Init();
  
  /* Configure the system clock */
  SystemClock_Config();
  
  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DFSDM1_Init();
  MX_I2S3_Init();
  MX_DMA_Init();
  
  /* Initialize power manager */
  PowerManager_Init();
  
  /* Initialize audio processing algorithms */
  NoiseFilter_FixedInit();
  SnoreDetection_OptimizedInit();
  
  /* Start DFSDM data acquisition */
  DFSDM_Start(&hdfsdm1_filter0);
  DFSDM_Start(&hdfsdm1_filter1);
  DFSDM_Start(&hdfsdm1_filter2);
  DFSDM_Start(&hdfsdm1_filter3);
  
  /* Main loop */
  uint32_t frame_counter = 0;
  
  while (1)
  {
    /* Process audio data in smaller frames for incremental processing */
    for (int frame_index = 0; frame_index < OPTIMIZED_BUFFER_SIZE / OPTIMIZED_FRAME_SIZE; frame_index++)
    {
      /* Get audio data frame */
      uint32_t *audio_frame = dfsdm_data[frame_index];
      
      /* Apply optimized noise filtering */
      NoiseFilter_FixedApply(&audio_frame, 1, OPTIMIZED_FRAME_SIZE);
      
      /* Detect snore patterns using optimized algorithm */
      bool snore_detected = SnoreDetection_OptimizedProcess(&audio_frame, 1, OPTIMIZED_FRAME_SIZE);
      
      /* Get confidence score */
      float confidence_score = SnoreDetection_GetConfidenceOptimized();
      
      /* Get SNR improvement */
      float snr_improvement = NoiseFilter_GetSNRImprovement();
      
      /* If high confidence snore detected, generate alert */
      if (snore_detected && confidence_score > 0.7f)
      {
        /* Generate alert signal */
        I2S_PlayAlert(&hi2s3);
        
        /* Log detection */
        printf("Snore detected! Confidence: %.2f, SNR improvement: %.2f dB\n", 
               confidence_score, snr_improvement);
      }
    }
    
    /* Update filter coefficients periodically */
    if (frame_counter % 10 == 0)
    {
      NoiseFilter_FixedUpdateCoefficients(dfsdm_data[0], OPTIMIZED_BUFFER_SIZE);
    }
    
    /* Manage power mode based on activity */
    PowerManager_Update();
    
    /* Sleep for efficiency */
    HAL_Delay(10);
    
    frame_counter++;
  }
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
  
  /* Configure the main internal regulator output voltage */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE3);
  
  /* Initializes the RCC Oscillators according to the specified parameters */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 20;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  
  /* Configure the clock */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
  
  /* Configure peripheral clocks */
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_DFSDM|RCC_PERIPHCLK_I2S;
  PeriphClkInit.DfsdmClockSelection = RCC_DFSDMCLKSOURCE_SYS;
  PeriphClkInit.I2sClockSelection = RCC_I2SCLKSOURCE_PLL;
  
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  
  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  
  /* Configure GPIO pins for DFSDM */
  GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF6_DFSDM1;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_2;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_12;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin = GPIO_PIN_14|GPIO_PIN_15;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
  
  /* Configure GPIO pins for I2S */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_15;
  GPIO_InitStruct.Alternate = GPIO_AF6_I2S3;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_12;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* Log error */
  printf("System error occurred\n");
  
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
}

/**
  * @brief Initialize UART for debugging output
  */
void MX_USART2_UART_Init(void)
{
  /* Add UART initialization for debugging */
  /* Used for printf output */
}

/**
  * @brief printf redirect for UART output
  */
int _write(int file, char *ptr, int len)
{
  /* Implement UART output */
  return len;
}