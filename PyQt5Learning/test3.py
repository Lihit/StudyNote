#coding=utf-8
import skvideo.io 
import cv2 
import time
cap = skvideo.io.VideoCapture('1.mp4')

while True:
    ret,frame = cap.read()
    if not ret:
        break
    
    (r, g, b)=cv2.split(frame)
    frame=cv2.merge([b,g,r])
    cv2.imshow('myvideo',frame)
    if cv2.waitKey(40) & 0xff==ord('q'):
        break

