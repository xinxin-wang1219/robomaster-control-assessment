#ifndef BUZZER_H
#define BUZZER_H

#include <stdint.h>

void Buzzer_PlayTone(uint32_t frequency_hz, uint32_t duration_ms);
void Buzzer_PlayStartup(void);
void Buzzer_PlayError1(void);
void Buzzer_PlayError2(void);

#endif