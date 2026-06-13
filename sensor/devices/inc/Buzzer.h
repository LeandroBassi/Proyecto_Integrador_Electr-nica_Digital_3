#ifndef BUZZER_H
#define BUZZER_H

#include <stdint.h>

void Buzzer_Init(void);
void Buzzer_SetFrequency(uint32_t hz);
void Buzzer_Stop(void);

#endif /* BUZZER_H */
