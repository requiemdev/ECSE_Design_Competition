#ifndef SPEAKER_H
#define SPEAKER_H

namespace Speaker {

    #define SPEAKER_BAUD_RATE 9600
    #define SPEAKER_UART_ID uart1

    // Use pins 4 and 5 for UART1
    // Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
    #define SPEAKER_UART_TX_PIN 4
    #define SPEAKER_UART_RX_PIN 5

    // The number of bytes sent by the speaker every time it sends data to the MCU
    #define SPEAKER_UART_RX_BYTE_COUNT 10

    /** The maximum volume allowed by the speaker */
    #define SPEAKER_MAX_VOLUME 30

    /* FOLDER_SONG_COUNTS used for random song selector.
    *  The value in index i = song count in folder number i+1
    *  These defines will change depending on what songs are in the speaker memory
    */
    #define USED_FOLDER_COUNT 2
    #define FOLDER_SONG_COUNTS {3, 2}
    #define TOTAL_SONGS 5

    /** Initialise the uart peripherals of the speaker and
     *   all other initialisations to be able to use the speaker.
     *  Volume = volume which the speaker should be set to <= 30
     */
    void initialise(uint8_t volume);

    /** This function happens when the UART receives a signal */
    void onUartRX();

    /** Send a command through the uart to the speaker
     *  with id UART_SPEAKER_ID defined in common.h and
     *  two input data bits
     */
    void sendCommand(uint8_t command, uint8_t data_1, uint8_t data_2);

    /** Send a command through the uart to the speaker
     *  with id UART_SPEAKER_ID defined in common.h and
     *  no input data bits
     */
    void sendEmptyCommand(uint8_t cmd);

    /** Send a command and listen for feedback from the command */
    void sendQueryCommand(uint8_t cmd);

    /** Get the command byte from the most recent received transmission */
    uint8_t getReceivedCommand();

    /** Get the high data byte from the most recent received transmission */
    uint8_t getReceivedDataByte1();

    /** Get the low data byte from the most recent received transmission */
    uint8_t getReceivedDataByte2();

    /** Sleep the speaker. Note that it will likely not be able to wake up. */
    void sleep();
    
    /** Wake up the speaker. This command does not seem to work */
    void wakeUp();

    /** Play specified song in memory.
     *  - directory[0] = folder.
     *      Folders start from 1 like in the speaker itself.
     *  - directory[1] = song number in folder.
     *      Song numbers start from 1 like in the speaker itself.
     */
    void playSong(uint8_t folder, uint8_t song);

    /** Pause the currently playing song */
    void pauseSong();

    /** Continue the song that was playing before pausing */
    void continueSong();

    /** Play the next song in the folder */
    void nextSong();

    /** Play the previous song in the folder */
    void previousSong();

    /** Stop the currently playing song */
    void stopSong();

    /** Change the volume to the specified value <= SPEAKER_MAX_VOLUME */
    void setVolume(uint8_t volume);

    /** Change the volume by the specified amount.
     *  If it would exceed the lower or upper limits (0 <= Volume <= SPEAKER_MAX_VOLUME),
     *   the volume is set to the limit instead
     */
    void changeVolume(int8_t volume_change);

    /** Returns: 
     * - 2 if there is a song that is paused
     * - 1 if there is a song playing
     * - 0 if there is no song playing
    */
   uint8_t isPlaying();

    /** Find the song currently being played and store its folder and song number details 
     * into the pointers folder and song. 
     * - Return (0,0) if there is no song currently playing
    */
    void queryActiveSong(uint8_t* folder, uint8_t* song);

    /** Select and play a random song in the speaker.
     *  This function depends on the defines 
     *      USED_FOLDER_COUNT, FOLDER_SONG_COUNTS & TOTAL_SONGS
     */
    void playRandomSong();

    /** Select and play a random song in a specified folder.
     *      Folders start from 1 like in the speaker itself.
     *  This function depends on the defines 
     *      USED_FOLDER_COUNT & FOLDER_SONG_COUNTS
     * 
     */
    void playRandomSongInFolder(uint8_t folder);

}

#endif // SPEAKER_H