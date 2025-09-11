# Remove warn logging from console
import logging
logging.basicConfig(level=logging.ERROR)
logging.getLogger().setLevel(logging.ERROR)
logging.getLogger("root").setLevel(logging.ERROR)

import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'

import warnings
warnings.filterwarnings("ignore", category=UserWarning)

from utils import FacialRec, OpenAiResponse, WakeWordListen

def main():
    print("Backend running")

    try:
        while True:
            if WakeWordListen.listenForWakeWord():
                print("Wakeword detected, detecting face")
                emotion = FacialRec.detectEmotion()
                print("Emotion detected: " + emotion)

                print("Awaiting OpenAi Response")
                res = OpenAiResponse.openAiResponse(emotion, "what a great day")
                print(res)
    except KeyboardInterrupt:
        print("Cancelled by user")
main()