 Source code derived from : 
 http://processing.org/learning/topics/sequential.html
 http://processing.org/discourse/beta/num_1267080062.html

import processing.serial.*;
Serial myPort;
String sensorReading="";

// Create the array that will hold the images
PImage[] movieImage = new PImage[31];

/* The frame variable is  used to control which 
 image is displayed */
int frame = 1;


void setup() {
  fullScreen();

  myPort = new Serial(this, "COM4", 9600);
  myPort.bufferUntil('\n');

  for (int i=0; i<30; i++) {
    movieImage[i] = loadImage("Screenshot 1 (" + (i+1) + ").png");
  }
}

void draw() {
 
  image(movieImage[frame-1], 0, 0, width, height);
}

void serialEvent (Serial myPort) {
  sensorReading = myPort.readStringUntil('\n');
  if (sensorReading != null) {
    sensorReading=trim(sensorReading);
    if (sensorReading.length()<2) {
      frame = integerFromChar(sensorReading.charAt(0));
    } else {
      frame = integerFromChar(sensorReading.charAt(0))*10;
      frame += integerFromChar(sensorReading.charAt(1));
    }
  }
}



/* This function used to convert the character received from the
 serial port (Arduino), and converts it to a number */

int integerFromChar(char myChar) {
  if (myChar < '0' || myChar > '9') {
    return -1;
  } else {
    return myChar - '0';
  }
}
