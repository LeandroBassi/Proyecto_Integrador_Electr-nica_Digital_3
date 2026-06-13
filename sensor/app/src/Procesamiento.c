#include "Procesamiento.h"
#include "DistanciaCm.h"
#include "Alarma.h"
#include "Comunicacion.h"

#define PERIODO_MUESTREO_MS    50   // 20 Hz loop
#define PERIODO_TELEMETRIA_MS  250  // 4 Hz loop
#define UMBRAL_MAX_SISTEMA     400

static uint16_t umbral_actual = UMBRAL_MAX_SISTEMA;
static uint32_t cronometro_sensores = 0;
static uint32_t cronometro_telemetria = 0;

static void TareaControlEstacionamiento(void);
static void TareaGestionEventos(void);

void Procesamiento_Run(void) {
    // 1. Check for immediate asynchronous updates (Mute / Overrides)
    TareaGestionEventos();

    // 2. Scheduled Sensor & Feedback Update Loop (Every 50ms)
    if (DistanciaCm_HitoTiempoAlcanzado(&cronometro_sensores, PERIODO_MUESTREO_MS)) {
        TareaControlEstacionamiento();
    }

    // 3. Scheduled PC Serial Telemetry Update Loop (Every 250ms)
    if (Comunicacion_HitoTiempoAlcanzado(&cronometro_telemetria, PERIODO_TELEMETRIA_MS)) {
        uint16_t dist = DistanciaCm_ObtenerUltimaMedida();
        // Telemetry service can request the active system state directly if needed
        Comunicacion_TransmitirEstadoActual(dist); 
    }
}

static void TareaGestionEventos(void) {
    uint16_t umbral_pc = 0;
    bool cmd_silencio_pc = false;

    // Process inputs from Notebook terminal
    if (Comunicacion_RecibirModificacionesPC(&umbral_pc, &cmd_silencio_pc)) {
        if (umbral_pc > 0 && umbral_pc <= UMBRAL_MAX_SISTEMA) {
            umbral_actual = umbral_pc;
        }
        if (cmd_silencio_pc) {
            Alarma_ConmutarSilencio();
        }
    }

    // Process input from physical EINT0 button ISR
    if (Alarma_ComprobarEventoPulsador()) {
        Alarma_ConmutarSilencio();
    }
}

static void TareaControlEstacionamiento(void) {
    uint16_t distancia_actual;
    EstadoSistema_t nuevo_estado;

    // Process GPDMA hardware buffers and read current system distance
    DistanciaCm_ProcesarMuestras();
    distancia_actual = DistanciaCm_ObtenerUltimaMedida();

    // Clean, domain-driven threshold assessment
    if (distancia_actual > umbral_actual) {
        nuevo_estado = ESTADO_SISTEMA_APAGADO;
    } 
    else if (distancia_actual >= 80 && distancia_actual <= 400) {
        nuevo_estado = ESTADO_SISTEMA_SEGURO;
    } 
    else if (distancia_actual >= 30 && distancia_actual < 80) {
        nuevo_estado = ESTADO_SISTEMA_ADVERTENCIA;
    } 
    else {
        nuevo_estado = ESTADO_SISTEMA_PELIGRO;
    }

    // ATOMIC SERVICE UPDATE: The service guarantees visual and audio synchronization
    Alarma_ActualizarInterfaz(nuevo_estado, distancia_actual);
}
