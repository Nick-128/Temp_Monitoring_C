#ifndef HAL_TIMER_H
#define HAL_TIMER_H

/* Arm the 100us sample clock. On the target the timer triggers the ADC
 * directly (TRGO -> ADC trigger input), so conversion timing does not depend
 * on software at all - we only see the end-of-conversion interrupt. */
void Hal_TimerStart100us(void);

#endif
