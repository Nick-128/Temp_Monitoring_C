/* STM32 target implementation - skeleton only, not part of the PC build.
 * Kept as a reference for where the register-level code goes. */
#include "hal_adc.h"
#include "hal_eeprom.h"
#include "hal_gpio.h"
#include "hal_timer.h"

#include "sensor.h" /* Sensor_AdcIsr() */

uint16_t Hal_AdcRead(void)
{
    /* TODO: return ADC1->DR; */
    return 0u;
}

void Hal_TimerStart100us(void)
{
    /* TODO: TIMx at 100us period, TRGO on update event, ADC external trigger
     * = TIMx_TRGO, EOC interrupt enabled in NVIC.
     * The conversion must be started by the timer trigger, not by software -
     * otherwise the low-jitter requirement is gone. */
}

bool Hal_EepromRead(uint16_t addr, uint8_t *dst, uint16_t len)
{
    /* TODO: I2C read from the EEPROM */
    (void)addr;
    (void)dst;
    (void)len;
    return false;
}

void Hal_GpioInit(void)
{
    /* TODO: GPIO clocks, LED pins as push-pull outputs */
}

void Hal_GpioWrite(uint8_t pin, bool level)
{
    /* TODO: GPIOx->BSRR */
    (void)pin;
    (void)level;
}

/* ADC end-of-conversion interrupt */
void ADC_IRQHandler(void);
void ADC_IRQHandler(void)
{
    /* TODO: clear EOC flag */
    Sensor_AdcIsr();
}
