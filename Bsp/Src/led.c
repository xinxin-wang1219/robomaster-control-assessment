#include "led.h"
#include "tim.h"
#include "main.h"

static const uint32_t led_channels[LED_COLOR_COUNT] =
{
    TIM_CHANNEL_1,  /* PH10: 蓝 */
    TIM_CHANNEL_2,  /* PH11: 绿 */
    TIM_CHANNEL_3   /* PH12: 红 */
};

void Led_Set(LedColor_t color, uint16_t brightness)
{
    if (color >= LED_COLOR_COUNT)
    {
        return;
    }

    if (brightness > 1000U)
    {
        brightness = 1000U;
    }

    uint32_t period = __HAL_TIM_GET_AUTORELOAD(&htim5) + 1U;
    uint32_t compare = (period * brightness) / 1000U;

    __HAL_TIM_SET_COMPARE(&htim5, led_channels[color], compare);
}

void Led_Start(void)
{
    for (uint32_t i = 0U; i < LED_COLOR_COUNT; i++)
    {
        Led_Set((LedColor_t)i, 0U);

        if (HAL_TIM_PWM_Start(&htim5, led_channels[i]) != HAL_OK)
        {
            Error_Handler();
        }
    }
}