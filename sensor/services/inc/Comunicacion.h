#ifndef COMUNICACION_H
#define COMUNICACION_H

#include <stdint.h>
#include <stdbool.h>

typedef enum
{
    COMMAND_NONE = 0,
    COMMAND_TOGGLE_MUTE,
    COMMAND_SET_THRESHOLD
} Command_t;

typedef struct
{
    Command_t command;
    uint16_t value;
} PCCommand_t;

void Comunicacion_Init(void);
void Comunicacion_TransmitCurrentState(uint16_t distance_cm);
PCCommand_t Comunicacion_ReceiveCommand(void);

#endif
