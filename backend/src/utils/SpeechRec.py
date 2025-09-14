import speech_recognition as sr

def recogniseSpeech(timeout=5, phrase_time_limit=20):
    r = sr.Recognizer()

    with sr.Microphone() as source:
        r.adjust_for_ambient_noise(source, duration=1)
        try:
            audio = r.listen(source, timeout=timeout, phrase_time_limit=phrase_time_limit)
        except sr.WaitTimeoutError:
            print("Listening timed out while waiting for phrase to start")
            return "Error"

    try:
        text = r.recognize_google(audio)
        print(text)
        return text
    except sr.UnknownValueError:
        return "Error"
    except sr.RequestError as e:
        return "Error"