

#!/usr/bin/python
import io
import os
import subprocess
import cv2
import numpy as np
import sys
import math
#import serial
from collections import Counter
from multiprocessing.dummy import Pool as ThreadPool
# Canny Edge Detector
low_threshold = 50
high_threshold = 150
# Global parameters
# Gaussian smoothing
kernel_size = 3
# Hough Transform
angle=np.array(200)
slope=np.array(200)
points=np.array(200)
previous_lines=np.array(200)
min_line_length = 10 #minimum number of pixels making up a line
max_line_gap = 20	# maximum gap in pixels between connectable line segments
# The grey image is used for most of the calculations and isn't displayed
WINDOW_GRAY_IMAGE = 'gray image'
# This is displayed on screen with overlays showing the line tracking
WINDOW_DISPLAY_IMAGE = 'display image'
# Trackbar controls so you can refine how the search works
CONTROL_SCAN_RADIUS = 'Scan Radius'
CONTROL_NUMBER_OF_CIRCLES = 'Number of Scans'
CONTROL_LINE_WIDTH = 'Line Width'
# Resolution of the camera image. larger images allow for more detail, but take more to process. valid resolutions include:
#   160 x 120 320 x 240 640 x 480 800 x 600 etc...
RESOLUTION_X = 640
RESOLUTION_Y = 480
# This is half the width of the line at the bottom of the screen that we start looking for the line we want to follow.
SCAN_RADIUS = RESOLUTION_X/4
# Start the scan height 10 pixels from the bottom.
SCAN_HEIGHT = RESOLUTION_Y - 10
# This is our centre. We assume that we want to try and track the line in relation to this point
SCAN_POS_X = RESOLUTION_X / 2
# This is the radius that we scan from the last known point for each of the circles
SCAN_RADIUS_REG = 90
# The number of itterations we scan to allow us to look ahead and give us more time to make better choices
NUMBER_OF_CIRCLES =0
NUMBER_OF_CIRCLES =0
def scanLine(image, display_image, point, radius):
        x = point[0];
        y = point[1];
        scan_start =  0  # x - radius
        scan_end =   640    # x + radius
        row = image[y]
        data = np.empty(640)
        data[:] = row[scan_start:scan_end]
        print(data)
        # Draw a line where we are reading the data
        cv2.line(display_image, (scan_start, y), (scan_end, y), (255, 0, 0), 2)
        cv2.circle(display_image, (scan_start, y), 5, (255, 0, 0), -1, 8, 0)
        cv2.circle(display_image, (scan_end, y), 5, (255, 0, 0), -1, 8, 0)
        #print("scanline x:{} y:{} - start x:{} end x:{} - {}".format(x, y, scan_start, scan_end, SCAN_DATA))
        return data;
def coordinateFromPoint(origin, angle, radius):
        xo = origin[0]
        yo = origin[1]
        # Work out the co-ordinate for the pixel on the circumference of the circle
        x = xo - radius * math.cos(math.radians(angle))
        y = yo + radius * math.sin(math.radians(angle))
        
        # We only want whole numbers
        x = int(round(x))
        y = int(round(y))
        return (x, y);
