/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "led.h"
#include "servo.h"

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
/* USER CODE BEGIN Variables */
static osThreadId_t ledTaskHandle;

static const osThreadAttr_t ledTask_attributes =
{
    .name = "ledTask",
    .stack_size = 256 * 4,
    .priority = (osPriority_t) osPriorityNormal,
};
static osThreadId_t servoTaskHandle;

static const osThreadAttr_t servoTask_attributes =
{
    .name = "servoTask",
    .stack_size = 256 * 4,
    .priority = (osPriority_t) osPriorityNormal,
};
/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
static void LedTask(void *argument);
static void ServoTask(void *argument);
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  ledTaskHandle = osThreadNew(LedTask, NULL, &ledTask_attributes);

if (ledTaskHandle == NULL)
{
    Error_Handler();
}
servoTaskHandle = osThreadNew(ServoTask, NULL,
                              &servoTask_attributes);

if (servoTaskHandle == NULL)
{
    Error_Handler();
}
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
static void LedTask(void *argument)
{
 const LedColor_t colors[] = {LED_BLUE, LED_GREEN, LED_RED};
    (void)argument;

    Led_Start();

    for (;;)
    {
        for (uint32_t i = 0U; i < 3U; i++)
        {
            for (uint16_t level = 0U; level <= 1000U; level += 50U)
            {
                Led_Set(colors[i], level);
                osDelay(10);
            }

            for (int32_t level = 950; level >= 0; level -= 50)
            {
                Led_Set(colors[i], (uint16_t)level);
                osDelay(10);
            }
        }
    }
}
static void ServoTask(void *argument)
{
    const uint8_t angles[] = {0U, 45U, 90U, 135U, 180U};
    (void)argument;

    Servo_Start();

    for (;;)
    {
        /* 从0°逐步转到180° */
        for (uint32_t i = 0U; i < 5U; i++)
        {
            Servo_SetAngle(angles[i]);
            osDelay(1000U);
        }

        /* 再从135°逐步返回0°，方便循环演示 */
        for (int32_t i = 3; i >= 0; i--)
        {
            Servo_SetAngle(angles[i]);
            osDelay(1000U);
        }
    }
}
/* USER CODE END Application */

