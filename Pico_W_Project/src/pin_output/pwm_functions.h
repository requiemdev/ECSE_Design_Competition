#ifndef PWM_FUNCTIONS_H
#define PWM_FUNCTIONS_H

#include "../common.h"

#define MAX_PWM_VALUE 329

namespace PWM {
    void pwm_init(uint8_t gpio);
    /** 0 <= voltage <= 3.3 */
    void pwm_enable_with_voltage(uint8_t gpio, float voltage);
    void pwm_disable(uint8_t gpio);
}

#endif // PWM_FUNCTIONS_H