def scanCircle(image, display_image, point, radius, look_angle):
        x = point[0];
        y = point[1];
        scan_start = x - radius
        scan_end = x + radius
        endpoint_left = coordinateFromPoint(point, look_angle - 90, radius)
        endpoint_right = coordinateFromPoint(point, look_angle + 90, radius)
        #print("scanline left:{} right:{} angle:{}".format(endpoint_left, endpoint_right, look_angle))
        # Draw a circle to indicate where we start and end scanning.
        cv2.circle(display_image, (endpoint_left[0], endpoint_left[1]), 5, (255, 100, 100), -1, 8, 0)
        cv2.circle(display_image, (endpoint_right[0], endpoint_right[1]), 5, (100, 255, 100), -1, 8, 0)
        cv2.line(display_image, (endpoint_left[0], endpoint_left[1]), (endpoint_right[0], endpoint_right[1]), (255, 0, 0), 1)
        cv2.circle(display_image, (x, y), radius, (100, 100, 100), 1, 8, 0)
        # We are only going to scan half the circumference
        data = np.zeros(shape=(180, 3))
        # Getting the co-ordinates and value for every degree in the semi circle
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
def findInCircle(display_image, scan_data):
        data = np.zeros(shape=(len(scan_data) -1, 1))
        data[0] = 0
        data[len(data)-1] = 0
        for index in range(1, len(data)):
                data[index] = scan_data[index - 1][0] - scan_data[index][0]
        # left and right should be the boundry values. first element will be the image value second element will be the index$
        left = [0,0]
        right = [0,0]

        for index in range(0, len(data)):
                if data[index] > left[1]:
                        left[1] = data[index]
                        left[0] = index

                if data[index] < right[1]:
                        right[1] = data[index]
        leftx = int(scan_data[left[0]][1])
        lefty = int(scan_data[left[0]][2])
        lefti = left[0]
        rightx = int(scan_data[right[0]][1])
        righty = int(scan_data[right[0]][2])
        righti = right[0]
        centre_index = int(round((righti + lefti)/2))

        position = [int(scan_data[centre_index][1]), int(scan_data[centre_index][2])]
        # mid point, where we believe is the centre of the line
        cv2.circle(display_image, (position[0], position[1]), 5, (255, 255, 255), -1, 8, 0)
        # left boundrary dot on the line
        cv2.circle(display_image, (leftx, lefty), 2, (0, 0, 102), 2, 8, 0)
        # right boundrary dot on the line
        cv2.circle(display_image, (rightx, righty), 2, (0, 0, 102), 2, 8, 0)

        return position; 

def inImageBounds(image, x, y):
        return x >=0 and y >= 0 and y < len(image) and x < len(image[y]) 
def findLine(display_image,gray_image, scan_data, x, y, radius):
        data = np.empty(len(scan_data) -1)
        data[0] = 0
        data[len(data)-1] = 0
        pos_255=  np.concatenate(np.where(scan_data[:]==255))
       # if len(pos_255) > 1
        j=0
        average=np.empty(100)
        data_now_pre=np.empty(100)
        data_pre_now=np.empty(100)
        for i in range(0, len(pos_255)-1,1):
             average[j]=np.average(scan_data[pos_255[i]+1:pos_255[i+1]])
             print(average[j])
             print(scan_data[pos_255[i]+1:pos_255[i+1]])
             j=j+1
        print(np.average(scan_data))
      #  d= np.asarray(gray_image,'int32')
      #  print(d[SCAN_HEIGHT][:])
        for i in pos_255 :
              data_pre_now[j]=scan_data[i-1]-scan_data[i]
              data_now_pre[j]=scan_data[i]-scan_data[i+1]
              print(i)
              print('previous- now')
              print(data_pre_now[j])
              print('now-previous')
              print(data_now_pre[j])
              j=j+1
       # else:
        #   continue 
        for index in range(1, len(data)):
                data[index] = scan_data[index - 1] - scan_data[index]
#        print(data)
        scan_start = x - radius
        scan_end = x + radius
        left = [0,0]
        right = [0,0]

        for index in range(0, len(data)):
                if data[index] > left[1]:
                        left[1] = data[index]
                        left[0] = index

                if data[index] < right[1]:
                        right[1] = data[index]
                        right[0] = index
        line_position = (right[0] + left[0]) / 2
        #print("line position {} {}, {} - {}".format(scan_start, left, right, line_position))
        # mid point, where we believe is the centre of the line cv2.circle(display_image, (scan_start + line_position, y), 5,$
        #boundrary dot on the line cv2.circle(display_image, (scan_start + left[0], y), 5, (0, 0, 102), -1, 4, 0)
        # right boundrary dot on the line cv2.circle(display_image, (scan_start + right[0], y), 5, (0, 0, 102), -1, 4, 0)
 
        #print("line position {} {}, {} - {}".format(scan_start, left, right, line_position))
        # mid point, where we believe is the centre of the line cv2.circle(display_image, (scan_start + line_position, y), 5, (0, 204, 102), -1, 8, 0) left 
        #boundrary dot on the line cv2.circle(display_image, (scan_start + left[0], y), 5, (0, 0, 102), -1, 4, 0)
        # right boundrary dot on the line cv2.circle(display_image, (scan_start + right[0], y), 5, (0, 0, 102), -1, 4, 0)
        return (scan_start + line_position, y); 
