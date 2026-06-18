/*
 * TimeService.h
 * Capa de Servicios - Base de tiempo del sistema
 */

#ifndef SERVICES_INC_TIMESERVICE_H_
#define SERVICES_INC_TIMESERVICE_H_

#include <stdint.h>
#include <stdbool.h>

void TimeService_Init(void);

// Retorna 'true' si ya pasó el intervalo desde la última vez que se leyó
bool TimeService_CheckAndClearTimeout(uint32_t ms_interval);

uint32_t TimeService_GetTicks(void);

#endif /* SERVICES_INC_TIMESERVICE_H_ */
