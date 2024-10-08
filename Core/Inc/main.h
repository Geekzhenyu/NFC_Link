/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"

#include "nfc04a1_conf.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_Pin GPIO_PIN_2
#define LED_GPIO_Port GPIOA
#define ST25_GPO_Pin GPIO_PIN_3
#define ST25_GPO_GPIO_Port GPIOA
#define ST25_GPO_EXTI_IRQn EXTI2_3_IRQn
#define INK_MOSI_Pin GPIO_PIN_5
#define INK_MOSI_GPIO_Port GPIOA
#define INK_SCK_Pin GPIO_PIN_6
#define INK_SCK_GPIO_Port GPIOA
#define INK_CS_Pin GPIO_PIN_7
#define INK_CS_GPIO_Port GPIOA
#define INK_DC_Pin GPIO_PIN_0
#define INK_DC_GPIO_Port GPIOB
#define INK_RES_Pin GPIO_PIN_1
#define INK_RES_GPIO_Port GPIOB
#define INK_BUSY_Pin GPIO_PIN_8
#define INK_BUSY_GPIO_Port GPIOA
#define TX_Pin GPIO_PIN_9
#define TX_GPIO_Port GPIOA
#define RX_Pin GPIO_PIN_10
#define RX_GPIO_Port GPIOA
#define KEY_Pin GPIO_PIN_15
#define KEY_GPIO_Port GPIOA
#define KEY_EXTI_IRQn EXTI4_15_IRQn

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
