import serial
import time
ser = serial.Serial('COM3', 9600)

with open('E:\SolarTracker\write_data.txt', 'w') as file:
    while True:
        data = ser.readline().decode().strip()
        file.write(data + '\n')
        print('Data written:', data)
        time.sleep(1)
