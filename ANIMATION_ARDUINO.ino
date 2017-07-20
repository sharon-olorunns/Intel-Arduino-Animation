/* Jumper: Using an Arduino to animate:
  Written by ScottC on 02/06/2012 */
#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

int photoRPin = 0;
int minLight;
int maxLight;
int lightLevel;
int adjustedLightLevel;
int oldLightLevel;


void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  lightLevel = analogRead(photoRPin);
  minLight = lightLevel - 10;
  maxLight = lightLevel;
  oldLightLevel = lightLevel;


}

void loop() {

  lightLevel = analogRead(photoRPin);
  delay(10);

  //auto-adjust the minimum and maximum limits in real time
  if (minLight > lightLevel) {
    minLight = lightLevel;
  }
  if (maxLight < lightLevel) {
    maxLight = lightLevel;
  }

  //Map the light level to produce a result between 1 and 28.
  adjustedLightLevel = map(lightLevel, (minLight + 20), (maxLight - 20), 1, 28);
  adjustedLightLevel = constrain (adjustedLightLevel, 1, 28);
  lcd.begin(0, 0);
  lcd.print("Adjusted LL: ");
  lcd.print(adjustedLightLevel);

  if ( adjustedLightLevel == 28) {
    digitalWrite(2, HIGH);
    int r = 25;
    int g = 200;
    int b = 160;
    lcd.setRGB(r, g, b);

  }
  else {
    digitalWrite(2, LOW);


  }

  /*Only send a new value to the Serial Port if the
    adjustedLightLevel value changes.*/
  if (oldLightLevel == adjustedLightLevel) {
    //do nothing if the old value and the new value are the same.
  } else {
    //Update the oldLightLevel value for the next round
    oldLightLevel = adjustedLightLevel;

    /*Send the adjusted Light level result
      to Serial port (processing)*/
    Serial.println(adjustedLightLevel);
  }
} 
