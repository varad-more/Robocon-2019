#!/usr/bin/python

import io
import os
import subprocess
import cv2
import numpy as np
import sys
import math
#from matplotlib import pyplot as plt
#from collections import counter
from multiprocessing.dummy import Pool as ThreadPool

#Global parameters

#Threshold for canny
low_threshold = 50
high_threshold = 150

#Gaussian Smoothing
kernel_size = 3

#Minimum number of pixels making up a line
min_line_length = 10
#Maximum gap(distance) between pixels to make connectable line segments
max_line_gap = 15

#The grey image is used for most of the calculations and isn't displayed
WINDOW_GRAY_IMAGE = 'gray image'
#This image window is displayed on screen with overlays showing the line tracking
WINDOW_DISPLAY_IMAGE = 'display image'

#Trackbar contols so you can refine how the pixel search works
CONTROL_SCAN_RADIUS = 'Scan Radius'
CONTROL_NUMBER_OF_CIRCLES = 'Number of scans'
CONTROL_LINE_WIDTH = 'Line Width'

#Setting Resolution of the camera. Larger images allow more details but take more resource to process.
#Valid Resolutions are 160x120 320x240 640x480 and so on
RESOLUTION_X = 640
RESOLUTION_Y = 480

#Setting Scan radius.We start scanning and start looking our line from here
SCAN_RADIUS = RESOLUTION_X/4
#Scan height is the height (in pixels) from the bottom of our image frame from where we start scanning for line.
SCAN_HEIGHT = RESOLUTION_Y - 10
#This is our centre.We assume that we want to try and track the line in relation to this point.
SCAN_POS_X = RESOLUTION_X/2
#This is the radius that we scan from the last known point for each of the circles
SCAN_RADIUS_REG = 90
#The number of iterations we scan to allow us to look ahead and give us more time to make better choices
NUMBER_OF_CIRCLES = 0



def scanLine(image, display_image, point, radius):
    try:
        x = point[0];
        y = point[1];
        scan_start = 0
        scan_end = 640
        row = image[y]
        data = np.empty(640)
        data[:] = row[scan_start:scan_end]
        #print(data)

        #Drawing a line where we are reading the data
        cv2.line(display_image, (scan_start, y), (scan_end, y), (255, 0, 0), 2)
        cv2.circle(display_image, (scan_start, y), 5, (255, 0, 0), -1, 8, 0)
        cv2.circle(display_image, (scan_end, y), 5, (255, 0, 0), -1, 8, 0)
        return data;
    except IndexError:
        print ("Something went wrong while scanning the line \n")
        print ("Look in scanLine function \n");

def coordinateFromPoint(origin, angle, radius):
    try:
        xo = origin[0]
        yo = origin[1]
        #Work out the co-ordinate for the pixel on the circumference of the circle
        x = xo - radius * math.cos(math.radians(angle))
        y = yo + radius * math.sin(math.radians(angle))

        #We only want whole numbers
        x = int(round(x))
        y = int(round(y))
        return(x, y);
    except (ArithmeticError, IndexError, ValueError, TypeError):
        print ("Something went wrong in coordinateFromPoint function");


def scanCircle(image, display_image, point, radius, look_angle):
    try:
        x = point[0]
        y = point[1]
        scan_start = x - radius
        scan_end = x + radius
        endpoint_left = coordinateFromPoint(point, look_angle -90, radius)
        endpoint_right = coordinateFromPoint(point, look_angle +90, radius)
        #Draw a circle to indicate where we start and end scanning
        cv2.circle(display_image, (endpoint_left[0], endpoint_left[1]), 5, (255, 100, 100), -1, 8, 0)
        cv2.circle(display_image, (endpoint_right[0], endpoint_left[1]), 5, (100, 255, 100), -1, 8, 0)
        cv2.line(display_image, (endpoint_left[0], endpoint_left[1]), (endpoint_right[0], endpoint_right[1]), (255, 0, 0), 1)
        cv2.circle(display_image, (x, y), radius, (100, 100, 100), 1, 8, 0)

        #We will only scan half the circumference(semi circle)
        data = np.zeros(shape=(180, 3))

        #Getting the co-ordinates and value for every degree in the semi-circle
        startAngle = look_angle - 90
        returnVal = True
        for i in range(0, 180, 1):
            current_angle = startAngle + i
            scan_point = coordinateFromPoint(point, current_angle, radius)
            if inImageBounds(image, scan_point[0], scan_point[1]):
                imageValue = image[scan_point[1]][scan_point[0]]
                data[i] = [imageValue, scan_point[0], scan_point[1]]
            else:
                returnVal = False
                break;
        return returnVal, data;
    except (IndexError, ArithmeticError, ValueError, TypeError):
        print ("Something went wrong in scanCircle function")

        
            
