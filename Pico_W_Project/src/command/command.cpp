#include "../common.h"
#include "command.h"
#include "command_list.h"
#include "../speaker/speaker.h"

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
    }
}