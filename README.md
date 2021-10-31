# Traffic_Management_Project
Project on traffic management for emergency vehicles on interconnected T-Junctions  with Arduinos and Object detection mechanism. 
# Main Hardware Functioning
This project consists of Arduino Mega and Unos; configured in Master-slave format , LCDs for display, some Ultrasonic sensors and RTC module for time calulations. The Unos regulated the lighting function in respective lanes whereas Mega kept logs of Uno's status and carried out any interrupt requests  generated by emergency vehicle detections.
# Emergency Vehicle Detection Process
The emergency vehicles are assumed to have an RFID card or Transreciever, that alerts our system when it gets close to a junction. When the emergency vehicle is detected via sensors, the Mega and sends out signals to regulate the traffic lights to slave arduinos.
# Lane-Density Calculation Process
The vehicles were counted using YOLOv3 algorithm with Darknet architecture. The algorithm was trained with Ms-coco dataset, enabling the object dection model to compare and count numerous vehicle types. This gave an advantage of counting and categorizing unique vehicles. On basis of real-time vehicle counts, the varying Density estimation for each lane was achieved. One huge advantage discoverd was when each unique vehicle type was assigned unique weightage, so that a variable time-duration for each lane to open could be generated.  
# Requirements
Arduino IDE
OpenCV
PyTorch
YoloV3 
