#include "SharpGP2Y.h"

typedef struct {
    uint32_t SrcAddr;
    uint32_t DstAddr;
    uint32_t NextLLI;
    uint32_t Control;
} DMA_LLI_Type;

static DMA_LLI_Type dma_lli;

void SharpGP2Y_Init(uint32_t* dest_buffer) {
    // 1. P0.23 como AD0.0
    LPC_PINCON->PINSEL1 &= ~(3 << 14);
    LPC_PINCON->PINSEL1 |= (1 << 14);
    LPC_PINCON->PINMODE1 &= ~(3 << 14);
    LPC_PINCON->PINMODE1 |= (2 << 14); // Sin pull-up ni pull-down

    // 2. Encender ADC
    LPC_SC->PCONP |= (1 << 12);
    LPC_ADC->ADCR = (1 << 0) | (4 << 8) | (1 << 21);

    // 3. Configurar DMA
    LPC_SC->PCONP |= (1 << 29);
    LPC_GPDMA->DMACConfig = 1;
    while (!(LPC_GPDMA->DMACConfig & 1));

    dma_lli.SrcAddr = (uint32_t)&(LPC_ADC->ADDR0);
    dma_lli.DstAddr = (uint32_t)dest_buffer;
    dma_lli.NextLLI = (uint32_t)&dma_lli;
    dma_lli.Control = ADC_BUFFER_SIZE
                    | (2 << 12)
                    | (2 << 15)
                    | (2 << 18)
                    | (2 << 21)
                    | (0 << 26)
                    | (1 << 27)
                    | (1U << 31);

    LPC_GPDMA_CH0->DMACCSrcAddr = dma_lli.SrcAddr;
    LPC_GPDMA_CH0->DMACCDestAddr = dma_lli.DstAddr;
    LPC_GPDMA_CH0->DMACCLLI = dma_lli.NextLLI;
    LPC_GPDMA_CH0->DMACCConfig = 1
                               | (8 << 1)
                               | (2 << 11)
                               | (1 << 14)
                               | (1 << 15);

    NVIC_EnableIRQ(DMA_IRQn);
}

void SharpGP2Y_StartConversion(void) {
    LPC_ADC->ADCR |= (1 << 16); // Modo Burst
}

void DMA_IRQHandler(void) {
    if (LPC_GPDMA->DMACIntStat & 1) {
        if (LPC_GPDMA->DMACIntTCStat & 1) {
            LPC_GPDMA->DMACIntTCClear = 1;
        }
    }
}
