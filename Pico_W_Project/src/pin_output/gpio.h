#ifndef GPIO_H
#define GPIO_H

#include "../common.h"

namespace GPIO {
    /** For dir, 0 = input, 1 = output */
    void gpio_init_with_dir(uint8_t gpio, bool dir);
    void gpio_set(uint8_t gpio, bool value);
}

#endif // GPIO_H