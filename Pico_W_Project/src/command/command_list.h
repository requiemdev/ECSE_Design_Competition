#ifndef COMMAND_LIST_H
#define COMMAND_LIST_H

enum CommandIndex {
    NULL_COMMAND = 0,
    STOP_SONG = -3,
    WAKE_UP_TOY = -4,
    SLEEP_TOY = -5,
    PAUSE_SONG = -6,
    CONTINUE_SONG = -7,
    NEXT_SONG = -8,
    PREV_SONG = -9,
    QUERY_SONG = -10
};

#endif //COMMAND_LIST_H