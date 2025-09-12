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

#ifdef __cplusplus
}
#endif


// Temporary includes for testing
#include "command/command_list.h"

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

int main()
{
    MainEvent::initialiseMCU();
    current_state = State::SLEEP;

    // Have some code to simulate functions being called

    // sleep_ms(5000);
    // MainEvent::onByteReceivedFromLaptop(1);
    // sleep_ms(2500);
    // MainEvent::onByteReceivedFromLaptop(CommandIndex::STOP_SONG);
    
    // for (uint8_t i=1; i<6; i++) {
    //     sleep_ms(5000);
    //     MainEvent::onByteReceivedFromLaptop(i);
    // }

    // sleep_ms(10000);

    // uint8_t folder, file;
    // for (uint8_t i=1; i<6; i++) {
    //     MainEvent::onByteReceivedFromLaptop(i);
    //     sleep_ms(1000);
    //     Speaker::queryActiveSong(&folder, &file);
    //     printf("Folder: %d, Song: %d\n", folder, file);
    //     sleep_ms(1000);
    // }

    // printf("going through serial...");

    multicore_launch_core1(mic_core);

    uint8_t d;
    uint8_t negative = 0;
    while (true) {
        int c = stdio_getchar_timeout_us(10);
        if ((c != PICO_ERROR_TIMEOUT) && (c != 0)) {
            d = c - '0';
            printf("received packet %c", c);
            if (c == '-') {
                negative = 1;
            } else if ((0 < d) && (d < 5) && (negative)) {
                MainEvent::onByteReceivedFromLaptop(-d);
                negative = 0;
            } else if ((0 < d) && (d < 5)) {
                MainEvent::onByteReceivedFromLaptop(d);
            }
        }
    }
}
