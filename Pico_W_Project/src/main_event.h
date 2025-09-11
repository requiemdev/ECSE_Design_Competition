#ifndef MAIN_EVENT_H
#define MAIN_EVENT_H

namespace MainEvent {

    /** Initialise the MCU along with all 
     * peripherals which should be on at the start of the program. 
    */
    void initialiseMCU();

    /** This will be constantly happening while the microphone 
     *  input into the MCU is on
    */
    void onByteReceivedFromMicrophone(uint8_t byte);

    /** This happens when the MCU detects "Hey Jarvis" from the 
    *  microphone while in SLEEP state
    */
    void onJarvisVoiceDetected();

    /** This happens when the MCU receives a byte from the laptop. */
    void onByteReceivedFromLaptop(int8_t byte);

    /** This happens when the Wait For Command timer runs out.
    *  In other words, no input has been heard by the MCU for a //  long time after the MCU has started listening.
    */ 
    void onWaitForCommandTimerDepletion();
    
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

}

#endif // MAIN_EVENT_H