def findInCircle(display_image, scan_data, gray_image):
    try:
        # left and right should be the boundry values. first element will be the image value second element will be the index$
        max = np.amax(scan_data[:][:,0])
        mean = np.array([])
        a = 1
        scan_data = scan_data.astype(int)

        where=np.where(scan_data[:,0]==max)
        image_value= scan_data[:,0]
        x=scan_data[:,1]
        y=scan_data[:,2]

        if max==255 and len(where[0])>=2 :
            for i in range(0,len(where[0])-1):
                if(where[0][i+1]-where[0][i]) > 5 :
                    data=image_value[where[0][i]:where[0][i+1]].copy()
                    mean=np.append(mean,data.mean())
                else :
                    mean=np.append(mean,0);
            if np.max(mean)>0:
                m=np.argmax(mean)
                a = 0
                location= int(round(where[0][m]/2+where[0][m+1]/2))
                position=[x[location],y[location]]
        if a:
            diff_data= np.diff(image_value)
            print ("no canny")
            location=int(round(diff_data.argmax()/2+diff_data.argmin()/2))
            position=[x[location],y[location]]
        return position;
    except (IndexError, ArithmeticError, ValueError, TypeError):
        print ("Something went wrong in findInCircle function");
        
            
def inImageBounds(image, x, y):
    try:
        return x>=0 and y>=0 and y<len(image) and x<len(image[y])
    except (IndexError, TypeError):
        print ("Something went wrong in inImageBounds function")
        
def findLine(display_image, gray_image, scan_data, x, y, radius):
    try:
        max=np.amax(scan_data)
        mean= np.array([])
        a=1

        where=np.where(scan_data==max)
        if max==255 and len(where[0])>=2 :
            for i in range(0,len(where[0])-1):
                if (where[0][i+1]-where[0][i]) > 5:
                    rect = gray_image[SCAN_HEIGHT-50:SCAN_HEIGHT,where[0][i]:where[0][i+1]].copy()
                    cv2.circle(display_image, (where[0][i], 470), 2, (255, 255, 255), 2, 8, 0)
                    mean=np.append(mean,rect.mean())
                else:
                    mean=np.append(mean,0)
            if np.max(mean)>0:
                m=np.argmax(mean)
                a=0
                x=int(round(where[0][m]/2+where[0][m+1]/2))
        if a:
            diff_data= np.diff(scan_data)
            print ("no canny")
            x=int(round(diff_data.argmax()/2+diff_data.argmin()/2))
        return ( x, y);
    except (IndexError, TypeError, ValueError, ArithmeticError):
        print("Something went wrong in findLine function")
        
            
            
def lineAngle(point1, point2):
    try:
        angle = round(math.atan2((point2[1] - point1[1]), -(point2[0] - point1[0]))*180/math.pi)
        return angle;
    except (IndexError, ArithmeticError, ValueError):
        print("Something went wrong in lineAngle function")

def point_angle(i, j):
    try:
        return int(math.atan2(i, j)*180/math.pi)
    except (ArithmeticError, ValueError, TypeError):
        print("Something went Wrong in point_angle function")
        

def lineLength(point1, point2):
    try:
        dx = point1[0] - point2[0]
        dy = point1[1] - point2[1]
        return int(round(math.sqrt(dx*dx + dy*dy)));
    except (IndexError, ValueError, TypeError, ArithmeticError):
        print("Something went wrong in lineLength function")

