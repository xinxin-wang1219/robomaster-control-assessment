#ifndef SERVO_H
#define SERVO_H

#include <stdint.h>

void Servo_Start(void);
void Servo_SetAngle(uint8_t angle);
void Servo_Stop(void);

#endif