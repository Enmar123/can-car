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

# PROGRAM SETUP --------------------------------------------------------
 
import cv2 as cv
import numpy as np
import time

# RASPI AND ARDUCAM
from picamera.array import PiRGBArray
from picamera import PiCamera
#import serial

#ser = serial.Serial('/dev/ttyACM0',9600) 	# 



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
camera.framerate = 32
rawCapture = PiRGBArray(camera, size=(frame_w_pix, frame_h_pix))
 
# allow the camera to warmup
time.sleep(0.1)


	
for frame in camera.capture_continuous(rawCapture, format="bgr", use_video_port=True):
	image = frame.array
	
	# Exit if any key is pressed
	key = cv.waitKey(1) & 0xFF
	if key == ord("p"):
		cv.destroyAllWindows()
		break
	
	rawCapture.truncate(0)

	
	# Image Processing
	hsv = cv.cvtColor(image, cv.COLOR_BGR2HSV)	# image from BGR to HSV color
	
	#color = 46 						# lime green color
	#color = 91 * (176/255)				# Brown/green Chip bag color
	#color = 64 * (176/255) 				# Yellow bag color
	#color = 155 * (176/360)
	#color = 97 * (176/360)
	color = 200 * (176/360) 			# Blue plastic bag
	
	colorLower = (color - 20, 80, 80)
	colorUpper = (color + 20, 255, 255)
	
	mask = cv.inRange(hsv, colorLower, colorUpper)
	mask = cv.erode(mask, None, iterations = 2)
	mask = cv.dilate(mask, None, iterations = 2)
	
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
	
	cv.line(hud, (xmid-offset, 1), (xmid-offset, frame_h_pix), (0,0,0), 5)
	cv.line(hud, (xmid+offset, 1), (xmid+offset, frame_w_pix), (0,0,0), 5)
	
	cv.circle(hud, (xmid,ymid), 6, (0,0,255), 3)
	
	cv.circle(hud, (x,y), 10, (0,0,255), 10)
	
	
	# Feedback
	#cv.imshow('Default Video Feed', image)
	#cv.imshow('Color Mask', mask)
	cv.imshow('Display HUD', hud)
	
	
	print('Number of white pixels:', n_white_pix)
	print('Centroid Location (X,Y)', [x,y])
	print('PWM Speed Weight       ', weight)
	
	#print('Size of image box      ', [rows, columns])
	#print('Arduino Data'		   , ino_data)				# not working yet
	
	#print('Data array', [n_white_pix, x, y])
	
# Clean resources
rawCapture.truncate(0)
cap.release()
cv.destroyAllWindows()
print("Program Terminated.")
