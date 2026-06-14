#include "Timebase.h"

#include "LPC17xx.h"

static volatile uint32_t msTicks = 0;

void SysTick_Handler(void) {
	msTicks++;
}

void Timebase_Init(void) {
	SysTick_Config(SystemCoreClock / 1000U);
}

uint32_t Timebase_GetTicks(void) {
	return msTicks;
}

bool Timebase_IsPeriodElapsed(uint32_t *timestamp, uint32_t periodMs) {
	if ((msTicks - *timestamp) >= periodMs) {
		*timestamp = msTicks;
		return true;
	}

	return false;
}
