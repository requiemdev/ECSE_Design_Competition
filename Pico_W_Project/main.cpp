// Pico Defines
#include "pico/cyw43_arch.h"

// C Defines
#include "common.h"
#include "speaker/speaker.h"

int main()
{
    stdio_init_all();
    
    speakerInitialise(30);

    cyw43_arch_init();
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);

    speakerPlaySong(2, 1);
    // sleep_ms(1000);
    // speakerChangeVolume(10);
    // sleep_ms(1000);
    // speakerChangeVolume(10);
    // sleep_ms(1000);
    // speakerChangeVolume(10);
    // sleep_ms(1000);
    // speakerChangeVolume(-10);
    // sleep_ms(1000);
    // speakerChangeVolume(-10);
    // sleep_ms(1000);
    // speakerChangeVolume(-10);
    // sleep_ms(1000);
    // speakerChangeVolume(-10);
    // sleep_ms(1000);
    // speakerChangeVolume(-10);
    // sleep_ms(1000);
    // speakerChangeVolume(10);
    // sleep_ms(1000);
    // speakerSetVolume(10);
    // sleep_ms(1000);
    // speakerSleepMode();
    // sleep_ms(5000);
    // speakerWakeUp();
    // sleep_ms(5000);
    sleep_ms(100000);

    while (true) {
        speakerPlayRandomSong();
        sleep_ms(10000);
    }
}
