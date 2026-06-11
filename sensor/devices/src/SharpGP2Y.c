#include "SharpGP2Y.h"
#include "lpc17xx_adc.h"
#include "lpc17xx_gpdma.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_clkpwr.h"

void SharpGP2Y_Init(uint32_t* dest_buffer) {
    PINSEL_CFG_Type pinCfg;
    pinCfg.Portnum = PINSEL_PORT_0;
    pinCfg.Pinnum = PINSEL_PIN_23;
    pinCfg.Funcnum = PINSEL_FUNC_1;
    pinCfg.Pinmode = PINSEL_PINMODE_TRISTATE;
    pinCfg.OpenDrain = PINSEL_PINMODE_NORMAL;
    PINSEL_ConfigPin(&pinCfg);

    CLKPWR_ConfigPPWR(CLKPWR_PCONP_PCAD, ENABLE);
    ADC_Init(LPC_ADC, 200000); // 200kHz

    CLKPWR_ConfigPPWR(CLKPWR_PCONP_PCGPDMA, ENABLE);
    GPDMA_Init();

    GPDMA_Channel_CFG_Type dmaCfg;
    dmaCfg.ChannelNum = 0;
    dmaCfg.TransferSize = ADC_BUFFER_SIZE;
    dmaCfg.TransferWidth = GPDMA_WIDTH_WORD;
    dmaCfg.SrcMemAddr = 0; // Not used for P2M
    dmaCfg.DstMemAddr = (uint32_t)dest_buffer;
    dmaCfg.TransferType = GPDMA_TRANSFERTYPE_P2M;
    dmaCfg.SrcConn = GPDMA_CONN_ADC;
    dmaCfg.DstConn = 0;
    dmaCfg.DMALLI = 0; // Circular buffer setup requires manual LLI

    GPDMA_Setup(&dmaCfg);
}

void SharpGP2Y_StartConversion(void) {
    ADC_BurstCmd(LPC_ADC, ENABLE);
}
