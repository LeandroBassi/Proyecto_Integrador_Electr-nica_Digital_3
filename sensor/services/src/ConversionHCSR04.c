#include "ConversionHCSR04.h"

float HCSR04_Width_to_Distance(uint32_t echo_width_us) {
    if (echo_width_us == 0) return 400.0f;
    float dist = (float)echo_width_us / 58.0f;
    if (dist < 80.0f) return 80.0f;
    if (dist > 400.0f) return 400.0f;
    return dist;
}
