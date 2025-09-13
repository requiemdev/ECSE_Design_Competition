import serial

ser = serial.Serial('COM6', 115200)  # Change COM3 to your Pico's port
<<<<<<< HEAD
ser.write(bytes({253})) # 251 = -5
=======
ser.write(bytes([251])) # = -5
>>>>>>> main
ser.close()