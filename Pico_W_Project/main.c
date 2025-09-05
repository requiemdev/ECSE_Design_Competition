// Pico Defines
#include "pico/cyw43_arch.h"

// C Defines
#include "common.h"
#include "speaker/speaker.h"

// UART defines
// By default the stdout UART is `uart0`, so we will use the second one
#define BAUD_RATE 9600

int main()
{
    stdio_init_all();
    
    speakerUartInit();

    cyw43_arch_init();
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);

    speakerPlaySong(1, 1);
    sleep_ms(10000);
    speakerStopSong();
    sleep_ms(5000);

    speakerPlaySong(1, 2);
    sleep_ms(10000);
    speakerStopSong();
    sleep_ms(5000);

    speakerPlaySong(2, 1);
    sleep_ms(10000);
    speakerStopSong();
    sleep_ms(5000);
    
    speakerPlaySong(2, 2);
    sleep_ms(10000);
    speakerStopSong();
    sleep_ms(5000);

    speakerPlaySong(1, 1);

    for (uint8_t i=0; i<3; i++) {
        speakerContinueSong();
        sleep_ms(5000);
        speakerPauseSong();
        sleep_ms(2500); 
    }
    speakerStopSong();

    while (true) {
    }
}