def lineAngle(point1, point2):
        angle = round(math.atan2((point2[1] - point1[1]), -(point2[0] - point1[0]))*180/math.pi) 
        return angle
def point_angle(i,j):
       return int(math.atan2(i, j)*180/math.pi) 
def lineLength(point1, point2):
        dx = point1[0] - point2[0]
        dy = point1[1] - point2[1]
        return int(round(math.sqrt(dx*dx + dy*dy))); 
def onScanRadiusChange(newValue):
        global SCAN_RADIUS_REG
        SCAN_RADIUS_REG = newValue
        return; 
def onCircleScanChange(newValue):
        global NUMBER_OF_CIRCLES
        NUMBER_OF_CIRCLES = newValue
        return; 
def onLineWidthChange(newValue):
        global SCAN_RADIUS
        SCAN_RADIUS = int(round(newValue/2))
        return;
def approx_equal(a,b):
    if a-b <=1  and a-b >=-1 :
      return 1;
    else :
      return 0;
def find_point(data):
    k=0
    angle=np.zeros(shape=(500,3))
    for i in range(1,640,1):
         if data[0][i]==255 and data[0][i-1] is not 255:
             for j in range(1,640,1):
             	if data[1][j]==255 and data[1][j-1] is not 255 :
                   previous2=255
                   angle[k]=[i,j,point_angle(i,j)]
                   print(angle[k])
                   k=k+1
    l=0
    print("data")
    print(data[0][:])
    print(data[1][:])
   # print("all lines")
  #  print(angle)
    print("angle")
    for i in range (0, k,1): 
        for j in range (i + 1, k,1):
           if angle[i][0] is not angle[j][0] and  angle[i][2]==angle[j][2] :
              print(i,j,angle[i][2],angle[j][2])
  #  return angle
def hough_lines(image,img, min_line_len, max_line_gap,y,previous_lines):
#	`img` should be the output of a Canny transform.
#	hough_image = np.zeros((240,320,3), np.uint8)
    #    img= cv2.addWeighted(img, 0.3, hough, 0.7, 0) 	
#	Returns an image with hough lines drawn 
	minLineLength = 100
        maxLineGap = 10
 #   angle=np.array([])
       # angle= [None]*200
       # slope=[None]*200
       # points=[None]*200
       # previous_lines=[None]*200
        k=0
        i=0
        lines = cv2.HoughLinesP(img,1,np.pi/180,50,minLineLength,maxLineGap)
        if lines is None:
         #  print(previous_lines[0]==None)
           if previous_lines[0] is not None:
                for j in range(0, len(previous_lines)):
                      for x1,y1,x2,y2 in previous_lines[j]:
                         slope[i]=round((y2-y1)/(x2-x1))
                         angle[i]=round(math.atan2((y2 -y1), -(x2 -x1))*180/math.pi)
                         x=((y-y1)/slope[i])+x1
                         if inImageBounds(image,x,y):
                               x=int(x)
                               points[k]=x
                               cv2.circle(image, (x, y-10), 2, (0, 0, 255), 2, 8, 0)
           #                    print(points[k])
            #                   print(slope[i])
                               k=k+1
                               cv2.line(image,(int(x1),int(y1)),(int(x),int(y)),(0,0,0),5)
                               cv2.line(img,(int(x1),int(y1)),(int(x),int(y)),(255,255,255),2)

                         i=i+1

 
           return image,img,points,lines;
        print("max_index_hough:")   
        for j in range(0, len(lines)):
            for x1,y1,x2,y2 in lines[j]:
                 slope[i]=round((y2-y1)/(x2-x1))
                 angle[i]=round(math.atan2((y2 -y1), -(x2 -x1))*180/math.pi)
                 x=((y-y1)/slope[i])+x1
                 
  
                 if inImageBounds(image,x,y):
                     x=int(x)
                     points[k]=x
                     cv2.circle(image, (x, y-10), 2, (0, 0, 255), 2, 8, 0)
                     print(points[k])
                     print(slope[i])
                     k=k+1
                     cv2.line(image,(int(x1),int(y1)),(int(x),int(y)),(0,0,0),5)
                     cv2.line(img,(int(x1),int(y1)),(int(x),int(y)),(255,255,255),2)
                 i=i+1
        
        return image,img,points,lines;

	
