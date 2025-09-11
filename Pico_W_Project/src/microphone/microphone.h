#ifndef MICROPHONE_H_
#define MICROPHONE_H_

#include "usb_microphone.h"

#include <stdio.h>
#include "analog_microphone.h"
#include "tusb.h"
#include "tusb_config.h"

extern const struct analog_microphone_config config;

/*
 * This function calls back from library when all the samples in the buffer are ready for reading
 */
void on_analog_samples_ready();

// callback functions
/*
 * This function calls back from TinyUSB library when all data is ready to be transmitted and 
 * writes local buffer to the USB microphone
 */
void on_usb_microphone_tx_ready();

/*
 * This function calls back from TinyUSB library when all data is ready to be transmitted and 
 * writes local buffer to the USB microphone
 */
void microphone_setup();

#endif
