// Pico Defines
#include "pico/cyw43_arch.h"

// C Defines
#include "common.h"
#include "speaker/speaker.h"
#include "states.h"
#include "main_event.h"
#include "timers/timer.h"
#include "command/command.h"

// Temporary includes for testing
#include "command/command_list.h"

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
        
            // A command has been received so stop the timer 
            //  which waits for a command.
            Timer::stopWaitForCommandTimer();  
        
        case State::TRANSMIT:
            // Send byte to laptop to interpret
            //transferByteToLaptop(byte);
            Timer::startLaptopTransmissionTimer();
    }
}

void MainEvent::onJarvisVoiceDetected() {
    
    // Transition to WAIT state while waiting for the next voice transmission
    current_state = State::WAIT;
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    Timer::startWaitForCommandTimer();
}

void inline MainEvent::onByteReceivedFromLaptop(int8_t b) {
    Command::runCommandFromByte(b);
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

    sleep_ms(5000);
    MainEvent::onJarvisVoiceDetected();

    sleep_ms(5000);
    MainEvent::onJarvisVoiceDetected();
    MainEvent::onByteReceivedFromLaptop(1);
    sleep_ms(2500);
    MainEvent::onByteReceivedFromLaptop(CommandIndex::STOP_SONG);
    
    for (uint8_t i=1; i<6; i++) {
        sleep_ms(5000);
        MainEvent::onJarvisVoiceDetected();
        MainEvent::onByteReceivedFromLaptop(i);
    }

    while (true) {
    }
}
