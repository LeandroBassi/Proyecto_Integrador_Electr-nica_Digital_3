#ifndef SENSORSHARP_H_
#define SENSORSHARP_H_

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

void SensorSharp_Init(void);
uint16_t SensorSharp_GetPromedioCrudo(void); // Retorna el valor crudo (0-4095) ya promediado

#endif /* SENSORSHARP_H_ */
