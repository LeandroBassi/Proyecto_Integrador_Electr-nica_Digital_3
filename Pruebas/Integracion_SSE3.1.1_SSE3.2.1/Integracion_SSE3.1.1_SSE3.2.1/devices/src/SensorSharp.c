#include "SensorSharp.h"
#include "lpc17xx_adc.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_timer.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_gpdma.h"

#define SRAM_BANK0_START	0x2007C000
#define SRAM_BANK0_MIDDLE	0x2007E000
#define SRAM_BANK0_END		0x2007FFFF

#define ADC_BUFFER_START    0x2007C000
#define NUM_MUESTRAS 		(uint32_t) 10

volatile uint32_t *adc_samples = (uint32_t*)ADC_BUFFER_START;

// ---------------------------------------------------------
// PROTOTIPOS DE FUNCIONES PRIVADAS
// ---------------------------------------------------------
static void cfgGPIO(void);
static void cfgTIMER1(void);
static void cfgADC(void);
static void cfgDMA(void);

// ---------------------------------------------------------
// FUNCIONES PUBLICAS
// ---------------------------------------------------------
void SensorSharp_Init(void) {
    // Configuración ADC para Sharp GP2Y
	cfgGPIO();
	cfgTIMER1();
	cfgADC();
	cfgDMA();

	return;
}

uint16_t SensorSharp_GetPromedioCrudo(void) {
    uint32_t sumatoria = 0;
    uint16_t min_val = 4095; // Arranca en el máximo posible
    uint16_t max_val = 0;    // Arranca en el mínimo posible

    for(int i = 0; i < NUM_MUESTRAS; i++) {
        uint16_t muestra = (adc_samples[i] >> 4) & 0x0FFF;
        sumatoria += muestra;

        // Buscamos el pico máximo y el mínimo dentro del buffer del DMA
        if (muestra < min_val) min_val = muestra;
        if (muestra > max_val) max_val = muestra;
    }

    // FILTRO DE ESTABILIDAD (JITTER)
    // Si la diferencia entre la muestra más alta y la más baja es mayor a 150 unidades
    // significa que el sensor está "viendo fantasmas" (puro ruido ambiental).
    // (Nota: Podés achicar o agrandar este '150' según las pruebas en tu casa).
    if ((max_val - min_val) > 150) {
        return 0; // Retornamos 0 indicando "Señal Inválida / Ruido"
    }

    // Si la señal es estable, retornamos el promedio normal
    return (uint16_t)(sumatoria / NUM_MUESTRAS);
}

// ---------------------------------------------------------
// DESARROLLO DE FUNCIONES PRIVADAS
// ---------------------------------------------------------
static void cfgGPIO(void) {
	//-- 1)Estructuras de Configuracion --
    //A)Configuración P0.23 AD0.0
    PINSEL_CFG_Type cfgPinADC0_CH0;

    //B)Configuración P1.22 MAT1.0
    PINSEL_CFG_Type cfgPinMAT1_CH0;

    //-- A)cfgPinADC0_CH0 --
    cfgPinADC0_CH0.Portnum = PINSEL_PORT_0;
    cfgPinADC0_CH0.Pinnum = PINSEL_PIN_23;
    cfgPinADC0_CH0.Funcnum = PINSEL_FUNC_1;
    cfgPinADC0_CH0.Pinmode = PINSEL_PINMODE_TRISTATE;
    cfgPinADC0_CH0.OpenDrain = PINSEL_PINMODE_NORMAL;

    //-- B)cfgPinMAT0_CH1 --
    cfgPinMAT1_CH0.Portnum = PINSEL_PORT_1;
    cfgPinMAT1_CH0.Pinnum = PINSEL_PIN_22;
    cfgPinMAT1_CH0.Funcnum = PINSEL_FUNC_3;
    cfgPinMAT1_CH0.OpenDrain = PINSEL_PINMODE_NORMAL;

    //-- 2)Inicializacion de cada uno --
    PINSEL_ConfigPin(&cfgPinADC0_CH0);
    PINSEL_ConfigPin(&cfgPinMAT1_CH0);

    return;
}

static void cfgTIMER1(void) {
	//-- 1)Estructuras de configuracion --
    //A)Configuración de Timer en Modo Temporizador
    TIM_TIMERCFG_Type cfgTimerMode;

    //B)Configuración MATCH
    TIM_MATCHCFG_Type cfgMATCH;

    //-- A)cfgTimerMode --
    cfgTimerMode.PrescaleOption = TIM_PRESCALE_USVAL;
    cfgTimerMode.PrescaleValue = 1; 					// Ajustado a 1us

    //-- B)cfgTimerMatch --
    cfgMATCH.MatchChannel = 0;
    cfgMATCH.MatchValue = 500;							// tmatch = 500us -> Conversion cada 1ms
    cfgMATCH.IntOnMatch = DISABLE;
    cfgMATCH.ResetOnMatch = ENABLE;
    cfgMATCH.StopOnMatch = DISABLE;
    cfgMATCH.ExtMatchOutputType = TIM_EXTMATCH_TOGGLE;


    TIM_Init(LPC_TIM1, TIM_TIMER_MODE, &cfgTimerMode);
    TIM_ConfigMatch(LPC_TIM1, &cfgMATCH);
    TIM_Cmd(LPC_TIM1, ENABLE);
    NVIC_DisableIRQ(TIMER1_IRQn);

    return;
}

