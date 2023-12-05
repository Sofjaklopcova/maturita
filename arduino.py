import serial
import time
com = "com6" # nastaveni portu arduina


ArduinoSerial = serial.Serial(com, 9600)
time.sleep(2)
# ArduinoSerial.readline() - cteni z arduina
# ArduinoSerial.write('1') - poslani do arduina
print("uvodni pozdrav")

while 1:
    user_input = input()
    if (user_input == '1'):
        time.sleep(1)
        ArduinoSerial.write(bytes('1', 'UTF-8'))



    if(user_input == '0'):
        ArduinoSerial.write(bytes('0', 'UTF-8'))
        time.sleep(1)


# ArduinoSerial.close()