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
#include "oled/oled.h"
#include "oled/oled_messages.h"

// C Defines
#ifdef __cplusplus
extern "C" {
#endif

#include "microphone.h"
#include "usb_microphone.h"

#ifdef __cplusplus
}
#endif

// Temporary includes for testing


// Global Variables
volatile bool song_playing = false;
volatile State current_state = State::SLEEP;

void MainEvent::initialiseMCU() {
    stdio_init_all();
    Speaker::initialise(SPEAKER_DEFAULT_VOLUME);
    cyw43_arch_init();
    microphone_setup();
}

void MainEvent::onToyWakeup() {
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    current_state = State::LISTENING;
    if (!song_playing) {
        Oled::displayIronMan();
        sleep_ms(2000);
        Oled::displayText(Oled_Message::LISTENING);
    }
}

void MainEvent::onToySleep() {
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
    current_state = State::SLEEP;
    if (!song_playing) {
        Oled::displayText(Oled_Message::DETECTING);
    }
}

void inline MainEvent::onByteReceivedFromLaptop(int8_t b) {
    Command::runCommandFromByte(b);
}

void MainEvent::onLaptopTransmissionTimerDepletion() {
    // Transition to SLEEP state while waiting for the next 
    //  voice transmission
    MainEvent::onToySleep();
}

void MainEvent::onSongTimerDepletion() {
    Speaker::stopSong();
}

void MainEvent::onSongStarted() {
    Timer::startSongTimer();
    song_playing = true;
    Oled::displayText(Oled_Message::PLAYING);
}

void MainEvent::onSongStopped() {
    Timer::stopSongTimer();
    if (current_state == State::SLEEP) {
        Oled::displayText(Oled_Message::DETECTING);
    } else {
        Oled::displayText(Oled_Message::LISTENING);
    }
    song_playing = false;
}

void mic_core() {
    while (1) {
        usb_microphone_task();
    }
}

int main()
{
    MainEvent::initialiseMCU();
    current_state = State::SLEEP;

    multicore_launch_core1(mic_core);

    Oled::initialise(OLED_PIN_1, OLED_PIN_2);
    Oled::displayText(Oled_Message::DETECTING);

    while (true) {
        int8_t c = stdio_getchar_timeout_us(10);
        if (c != PICO_ERROR_TIMEOUT) {
            MainEvent::onByteReceivedFromLaptop(c);
        }
    }
}
