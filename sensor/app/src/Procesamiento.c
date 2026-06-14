#include "Procesamiento.h"
#include "DistanciaCm.h"
#include "Alarma.h"
#include "Comunicacion.h"

#include "DistanciaCm.h"
#include "Alarma.h"
#include "Comunicacion.h"

#include "Timebase.h"

#define SENSOR_UPDATE_PERIOD_MS     50
#define TELEMETRY_PERIOD_MS         250
#define MAX_DISTANCE_THRESHOLD_CM   400

static uint16_t currentThreshold = MAX_DISTANCE_THRESHOLD_CM;

static uint32_t sensorTimestamp = 0;
static uint32_t telemetryTimestamp = 0;

static void ParkingControlTask(void);

void Procesamiento_Run(void) {
	PCCommand_t command;

	command = Comunicacion_ReceiveCommand();

	switch (command.command) {
	case COMMAND_TOGGLE_MUTE:
		Alarma_ToggleMute();
		break;
	case COMMAND_SET_THRESHOLD:
		if ((command.value > 0)
				&& (command.value <= MAX_DISTANCE_THRESHOLD_CM)) {
			currentThreshold = command.value;
		}
		break;
	case COMMAND_NONE:
	default:
		break;
	}

	if (Alarma_CheckButtonEvent()) {
		Alarma_ToggleMute();
	}
	if (Timebase_IsPeriodElapsed(&sensorTimestamp, SENSOR_UPDATE_PERIOD_MS)) {
		ParkingControlTask();
	}
	if (Timebase_IsPeriodElapsed(&telemetryTimestamp, TELEMETRY_PERIOD_MS)) {
		Comunicacion_TransmitCurrentState(DistanciaCm_GetLatestMeasurement());
	}
}

static void ParkingControlTask(void) {
	uint16_t currentDistance;
	SystemState_t nextState;

	DistanciaCm_ProcessSamples();

	currentDistance = DistanciaCm_GetLatestMeasurement();

	if (currentDistance > currentThreshold) {
		nextState = SYSTEM_STATE_OFF;
	} else if (currentDistance >= 80) {
		nextState = SYSTEM_STATE_SAFE;
	} else if (currentDistance >= 30) {
		nextState = SYSTEM_STATE_WARNING;
	} else {
		nextState = SYSTEM_STATE_DANGER;
	}

	Alarma_UpdateInterface(nextState, currentDistance);
}