def onScanRadiusChange(newValue):
    try:
        global SCAN_RADIUS_REG
        SCAN_RADIUS_REG = newValue
        return;
    except NameError:
        print("Something went wrong in onScanRadiusChange function")

def onCircleScanChange(newValue):
    try:
        global NUMBER_OF_CIRCLES
        NUMBER_OF_CIRCLES = newValue
        return;
    except NameError:
        print("Something went wrong in onCircleScanChange function")

        
def onLineWidthChange(newValue):
    try:
        global SCAN_RADIUS
        SCAN_RADIUS = int(round(newValue/2))
        return;
    except (NameError, ValueError, TypeError, ArithmeticError):
        print("Something went wrong in onLineWidthChange function")


def hough_lines(canny, gray_canny, display_img):
    try:
        lines = cv2.HoughLines(canny,1,np.pi/180,50)
        if lines is not None:
            for rho,theta in lines[0]:
                a = np.cos(theta)
                b = np.sin(theta)
                x0 = a*rho
                y0 = b*rho
                x1 = int(x0 + 1000*(-b))
                y1 = int(y0 + 1000*(a))
                x2 = int(x0 - 1000*(-b))
                y2 = int(y0 - 1000*(a))
                cv2.line(display_img,(x1,y1),(x2,y2),(255,255,255),1)
                cv2.line(gray_canny,(x1,y1),(x2,y2),(255,255,255),1)
                
        return display_img, gray_canny;
    except (ArithmeticError, ValueError, TypeError):
        print("Something went wrong in hough_lines function")


