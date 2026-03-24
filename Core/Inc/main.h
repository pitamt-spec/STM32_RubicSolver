/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "stm32l4xx_hal.h"

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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define STPR_D1_Pin GPIO_PIN_2
#define STPR_D1_GPIO_Port GPIOE
#define STPR_D5_Pin GPIO_PIN_3
#define STPR_D5_GPIO_Port GPIOE
#define STPR_D2_Pin GPIO_PIN_4
#define STPR_D2_GPIO_Port GPIOE
#define STPR_D3_Pin GPIO_PIN_5
#define STPR_D3_GPIO_Port GPIOE
#define STPR_D4_Pin GPIO_PIN_6
#define STPR_D4_GPIO_Port GPIOE
#define DISPL_RST_Pin GPIO_PIN_1
#define DISPL_RST_GPIO_Port GPIOF
#define DISPL_DC_Pin GPIO_PIN_2
#define DISPL_DC_GPIO_Port GPIOF
#define TOUCH_CS_Pin GPIO_PIN_3
#define TOUCH_CS_GPIO_Port GPIOF
#define TOUCH_INT_Pin GPIO_PIN_5
#define TOUCH_INT_GPIO_Port GPIOF
#define STPR_EN_Pin GPIO_PIN_7
#define STPR_EN_GPIO_Port GPIOF
#define STPR_D6_Pin GPIO_PIN_8
#define STPR_D6_GPIO_Port GPIOF
#define DISP_LED_Pin GPIO_PIN_9
#define DISP_LED_GPIO_Port GPIOF
#define DEMUX_S0_Pin GPIO_PIN_0
#define DEMUX_S0_GPIO_Port GPIOC
#define DEMUX_S2_Pin GPIO_PIN_1
#define DEMUX_S2_GPIO_Port GPIOC
#define DEMUX_S1_Pin GPIO_PIN_3
#define DEMUX_S1_GPIO_Port GPIOC
#define PTMTR_OUT_Pin GPIO_PIN_3
#define PTMTR_OUT_GPIO_Port GPIOA
#define DISPL_CS_Pin GPIO_PIN_0
#define DISPL_CS_GPIO_Port GPIOG
#define LED_RED_Pin GPIO_PIN_14
#define LED_RED_GPIO_Port GPIOB
#define LED_GREEN_Pin GPIO_PIN_7
#define LED_GREEN_GPIO_Port GPIOC
#define LED_TIM_Pin GPIO_PIN_8
#define LED_TIM_GPIO_Port GPIOC
#define TOUCH_SCK_Pin GPIO_PIN_10
#define TOUCH_SCK_GPIO_Port GPIOC
#define TOUCH_MISO_Pin GPIO_PIN_11
#define TOUCH_MISO_GPIO_Port GPIOC
#define TOUCH_MOSI_Pin GPIO_PIN_12
#define TOUCH_MOSI_GPIO_Port GPIOC
#define DISPL_SCK_Pin GPIO_PIN_1
#define DISPL_SCK_GPIO_Port GPIOD
#define LCD_MISO_Pin GPIO_PIN_3
#define LCD_MISO_GPIO_Port GPIOD
#define LCD_MOSI_Pin GPIO_PIN_4
#define LCD_MOSI_GPIO_Port GPIOD
#define LED_BLUE_Pin GPIO_PIN_7
#define LED_BLUE_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
