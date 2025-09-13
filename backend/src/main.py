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
        # ser = serial.Serial('COM3', 115200)  # Change COM3 to your Pico's port
        while True:
            if WakeWordListen.listenForWakeWord():
                print("Wakeword detected, detecting speech")
                speech = SpeechRec.recogniseSpeech()

                if speech == "Error":
                    # ser.write(0)
                    print("Error")
                    continue
                print("Speech detected, detecting face")
                emotion = FacialRec.detectEmotion()
                print("Emotion detected: " + emotion)

                print("Awaiting OpenAi Response")
                res = OpenAiResponse.openAiResponse(emotion, speech)
                print(res)
    except KeyboardInterrupt:
        # ser.close()
        print("Cancelled by user")
main()