def main():

    #Creating in-memory stream
    stream = io.BytesIO()
    #Create a window
    cv2.namedWindow(WINDOW_DISPLAY_IMAGE)
    #position the window
    cv2.moveWindow(WINDOW_DISPLAY_IMAGE, 0, 35)
    # Add some controls to the window
    cv2.createTrackbar(CONTROL_SCAN_RADIUS, WINDOW_DISPLAY_IMAGE, 5, 100, onScanRadiusChange)
    cv2.setTrackbarPos(CONTROL_SCAN_RADIUS, WINDOW_DISPLAY_IMAGE, SCAN_RADIUS_REG)
    cv2.createTrackbar(CONTROL_NUMBER_OF_CIRCLES, WINDOW_DISPLAY_IMAGE, 0, 7, onCircleScanChange)
    cv2.setTrackbarPos(CONTROL_NUMBER_OF_CIRCLES, WINDOW_DISPLAY_IMAGE, NUMBER_OF_CIRCLES)
    cv2.createTrackbar(CONTROL_LINE_WIDTH, WINDOW_DISPLAY_IMAGE, 0, RESOLUTION_X, onLineWidthChange)
    cv2.setTrackbarPos(CONTROL_LINE_WIDTH, WINDOW_DISPLAY_IMAGE, SCAN_RADIUS *2)

    returnString = """ Press Esc to end the program Using camera resolution: {}x{} Centre point: {}:{} Scan radius: {} Number of search itterations: {} Baseline Width: {} """.format(RESOLUTION_X, RESOLUTION_Y, SCAN_POS_X, SCAN_HEIGHT, SCAN_RADIUS_REG, NUMBER_OF_CIRCLES, SCAN_RADIUS *2)
    print(returnString)

    #Capturing Video
    cap = cv2.VideoCapture(0)

    #Start infinite loop
    while True:
        try:
            # Get the tick count so we can keep track of performance
            e1 = cv2.getTickCount()
            
            ret,image = cap.read()
            if (ret== False):
                cap = cv2.VideoCapture(0)
                print("Error opening video stream or file")
                continue
            data = np.asarray( image, dtype="int32" )
            #cv2.imshow('image',image)
            gray_image = cv2.cvtColor(image, cv2.COLOR_RGB2GRAY)

            #blurr_image=cv2.GaussianBlur(gray_black_image, (kernel_size, kernel_size), 0)
            #cv2.imshow('blurr',blurr_image)
            canny_image=cv2.Canny(gray_image, low_threshold, high_threshold)
            gray_canny=cv2.addWeighted(canny_image,1,gray_image,1,0)
            hough_image=gray_canny
            cv2.imshow('canny',hough_image)
            display_image = cv2.copyMakeBorder(image, 0, 0, 0, 0, cv2.BORDER_REPLICATE)
            center_point = (SCAN_POS_X, SCAN_HEIGHT)
            # Scan a horizontal line based on the centre point We could just use this data to work out how far off centre we are and steer 
            # accordingly. Get a data array of all the falues along that line scan_data is an array containing:
            #   - pixel value
            scan_data = scanLine(hough_image, display_image, center_point, SCAN_RADIUS)
            # The center point we believe the line we are following intersects with our scan line.
            point_on_line = findLine(display_image,gray_image, scan_data ,SCAN_POS_X, SCAN_HEIGHT, SCAN_RADIUS)

            # Start scanning the arcs This allows us to look ahead further ahead at the line and work out an angle to steer From the intersection
            # point of the line, scan in an arc to find the line The scan data contains an array
            #   - pixel value - x co-ordinate - y co-ordinate
            
            returnVal, scan_data = scanCircle(hough_image, display_image, point_on_line, SCAN_RADIUS_REG, -90)
            previous_point = point_on_line
            # in the same way ads the findLine, go through the data, find the mid point and return the co-ordinates.
            last_point = findInCircle(display_image, scan_data,hough_image)
            cv2.line(display_image, (previous_point[0], previous_point[1]), (last_point[0], last_point[1]), (255, 255, 255), 1)
            actual_number_of_circles = 0
            for scan_count in range(0, NUMBER_OF_CIRCLES):
                returnVal, scan_data = scanCircle(hough_image, display_image, last_point, SCAN_RADIUS_REG, lineAngle(previous_point, last_point))
                # Only work out the next itteration if our point is within the bounds of the image
                if returnVal == True:
                    actual_number_of_circles += 1
                    previous_point = last_point
                    last_point = findInCircle(display_image, scan_data,hough_image)
                    cv2.line(display_image, (previous_point[0], previous_point[1]), (last_point[0], last_point[1]), (255, 255, 255), 1)
                else:
                    break;
                
            # Draw a line from the centre point to the end point where we last found the line we are following
            cv2.line(display_image, (center_point[0], center_point[1]), (last_point[0], last_point[1]), (0, 0, 255), 1)

            # Display the image
            cv2.imshow(WINDOW_DISPLAY_IMAGE, display_image)

            # This is the maximum distance the end point of our search for a line can be from the centre point.
            line_scan_length = SCAN_RADIUS_REG * (actual_number_of_circles + 1)
            # This is the measured line length from the centre point
            line_length_from_center = lineLength(center_point, last_point)
            center_y_distance = center_point[1] - last_point[1]
            center_x_distance = center_point[0] - last_point[0]
            # Stop counting all work is done at this point and calculate how we are doing.
            e2 = cv2.getTickCount()

        except (AttributeError, TypeError, ValueError, ImportError, NameError):
            print("Something went wrong in main function")
            
        try:
            
            #I2C communication
            returnString = "fps {} - bearing {} - x:{} y:{} look distance:{} distance from origin:{}".format(1000/ ((e2 -e1)/cv2.getTickFrequency() *1000),lineAngle(center_point, last_point) *-1 -90,center_x_distance,center_y_distance,line_scan_length,line_length_from_center)
            bearing = int (lineAngle(center_point, last_point) *-1 -90)
            print(returnString)
            print("center={} error={}",center_point[0],center_x_distance)
            send_string=[center_x_distance,bearing]
            send=str(send_string).strip('[]')
            send+=','
            print (send)
            data=send

            data_list = list(data)
            for i in data_list:
                #Sends to the Slave
                writeNumber(int(ord(i)))
                
        except (TypeError, ValueError, IndexError, NameError):
            
            print("Something went wrong in I2C communication")
                
        # Wait for ESC to end program
        c = cv2.waitKey(7) % 0x100
        if c == 27:
            break
    print("Closing Program")
    cv2.destroyAllWindows()
    print("All the windows should be closed")
    return;

if __name__ == "__main__":
    main()


#END OF PROGRAM.    
    