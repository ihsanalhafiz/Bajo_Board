/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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
#include "stm32g4xx_hal.h"

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
#define EEPROM_SDA_Pin GPIO_PIN_0
#define EEPROM_SDA_GPIO_Port GPIOF
#define ACC_INT2_Pin GPIO_PIN_1
#define ACC_INT2_GPIO_Port GPIOA
#define ACC_INT2_EXTI_IRQn EXTI1_IRQn
#define ACC_INT1_Pin GPIO_PIN_2
#define ACC_INT1_GPIO_Port GPIOA
#define ACC_INT1_EXTI_IRQn EXTI2_IRQn
#define ACC_DRDY_Pin GPIO_PIN_3
#define ACC_DRDY_GPIO_Port GPIOA
#define ACC_DRDY_EXTI_IRQn EXTI3_IRQn
#define ACC_CS_Pin GPIO_PIN_4
#define ACC_CS_GPIO_Port GPIOA
#define ACC_SCK_Pin GPIO_PIN_5
#define ACC_SCK_GPIO_Port GPIOA
#define ACC_MISO_Pin GPIO_PIN_6
#define ACC_MISO_GPIO_Port GPIOA
#define ACC_MOSI_Pin GPIO_PIN_7
#define ACC_MOSI_GPIO_Port GPIOA
#define EEPROM_SCL_Pin GPIO_PIN_4
#define EEPROM_SCL_GPIO_Port GPIOC
#define INC_RST_Pin GPIO_PIN_11
#define INC_RST_GPIO_Port GPIOB
#define INC_CS_Pin GPIO_PIN_12
#define INC_CS_GPIO_Port GPIOB
#define INC_SCK_Pin GPIO_PIN_13
#define INC_SCK_GPIO_Port GPIOB
#define INC_MISO_Pin GPIO_PIN_14
#define INC_MISO_GPIO_Port GPIOB
#define INC_MOSI_Pin GPIO_PIN_15
#define INC_MOSI_GPIO_Port GPIOB
#define RS232_TX_Pin GPIO_PIN_9
#define RS232_TX_GPIO_Port GPIOA
#define RS232_RX_Pin GPIO_PIN_10
#define RS232_RX_GPIO_Port GPIOA
#define LED2_Pin GPIO_PIN_10
#define LED2_GPIO_Port GPIOC
#define LED1_Pin GPIO_PIN_11
#define LED1_GPIO_Port GPIOC
#define TTL_TX_Pin GPIO_PIN_3
#define TTL_TX_GPIO_Port GPIOB
#define TTL_RX_Pin GPIO_PIN_4
#define TTL_RX_GPIO_Port GPIOB
#define SEIS_INT2_Pin GPIO_PIN_5
#define SEIS_INT2_GPIO_Port GPIOB
#define SEIS_INT2_EXTI_IRQn EXTI9_5_IRQn
#define SEIS_INT1_Pin GPIO_PIN_6
#define SEIS_INT1_GPIO_Port GPIOB
#define SEIS_INT1_EXTI_IRQn EXTI9_5_IRQn
#define SEIS_SDA_Pin GPIO_PIN_7
#define SEIS_SDA_GPIO_Port GPIOB
#define SEIS_SCL_Pin GPIO_PIN_8
#define SEIS_SCL_GPIO_Port GPIOB
#define SEIS_SETTING_Pin GPIO_PIN_9
#define SEIS_SETTING_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
