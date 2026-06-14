#ifndef TIMEBASE_H
#define TIMEBASE_H

#include <stdint.h>
#include <stdbool.h>

void Timebase_Init(void);
uint32_t Timebase_GetTicks(void);
bool Timebase_IsPeriodElapsed(uint32_t *timestamp, uint32_t periodMs);

#endif
