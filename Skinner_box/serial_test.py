# coding:utf-8
import serial
import os
import time

def main():
	ser = serial.Serial()
	ser.baudrate = 9600
	for file in os.listdir('/dev'):
		if "tty.usbmodem" in file:
			ser.port = '/dev/'+file
			ser.open()
	time.sleep(3)
	ser.write('b'.encode('utf-8'))
	time.sleep(3)
	ser.write('l'.encode('utf-8'))
	time.sleep(3)
	ser.write('b'.encode('utf-8'))
	time.sleep(3)
	input_char = ser.read_all()
	print(input_char)
	ser.close()

if __name__ == "__main__":
	main()