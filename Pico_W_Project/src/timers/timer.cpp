#include "timer.h"
#include "../main_event.h"

volatile alarm_id_t waitForCommandTimer;
volatile alarm_id_t laptopTransmissionTimer;
volatile alarm_id_t songTimer;

int64_t Timer::waitForCommandTimerTrigger(__unused alarm_id_t id, __unused void *user_data) {
    MainEvent::onWaitForCommandTimerDepletion();
    return 0;
}

int64_t Timer::laptopTransmissionTimerTrigger(__unused alarm_id_t id, __unused void *user_data) {
    MainEvent::onLaptopTransmissionTimerDepletion();
    return 0;
}

int64_t Timer::songTimerTrigger(__unused alarm_id_t id, __unused void *user_data) {
    MainEvent::onSongTimerDepletion();
    return 0;
}

void Timer::startWaitForCommandTimer() {
    Timer::stopWaitForCommandTimer();
    waitForCommandTimer = add_alarm_in_ms(WAIT_FOR_COMMAND_TIMER_DURATION_MS, Timer::waitForCommandTimerTrigger, NULL, true);
}

void Timer::stopWaitForCommandTimer() {
    cancel_alarm(waitForCommandTimer);
}  

void Timer::startLaptopTransmissionTimer() {
    Timer::stopLaptopTransmissionTimer();
    laptopTransmissionTimer = add_alarm_in_ms(LAPTOP_TRANSMISSION_TIMER_DURATION_MS, Timer::laptopTransmissionTimerTrigger, NULL, true);
}

void Timer::stopLaptopTransmissionTimer() {
    cancel_alarm(laptopTransmissionTimer);
}

void Timer::startSongTimer() {
    Timer::stopSongTimer();
    songTimer = add_alarm_in_ms(SONG_TIMER_DURATION_MS, Timer::songTimerTrigger, NULL, true);
}

void Timer::stopSongTimer() {
    cancel_alarm(songTimer);
}