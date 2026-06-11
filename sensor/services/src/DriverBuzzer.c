#include "DriverBuzzer.h"
#include "BuzzerPower.h"

void DriverBuzzer_Init(void) { BuzzerPower_Init(); }
void DriverBuzzer_SetFrequency(uint32_t freq) { BuzzerPower_SetFrequency(freq); }
void DriverBuzzer_Stop(void) { BuzzerPower_Stop(); }
