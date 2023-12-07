import cv2
import math
import keyboard as keyboard
import mediapipe as mp
import serial
import time
import threading as th

upCount = 0
cap = cv2.VideoCapture(0)
mpHands = mp.solutions.hands
hands = mpHands.Hands()
mpDraw = mp.solutions.drawing_utils
finger_Coord = [(8, 6), (12, 10), (16, 14), (20, 18)]
thumb_Coord = (4, 2)

com = "com7"  # nastaveni portu arduina
change = False
delay = 4
mode = 1


# distance - min: 2 max: 320 (me)


def arduinoWrite():
    global delay, change, mode
    arduinoSerial = serial.Serial(com, 9600)
    time.sleep(delay)
    if change is False:
        arduinoSerial.write(bytes(str(upCount), 'UTF-8'))
        print(upCount)
        if upCount is 1 or upCount is 2:
            delay = 1000
            mode = upCount
            change = True

    else:
        arduinoSerial.write(bytes(str(distance), 'UTF-8'))
        print(distance)
        if (distance < 30 and mode == 1) or (distance > 50 and mode == 2):
            delay = 4000
            change = False
    return


t1 = th.Thread(target=arduinoWrite, )
t1.start()


while True:
    success, image = cap.read()
    imageRGB = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
    results = hands.process(imageRGB)
    multiLandMarks = results.multi_hand_landmarks
    # checking whether a hand is detected

    if results.multi_hand_landmarks:
        handList = []

        for handLms in results.multi_hand_landmarks:  # working with each hand
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

                distance = math.sqrt(pow(handList[8][0] - handList[4][0], 2) + pow(handList[8][1] - handList[4][1], 2))

                print("--------")
                print(handList[7])
                print(handList[3])
                print("---------")
                # print(abs(distance))

                cv2.circle(image, handList[8], 25, (255, 0, 255), cv2.FILLED)
                cv2.circle(image, handList[4], 25, (255, 0, 255), cv2.FILLED)

                mpDraw.draw_landmarks(image, handLms, mpHands.HAND_CONNECTIONS)
    cv2.imshow("Output", image)
    cv2.waitKey(1)
    if keyboard.is_pressed("q") or keyboard.is_pressed("esc"):
        #  ArduinoSerial.close()
        break