def main():
        # Create the in-memory stream
        stream = io.BytesIO()
        # Create a window
        cv2.namedWindow(WINDOW_DISPLAY_IMAGE)
        # position the window
        cv2.moveWindow(WINDOW_DISPLAY_IMAGE, 0, 35)
        # Add some controls to the window
        cv2.createTrackbar(CONTROL_SCAN_RADIUS, WINDOW_DISPLAY_IMAGE, 5, 100, onScanRadiusChange)
        cv2.setTrackbarPos(CONTROL_SCAN_RADIUS, WINDOW_DISPLAY_IMAGE, SCAN_RADIUS_REG)
        cv2.createTrackbar(CONTROL_NUMBER_OF_CIRCLES, WINDOW_DISPLAY_IMAGE, 0, 7, onCircleScanChange)
        cv2.setTrackbarPos(CONTROL_NUMBER_OF_CIRCLES, WINDOW_DISPLAY_IMAGE, NUMBER_OF_CIRCLES)
        cv2.createTrackbar(CONTROL_LINE_WIDTH, WINDOW_DISPLAY_IMAGE, 0, RESOLUTION_X, onLineWidthChange)
        cv2.setTrackbarPos(CONTROL_LINE_WIDTH, WINDOW_DISPLAY_IMAGE, SCAN_RADIUS *2)
        returnString = """ Press Esc to end the program Using camera resolution: {}x{} Centre point: {}:{} Scan radius: {} Number of search itterations: {} 
        Baseline Width: {} """.format(RESOLUTION_X, RESOLUTION_Y, SCAN_POS_X, SCAN_HEIGHT, SCAN_RADIUS_REG, NUMBER_OF_CIRCLES, SCAN_RADIUS *2)
        print(returnString)
        cap = cv2.VideoCapture(0)
# Define the codec and create VideoWriter object
     #   fourcc = cv2.VideoWriter_fourcc(*'XVID')
    #    out = cv2.VideoWriter('output.avi',fourcc, 20.0, (640,480))
 
                # Start loop
        while True:
                        # Get the tick count so we can keep track of performance
                        e1 = cv2.getTickCount()
                        
                       # subprocess.call(["fswebcam", "-d/dev/video0",  "-r", "320x240", "/home/pi/image_processing/image.jpeg"]) # Capture image from camera
                       # os.system('fswebcam -r 320x240 -S 3 --jpeg 50 --save /home/pi/image_processing/image.jpeg')
                       # image = cv2.imread('image.jpeg')
                        ret,image = cap.read()
                        if (ret== False):
                              cap = cv2.VideoCapture(0)
