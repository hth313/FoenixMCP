#include "interrupt.h"
#include "timers.h"
#include "gabe_reg.h"

long jiffy_count;

/*
 * Interrupt handler for the Channel A SOF interrupt... just counts jiffies
 *
 * NOTE: in time, this should be handled by the RTC or another timer.
 */
void sof_a_handler() {
    long jc_mod;

    jiffy_count++;

    jc_mod = jiffy_count % 60;
    if (jc_mod == 30) {
        *GABE_CTRL_REG = *GABE_CTRL_REG | POWER_ON_LED;
    } else if (jc_mod == 0) {
        *GABE_CTRL_REG = *GABE_CTRL_REG & ~POWER_ON_LED;
    }
}

/*
 * Initialize the timers and their interrupts
 */
void timers_init() {
    jiffy_count = 0;

    int_register(INT_SOF_A, sof_a_handler);
    // int_enable(INT_SOF_A);
}

/*
 * Return the number of jiffies (1/60 of a second) since last reset time
 */
long timers_jiffies() {
    return jiffy_count;
}