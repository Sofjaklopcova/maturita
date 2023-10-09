import cv2
import keyboard as keyboard
import mediapipe as mp

cap = cv2.VideoCapture(0)
mpHands = mp.solutions.hands
hands = mpHands.Hands()
mpDraw = mp.solutions.drawing_utils
finger_Coord = [(8, 6), (12, 10), (16, 14), (20, 18)]
thumb_Coord = (4,2)

while True:
    success, image = cap.read()
    imageRGB = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
    results = hands.process(imageRGB)
    multiLandMarks = results.multi_hand_landmarks
    # checking whether a hand is detected

    if results.multi_hand_landmarks:
        handList = []

        for handLms in results.multi_hand_landmarks: # working with each hand
            for id, lm in enumerate(handLms.landmark):
                h, w, c = image.shape
                cx, cy = int(lm.x * w), int(lm.y * h)
                handList.append((cx, cy))
            if id == 20:
                upCount = 0
                for coordinate in finger_Coord:
                    if handList[coordinate[0]][1] < handList[coordinate[1]][1]:
                        upCount += 1
                if handList[thumb_Coord[0]][0] > handList[thumb_Coord[1]][0]:
                    upCount += 1
                print(upCount)

            mpDraw.draw_landmarks(image, handLms, mpHands.HAND_CONNECTIONS)
    cv2.imshow("Output", image)
    cv2.waitKey(1)
    if keyboard.is_pressed("q") or keyboard.is_pressed("esc"):
        break