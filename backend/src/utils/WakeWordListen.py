import openwakeword
import pyaudio
import numpy as np

openwakeword.utils.download_models()

def listenForWakeWord(threshold = 0.95):
    model = openwakeword.Model(wakeword_models=["hey jarvis"]
)
    # Model expects 1x16x96 sample size
    CHUNK = 1536
    FORMAT = pyaudio.paInt16
    # Mono
    CHANNELS = 1
    # 16 kHz
    RATE = 16000

    p = pyaudio.PyAudio()
    stream = p.open(format=FORMAT,
                    channels=CHANNELS,
                    rate=RATE,
                    input=True,
                    frames_per_buffer=CHUNK,
                    input_device_index=0)

    print("Listening for Hey Jarvis...")

    try:
        while True:
            audio_data = stream.read(CHUNK, exception_on_overflow=False)
            audio_np = np.frombuffer(audio_data, dtype=np.int16)
            # openwakeword expects 1D numpy array of int16
            predictions = model.predict(audio_np)

            if predictions.get("hey jarvis", 0) > threshold:
                print(f"Wake word detected! (Confidence: {predictions['hey jarvis']:.2f})")
                stream.stop_stream()
                stream.close()
                p.terminate()
                return True
    except KeyboardInterrupt:
        print("Stopping...")
        stream.stop_stream()
        stream.close()
        p.terminate()
        return False
    finally:
        stream.stop_stream()
        stream.close()
        p.terminate()

listenForWakeWord()
