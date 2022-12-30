import cv2
import glob
import os
import numpy as np
from os import listdir
from os.path import isfile,join
import math
import serial


ser = serial.Serial('COM5',baudrate = 115200,timeout =0.1) #create serial port
ser_1 = serial.Serial('COM1',baudrate = 115200,timeout =0.1) #create serial port


cap = cv2.VideoCapture(0)
font = cv2.FONT_HERSHEY_COMPLEX


while True:
        _,frame_camera_cap = cap.read()        
        frame_camera = frame_camera_cap[120:380,0:640]
        cv2.imshow('frame',frame_camera);

        data = ser.readline().decode('ascii')
        if data == 'X':
            _,frame_cap = cap.read()
            frame = frame_cap[120:380,0:640]
            #Gauss filtering
            frame_gauss = cv2.GaussianBlur(frame,(5,5),0.3)

            obj_hsv = np.zeros(frame.shape,dtype="uint8")
            mask_green = np.zeros(frame.shape,dtype="uint8")
            mask_yellow = np.zeros(frame.shape,dtype="uint8")
            frame_copy = []
            frame_copy = frame.copy()
                
                
            hsv_frame =cv2.cvtColor(frame_gauss,cv2.COLOR_BGR2HSV)        

            #remove white background
            lower_background = np.array([0,67,0])
            upper_background = np.array([180,255,255])
            mask_background = cv2.inRange(hsv_frame,lower_background,upper_background)
            kernel_background = np.ones((5,5),np.uint8)
            mask_background = cv2.erode(mask_background,kernel_background)    

            #find largest contour
            _, contours,_ = cv2.findContours(mask_background,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)
            contours = sorted(contours,key = cv2.contourArea)
            cnt = contours[len(contours)-1]
            area = cv2.contourArea(cnt)
            
            approx = cv2.approxPolyDP(cnt,0.0001*cv2.arcLength(cnt,True),True)
            cv2.drawContours(frame_copy,[approx],0,(255,0,0),5)
        
            #draw rectangle in the found contour
            rect = cv2.minAreaRect(cnt)
            box = cv2.boxPoints(rect)
            box = np.int0(box)
            cv2.drawContours(frame_copy, [box], 0, (0,0,255), 2)
            #find and draw the center of contour
            M = cv2.moments(cnt)
            cX = int(M["m10"] / M["m00"])
            cY = int(M["m01"] / M["m00"])                
            cv2.circle(frame_copy, (cX, cY), 7, (255, 255, 255), -1)
            cv2.putText(frame_copy, "center", (cX - 20, cY - 20),cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 255, 255), 2)

            size_1 = rect[1][0] 
            size_2 = rect[1][1]
            if size_1 > size_2:
                    long_pixel = int(size_1)
                    short_pixel = int(size_2)
            else:
                    long_pixel = int(size_2)
                    short_pixel = int(size_1)
            long_real_number = int(long_pixel*10 /28)
            short_real_number = int(short_pixel*10/28)
                 
            mask = np.zeros(frame.shape,dtype="uint8")
            cv2.drawContours(mask, [cnt], -1, 255, -1)
            mask_gray = cv2.cvtColor(mask,cv2.COLOR_BGR2GRAY)            
            _, mask_threshhold = cv2.threshold(mask_gray, 10, 255, cv2.THRESH_BINARY)           
            obj_rbg = cv2.bitwise_and(frame,frame,mask = mask_threshhold)
            obj_hsv = cv2.cvtColor(obj_rbg,cv2.COLOR_BGR2HSV)

            #green filtering
            lower_green = np.array([30,0,9])
            upper_green = np.array([80,255,255])
            mask_green = cv2.inRange(obj_hsv,lower_green,upper_green)
            kernel_green = np.ones((5,5),np.uint8)
            mask_green = cv2.erode(mask_green,kernel_green)
            pixel_green = cv2.countNonZero(mask_green)
            green_rate = int((pixel_green / area) *100)

            #yellow filtering
            lower_yellow = np.array([15,0,9])
            upper_yellow = np.array([30,255,255])
            mask_yellow = cv2.inRange(obj_hsv,lower_yellow,upper_yellow)
            kernel_yellow = np.ones((5,5),np.uint8)
            mask_yellow = cv2.erode(mask_yellow,kernel_yellow)
            pixel_yellow = cv2.countNonZero(mask_yellow)
            yellow_rate = int((pixel_yellow / area) *100)

            #calculate the number of black pixel
            pixel_black = area - pixel_green - pixel_yellow
            black_rate = 100 - green_rate - yellow_rate
            #color classification
            if pixel_green > pixel_yellow:
                    color = 'green'
            else:
                    color = 'yellow'


            #size classification
            if long_real_number > 120:
                    size = 'long'
            else:
                    size = 'short'

            #overall classification
            if (color == 'green') and (size == 'long'):    classification = 1;
            if (color == 'green') and (size == 'short'):    classification = 2;
            if (color == 'yellow') and (size == 'long'):    classification = 3;
            if (color == 'yellow') and (size == 'short'):    classification = 4;

            cv2.putText(frame_copy,'pixel_green ='+ str(pixel_green),(0,30),font,1,(13,255,255))
            cv2.putText(frame_copy,'pixel_yellow ='+ str(pixel_yellow),(0,60),font,1,(13,255,255))
            cv2.putText(frame_copy,'pixel_black ='+ str(pixel_black),(0,90),font,1,(13,255,255))
            cv2.putText(frame_copy,'black_rate ='+ str(black_rate)+'%',(0,120),font,1,(13,255,255))
            cv2.putText(frame_copy,'chieu long ='+ str(long_pixel) + 'pixel'+ '=' + str(long_real_number),(0,150),font,1,(13,255,255))
            cv2.putText(frame_copy,'chieu rong='+ str(short_pixel) + 'pixel'+ '=' + str(short_real_number),(0,180),font,1,(13,255,255))
            cv2.putText(frame_copy,'Phan loai: ' + color +'  ' + size ,(0,210),font,1,(13,255,255))                
            cv2.putText(frame_copy,'Toa do tam ' + str(cX) +'  ' + str(cY) ,(0,240),font,1,(13,255,255))

            #transfer data for micro controller
            info = str(cX)+'.'+str(cY)+'.'+ str(short_real_number)+'.'+str(classification)+'A'
            ser.write(bytes(info,encoding='utf8'))
            #display the information in the screen
            info_to_display = str(long_real_number) +'.' +  str(short_real_number)+ '.' +str(green_rate)+ '.' + str(yellow_rate)+ '.' + str(black_rate)+ '.'+str(classification);
            ser_1.write(bytes(info_to_display,encoding='utf8'))

        key = cv2.waitKey(1);
        if key == 27:
            break

cap.release()
cv2.destroyAllWindows()


