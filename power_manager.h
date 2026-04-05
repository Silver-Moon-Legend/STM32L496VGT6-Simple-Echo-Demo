/**
  * @file power_manager.h
  * @brief Power management for STM32L496VGT6
  */

#ifndef POWER_MANAGER_H
#define POWER_MANAGER_H

#include "stm32l4xx_hal.h"

/* Power modes */
typedef enum {
    POWER_MODE_RUN = 0,
    POWER_MODE_SLEEP,
    POWER_MODE_STOP,
    POWER_MODE_STANDBY
} PowerMode_t;

/* Power management functions */
void PowerManager_Init(void);
void PowerManager_SetMode(PowerMode_t mode);
void PowerManager_Update(void);
uint32_t PowerManager_GetBatteryLevel(void);
bool PowerManager_IsLowPower(void);

#endif /* POWER_MANAGER_H */