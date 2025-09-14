#include "timer.h"
#include "../main_event.h"

volatile alarm_id_t laptopTransmissionTimer;
volatile alarm_id_t songTimer;

int64_t Timer::laptopTransmissionTimerTrigger(__unused alarm_id_t id, __unused void *user_data) {
    MainEvent::onLaptopTransmissionTimerDepletion();
    return 0;
}

void Timer::startLaptopTransmissionTimer() {
    Timer::stopLaptopTransmissionTimer();
    laptopTransmissionTimer = add_alarm_in_ms(LAPTOP_TRANSMISSION_TIMER_DURATION_S * (uint32_t(1000)), Timer::laptopTransmissionTimerTrigger, NULL, true);
}

void Timer::stopLaptopTransmissionTimer() {
    cancel_alarm(laptopTransmissionTimer);
}

int64_t Timer::songTimerTrigger(__unused alarm_id_t id, __unused void *user_data) {
    MainEvent::onSongTimerDepletion();
    return 0;
}

void Timer::startSongTimer() {
    Timer::stopSongTimer();
    songTimer = add_alarm_in_ms(SONG_TIMER_DURATION_S * (uint32_t(1000)), Timer::songTimerTrigger, NULL, true);
}

void Timer::stopSongTimer() {
    cancel_alarm(songTimer);
}