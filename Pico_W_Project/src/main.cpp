// Pico Defines
#include "pico/cyw43_arch.h"

// C Defines
#include "common.h"
#include "speaker/speaker.h"
#include "states.h"
#include "main_event.h"
#include "timers/timer.h"

// Global Variables
volatile bool song_playing = true;
volatile State current_state = State::SLEEP;

void MainEvent::initialiseMCU() {
    stdio_init_all();
    Speaker::initialise(SPEAKER_DEFAULT_VOLUME);
        // Also start microphone listening
        cyw43_arch_init();
}

void MainEvent::onByteReceivedFromMicrophone(uint8_t byte) {
    switch (current_state) {
        case State::SLEEP:
            // checkInputForJarvis();
            break;
        case State::WAIT: 
            current_state = State::TRANSMIT;   
            //startLaptopTransmission();
            Timer::startLaptopTransmissionTimer();
        
            // A command has been received so stop the timer 
            //  which waits for a command.
            Timer::stopWaitForCommandTimer();  
        case State::TRANSMIT:
            // Send byte to laptop to interpret
            //transferByteToLaptop(byte);
            Timer::resetLaptopTransmissionTimer();
    }
}

void MainEvent::onJarvisVoiceDetected() {
    
    // Transition to WAIT state while waiting for the next voice transmission
    current_state = State::WAIT;
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    Timer::startWaitForCommandTimer();
}

void MainEvent::onWaitForCommandTimerDepletion() {
    current_state = State::SLEEP;
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
    Timer::stopLaptopTransmissionTimer();
}


void MainEvent::onLaptopTransmissionTimerDepletion() {
    // Transition to WAIT state while waiting for the next 
    //  voice transmission
    current_state = State::WAIT;
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    
    Timer::startWaitForCommandTimer();
    //stopLaptopTransmission();
    }


void MainEvent::onSongTimerDepletion() {
    Speaker::stopSong();
}


int main()
{
    MainEvent::initialiseMCU();
    current_state = State::SLEEP;

    // Have some code to simulate functions being called

    sleep_ms(10000);
    MainEvent::onJarvisVoiceDetected();

    while (true) {
    }
}
