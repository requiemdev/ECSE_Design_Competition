from fer import FER
import cv2
import time


def detectEmotion():
    detector = FER(mtcnn=True)
    cap = cv2.VideoCapture(0)

    launch_time = time.time()

    while True:
        ret, frame = cap.read()
        cv2.imshow("image", frame)
        key = cv2.waitKey(1)
        if key == 27:  # ESC to exit
            break

        begin_time = time.time()
        # Run detection every second
        while time.time() - begin_time < 1:

            # Time out
            if time.time() - launch_time >= 15:
                cap.release()
                cv2.destroyAllWindows()
                print("No face detected, returning neutral")
                return "neutral"

            cv2.waitKey(1)
            ret, frame = cap.read()
            result = detector.detect_emotions(frame)
            if result:
                emotions = result[0]["emotions"]
                max_emotion = max(emotions, key=emotions.get)
                print(f"Detected emotion: {max_emotion} ({emotions[max_emotion]:.2f})")
                cap.release()
                cv2.destroyAllWindows()
                return max_emotion
    cap.release()
    cv2.destroyAllWindows()
    return None