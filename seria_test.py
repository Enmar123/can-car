import serial
import time
import numpy
from time import sleep

ser = serial.Serial('/dev/ttyACM0',9600) 
s = [0,1]
sleep(.1)
q = (0,1)

while True:
	#read_serial=ser.readline()
	#s[0] = str(int (ser.readline(),16)) #16 = hexa!
	#print(s[0])
	#print(s)
	
	
	#data = ser.readline()
	#data = ser.readline()
	#sleep(.01)
	#print(data)
	data = str(int (ser.readline(),10))
	#sleep(.01)
	#if okay == False:						# Testing to see if fixes error
		#continue
	#print(data)
	data = int(data)
	print(data)
	
	mult = data/10
	
	if (mult).is_integer():
		print('Hey this number is a multiple of 10!')
	if(data == 10):
		print('Hey look a FRIGGING 10')
		
	
	#sleep(.01)
	
	#data = ser.readline()
	#print(data)
	
	#print(read_serial)

	#if( a == data):
		#print('hey look an a!!')
	
