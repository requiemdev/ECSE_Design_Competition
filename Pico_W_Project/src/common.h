#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>
#include <stdio.h>
#include "pico/stdlib.h"

// Pins used (GPIO numbers)
#define OLED_PIN_1 2
#define OLED_PIN_2 3

#define SPEAKER_UART_TX_PIN 4
#define SPEAKER_UART_RX_PIN 5
#define SPEAKER_UART_ID uart1

/** GPIO Pin at which the microphone is connected to */
#define MICROPHONE_INPUT_PIN 26

/** GPIO pin which the status LED is connected to */
#define LED_STATUS_PIN 20

/** The starting volume of the speaker module */
#define SPEAKER_DEFAULT_VOLUME 30

// Timer durations
#define LED_BLINK_TIMER_DURATION_MS 500  // Half a period
#define LAPTOP_TRANSMISSION_TIMER_DURATION_S 30
#define SONG_TIMER_DURATION_S 150

#endif //COMMON_H