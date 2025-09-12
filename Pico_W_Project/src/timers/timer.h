#ifndef TIMER_H
#define TIMER_H

#include "../common.h"

namespace Timer {

    /** Automatically triggers when timer expires */
    int64_t songTimerTrigger(__unused alarm_id_t id, __unused void *user_data);

    /** Start or reset this timer */
    void startSongTimer();
    
    /** Stop this timer or do nothing if the timer is not going */
    void stopSongTimer();
}

#endif // TIMER_H