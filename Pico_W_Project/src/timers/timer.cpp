#include "timer.h"
#include "../main_event.h"

volatile alarm_id_t songTimer;

int64_t Timer::songTimerTrigger(__unused alarm_id_t id, __unused void *user_data) {
    MainEvent::onSongTimerDepletion();
    return 0;
}

void Timer::startSongTimer() {
    Timer::stopSongTimer();
    songTimer = add_alarm_in_ms(SONG_TIMER_DURATION_MS, Timer::songTimerTrigger, NULL, true);
}

void Timer::stopSongTimer() {
    cancel_alarm(songTimer);
}