# Define the codec and create VideoWriter object
                #              fourcc = cv2.VideoWriter_fourcc(*'XVID')
                 #             out = cv2.VideoWriter('output.avi',fourcc, 20.0, (640,480))
                              print("Error opening video stream or file")
                              continue
                       # print(image.shape)
                    #    cv2.imshow('frame',image)
                        # Convert image from camera to a numpy array
                        data = np.asarray( image, dtype="int32" )
                       # print(data[SCAN_HEIGHT][:])
                        # Empty and return the in-memory stream to beginning
                       # stream.seek(0)
                       # stream.truncate(0)
                        # Create other images
			#image = filter_colors(image)
                      #  gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
                      #  blurred = cv2.GaussianBlur(gray, (3,3), 0)
                       # thresh = cv2.threshold(blurred, 225, 255, cv2.THRESH_BINARY)[1]

                      #  dst_TELEA = cv2.inpaint(image,thresh,3,cv2.INPAINT_TELEA)
                      #  cv2.imshow('after_INPAINT.png',dst_TELEA)
                     #   previous_img=np.zeros((480,640),np.uint8)
                      #  test_img=np.array(5)
                      #  value=0 
                      #  max=0
                      #  for i in range(0,2,1):
                       #    ret,test_img=cap.read()
                        #   value= cv2.Laplacian(test_img, cv2.CV_64F).var()
                         #  if value > max:
                          #      image=test_img
                           #     max=value
                        cv2.imshow('image',image)
                        gray_image = cv2.cvtColor(image, cv2.COLOR_RGB2GRAY)
                       # print(gray_image.shape)
                        black = np.zeros((gray_image.shape), np.uint8)
                      #  print(previous_img.shape)
                        gray_black_image= cv2.addWeighted(black, 0.5, gray_image, 0.5, 0) 
                	blurr_image=cv2.GaussianBlur(gray_black_image, (kernel_size, kernel_size), 0)
                      #  cv2.imshow('blurr',blurr_image)
                        canny_image=cv2.Canny(gray_black_image, low_threshold, high_threshold)
                        gray_canny=cv2.addWeighted(canny_image,1,gray_black_image,1,0)
                      #  print(canny.shape)
                      #  gray_canny=cv2.addWeighted(canny,1,previous_img,1,0)
                      #  ret,image=cap.read()
                      #  previous_img=canny
                        cv2.imshow('with_canny',gray_canny)
                        print(gray_image[SCAN_HEIGHT][:])
                       # print(canny_image.shape)
                        cv2.imwrite('canny.jpeg',canny_image)
                      #  print(canny_image.shape)
		#	image,canny,points,lines = hough_lines(image,canny_image, min_line_length, max_line_gap,SCAN_HEIGHT,previous_lines)
                  #      if lines is not None:
                   #        pervious_lines=lines
               #         canny= cv2.addWeighted(canny_image, 1, gray_image, 1, 0)
                 #       cv2.imshow('frame',canny)
                       # image= cv2.addWeighted(hough, 0.3, img, 0.7, 0) 
       #                 print(hough_image.shape)
        #                print(image.shape
                        hough_image=gray_canny
                     #   hough_image=cv2.cvtColor(image, cv2.COLOR_RGB2GRAY)
                        cv2.imwrite('hough.jpeg',hough_image)
			display_image = cv2.copyMakeBorder(image, 0, 0, 0, 0, cv2.BORDER_REPLICATE) #change image to display_image for hough transform
                       # print(display_image.shape)
                       # print(hough_image.shape)
                        center_point = (SCAN_POS_X, SCAN_HEIGHT)
                        # San a horizontal line based on the centre point We could just use this data to work out how far off centre we are and steer 
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
                        last_point = findInCircle(display_image, scan_data)
                        cv2.line(display_image, (previous_point[0], previous_point[1]), (last_point[0], last_point[1]), (255, 255, 255), 1)
                        actual_number_of_circles = 0
                        for scan_count in range(0, NUMBER_OF_CIRCLES):
                                returnVal, scan_data = scanCircle(hough_image, display_image, last_point, SCAN_RADIUS_REG, lineAngle(previous_point, last_point))
                                # Only work out the next itteration if our point is within the bounds of the image
                                if returnVal == True:
                                        actual_number_of_circles += 1
                                        previous_point = last_point
                                        last_point = findInCircle(display_image, scan_data)
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
                        
                        returnString = "fps {} - bearing {} - x:{} y:{} look distance:{} distance from origin:{}".format(
                                      1000/ ((e2 -e1)/cv2.getTickFrequency() *1000),
                                      lineAngle(center_point, last_point) *-1 -90,
                                      center_x_distance,
                                      center_y_distance,
                                      line_scan_length,
                                      line_length_from_center)
                        print(returnString)
                        print("center={} error={}",center_point[0],center_x_distance)                                                   
                        # Wait for ESC to end program
                        c = cv2.waitKey(7) % 0x100
                        if c == 27:
                                break
        print "Closing program"
        cv2.destroyAllWindows()
        print "All windows should be closed"
        return; 
if __name__ == "__main__":
        main()
