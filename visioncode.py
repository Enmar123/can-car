#!/usr/bin/env python3
# EML ???? Smart Machine Design and Development
# Florida International University
# Department of Mechanical and Materials Engineering
# Jason Soto <jsoto103@fiu.edu>
# Miami, Spring 2018

# USER INPUTS ----------------------------------------------------------
frame_w_pix = 640
frame_h_pix = 480
#pix_width  = 640
#pix_height = 480

safezone_pix = 100

hudcolor = (255,255,255)

# PROGRAM SETUP --------------------------------------------------------
 
import cv2 as cv
import numpy as np
import time

# RASPI AND ARDUCAM
from picamera.array import PiRGBArray
from picamera import PiCamera
import serial

ser = serial.Serial('/dev/ttyACM0',9600)



# FUNCTIONS ------------------------------------------------------------

# Define function that computes centroid of monochrome blob (mask)
def centroid( mask ):
	M = cv.moments(mask,True)
	m00 = M['m00']
	if m00 == 0: # Ops, don't want divide by zero!
		x = -100 
		y = -100
	else:
		x = int( M['m10']/m00 )
		y = int( M['m01']/m00 )
	return x,y

def weightfcn( x ):
	offset = 1*x - 640/2
	weight = int( offset * 255/(640/2) )
	return weight
	

# PRIMARY LOOP --------------------------------------------------------- 

camera = PiCamera()
camera.vflip = True
camera.resolution = (frame_w_pix, frame_h_pix)
camera.framerate = 24
rawCapture = PiRGBArray(camera, size=(frame_w_pix, frame_h_pix))
 
# allow the camera to warmup
time.sleep(0.1)

cola = 0
	
for frame in camera.capture_continuous(rawCapture, format="bgr", use_video_port=True):
	t0 = time.time()
	image = frame.array
	
	# Exit if any key is pressed
	key = cv.waitKey(1) & 0xFF
	if key == ord("q"):
		cv.destroyAllWindows()
		break
	
	# Choose which Cola-can to detect	
	if key == ord("p"):
		cola = 1
	elif key == ord("o"):
		cola = 0
	
	rawCapture.truncate(0)

	
	# Image Processing
	hsv = cv.cvtColor(image, cv.COLOR_BGR2HSV)	# image from BGR to HSV color
	
	#color = 46 						# lime green color
	#color = 91 * (176/255)				# Brown/green Chip bag color
	#color = 64 * (176/255) 				# Yellow bag color
	#color = 155 * (176/360)
	#color = 97 * (176/360)
	#color = 200 * (176/360) 			# Blue plastic bag
	
	if(cola == 1):
		color = 120 * (176/360)				# Green Sprite Can
		margin = 5
		colorLower = (color - margin, 80, 25)
		colorUpper = (color + margin, 255, 255)
		mask = cv.inRange(hsv, colorLower, colorUpper)
	elif(cola == 0):
		color1 = 0 * (179/360)				# Red Coca-Cola Can
		color2 = 360 * (179/360)			# Red Coca-Cola Can
		margin = 10
		bound1_low = (color1 - margin, 80, 80)
		bound1_up = (color1 + margin, 255, 255)
		bound2_low = (color2 - margin, 80, 80)
		bound2_up = (color2 + margin, 255, 255)
		mask1 = cv.inRange(hsv, bound1_low,bound1_up )
		mask2 = cv.inRange(hsv, bound2_low, bound2_up)
		mask = mask1 + mask2

	#mask = cv.erode(mask, None, iterations = 2)
	#mask = cv.dilate(mask, None, iterations = 2)
	
	mask = cv.dilate(mask, None, iterations = 2)
	mask = cv.erode(mask, None, iterations = 3)
	
	hud = image
	
	# Data extraction
	x,y = centroid(mask)

	n_white_pix = np.sum(mask == 255)
	
	rows = len(mask)
	columns = len(mask[0])
	
	weight = weightfcn(x)
	
	# Building HUD
	
	xmid = int(frame_w_pix/2)
	ymid = int(frame_h_pix/2)
	offset = int(safezone_pix/2)
	
	cv.line(hud, (xmid-offset, 1), (xmid-offset, frame_h_pix), hudcolor, 5)
	cv.line(hud, (xmid+offset, 1), (xmid+offset, frame_w_pix), hudcolor, 5)
	
	cv.circle(hud, (xmid,ymid), 6, (0,0,255), 3)
	
	cv.circle(hud, (x,y), 10, (0,0,255), 10)
	
	# PI->INO Char Data out
	
	if key == ord("x"):
		dataout = 'X'		# reset fetch counter
	elif key == ord("s"):
		dataout = 'S'		# Stop car movement (stop)
	elif key == ord("g"):	# Go car movement (go)
		dataout = 'G'
	elif(x == -100):
		dataout = 'O'
	elif(x >= (xmid+offset)):
		dataout = 'L'
	elif(x <= (xmid-offset)):
		dataout = 'R'
	else:
		dataout = 'M'
	
	ser.write(bytes(dataout, 'UTF-8')) #
	
	# Feedback ----------
	#cv.imshow('Default Video Feed', image)
	cv.imshow('Color Mask', mask)
	cv.imshow('Display HUD', hud)
	t1 = time.time()
	total = t1-t0
	
	print('--------------------------------------')
	print('Number of white pixels:', n_white_pix)
	print('Centroid Location (X,Y)', [x,y])
	print('PWM Speed Weight       ', weight)
	print('Char Data out          ', dataout)
	print('Cycle time             ', total)
	
	#print('Size of image box      ', [rows, columns])
	#print('Arduino Data'		   , ino_data)				# not working yet
	
	#print('Data array', [n_white_pix, x, y])
	
# Clean resources
rawCapture.truncate(0)
#cap.release()
cv.destroyAllWindows()
print("Program Terminated.")
