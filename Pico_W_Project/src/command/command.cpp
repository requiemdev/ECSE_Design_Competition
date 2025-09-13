#include "../common.h"
#include "command.h"
#include "command_list.h"
#include "../speaker/speaker.h"
#include "../main_event.h"

void Command::runCommandFromByte(int8_t byte) {
    // Shuffle folder with value specifed (if in range)
    if ((0 < byte) && (byte <= USED_FOLDER_COUNT)) {
        Speaker::folderCycle(byte);
    }
    
    // Do something else if byte < 0
    switch (byte) {
        case CommandIndex::STOP_SONG:
            Speaker::stopSong();
            return;        
        case CommandIndex::WAKE_UP_TOY:
            MainEvent::onToyWakeup();   
            return; 
        case CommandIndex::SLEEP_TOY:
            MainEvent::onToySleep(); 
            return; 
        case CommandIndex::PAUSE_SONG:
            Speaker::pauseSong();
            return;
        case CommandIndex::CONTINUE_SONG:
            Speaker::continueSong();
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