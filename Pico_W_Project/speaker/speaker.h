#ifndef SPEAKER_H
#define SPEAKER_H

#define SPEAKER_BAUD_RATE 9600
#define SPEAKER_UART_ID uart1

// Use pins 4 and 5 for UART1
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define SPEAKER_UART_TX_PIN 4
#define SPEAKER_UART_RX_PIN 5

/* FOLDER_SONG_COUNTS used for random song selector.
*  The value in index i = song count in folder number i+1
*/
#define USED_FOLDER_COUNT 2
#define FOLDER_SONG_COUNTS {4, 2}
#define TOTAL_SONGS 6

/** Initialise the speaker UART using defines:
 *  SPEAKER_UART_ID,
 *  SPEAKER_UART_TX_PIN,
 *  SPEAKER_UART_RX_PIN
 */
void speakerUartInit();


/** Send a command through the uart to the speaker
 *  with id UART_SPEAKER_ID defined in common.h and
 *  two input data bits
 */
void speakerSendCommand(uint8_t command, uint8_t data_1, uint8_t data_2);

/** Send a command through the uart to the speaker
 *  with id UART_SPEAKER_ID defined in common.h and
 *  no input data bits
 */
void speakerSendEmptyCommand(uint8_t cmd);

/** Play specified song in memory.
 *  - directory[0] = folder
 *  - directory[1] = song number in folder
 */
void speakerPlaySong(uint8_t folder, uint8_t song);

/** Pause the currently playing song */
void speakerPauseSong();

/** Continue the song that was playing before pausing */
void speakerContinueSong();

/** Stop the currently playing song */
void speakerStopSong();

/** Select and play a random song in the speaker.
 * The input is an array containing the number of songs in each folder.
 * - Value in index i = number of songs in folder number i+1.
 */
void speakerPlayRandomSong();

#endif // SPEAKER_H