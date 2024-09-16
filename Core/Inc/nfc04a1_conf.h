/**
  ******************************************************************************
  * @file    nfc04a1_conf.h
  * @author  SRA Application Team
  * @brief   This file contains definitions for the NFC4 components bus interfaces
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __NFC04A1_CONF_H__
#define __NFC04A1_CONF_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../../Drivers/STM32L0xx_HAL_Driver/Inc/stm32l0xx_hal.h"
#include "custom_bus.h"
#include "custom_errno.h"

#include "../../Drivers/STM32L0xx_HAL_Driver/Inc/stm32l0xx_hal_exti.h"

#define NFC04A1_I2C_Init         BSP_I2C1_Init
#define NFC04A1_I2C_DeInit       BSP_I2C1_DeInit
#define NFC04A1_I2C_ReadReg16    BSP_I2C1_ReadReg16
#define NFC04A1_I2C_WriteReg16   BSP_I2C1_WriteReg16
#define NFC04A1_I2C_Recv         BSP_I2C1_Recv
#define NFC04A1_I2C_IsReady      BSP_I2C1_IsReady

#define NFC04A1_GetTick          HAL_GetTick

#define NFC04A1_GPO_PIN_PORT GPIOA
#define NFC04A1_GPO_PIN GPIO_PIN_3
#define NFC04A1_NFCTAG_GPO_EXTI_LINE EXTI_LINE_3
#define NFC04A1_GPO_EXTI EXTI2_3_IRQn
extern EXTI_HandleTypeDef GPO_EXTI;
#define H_EXTI_3 GPO_EXTI

#define NFC04A1_NFCTAG_INSTANCE         (0)

#define NFC04A1_NFCTAG_GPO_PRIORITY     (0)

#define I2C_INSTANCE  hi2c1
extern I2C_HandleTypeDef hi2c1;

#ifdef __cplusplus
}
#endif

#endif /* __NFC04A1_CONF_H__*/

