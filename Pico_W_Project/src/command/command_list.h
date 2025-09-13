#ifndef COMMAND_LIST_H
#define COMMAND_LIST_H

enum CommandIndex {
    NULL_COMMAND = 0,
    STOP_SONG = -3,
    WAKE_UP_TOY = -4,
    SLEEP_TOY = -5,
    NEXT_SONG = -6,
    PREV_SONG = -7,
    QUERY_SONG = -8
};

#endif //COMMAND_LIST_H