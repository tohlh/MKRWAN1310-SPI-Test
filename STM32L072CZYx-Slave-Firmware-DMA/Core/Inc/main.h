/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
/* Uncomment this line to compile for SPI_NSS_SOFT, if not it is compiled as SPI_NSS_HARD_INPUT */
//#define USE_SPI_NSS_SOFT
/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN Private defines */
#ifdef USE_SPI_NSS_SOFT
  #define PROJECT_TITLE "SPI_NSS_SOFT"
  #define USE_SPI_NSS_MODE_DEFINED_TODO_TO_START_RX TODO_DETECT_PIN_RESET
  #define USE_SPI_NSS_MODE_DEFINED_TODO_TO_WAIT_RX  TODO_DETECT_PIN_SET
#else
  #define PROJECT_TITLE "SPI_NSS_HARD_INPUT"
  #define USE_SPI_NSS_MODE_DEFINED_TODO_TO_START_RX TODO_START_RX
  #define USE_SPI_NSS_MODE_DEFINED_TODO_TO_WAIT_RX  TODO_WAIT_RX
#endif
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
