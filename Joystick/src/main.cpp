/**
 * @file: Joystick
 * @brief: Main code that takes position of joystick as input to be sent to robot to control its movement
 * @author: Ellie Zhang
 * @bug: No known bugs
*/

#include <Arduino.h>
#include <math.h>

#define joyX A0
#define joyY A1
int x_coord; int y_coord;
double magnitude; int max_magnitude; double percentage;
double left; double right;
unsigned long time; unsigned long loop_time; unsigned long difference;
 
void setup() {
  Serial.begin(9600);
  time = millis(); //time since program started running
}
 
void loop() { // put your main code here, to run repeatedly:

  loop_time = millis(); //start time of loop
  difference = loop_time - time; //time taken to execute loop

  if (difference >= 50){ //ensures data is only read every 50 milliseconds
    time = loop_time; 
    int xValue = analogRead(joyX); //read raw x-component value from joystick position
    int yValue = analogRead(joyY); //read raw y-component value from joystick position

    // adjusts joystick axes values to reflect that of a standard axis using the map function
    // x_coord is calibrated adjusted xValue and y_coord is adjusted yValue
    if (xValue > 535){
      x_coord = map(xValue, 535, 1023, 0, 511);
    }
    else if (xValue < 525){
      x_coord = map (xValue, 0, 525, -511, 0);
    }
    else if (xValue >= 525 && xValue < 535){
      x_coord = 0;
    }
    
    if (yValue < 515){
        y_coord = map(yValue, 0, 515, 511, 0 );
    }
    else if (yValue >= 525){
      y_coord = map(yValue, 525, 1023, 0, -511);
    }
    else if (yValue >= 515 && yValue < 525) {
      y_coord = 0;
    }

    int magnitude = sqrt(sq(x_coord) + sq(y_coord));  //finds magnitude of joystick vector
    double max_magnitude = 511; // sets max magnitude to the radius of joystick's circular range
    magnitude = max_magnitude; //accounts for actual joystick specifications (translates square to circle)
    
    double angle = atan2(y_coord, x_coord); //finds the angle of joystick position (from the x axis)
    double degrees = angle * 180 / PI; //convert radians to degrees
    double percentage = magnitude/max_magnitude * 100; //finds percent of max magnitude of joystick position

    //If the joystick is in first quadrant, turns the robot to the right.
    if (degrees <= 90 && degrees >= 0){
      left = percentage;
      right = sin(angle)*percentage;
    }

    //If the joystick is in the second quadrant, turns the robot to the left.
    else if (degrees > 90 && degrees <= 180){
      right = percentage;
      left = sin(angle) * percentage;
    }

    //If the joystick is in the third quadrant, turns the robot back and to the left.
    else if (degrees < 0 && degrees < -90){
      right = -percentage;
      left = sin(angle) * percentage;
    }

    //If the joystick is in the fourth quadrant, turns the robot back and to the right.
    else if (degrees < 0 && degrees >= -90){
      left = -percentage;
      right = sin(angle) * percentage;
    }


    /**
     * Following comments print out values for debugging purposes:
     * 
     * 
     * Serial.print("rX: " ); Serial.print(xValue); Serial.print("\t"); Serial.print("rY: "); Serial.print(yValue);
     * Serial.print("\t");
     * Serial.print("X: "); Serial.print(x_coord); Serial.print("\t"); Serial.print("Y: "); Serial.print(y_coord);
     * Serial.print("\t");
     * Serial.print("Angle: "); Serial.print(degrees);
     * Serial.print("\t");
     * Serial.print("Magnitude: "); Serial.print(magnitude); Serial.print("\t"); Serial.print("Percent: "); Serial.print(percentage);
     * Serial.print("\t");
     * Serial.print("L: "); Serial.print(left); Serial.print("\t"); Serial.print("R: "); Serial.println(right);
    */
  }
  
}