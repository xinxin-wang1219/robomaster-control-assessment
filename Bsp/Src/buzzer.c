#include "buzzer.h"
#include "tim.h"
#include "main.h"

#define BUZZER_TIMER_TICK_HZ 1000000U

static void Buzzer_SetFrequency(uint32_t frequency_hz)
{
    uint32_t period;

    if (frequency_hz == 0U)
    {
        return;
    }

    period = BUZZER_TIMER_TICK_HZ / frequency_hz;

    if (period < 2U)
    {
        period = 2U;
    }

    __HAL_TIM_SET_AUTORELOAD(&htim4, period - 1U);
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, period / 2U);
    __HAL_TIM_SET_COUNTER(&htim4, 0U);
}

void Buzzer_PlayTone(uint32_t frequency_hz, uint32_t duration_ms)
{
    Buzzer_SetFrequency(frequency_hz);

    if (HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3) != HAL_OK)
    {
        Error_Handler();
    }

    HAL_Delay(duration_ms);

    if (HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_3) != HAL_OK)
    {
        Error_Handler();
    }
}

void Buzzer_PlayStartup(void)
{
    Buzzer_PlayTone(4000U, 300U);
}

void Buzzer_PlayError1(void)
{
    for (uint32_t i = 0U; i < 3U; i++)
    {
        Buzzer_PlayTone(3000U, 120U);
        HAL_Delay(80U);
    }
}

void Buzzer_PlayError2(void)
{
    Buzzer_PlayTone(1000U, 150U);
    HAL_Delay(60U);
    Buzzer_PlayTone(1500U, 150U);
    HAL_Delay(60U);
    Buzzer_PlayTone(2000U, 250U);
}