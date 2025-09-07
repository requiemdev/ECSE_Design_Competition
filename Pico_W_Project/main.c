// Pico Defines
#include "pico/cyw43_arch.h"

// C Defines
#include "common.h"
#include "speaker/speaker.h"

int main()
{
    stdio_init_all();
    
    speakerInitialise(15);

    cyw43_arch_init();
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);

    while (true) {
    }
}