static void cfgADC(void) {
    //1.Inicialización del ADC con fm = 200KHz
    ADC_Init(LPC_ADC, 200000);

    //2.Deshabilitación del Modo Burst
    ADC_BurstCmd(LPC_ADC, DISABLE);

    //3.Inicialización de Conversión debido a MAT1.0
    ADC_StartCmd(LPC_ADC, ADC_START_ON_MAT10);

    //4.Inicialización de Conversión ante Flanco Descendente debido a MAT1.0
    ADC_EdgeStartConfig(LPC_ADC, ADC_START_ON_FALLING);

    //5.Funcionalidad de P0.23 como AD0.0
    ADC_ChannelCmd(LPC_ADC, ADC_CHANNEL_0, ENABLE);

    //6.Deshabilitación de Interrupción ante Finalización de Conversión por AD0.0
    ADC_IntConfig(LPC_ADC, ADC_ADINTEN0, DISABLE);

    //7.Deshabilitación de Interrupción por AD0.0
    NVIC_DisableIRQ(ADC_IRQn);

    return;
}

static void cfgDMA(void) {
	//-- 1)Estructuras de configuracion --
    //A)Estructura para Lista Enlazada 0 para canal 0 del DMA
    static GPDMA_LLI_Type cfgADC_LLI0_CH0;

    //B)Estructura de Configuración para canal 0 del DMA
    GPDMA_Channel_CFG_Type cfgADC_MEM_CH0;


    //-- A)cfgDAC_LLI0_CH0 --
    //1.Dirección de Fuente de Datos (Memoria)
    cfgADC_LLI0_CH0.SrcAddr = (uint32_t)&(LPC_ADC->ADDR0);

    //2.Dirección de Destino de Datos (memoria)
    cfgADC_LLI0_CH0.DstAddr = (uint32_t)adc_samples;

    //3.Próxima Dirección de Destino de Datos (LLI Repetitiva)
    cfgADC_LLI0_CH0.NextLLI = (uint32_t)&cfgADC_LLI0_CH0;

    //4.Tamaño de la Transferencia de la LLI0
    cfgADC_LLI0_CH0.Control = (NUM_MUESTRAS << 0)
                            // Ancho de la Transferencia de Fuente (32-bit)
                            | (2 << 18)
                            // Ancho de la Transferencia de Destino (32-bit)
                            | (2 << 21)
                            // SI=0: Sin Incremento de la Dirección de Fuente
                            // DI=1: Con Incremento de la Dirección de Destino
                            | (1 << 27);

    //-- B)GPDMA_CHANNEL_CFG_TYPE --
    //1.Selección del Canal de Transferencia
    cfgADC_MEM_CH0.ChannelNum = 0;

    //2.Periférico de Fuente de Datos
    cfgADC_MEM_CH0.SrcConn = GPDMA_CONN_ADC;

    //3.Periférico de Destino de Datos (Sin Uso)
    cfgADC_MEM_CH0.DstConn = 0;

    //4.Dirección de Fuente de Datos en Memoria (Sin Uso)
    cfgADC_MEM_CH0.SrcMemAddr = 0;

    //5.Dirección de Destino de Datos en Memoria
    cfgADC_MEM_CH0.DstMemAddr = (uint32_t)adc_samples;

    //6.Tipo de Transferencia (P2M)
    cfgADC_MEM_CH0.TransferType = GPDMA_TRANSFERTYPE_P2M;

    //7.Tamaño de Transferencia de Datos
    cfgADC_MEM_CH0.TransferSize = NUM_MUESTRAS;

    //8.Ancho de Transferencia de Datos
    cfgADC_MEM_CH0.TransferWidth = GPDMA_WIDTH_WORD;

    //9.Lista Enlazada Inicial
    cfgADC_MEM_CH0.DMALLI = (uint32_t)&cfgADC_LLI0_CH0;


    //2.Inicialización del Controlador GPDMA
    GPDMA_Init();

    //3.Configuración del Canal 0 de DMA
    GPDMA_Setup(&cfgADC_MEM_CH0);

    //4.Habilitacion del canal 0
    GPDMA_ChannelCmd(0, ENABLE);

    //5.Deshabilitación de Interrupción por DMA
    NVIC_DisableIRQ(DMA_IRQn);

    return;
}
