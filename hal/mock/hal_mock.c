/* PC mock of the HAL. ADC/EEPROM values are set by the demo harness,
 * GPIO writes go to stdout. Selected at link time via the Makefile. */
#include <stdio.h>
#include <string.h>

#include "hal_adc.h"
#include "hal_eeprom.h"
#include "hal_gpio.h"
#include "hal_mock.h"
#include "hal_timer.h"

static uint32_t s_time_us;
static uint16_t s_adc_raw;
static uint8_t  s_eeprom[64];
static bool     s_eeprom_fail;
static bool     s_pins[3];
static bool     s_timer_armed;

void Mock_Reset(void)
{
    s_time_us = 0u;
    s_adc_raw = 0u;
    memset(s_eeprom, 0, sizeof s_eeprom);
    s_eeprom_fail = false;
    memset(s_pins, 0, sizeof s_pins);
    s_timer_armed = false;
}

void MockTime_Advance(uint32_t us) { s_time_us += us; }
void MockAdc_Set(uint16_t raw)     { s_adc_raw = raw; }

void MockEeprom_Load(const uint8_t *image, uint16_t len)
{
    memcpy(s_eeprom, image, len);
}

void MockEeprom_SetFail(bool fail) { s_eeprom_fail = fail; }

/* --- hal_adc.h --- */
uint16_t Hal_AdcRead(void) { return s_adc_raw; }

/* --- hal_timer.h --- */
void Hal_TimerStart100us(void) { s_timer_armed = true; }

/* --- hal_eeprom.h --- */
bool Hal_EepromRead(uint16_t addr, uint8_t *dst, uint16_t len)
{
    if (s_eeprom_fail) {
        return false;
    }
    memcpy(dst, &s_eeprom[addr], len);
    return true;
}

/* --- hal_gpio.h --- */
void Hal_GpioInit(void) {}

void Hal_GpioWrite(uint8_t pin, bool level)
{
    if (s_pins[pin] == level) {
        return; /* only log actual level changes */
    }
    s_pins[pin] = level;
    /* 0/1/2 = G/Y/R, matches the pin defines in led_panel.c */
    printf("t=%luus GPIO %c=%d\n", (unsigned long)s_time_us, "GYR"[pin], level ? 1 : 0);
}
