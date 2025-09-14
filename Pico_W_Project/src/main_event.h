#ifndef MAIN_EVENT_H
#define MAIN_EVENT_H

namespace MainEvent {

    /** Initialise the MCU along with all 
     * peripherals which should be on at the start of the program. 
    */
    void initialiseMCU();

    /** This happens when the toy starts listening and controls wake up movements */
    void onToyWakeup();

    /** This happens when the toy stops listening and reverses wake up movements */
    void onToySleep();

    /** This happens when the timer controlling the LED blinking stops and the LED switches states */
    void onStatusLedTrigger();

    /** This happens when the MCU receives a byte from the laptop. */
    void onByteReceivedFromLaptop(int8_t byte);

    /** This happens when the Laptop Transmission timer runs out.
    *  In other words, nothing has been heard from the MCU for a 
    *  long time after it started transmitting sound data to the 
    *  laptop. 
    */
    void onLaptopTransmissionTimerDepletion();

    /** When a song is started, a timer starts which allows the
    * song player to automatically stop after enough time of no 
    * commands heard.
    */
    void onSongTimerDepletion();

    /** This code is executed when a song starts playing on the speaker */
    void onSongStarted();

    /** This code is executed when the currently playing song is stopped on the speaker */
    void onSongStopped();

}

#endif // MAIN_EVENT_H