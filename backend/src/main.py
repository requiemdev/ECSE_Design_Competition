# Remove warn logging from console
import logging
logging.basicConfig(level=logging.ERROR)
logging.getLogger().setLevel(logging.ERROR)
logging.getLogger("root").setLevel(logging.ERROR)

import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'

import warnings
warnings.filterwarnings("ignore", category=UserWarning)

from utils import FacialRec, OpenAiResponse, WakeWordListen, SpeechRec
import serial

def main():
    print("Backend running")

    try:
        port = 'COM6' # Change serial port accordingly
        ser = serial.Serial(port, 115200)
        print("Connected to:" + port)
        while True:
            if WakeWordListen.listenForWakeWord():
                ser.write(bytes([252]))
                print("Wakeword detected, detecting speech")
                speech = SpeechRec.recogniseSpeech()
                if speech == "Error":
                    ser.write(0)
                    print("Error")
                    continue
                print("Speech detected, detecting face")
                emotion = FacialRec.detectEmotion()
                print("Emotion detected: " + emotion)

                print("Awaiting OpenAi Response")
                res = OpenAiResponse.openAiResponse(emotion, speech)
                if (res == "Neutral"):
                    ser.write(bytes([6]))
                elif(res == "Surprised"):
                    ser.write(bytes([5]))
                elif(res == "Fear"):
                    ser.write(bytes([4]))
                elif(res == "Sad"):
                    ser.write(bytes([3]))
                elif(res == "Happy"):
                    ser.write(bytes([2]))
                elif(res == "Angry"):
                    ser.write(bytes([1]))
                elif(res == "Stop"):
                    ser.write(bytes([253]))
                elif(res == "Sleep"):
                    ser.write(bytes([251]))
                elif(res == "Pause"):
                    ser.write(bytes([250]))
                elif(res == "Continue"):
                    ser.write(bytes([249]))
                elif(res == "Next"):
                    ser.write(bytes([248]))
                elif(res == "Preious"):
                    ser.write(bytes([247]))

    except KeyboardInterrupt:
        ser.close()
        print("Cancelled by user")
main()