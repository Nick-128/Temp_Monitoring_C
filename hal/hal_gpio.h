#ifndef HAL_GPIO_H
#define HAL_GPIO_H

#include <stdbool.h>
#include <stdint.h>

/* Plain pin access. Pin assignment lives in led_panel.c. */
void Hal_GpioInit(void);
void Hal_GpioWrite(uint8_t pin, bool level);

#endif
