#ifndef BUZZER_H_
#define BUZZER_H_

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif
#include <stdbool.h>

// Inicializa el pin GPIO asociado al buzzer
void Buzzer_Init(void);

// Enciende o apaga el estado base del buzzer
void Buzzer_Set(bool state);

// Invierte el estado actual del pin (Mecanismo vital para el oscilador pasivo)
void Buzzer_Toggle(void);

#endif /* BUZZER_H_ */
