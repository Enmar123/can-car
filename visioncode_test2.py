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
import time
import picamera
import cv2

with picamera.PiCamera() as camera:
    camera.resolution = (640, 480)
    camera.vflip = True
    camera.start_preview()
    time.sleep(3)
    #image = camera.read()
    #cv2.imshow(image)


with picamera.PiCamera() as camera:
	camera.resolution = (640, 480)
	camera.vflip = True
	camera.capture(camera, format='bgr')
	image = camera
	cv2.imshow(image)
