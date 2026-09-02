#ifndef HAL_ADC_H
#define HAL_ADC_H

#include <stdint.h>

/* Returns the latest conversion result, raw digits.
 * Scaling to temperature happens in the sensor layer, not here. */
uint16_t Hal_AdcRead(void);

#endif
