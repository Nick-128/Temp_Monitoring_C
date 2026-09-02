#ifndef LED_PANEL_H
#define LED_PANEL_H

/* During normal operation exactly one LED is lit. */
typedef enum {
    LED_OK,   /* Green  */
    LED_WARN, /* Yellow */
    LED_CRIT  /* Red    */
} LedState;

/* Init GPIOs; all LEDs stay off until the first measurement. */
void LedPanel_Init(void);

/* Update the LEDs for the given state. Only writes on state change. */
void LedPanel_Show(LedState state);

/* Config error indication: all three LEDs on. Normal operation never lights
 * more than one, so this cannot be mistaken for a temperature reading. */
void LedPanel_ShowError(void);

#endif
