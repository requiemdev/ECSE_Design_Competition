// Pico Defines
#include "pico/cyw43_arch.h"

// C Defines
#include "common.h"
#include "speaker/speaker.h"

volatile bool song_playing = true;

/** Initialise the MCU along with all 
 * peripherals which should be on at the start of the program. 
*/
void initialiseMCU() {
    stdio_init_all();
    Speaker::speakerInitialise(SPEAKER_DEFAULT_VOLUME);
    cyw43_arch_init();
}

int main()
{
    initialiseMCU();

    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);

    while (true) {

    }
}
