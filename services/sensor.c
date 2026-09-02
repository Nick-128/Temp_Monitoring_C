#include "sensor.h"

#include "hal_adc.h"

/* Latest-sample mailbox. The ISR overwrites it at 10kHz, the main loop picks
 * up whatever is newest - nothing downstream needs the full sample stream,
 * so older values are simply superseded.
 *
 * A 16-bit aligned access is a single bus transaction on a 32-bit MCU, so
 * reading s_latest_raw without an IRQ lock is fine. If this ever grows into
 * a struct (e.g. raw + timestamp) that stops being true - reads can tear,
 * add a critical section or seqlock then. */
static volatile uint16_t s_latest_raw;
static volatile bool     s_have_sample; /* set on first sample, never cleared */

/* Rev-A: 1.0 degC/digit -> 10, Rev-B: 0.1 degC/digit -> 1. Set once at init. */
static int32_t s_scale_dC_per_digit;

void Sensor_Init(HwRevision rev)
{
    s_scale_dC_per_digit = (rev == HW_REV_A) ? 10 : 1;
}

void Sensor_AdcIsr(void)
{
    /* Just fetch and store. The conversion was triggered by the timer, so
     * ISR latency has no effect on the sample timing. */
    s_latest_raw  = Hal_AdcRead();
    s_have_sample = true;
}

bool Sensor_Get_dC(int32_t *out_dC)
{
    if (!s_have_sample) {
        return false;
    }
    uint16_t raw = s_latest_raw;
    *out_dC = (int32_t)raw * s_scale_dC_per_digit;
    return true;
}
