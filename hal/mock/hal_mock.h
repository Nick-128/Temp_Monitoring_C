#ifndef HAL_MOCK_H
#define HAL_MOCK_H

#include <stdbool.h>
#include <stdint.h>

/* Control interface for the PC mocks. Only the demo harness includes this;
 * application code sees just the hal_*.h headers. */
void Mock_Reset(void);
void MockTime_Advance(uint32_t us);
void MockAdc_Set(uint16_t raw);
void MockEeprom_Load(const uint8_t *image, uint16_t len);
void MockEeprom_SetFail(bool fail);

#endif
