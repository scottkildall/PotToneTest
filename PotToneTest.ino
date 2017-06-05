/*
  Pot Tone Test
  By Scott Kildall
    
  Output Pot Values to Serial Monitor and play tone
  And to Adafruit Backpack

  Wiring like this:
  https://www.arduino.cc/en/tutorial/potentiometer
  
 */

#include "Adafruit_LEDBackpack.h"

//-- initialize 7-segment display
Adafruit_7segment matrix = Adafruit_7segment();



// pins
const int speakerPin = 12;     // output to speaker (+), speaker (-) goes to ground
const int potPin = A1;         // input pin for the potentiometer

// other variables
const int delayTime = 1;            // how long we delay between each loop
const int analogTolerance = 5;  // how much variance we will allow before storing the last pot value, zero = none
int savedVal;                    // last potentiometer reading

void setup() {
  Serial.begin(115200);
  Serial.println("Starting Pot Tone Test");
  Serial.println("");

  //-- initialize the 4-segment number display
  matrix.begin(0x70);
  matrix.print(0);
  matrix.writeDisplay();

  pinMode(speakerPin, OUTPUT); 

  savedVal = 9999;     // set to impossible reading so that we always will store the first value
}

void loop() {
  // read the value from the sensor
  int val = analogRead(potPin);

  if( abs(val - savedVal) > analogTolerance )
    savedVal = val;
    
  // output to serial monitor and LED backpage
  Serial.println(savedVal);    
  
  matrix.print(savedVal);
  matrix.writeDisplay();
  
  tone( speakerPin, savedVal );
  
  delay(delayTime);                // stop the program for some time
}
 
