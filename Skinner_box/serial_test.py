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
	for i in range(20):
		time.sleep(2)
		ser.write('b'.encode('utf-8'))
		state	= int(ser.read())
		reward	= int(ser.read())
		print('state:' , state,'reward:' , reward)
	ser.close()

if __name__ == "__main__":
	main()