#ifndef LED_H
#define LED_H

#include <stdint.h>

typedef enum
{
    LED_BLUE = 0,
    LED_GREEN,
    LED_RED,
    LED_COLOR_COUNT
} LedColor_t;

void Led_Start(void);
void Led_Set(LedColor_t color, uint16_t brightness);

#endif