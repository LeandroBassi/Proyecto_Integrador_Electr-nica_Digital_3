#include "Comunicacion.h"
#include "UART.h"

static uint32_t UIntToString(uint16_t value, char *buffer);
static uint16_t StringToUInt(const char *str);

void Comunicacion_Init(void) {
	UART3_Init();
}

void Comunicacion_TransmitCurrentState(uint16_t distanceCm) {
	char buffer[8];
	uint32_t length;

	length = UIntToString(distanceCm, buffer);

	buffer[length++] = '\r';
	buffer[length++] = '\n';

	UART3_Transmit((uint8_t*) buffer, length);
}

PCCommand_t Comunicacion_ReceiveCommand(void) {
	PCCommand_t msg;
	uint8_t receivedByte;

	msg.command = COMMAND_NONE;
	msg.value = 0;

	if (!UART3_Receive(&receivedByte)) {
		return msg;
	}

	switch (receivedByte) {
	case 'M':
	case 'm':
		msg.command = COMMAND_TOGGLE_MUTE;
		break;

	case 'T':
	case 't': {
		char thresholdBuffer[6];
		uint8_t byte;
		uint32_t index = 0;

		while (index < (sizeof(thresholdBuffer) - 1U)) {
			if (!UART3_Receive(&byte)) {
				break;
			}

			if ((byte == '\r') || (byte == '\n')) {
				break;
			}

			if ((byte >= '0') && (byte <= '9')) {
				thresholdBuffer[index++] = (char) byte;
			}
		}

		thresholdBuffer[index] = '\0';

		msg.command = COMMAND_SET_THRESHOLD;
		msg.value = StringToUInt(thresholdBuffer);
		break;
	}

	default:
		break;
	}

	return msg;
}

static uint32_t UIntToString(uint16_t value, char *buffer) {
	char temp[6];
	uint32_t length = 0;
	uint32_t i;

	if (value == 0U) {
		buffer[0] = '0';
		return 1;
	}

	while (value > 0U) {
		temp[length++] = (char) ((value % 10U) + '0');
		value /= 10U;
	}

	for (i = 0; i < length; i++) {
		buffer[i] = temp[length - 1U - i];
	}

	return length;
}

static uint16_t StringToUInt(const char *str) {
	uint16_t value = 0;

	while ((*str >= '0') && (*str <= '9')) {
		value = (uint16_t) ((value * 10U) + (*str - '0'));
		str++;
	}

	return value;
}
