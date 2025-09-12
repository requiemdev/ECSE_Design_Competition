import serial

ser = serial.Serial('COM6', 115200)  # Change COM3 to your Pico's port
ser.write(bytes({251})) # = -5
ser.close()