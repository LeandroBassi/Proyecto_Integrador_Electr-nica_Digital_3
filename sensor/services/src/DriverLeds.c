#include "DriverLeds.h"
#include "LedsPlaca.h"

void DriverLeds_Init(void) { LedsPlaca_Init(); }

void DriverLeds_SetRango(int rango) {
    if (rango == 0) LedsPlaca_SetState(1, 0, 0);
    else if (rango == 1) LedsPlaca_SetState(0, 1, 0);
    else LedsPlaca_SetState(0, 0, 1);
}
