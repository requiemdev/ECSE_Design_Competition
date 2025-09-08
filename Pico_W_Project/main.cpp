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

    speakerPlaySong(2, 1);
    sleep_ms(10000);
    speakerNextSong();
    sleep_ms(10000);
    speakerPreviousSong();
    sleep_ms(10000);
    speakerPreviousSong();
    sleep_ms(10000);


    while (true) {
        speakerPlayRandomSongInFolder(1);
        sleep_ms(10000);
        speakerPlayRandomSongInFolder(2);
        sleep_ms(10000);
    }
}
