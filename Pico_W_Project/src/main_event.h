#ifndef MAIN_EVENT_H
#define MAIN_EVENT_H

namespace MainEvent {

    /** Initialise the MCU along with all 
     * peripherals which should be on at the start of the program. 
    */
    void initialiseMCU();


    /** This happens when the MCU receives a byte from the laptop. */
    void onByteReceivedFromLaptop(int8_t byte);

    /** When a song is started, a timer starts which allows the
    * song player to automatically stop after enough time of no 
    * commands heard.
    */
    void onSongTimerDepletion();

}

#endif // MAIN_EVENT_H