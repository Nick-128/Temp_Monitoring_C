#include "config.h"

#include "hal_eeprom.h"

/* EEPROM layout: [0] hw revision (0 = Rev-A, 1 = Rev-B),
 *                [1..15] serial number string, nul-terminated */
#define CFG_ADDR 0u
#define CFG_LEN  16u

bool Config_Load(Config *out)
{
    uint8_t image[CFG_LEN];

    if (!Hal_EepromRead(CFG_ADDR, image, CFG_LEN)) {
        return false;
    }
    if (image[0] > 1u) {
        /* covers blank EEPROM (0xFF) and any other garbage */
        return false;
    }
    out->rev = (HwRevision)image[0];
    for (uint16_t i = 1u; i < CFG_LEN; i++) {
        out->serial[i - 1u] = (char)image[i];
    }
    out->serial[sizeof out->serial - 1u] = '\0';
    return true;
}
