#include "common.h"
#include "speaker.h"

#include <stdlib.h>
#include <time.h>

uint8_t const songCounts[] = FOLDER_SONG_COUNTS;
int8_t volume = 0;

void Speaker::speakerInitialise(uint8_t v) {
    uart_init(SPEAKER_UART_ID, SPEAKER_BAUD_RATE);
    gpio_set_function(SPEAKER_UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(SPEAKER_UART_RX_PIN, GPIO_FUNC_UART);
    srand((unsigned int)time(NULL));
    Speaker::speakerSetVolume(v);   
}

void Speaker::speakerSendCommand(uint8_t cmd, uint8_t data_1, uint8_t data_2) {
    uart_putc(SPEAKER_UART_ID, 0x7E);
    uart_putc(SPEAKER_UART_ID, 0xFF);
    uart_putc(SPEAKER_UART_ID, 0x06);
    uart_putc(SPEAKER_UART_ID, cmd);
    uart_putc(SPEAKER_UART_ID, 0x00);
    uart_putc(SPEAKER_UART_ID, data_1);
    uart_putc(SPEAKER_UART_ID, data_2);
    uart_putc(SPEAKER_UART_ID, 0xEF);
}

void Speaker::speakerSendEmptyCommand(uint8_t cmd) {
    Speaker::speakerSendCommand(cmd, 0x00, 0x00);
}

void Speaker::speakerPlaySong(uint8_t folder, uint8_t song) {
    Speaker::speakerSendCommand(0x0F, folder, song);
}

void Speaker::speakerPauseSong() {
    Speaker::speakerSendEmptyCommand(0x0E);
}

void Speaker::speakerContinueSong() {
    Speaker::speakerSendEmptyCommand(0x0D);
}

void Speaker::speakerNextSong() {
    Speaker::speakerSendEmptyCommand(0x01);
}

void Speaker::speakerPreviousSong() {
    Speaker::speakerSendEmptyCommand(0x02);
}

void Speaker::speakerStopSong() {
    Speaker::speakerSendEmptyCommand(0x16);
}

void Speaker::speakerSetVolume(uint8_t v) {
    if (v > SPEAKER_MAX_VOLUME) {
        v = SPEAKER_MAX_VOLUME;
    }
    Speaker::speakerSendCommand(0x06, 0x00, v);
    volume = v;
}

void Speaker::speakerChangeVolume(int8_t dv) {
    int8_t new_volume = volume + dv;
    if (new_volume < 0) {
        Speaker::speakerSetVolume(0);
        return;
    } else if (new_volume > SPEAKER_MAX_VOLUME) {
        Speaker::speakerSetVolume(SPEAKER_MAX_VOLUME);
        return;
    }
    Speaker::speakerSetVolume(new_volume);
}

void Speaker::speakerPlayRandomSong() {
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
    Speaker::speakerPlaySong(folder_index, random_song - (songs_checked - songCounts[folder_index - 1]) + 1);
}

void Speaker::speakerPlayRandomSongInFolder(uint8_t folder) {
    
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
    Speaker::speakerPlaySong(folder, rand() % songCounts[f_index-1] + 1);
}