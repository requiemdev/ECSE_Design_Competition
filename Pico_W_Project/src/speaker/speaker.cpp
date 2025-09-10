#include "../common.h"
#include "speaker.h"

#include <stdlib.h>
#include <time.h>

uint8_t const songCounts[] = FOLDER_SONG_COUNTS;
volatile int8_t volume = 0;

void Speaker::initialise(uint8_t v) {
    uart_init(SPEAKER_UART_ID, SPEAKER_BAUD_RATE);
    gpio_set_function(SPEAKER_UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(SPEAKER_UART_RX_PIN, GPIO_FUNC_UART);
    srand((unsigned int)time(NULL));
    Speaker::setVolume(v);   
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

void Speaker::sendEmptyCommand(uint8_t cmd) {
    Speaker::sendCommand(cmd, 0x00, 0x00);
}

void Speaker::playSong(uint8_t folder, uint8_t song) {
    Speaker::sendCommand(0x0F, folder, song);
}

void Speaker::pauseSong() {
    Speaker::sendEmptyCommand(0x0E);
}

void Speaker::continueSong() {
    Speaker::sendEmptyCommand(0x0D);
}

void Speaker::nextSong() {
    Speaker::sendEmptyCommand(0x01);
}

void Speaker::previousSong() {
    Speaker::sendEmptyCommand(0x02);
}

void Speaker::stopSong() {
    Speaker::sendEmptyCommand(0x16);
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

void Speaker::playRandomSong() {
    // Select random song
    uint8_t random_song = rand() % TOTAL_SONGS;

    // Find song in the folder structure
    uint8_t folder_index = 0;
    uint8_t songs_checked = 0;
    while (songs_checked <= random_song) {
        songs_checked += songCounts[folder_index];
        folder_index ++;
    }

    // The song was in the previous folder so play that one.
    Speaker::playSong(folder_index, random_song - (songs_checked - songCounts[folder_index - 1]) + 1);
}

void Speaker::playRandomSongInFolder(uint8_t folder) {
    
    uint8_t f_index = folder - 1;

    // Check that the folder is in the range of allowed folders
    //  and that there is at least one song in the foler
    if (f_index >= USED_FOLDER_COUNT) {
        return;
    }
    if (songCounts[f_index-1] == 0) {
        return;
    }

    // Play a random song in this folder
    Speaker::playSong(folder, rand() % songCounts[f_index-1] + 1);
}