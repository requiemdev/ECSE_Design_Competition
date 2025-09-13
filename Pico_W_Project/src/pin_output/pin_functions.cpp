#include "gpio.h"
#include "pwm_functions.h"

#include "hardware/pwm.h"

void GPIO::gpio_init_with_dir(uint8_t gpio, bool dir) {
    gpio_init(gpio);
    gpio_set_dir(gpio, dir);
}

void GPIO::gpio_set(uint8_t gpio, bool value) {
    gpio_put(gpio, value);
}

void PWM::pwm_init(uint8_t gpio) {
    uint slice_num = pwm_gpio_to_slice_num(gpio);

    pwm_config config = pwm_get_default_config();
    pwm_config_set_wrap(&config, MAX_PWM_VALUE);
    pwm_init(slice_num, &config, true);
}

void PWM::pwm_enable_with_voltage(uint8_t gpio, float v) {
    pwm_set_gpio_level(0, v * 100);
    pwm_set_enabled(pwm_gpio_to_slice_num(gpio), true);
}

void PWM::pwm_disable(uint8_t gpio) {
    pwm_set_enabled(pwm_gpio_to_slice_num(gpio), false);
}