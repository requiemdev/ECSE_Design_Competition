#ifndef TIMER_H
#define TIMER_H

#include "../common.h"

#define WAIT_FOR_COMMAND_TIMER_DURATION_MS 20000
#define LAPTOP_TRANSMISSION_TIMER_DURATION_MS 20000
#define SONG_TIMER_DURATION_MS 20000

namespace Timer {

    int64_t waitForCommandTimerTrigger(__unused alarm_id_t id, __unused void *user_data);
    
    int64_t laptopTransmissionTimerTrigger(__unused alarm_id_t id, __unused void *user_data);
    
    int64_t songTimerTrigger(__unused alarm_id_t id, __unused void *user_data);

    void startWaitForCommandTimer();
    void stopWaitForCommandTimer();  

    void startLaptopTransmissionTimer();
    void resetLaptopTransmissionTimer();
    void stopLaptopTransmissionTimer();

    void startSongTimer();
    void resetSongTimer();
    void stopSongTimer();
}

#endif // TIMER_H