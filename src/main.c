/* PC demonstration main. */
#include <stdio.h>
#include <string.h>

#include "classify.h"
#include "config.h"
#include "hal_mock.h"
#include "hal_timer.h"
#include "led_panel.h"
#include "sensor.h"

/* Temperature profile in deci-degC, crosses every threshold from both sides.
 * Raw digits are derived per revision (Rev-A /10, Rev-B as-is). */
static const int32_t PROFILE_DC[] = {200, 849, 850, 1049, 1050, 600, 50, 49, 200};
#define PROFILE_LEN (sizeof PROFILE_DC / sizeof PROFILE_DC[0])

static void RunScenario(const char *name, uint8_t rev_byte, bool eeprom_fail)
{
    uint8_t image[16] = {0};
    image[0] = rev_byte;
    strcpy((char *)&image[1], "ABC1234");

    Mock_Reset();
    MockEeprom_Load(image, sizeof image);
    MockEeprom_SetFail(eeprom_fail);

    printf("=== Scenario: %s ===\n", name);

    /* boot: LEDs first, then config; sampling is armed last */
    LedPanel_Init();
    Config cfg;
    if (!Config_Load(&cfg)) {
        LedPanel_ShowError();
        printf("Config invalid -> CONFIG ERROR state (terminal until reset)\n\n");
        return; /* on target: for (;;) {} */
    }
    printf("Boot OK: revision=%s serial=%s\n", cfg.rev == HW_REV_A ? "Rev-A" : "Rev-B", cfg.serial);
    Sensor_Init(cfg.rev);
    Hal_TimerStart100us(); /* only now that the scale factor is known */

    /* --- steady state --- */
    for (size_t i = 0; i < PROFILE_LEN; i++) {
        uint16_t raw = (uint16_t)(cfg.rev == HW_REV_A ? PROFILE_DC[i] / 10 : PROFILE_DC[i]);
        MockAdc_Set(raw);
        Sensor_AdcIsr(); /* stands in for the ADC EOC interrupt */

        /* one main-loop iteration */
        int32_t temp_dC;
        if (Sensor_Get_dC(&temp_dC)) {
            LedPanel_Show(Classify(temp_dC));
        }
        MockTime_Advance(100);
    }
    printf("\n");
}

int main(void)
{
    RunScenario("Rev-A", 0u, false);
    RunScenario("Rev-B", 1u, false);
    RunScenario("Corrupt EEPROM", 0u, true);
    return 0;
}
