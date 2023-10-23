import serial
import time
ser = serial.Serial('COM3', 9600)
def send_angles_from_file():
    with open('E:\SolarTracker\azimuth_elevation_writefile.txt', 'r') as file:
        for line in file:
            azimuth, elevation = map(float, line.strip().split(','))
            angles_string = f'{azimuth},{elevation}\n'
            ser.write(angles_string.encode())
            print("Angles sent successfully")
            print('Angles sent:', angles_string.strip())
            time.sleep(2)
send_angles_from_file()
ser.close()
