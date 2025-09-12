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
#include "hardware/pwm.h"

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

    // PWM Testing

    gpio_set_function(0, GPIO_FUNC_PWM);
    gpio_set_function(1, GPIO_FUNC_PWM);

    // Find out which PWM slice is connected to GPIO 0 (it's slice 0)
    uint slice_num = pwm_gpio_to_slice_num(0);

    // Set period of 4 cycles (0 to 3 inclusive)
    pwm_set_wrap(slice_num, 3);
    // Set channel A output high for one cycle before dropping
    pwm_set_chan_level(slice_num, PWM_CHAN_A, 1);
    // Set initial B output high for three cycles before dropping
    pwm_set_chan_level(slice_num, PWM_CHAN_B, 3);
    // Set the PWM running
    pwm_set_enabled(slice_num, true);

    multicore_launch_core1(mic_core);

    while (true) {
        int8_t c = stdio_getchar_timeout_us(10);
        if (c != PICO_ERROR_TIMEOUT) {
            MainEvent::onByteReceivedFromLaptop(c);
        }
    }
}
