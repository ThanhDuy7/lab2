/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */
uint16_t segmentPins[7] = {seg0_Pin, seg1_Pin, seg2_Pin, seg3_Pin, seg4_Pin, seg5_Pin, seg6_Pin};
  GPIO_TypeDef* segmentPorts[7] = {seg0_GPIO_Port, seg1_GPIO_Port, seg2_GPIO_Port, seg3_GPIO_Port, seg4_GPIO_Port, seg5_GPIO_Port, seg6_GPIO_Port};

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
  void display7SEG(int num) {

    	for (int i = 0; i < 7; i++) {
    	        HAL_GPIO_WritePin(segmentPorts[i], segmentPins[i], GPIO_PIN_SET);
    	    }
    	if (num == 0) {
    		for (int i = 0; i < 6; i++) {
    			HAL_GPIO_WritePin(segmentPorts[i], segmentPins[i], GPIO_PIN_RESET);
    		}
    	} else if (num == 1) {
    		HAL_GPIO_WritePin(segmentPorts[1], segmentPins[1], GPIO_PIN_RESET);
    		HAL_GPIO_WritePin(segmentPorts[2], segmentPins[2], GPIO_PIN_RESET);
    	} else if (num == 2) {
    		for (int i = 0; i < 7; i++) {
    			if (i == 2 || i == 5) continue;
    			HAL_GPIO_WritePin(segmentPorts[i], segmentPins[i], GPIO_PIN_RESET);
    		}
    	} else if (num == 3) {
    		for (int i = 0; i < 7; i++) {
    			if (i == 4 || i == 5) continue;
    			HAL_GPIO_WritePin(segmentPorts[i], segmentPins[i], GPIO_PIN_RESET);
    		}
    	} else if (num == 4) {
    		for (int i = 0; i < 7; i++) {
    			if (i == 0 || i == 3 || i == 4) continue;
    			HAL_GPIO_WritePin(segmentPorts[i], segmentPins[i], GPIO_PIN_RESET);
    		}
    	} else if (num == 5) {
    		for (int i = 0; i < 7; i++) {
    			if (i == 1 || i == 4) continue;
    			HAL_GPIO_WritePin(segmentPorts[i], segmentPins[i], GPIO_PIN_RESET);
    		}
    	} else if (num == 6) {
    		for (int i = 0; i < 7; i++) {
    			if (i == 1) continue;
    			HAL_GPIO_WritePin(segmentPorts[i], segmentPins[i], GPIO_PIN_RESET);
    		}
    	} else if (num == 7) {
    		for (int i = 0; i < 3; i++) {
    			HAL_GPIO_WritePin(segmentPorts[i], segmentPins[i], GPIO_PIN_RESET);
    		}
    	} else if (num == 8) {
    		for (int i = 0; i < 7; i++) {
    			HAL_GPIO_WritePin(segmentPorts[i], segmentPins[i], GPIO_PIN_RESET);
    		}
    	} else if (num == 9) {
    		for (int i = 0; i < 7; i++) {
    			if (i == 4) continue;
    			HAL_GPIO_WritePin(segmentPorts[i], segmentPins[i], GPIO_PIN_RESET);
    		}
    	}


    }
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */


  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT (& htim2 ) ;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7999;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 9;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, Led1_Pin|EN0_Pin|EN1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, seg0_Pin|seg1_Pin|seg2_Pin|seg3_Pin
                          |seg4_Pin|seg5_Pin|seg6_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : Led1_Pin EN0_Pin EN1_Pin */
  GPIO_InitStruct.Pin = Led1_Pin|EN0_Pin|EN1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : seg0_Pin seg1_Pin seg2_Pin seg3_Pin
                           seg4_Pin seg5_Pin seg6_Pin */
  GPIO_InitStruct.Pin = seg0_Pin|seg1_Pin|seg2_Pin|seg3_Pin
                          |seg4_Pin|seg5_Pin|seg6_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
int currentNumber = 1;
int counter = 50;
void HAL_TIM_PeriodElapsedCallback ( TIM_HandleTypeDef * htim ) {
	 counter--;
	    if (counter <= 0) {
	        counter = 50; // Half a second
	        // Toggle between 1 and 2
	        if (currentNumber == 1) {
	        	HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, GPIO_PIN_SET);
	        	HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, GPIO_PIN_RESET);
	            currentNumber = 2;
	        } else {
	            currentNumber = 1;
	            HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, GPIO_PIN_RESET);
	            HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, GPIO_PIN_SET);
	        }
	        display7SEG(currentNumber);
	    }
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {

  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
