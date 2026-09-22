#include "servo.h"
#include "tim.h"

/* SG90：50 Hz PWM，1个计数对应1微秒 */
#define SERVO_MIN_PULSE_US     1000U
#define SERVO_MAX_PULSE_US     2000U
#define SERVO_CENTER_PULSE_US  1500U

void Servo_Start(void)
{
    /* 启动前先放在中间位置，避免产生异常脉冲 */
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2,
                          SERVO_CENTER_PULSE_US);

    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
}

void Servo_SetAngle(uint8_t angle)
{
    uint32_t pulse;

    if (angle > 180U)
    {
        angle = 180U;
    }

    /*
     * 0°   -> 1000 us
     * 90°  -> 1500 us
     * 180° -> 2000 us
     */
    pulse = SERVO_MIN_PULSE_US
          + ((uint32_t)angle
          * (SERVO_MAX_PULSE_US - SERVO_MIN_PULSE_US))
          / 180U;

    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, pulse);
}

void Servo_Stop(void)
{
    HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);
}