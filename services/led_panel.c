#include "led_panel.h"

#include <stdbool.h>

#include "hal_gpio.h"

/* LED pin assignment */
#define PIN_G 0u
#define PIN_Y 1u
#define PIN_R 2u

static LedState s_last;
static bool     s_last_valid;

static void SetAll(bool g, bool y, bool r)
{
    Hal_GpioWrite(PIN_G, g);
    Hal_GpioWrite(PIN_Y, y);
    Hal_GpioWrite(PIN_R, r);
}

void LedPanel_Init(void)
{
    Hal_GpioInit();
    SetAll(false, false, false);
    s_last_valid = false;
}

void LedPanel_Show(LedState state)
{
    if (s_last_valid && state == s_last) {
        return;
    }
    SetAll(state == LED_OK, state == LED_WARN, state == LED_CRIT);
    s_last       = state;
    s_last_valid = true;
}

void LedPanel_ShowError(void)
{
    SetAll(true, true, true);
    s_last_valid = false;
}
