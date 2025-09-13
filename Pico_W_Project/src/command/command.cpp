#include "../common.h"
#include "command.h"
#include "command_list.h"
#include "../speaker/speaker.h"

#include "pico/cyw43_arch.h"

void Command::runCommandFromByte(int8_t byte) {
    // Play a song if byte > 0
    if (byte > 3) {
        Speaker::playSong(2, byte - 3);
        return;
    } else if (byte > 0) {
        Speaker::playSong(1, byte);
        return;
    }
    
    // Do something else if byte < 0
    switch (byte) {
        case CommandIndex::STOP_SONG:
            Speaker::stopSong();
            return;        
        case CommandIndex::WAKE_UP_TOY:
            cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
            return; 
        case CommandIndex::SLEEP_TOY:
            cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
            return; 
        case CommandIndex::NEXT_SONG:
            Speaker::nextSong();
            return;
        case CommandIndex::PREV_SONG:
            Speaker::previousSong();
            return;
        case CommandIndex::QUERY_SONG:
            uint8_t folder, song;
            Speaker::queryActiveSong(&folder, &song);
            printf("Folder = %d, Song = %d", folder, song);      
            return;
    }
}