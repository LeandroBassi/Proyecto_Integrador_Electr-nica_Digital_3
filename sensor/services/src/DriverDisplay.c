#include "DriverDisplay.h"

static uint8_t digits[4] = {0,0,0,0};
static uint8_t decimal_pos = 2;
static uint8_t cur_digit = 0;
static const uint8_t Table[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

void DriverDisplay_Init(void) { Display7SegHW_Init(); }

void DriverDisplay_SetNumber(float val) {
    uint32_t v = (uint32_t)(val * 10.0f);
    digits[0] = (v / 1000) % 10;
    digits[1] = (v / 100) % 10;
    digits[2] = (v / 10) % 10;
    digits[3] = v % 10;
}

void DriverDisplay_Refresh(void) {
    Display7SegHW_SelectDigit(cur_digit);
    uint8_t p = Table[digits[cur_digit]];
    if (cur_digit == decimal_pos) p |= 0x80;
    Display7SegHW_SetSegments(p);
    cur_digit = (cur_digit + 1) % 4;
}
