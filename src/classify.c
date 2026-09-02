#include "classify.h"

/* thresholds in deci-degC */
#define TEMP_WARN_DC    850  /* >= 85.0 degC -> Yellow */
#define TEMP_CRIT_HI_DC 1050 /* >= 105.0 degC -> Red   */
#define TEMP_CRIT_LO_DC 50   /* <  5.0 degC  -> Red    */

LedState Classify(int32_t temp_dC)
{
    if (temp_dC >= TEMP_CRIT_HI_DC || temp_dC < TEMP_CRIT_LO_DC) {
        return LED_CRIT;
    }
    if (temp_dC >= TEMP_WARN_DC) {
        return LED_WARN;
    }
    return LED_OK;
}
