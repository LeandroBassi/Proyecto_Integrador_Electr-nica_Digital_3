#ifndef DRIVERBUZZER_H
#define DRIVERBUZZER_H

#include <stdint.h>

void DriverBuzzer_Init(void);
void DriverBuzzer_SetFrequency(uint32_t freq);
void DriverBuzzer_Stop(void);

#endif
