# import the opencv library
from picamera.array import PiRGBArray
from picamera import PiCamera
import time
import cv2
import socket
import struct
import pickle
import imutils

# Socket Create
server_socket = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
host_ip ='192.168.1.145'# avec raspberry pi assigner manuelement l adresse ip
print('HOST IP:',host_ip)
port = 1250
socket_address = (host_ip,port)
server_socket.bind(socket_address)
server_socket.listen(5)
print("LISTENING AT:",socket_address)

while True:
    client_socket,addr = server_socket.accept()
    print('GOT CONNECTION FROM:',addr)
    if client_socket:
        camera = PiCamera()
        camera.resolution=(640,480)
        #camera.framerate = 64
        camera.framerate = 64
        rawCapture = PiRGBArray(camera,size=(640,480))
        time.sleep(0.1)
        for frame in camera.capture_continuous(rawCapture,format="bgr",use_video_port = True):
            image=frame.array
            a = pickle.dumps(image)
            message = struct.pack("Q",len(a))+a
            client_socket.sendall(message)
            cv2.imshow('frame', image)
            key = cv2.waitKey(1) & 0xFF
            rawCapture.truncate(0)
            if key == ord("q"):
                client_socket.close()
                break
        

'''
# define a video capture object
#vid = cv2.VideoCapture(0)
camera = PiCamera()
camera.resolution=(640,480)
camera.framerate = 64
rawCapture = PiRGBArray(camera,size=(640,480))
time.sleep(0.1)

for frame in camera.capture_continuous(rawCapture,format="bgr",use_video_port = True):
    image=frame.array
    cv2.imshow('frame', image)
    key = cv2.waitKey(1) & 0xFF
    rawCapture.truncate(0)
    if key == ord("q"):
        break
        '''