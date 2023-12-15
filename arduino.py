import serial
import time
com = "com7" # nastaveni portu arduina


ArduinoSerial = serial.Serial(com, 9600,timeout=0.05)
time.sleep(2)
# ArduinoSerial.readline() - cteni z arduina
# ArduinoSerial.write('1') - poslani do arduina
print("uvodni pozdrav")

while 1:
    user_input = input()

    ArduinoSerial.write(bytes(str(user_input), 'UTF-8'))






# ArduinoSerial.close()