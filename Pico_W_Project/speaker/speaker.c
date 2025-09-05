#include "common.h"
#include "speaker.h"

#include <stdlib.h>
#include <time.h>

uint8_t const songCounts[2] = FOLDER_SONG_COUNTS;

void speakerUartInit() {
    uart_init(SPEAKER_UART_ID, SPEAKER_BAUD_RATE);
    gpio_set_function(SPEAKER_UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(SPEAKER_UART_RX_PIN, GPIO_FUNC_UART);
}

void speakerSendCommand(uint8_t cmd, uint8_t data_1, uint8_t data_2) {
    uart_putc(SPEAKER_UART_ID, 0x7E);
    uart_putc(SPEAKER_UART_ID, 0xFF);
    uart_putc(SPEAKER_UART_ID, 0x06);
    uart_putc(SPEAKER_UART_ID, cmd);
    uart_putc(SPEAKER_UART_ID, 0x00);
    uart_putc(SPEAKER_UART_ID, data_1);
    uart_putc(SPEAKER_UART_ID, data_2);
    uart_putc(SPEAKER_UART_ID, 0xEF);
}

void speakerSendEmptyCommand(uint8_t cmd) {
    speakerSendCommand(cmd, 0x00, 0x00);
}

void speakerPlaySong(uint8_t folder, uint8_t song) {
    speakerSendCommand(0x0F, folder, song);
}

void speakerPauseSong() {
    speakerSendEmptyCommand(0x0E);
}

void speakerContinueSong() {
    speakerSendEmptyCommand(0x0D);
}

void speakerStopSong() {
    speakerSendEmptyCommand(0x16);
}

void speakerPlayRandomSong() {
    uint8_t const songCounts[USED_FOLDER_COUNT] = FOLDER_SONG_COUNTS;

    // Select random song
    srand((unsigned int)time(NULL));
    uint8_t random_song = rand() % TOTAL_SONGS;

    // Find song in the folder structure
    uint8_t folder_index = 0;
    uint8_t songs_checked = 0;
    while (songs_checked <= random_song) {
        songs_checked += songCounts[folder_index];
        folder_index ++;
    }

    // The song was in the previous folder so play that one.
    speakerPlaySong(folder_index, random_song - songs_checked + songCounts[folder_index - 1] + 1);
}