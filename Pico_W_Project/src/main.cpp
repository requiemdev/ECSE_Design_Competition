// Pico Defines
#include "pico/cyw43_arch.h"
#include "pico/multicore.h"

// C++ Defines
#include "common.h"
#include "speaker/speaker.h"
#include "states.h"
#include "main_event.h"
#include "timers/timer.h"
#include "command/command.h"

// C Defines
#ifdef __cplusplus
extern "C" {
#endif

#include "microphone.h"
#include "usb_microphone.h"
#include "oled/ssd1306.h"
#include "oled/font.h"

#ifdef __cplusplus
}
#endif


// Temporary includes for testing
#include "command/command_list.h"
#include "hardware/i2c.h"

// Global Variables
volatile bool song_playing = true;
volatile State current_state = State::SLEEP;

void MainEvent::initialiseMCU() {
    stdio_init_all();
    Speaker::initialise(SPEAKER_DEFAULT_VOLUME);
    cyw43_arch_init();
    microphone_setup();
}

void inline MainEvent::onByteReceivedFromLaptop(int8_t b) {
    Command::runCommandFromByte(b);
}

void MainEvent::onSongTimerDepletion() {
    Speaker::stopSong();
}

void mic_core() {
    while (1) {
        usb_microphone_task();
    }
}

// Test code
void setup_gpios(void) {
    i2c_init(i2c1, 400000);
    gpio_set_function(2, GPIO_FUNC_I2C);
    gpio_set_function(3, GPIO_FUNC_I2C);
    gpio_pull_up(2);
    gpio_pull_up(3);
}


int main()
{
    MainEvent::initialiseMCU();
    current_state = State::SLEEP;

    multicore_launch_core1(mic_core);

    // OLED Testing
    char s[] = "Detecting";
    setup_gpios();
    ssd1306_t disp;
    disp.external_vcc=false;
    ssd1306_init(&disp, 128, 64, 0x3C, i2c1);
    ssd1306_clear(&disp);
    ssd1306_draw_string_with_font(&disp, 8, 24, 2, font_8x5, s);
    // Make functions for "detecting", "listening", "playing"
    ssd1306_show(&disp);

    while (true) {
        int8_t c = stdio_getchar_timeout_us(10);
        if (c != PICO_ERROR_TIMEOUT) {
            MainEvent::onByteReceivedFromLaptop(c);
        }
    }
}
