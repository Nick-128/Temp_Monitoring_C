#ifndef SENSOR_H
#define SENSOR_H

#include <stdbool.h>
#include <stdint.h>

#include "config.h"

/* Set the scale factor for the fitted sensor revision.
 * Must be called before sampling is started. */
void Sensor_Init(HwRevision rev);

/* ADC end-of-conversion ISR. On the target this is called from the ADC
 * interrupt vector; the PC demo calls it directly. */
void Sensor_AdcIsr(void);

/* Latest temperature in deci-degC.
 * Returns false until the first sample has arrived. */
bool Sensor_Get_dC(int32_t *out_dC);

#endif
