#ifndef HAL_EEPROM_H
#define HAL_EEPROM_H

#include <stdbool.h>
#include <stdint.h>

/* Read len bytes from the EEPROM starting at addr.
 * Returns false on a bus/device error; dst is undefined in that case. */
bool Hal_EepromRead(uint16_t addr, uint8_t *dst, uint16_t len);

#endif
