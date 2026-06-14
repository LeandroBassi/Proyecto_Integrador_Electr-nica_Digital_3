#ifndef DISTANCIACM_H
#define DISTANCIACM_H

#include <stdint.h>
#include <stdbool.h>

void DistanciaCm_Init(void);
void DistanciaCm_ProcessSamples(void);
uint16_t DistanciaCm_GetLatestMeasurement(void);

#endif /* DISTANCIACM_H */
