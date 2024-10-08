
/**
  ******************************************************************************
  * File Name          :  app_x-cube-nfc4.c
  * Description        : This file provides code for the configuration
  *                      of the STMicroelectronics.X-CUBE-NFC4.3.0.0 instances.
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

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "app_x-cube-nfc4.h"
#include "main.h"

/* Includes ------------------------------------------------------------------*/
#include "nfc04a1_nfctag.h"
#include <stdio.h>
#include "oled.h"

/** @defgroup ST25_Nucleo
  * @{
  */

/** @defgroup Main
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Global variables ----------------------------------------------------------*/

uint8_t awritedata[16];
uint8_t areaddata[16];
uint8_t cnt = 0;
uint16_t mblength;
ST25DV_MB_CTRL_DYN_STATUS mbctrldynstatus;
ST25DV_EN_STATUS MB_mode;
ST25DV_PASSWD passwd;
ST25DV_I2CSSO_STATUS i2csso;
volatile uint8_t GPOActivated = 0;

volatile uint8_t picture__flag =0;
extern unsigned char nfcBuffer[];
/* Private functions ---------------------------------------------------------*/
void MX_NFC4_MAILBOX_Init(void);
void MX_NFC4_MAILBOX_Process(void);

void MX_NFC_Init(void)
{
  /* USER CODE BEGIN SV */

  /* USER CODE END SV */

  /* USER CODE BEGIN NFC4_Library_Init_PreTreatment */

  /* USER CODE END NFC4_Library_Init_PreTreatment */

  /* Initialize the peripherals and the NFC4 components */

  MX_NFC4_MAILBOX_Init();

  /* USER CODE BEGIN SV */

  /* USER CODE END SV */

  /* USER CODE BEGIN NFC4_Library_Init_PostTreatment */

  /* USER CODE END NFC4_Library_Init_PostTreatment */
}
/*
 * LM background task
 */
void MX_NFC_Process(void)
{
  /* USER CODE BEGIN NFC4_Library_Process */
  if(picture__flag == 1)
  {
    picture__flag =0;
    // EpdInitFull();
    // EpdDisFull((unsigned char *) nfcBuffer, 1);
    OLED_ShowPicture(0,0,200,200,nfcBuffer,BLACK);
    OLED_Display(nfcBuffer);
    HAL_Delay(3000);
    //OLED_Clear(WHITE);
  }
  /* USER CODE END NFC4_Library_Process */

  MX_NFC4_MAILBOX_Process();

}

/**
  * @brief  Initialize the MAILBOX  feature Example
  * @retval None
  */
void MX_NFC4_MAILBOX_Init(void)
{
  /* Init ST25DV driver */
  while( NFC04A1_NFCTAG_Init(NFC04A1_NFCTAG_INSTANCE) != NFCTAG_OK );
  /* Energy harvesting activated after Power On Reset */
  NFC04A1_NFCTAG_WriteEHMode(NFC04A1_NFCTAG_INSTANCE, ST25DV_EH_ACTIVE_AFTER_BOOT);
  NFC04A1_NFCTAG_SetEHENMode_Dyn(NFC04A1_NFCTAG_INSTANCE);
  /* If not activated, activate Mailbox, as long as MB is ON EEPROM is not available */
  NFC04A1_NFCTAG_ReadMBMode(NFC04A1_NFCTAG_INSTANCE, &MB_mode);
  if( MB_mode == ST25DV_DISABLE )
  {
    /* You need to present password before changing static configuration */
    NFC04A1_NFCTAG_ReadI2CSecuritySession_Dyn(NFC04A1_NFCTAG_INSTANCE, &i2csso );
    if( i2csso == ST25DV_SESSION_CLOSED )
    {
      /* if I2C session is closed, present password to open session */
      passwd.MsbPasswd = 0; /* Default value for password */
      passwd.LsbPasswd = 0; /* change it if password has been modified */
      NFC04A1_NFCTAG_PresentI2CPassword(NFC04A1_NFCTAG_INSTANCE, passwd );
    }
   NFC04A1_NFCTAG_WriteMBMode(NFC04A1_NFCTAG_INSTANCE,ST25DV_ENABLE);

    /* Close session as dynamic register doesn't need open session for modification */
    passwd.MsbPasswd = 123;
    passwd.LsbPasswd = 123;
	NFC04A1_NFCTAG_PresentI2CPassword(NFC04A1_NFCTAG_INSTANCE, passwd );
  }


  /* Enable Mailbox in dynamique register */
  NFC04A1_NFCTAG_SetMBEN_Dyn(NFC04A1_NFCTAG_INSTANCE);
  /* Set EXTI settings for GPO Interrupt */
  NFC04A1_GPO_Init();
  /* Present configuration password */
  passwd.MsbPasswd = 0; /* Default value for password */
  passwd.LsbPasswd = 0; /* change it if password has been modified */
  NFC04A1_NFCTAG_PresentI2CPassword(NFC04A1_NFCTAG_INSTANCE, passwd);
  /* Set GPO Configuration */
  NFC04A1_NFCTAG_ConfigIT(NFC04A1_NFCTAG_INSTANCE,
                          ST25DV_GPO_ENABLE_MASK | ST25DV_GPO_RFGETMSG_MASK | ST25DV_GPO_RFPUTMSG_MASK);

}


int bufferIndex = 0;
/**
* @brief  Process of the MAILBOX application
* @retval None
*/
void MX_NFC4_MAILBOX_Process(void)
{
  if (GPOActivated == 1)
  {
    /* Check if Mailbox is available */
    NFC04A1_NFCTAG_ReadMBCtrl_Dyn(NFC04A1_NFCTAG_INSTANCE, &mbctrldynstatus);

    if (mbctrldynstatus.RfPutMsg == 1)
    {
      /* Read length of message */
      NFC04A1_NFCTAG_ReadMBLength_Dyn(NFC04A1_NFCTAG_INSTANCE, (uint8_t *) &mblength);
      mblength += 1;
      if (mblength == 3) // frame header
      {
        bufferIndex = 0;
      } else if (mblength == 200) // picture data
      {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET);

        /* Read all data in Mailbox */
        NFC04A1_NFCTAG_ReadMailboxData(NFC04A1_NFCTAG_INSTANCE, nfcBuffer + bufferIndex, 0, 200);
        bufferIndex += 200;

        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);
      }

      if (bufferIndex == 5000)
      {
        bufferIndex = 0;
        picture__flag =1;
      }

    }

    GPOActivated = 0;
  }
}


void BSP_GPO_Callback(void)
{
  /* Prevent unused argument(s) compilation warning */
  GPOActivated = 1;
  /* This function should be implemented by the user application.
     It is called into this driver when an event on Button is triggered. */
}

#ifdef __cplusplus
}
#endif

