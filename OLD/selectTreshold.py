#!/usr/bin/env python3
# EML 4840 Robot Design
# Florida International University
# Department of Mechanical and Materials Engineering
# Anthony Abrahao <aabra037@fiu.edu>
# Miami, Spring 2018

# In OpenCV the HSV range is:
# H: 0 to 179
# S: 0 to 255
# V: 0 to 255

import cv2 as cv
import time

# Create a capture object from device number (or video file)
cap = cv.VideoCapture(0)

def nothing(x):
	pass

# Creating a window for later use
cv.namedWindow('EML4840: Treshold')

# Starting with 100's to prevent error while masking
h = 100
s = 100
v = 100

# Creating track bar
cv.createTrackbar('h', 'EML4840: Treshold', 0, 179, nothing)
cv.createTrackbar('s', 'EML4840: Treshold', 0, 255, nothing)
cv.createTrackbar('v', 'EML4840: Treshold', 0, 255, nothing)

print("Press any key to exit...")
while True:
	# Exit if any key is pressed
	if cv.waitKey(1) > -1:
		break
	# Capture frame
	okay, frame = cap.read()
	# Skip frame if any capture error happened (or video ended)
	if okay == False:
		continue
	# Convert frame image from BGR to HSV color space
	hsv = cv.cvtColor(frame, cv.COLOR_BGR2HSV)
	# get info from track bar and appy to result
	h = cv.getTrackbarPos('h', 'EML4840: Treshold')
	s = cv.getTrackbarPos('s', 'EML4840: Treshold')
	v = cv.getTrackbarPos('v', 'EML4840: Treshold')
	# Normal masking algorithm
	lower = (h - 20, s, v)
	upper = (h + 20, 255, 255)
	mask = cv.inRange(hsv, lower, upper)
	result = cv.bitwise_and(frame, frame, mask = mask)
	cv.imshow('EML4840: Treshold', result)
	# Slow video
	time.sleep(.01)	

cap.release()
cv.destroyAllWindows()