// Pico Defines
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
#include "pin_output/gpio.h"

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
volatile bool status_led_state = false;

void MainEvent::initialiseMCU() {
    stdio_init_all();
    #ifdef LED_STATUS_PIN
    GPIO::gpio_init_with_dir(LED_STATUS_PIN, 1);
    #endif
    #ifdef SPIN_PIN
    GPIO::gpio_init_with_dir(SPIN_PIN, 1);
    #endif
    Speaker::initialise(SPEAKER_DEFAULT_VOLUME);
    microphone_setup();
}

void MainEvent::onToyWakeup() {
    current_state = State::LISTENING;
    Timer::startLaptopTransmissionTimer();
    if (!song_playing) {
        Oled::displayIronMan();
        sleep_ms(2000);
        Oled::displayText(Oled_Message::LISTENING);
        Timer::startLedBlinkTimer();
    }
}

void MainEvent::onToySleep() {
    current_state = State::SLEEP;
    Timer::stopLaptopTransmissionTimer();
    if (!song_playing) {
        Oled::displayText(Oled_Message::DETECTING);
        Timer::stopLedBlinkTimer();
        status_led_state = 0;
        GPIO::gpio_set(LED_STATUS_PIN, 0);
    }
}

void MainEvent::onStatusLedTrigger() {
    status_led_state = !status_led_state;
    GPIO::gpio_set(LED_STATUS_PIN, status_led_state);
    Timer::startLedBlinkTimer();
}

void inline MainEvent::onByteReceivedFromLaptop(int8_t b) {
    Timer::startLaptopTransmissionTimer();
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
    Timer::stopLedBlinkTimer();
    status_led_state = 1;
    GPIO::gpio_set(LED_STATUS_PIN, 1);
    GPIO::gpio_set(SPIN_PIN, 1);
}

void MainEvent::onSongStopped() {
    Timer::stopSongTimer();
    if (current_state == State::SLEEP) {
        Oled::displayText(Oled_Message::DETECTING);
        status_led_state = 0;
        GPIO::gpio_set(LED_STATUS_PIN, 0);
    } else {
        Oled::displayText(Oled_Message::LISTENING);
        Timer::startLedBlinkTimer();
    }
    song_playing = false;
    GPIO::gpio_set(SPIN_PIN, 0);
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
