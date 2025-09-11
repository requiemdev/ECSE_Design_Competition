#include "../common.h"
#include "speaker.h"
#include "../timers/timer.h"

#include <stdlib.h>
#include <time.h>

uint8_t const songCounts[] = FOLDER_SONG_COUNTS;
volatile int8_t volume = 0;

volatile uint8_t receiveData[SPEAKER_UART_RX_BYTE_COUNT];
volatile uint8_t receive_index = 0;
volatile bool receiving_command = false;

volatile uint8_t current_folder = 0;
volatile uint8_t current_song = 0;

void Speaker::initialise(uint8_t v) {
    uart_init(SPEAKER_UART_ID, SPEAKER_BAUD_RATE);
    gpio_set_function(SPEAKER_UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(SPEAKER_UART_RX_PIN, GPIO_FUNC_UART);
    srand((unsigned int)time(NULL));
    Speaker::setVolume(v);  
    
    // Set up interrupt for receiving data
    irq_set_exclusive_handler(UART1_IRQ, onUartRX);
    //irq_set_enabled(UART1_IRQ, true);
    uart_set_irq_enables(SPEAKER_UART_ID, true, false); 
}


void Speaker::onUartRX() {
    while (uart_is_readable(SPEAKER_UART_ID)) {
        receiveData[receive_index] = uart_getc(SPEAKER_UART_ID);
        receive_index ++;
        if (receive_index >= SPEAKER_UART_RX_BYTE_COUNT) {
            receive_index = 0;
            receiving_command = false;
        }
    }
}

void Speaker::sendCommand(uint8_t cmd, uint8_t data_1, uint8_t data_2) {
    uart_putc(SPEAKER_UART_ID, 0x7E);
    uart_putc(SPEAKER_UART_ID, 0xFF);
    uart_putc(SPEAKER_UART_ID, 0x06);
    uart_putc(SPEAKER_UART_ID, cmd);
    uart_putc(SPEAKER_UART_ID, 0x00);
    uart_putc(SPEAKER_UART_ID, data_1);
    uart_putc(SPEAKER_UART_ID, data_2);
    uart_putc(SPEAKER_UART_ID, 0xEF);
}

void inline Speaker::sendEmptyCommand(uint8_t cmd) {
    Speaker::sendCommand(cmd, 0x00, 0x00);
}

void Speaker::sendQueryCommand(uint8_t cmd) {
    irq_set_enabled(UART1_IRQ, true);
    receiving_command = true;
    Speaker::sendEmptyCommand(cmd);
    while (receiving_command) {
    }
    irq_set_enabled(UART1_IRQ, false);
}


uint8_t Speaker::getReceivedCommand() {
    return receiveData[3];
}


uint8_t Speaker::getReceivedDataByte1() {
    return receiveData[5];
}


uint8_t Speaker::getReceivedDataByte2() {
    return receiveData[6];
}


void inline Speaker::sleep() {
    Speaker::sendEmptyCommand(0x0A);
}

void inline Speaker::wakeUp() {
    Speaker::sendEmptyCommand(0x0B);
}

void Speaker::playSong(uint8_t folder, uint8_t song) {
    Speaker::sendCommand(0x0F, folder, song);
    current_folder = folder;
    current_song = song;
    Timer::startSongTimer();
}

void Speaker::pauseSong() {
    Speaker::sendEmptyCommand(0x0E);
    Timer::stopSongTimer();
}

void Speaker::continueSong() {
    Speaker::sendEmptyCommand(0x0D);
    Timer::startSongTimer();
}

void Speaker::nextSong() {
    Speaker::sendEmptyCommand(0x01);
    current_song ++;
    Timer::startSongTimer();
}

void Speaker::previousSong() {
    Speaker::sendEmptyCommand(0x02);
    current_song --;
    Timer::startSongTimer();
}

void Speaker::stopSong() {
    Speaker::sendEmptyCommand(0x16);
    Timer::stopSongTimer();
}

void Speaker::setVolume(uint8_t v) {
    if (v > SPEAKER_MAX_VOLUME) {
        v = SPEAKER_MAX_VOLUME;
    }
    Speaker::sendCommand(0x06, 0x00, v);
    volume = v;
}

void Speaker::changeVolume(int8_t dv) {
    int8_t new_volume = volume + dv;
    if (new_volume < 0) {
        Speaker::setVolume(0);
        return;
    } else if (new_volume > SPEAKER_MAX_VOLUME) {
        Speaker::setVolume(SPEAKER_MAX_VOLUME);
        return;
    }
    Speaker::setVolume(new_volume);
}

uint8_t Speaker::isPlaying() {
    Speaker::sendQueryCommand(0x42);
    return Speaker::getReceivedDataByte2();
}

void Speaker::queryActiveSong(uint8_t* folder, uint8_t* song) {
    if (Speaker::isPlaying()) {
        *folder = current_folder;
        *song = current_song;
    } else {
        *folder = 0;
        *song = 0;
    }

}

void Speaker::playRandomSong() {
    // Select random song
    uint8_t random_song = rand() % TOTAL_SONGS;

    // Find song in the folder structure
    uint8_t f_index = 0;
    uint8_t songs_checked = 0;
    while (songs_checked <= random_song) {
        songs_checked += songCounts[f_index];
        f_index ++;
    }

    // The song was in the previous folder so play that one.
    Speaker::playSong(f_index, (random_song - (songs_checked - songCounts[f_index - 1]) + 1));
    Timer::startSongTimer();
}

void Speaker::playRandomSongInFolder(uint8_t folder) {
    
    uint8_t f_index = folder - 1;

    // Check that the folder is in the range of allowed folders
    //  and that there is at least one song in the foler
    if (f_index >= USED_FOLDER_COUNT) {
        return;
    }
    if (songCounts[f_index] == 0) {
        return;
    }

    // Play a random song in this folder
    Speaker::playSong(folder, (rand() % songCounts[f_index]) + 1);
    Timer::startSongTimer();
}