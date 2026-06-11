#include "ConversionSharp.h"

float Sharp_ADC_to_Distance(uint32_t raw_adc) {
    uint32_t val = (raw_adc >> 4) & 0xFFF;
    float voltage = (val * 3.3f) / 4095.0f;
    if (voltage < 0.4f) return 80.0f;
    float distance_cm = 27.2f / (voltage - 0.12f);
    if (distance_cm < 10.0f) return 10.0f;
    if (distance_cm > 80.0f) return 80.0f;
    return distance_cm;
}
