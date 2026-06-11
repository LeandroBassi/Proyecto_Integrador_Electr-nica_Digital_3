#include "BuzzerPower.h"
#include "lpc17xx_pwm.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_clkpwr.h"

void BuzzerPower_Init(void) {
    PINSEL_CFG_Type pinCfg;
    pinCfg.Portnum = PINSEL_PORT_1;
    pinCfg.Pinnum = PINSEL_PIN_18;
    pinCfg.Funcnum = PINSEL_FUNC_2;
    PINSEL_ConfigPin(&pinCfg);

    // PWM1 init
    PWM_TIMERCFG_Type pwmCfg;
    pwmCfg.PrescaleOption = TIM_PRESCALE_USVAL;
    pwmCfg.PrescaleValue = 1;
    PWM_Init(LPC_PWM1, PWM_MODE_TIMER, &pwmCfg);
    
    PWM_CHANNEL_CFG_Type chCfg;
    chCfg.channelNum = 1;
    chCfg.channelType = PWM_CHANNEL_SINGLE_EDGE;
    chCfg.channelPolarity = MCPWM_CHANNEL_PASSIVE_LO;
    chCfg.channelPeriodValue = 1000;
    chCfg.channelPulsewidthValue = 0;
    PWM_ConfigChannel(LPC_PWM1, 1, &chCfg);
    PWM_ChannelCmd(LPC_PWM1, 1, ENABLE);
    PWM_Cmd(LPC_PWM1, ENABLE);
}

void BuzzerPower_SetFrequency(uint32_t freq_hz) {
    if (freq_hz == 0) {
        BuzzerPower_Stop();
        return;
    }
    uint32_t period = 1000000 / freq_hz;
    PWM_MatchUpdate(LPC_PWM1, 0, period, PWM_MATCH_UPDATE_NOW);
    PWM_MatchUpdate(LPC_PWM1, 1, period / 2, PWM_MATCH_UPDATE_NOW);
}

void BuzzerPower_Stop(void) {
    PWM_MatchUpdate(LPC_PWM1, 1, 0, PWM_MATCH_UPDATE_NOW);
}
