/**
  ******************************************************************************
  * @file    nfc04a1.c 
  * @author  MMY-SRA Team
  * @brief   This file provides set of driver functions to intialized X-NUCLEO-NFC04A1 
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "nfc04a1.h"

/** @addtogroup BSP
 * @{
 */

/** @defgroup X_NUCLEO_NFC04A1
 * @{
 */
/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/ 
/* Global variables ----------------------------------------------------------*/
/** @defgroup X_NUCLEO_NFC04A1_Global_Variables
 * @{
 */

/**
 * @}
 */

/* Private function prototypes -----------------------------------------------*/

																		 
__weak void BSP_GPO_Callback(void);
																			 
EXTI_HandleTypeDef GPO_EXTI = {.Line=NFC04A1_NFCTAG_GPO_EXTI_LINE};
																			 
/* Functions Definition ------------------------------------------------------*/
/** @defgroup X_NUCLEO_NFC04A1_Public_Functions
 * @{
 */

/**
  * @brief  This function initialize the GPIO to manage the Leds
  * @brief  through GPIO
  * @param  Led: LED to be initialized. 
  * @return Status
  */

/**
  * @brief  This function initialize the GPIO to manage the NFCTAG GPO pin
  * @param  None
  * @return Status
  */
int32_t NFC04A1_GPO_Init( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;

  GPIO_InitStruct.Pin   = NFC04A1_GPO_PIN;
  GPIO_InitStruct.Mode  = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Pull  = GPIO_NOPULL;
  HAL_GPIO_Init( NFC04A1_GPO_PIN_PORT, &GPIO_InitStruct );

  (void)HAL_EXTI_GetHandle(&GPO_EXTI, NFC04A1_NFCTAG_GPO_EXTI_LINE);
  (void)HAL_EXTI_RegisterCallback(&GPO_EXTI,  HAL_EXTI_COMMON_CB_ID, BSP_GPO_Callback);
    

  /* Enable interruption */
  HAL_NVIC_SetPriority( NFC04A1_GPO_EXTI, NFC04A1_NFCTAG_GPO_PRIORITY, 0 );
  HAL_NVIC_EnableIRQ( NFC04A1_GPO_EXTI );

  return BSP_ERROR_NONE;

}

/**
  * @brief  DeInit GPO.
  * @param  None.
  * @return Status
  * @note GPO DeInit does not disable the GPIO clock nor disable the Mfx
  */
int32_t NFC04A1_GPO_DeInit( void )
{
  GPIO_InitTypeDef  gpio_init_structure;

  /* DeInit the GPIO_GPO pin */
  gpio_init_structure.Pin = NFC04A1_GPO_PIN;
  HAL_GPIO_DeInit( NFC04A1_GPO_PIN_PORT, gpio_init_structure.Pin);

  return BSP_ERROR_NONE;

}

/**
  * @brief  This function get the GPO value through GPIO
  * @param  None
  * @retval GPIO pin status
  */
int32_t NFC04A1_GPO_ReadPin( void )
{
  return (int32_t)HAL_GPIO_ReadPin( NFC04A1_GPO_PIN_PORT, NFC04A1_GPO_PIN );
}

/**
  * @brief  This function initialize the GPIO to manage the NFCTAG LPD pin
  * @param  None
  * @return Status
  */


/**
  * @brief  BSP GPO callback
  * @retval None.
  */
__weak void BSP_GPO_Callback(void)
{
  /* Prevent unused argument(s) compilation warning */
  
  /* This function should be implemented by the user application.
     It is called into this driver when an event on Button is triggered. */   
}

void NFC04A1_GPO_IRQHandler(void)
{
  HAL_EXTI_IRQHandler(&GPO_EXTI);
}



/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */


