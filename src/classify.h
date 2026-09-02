#ifndef CLASSIFY_H
#define CLASSIFY_H

#include <stdint.h>

#include "led_panel.h" /* LedState */

/* Map a temperature in deci-degC to an LED state. Checked in severity order,
 * critical first. Boundaries: 85.0 is already warning, 105.0 is already
 * critical, 5.0 is still OK (spec says < 5). */
LedState Classify(int32_t temp_dC);

#endif
