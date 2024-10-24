#include <MODSPI.h>

// Create an instance of the MODSPI_StepperController class named "motor1".
MODSPI_StepperController motor1;

const float motorRatedCurrent = 1.0; //The maximum current of the motor specified.
const float runCurrent = 0.8; //The current used when the motor is moving
const float idleCurrent = 0.2; //The current used when the motor is idle. 
const int maxSpeed = 2 * 200; //Max speed to 2 revs per second
const int maxAccel = 8 * 200; //Max acceleration to 8 revs per second

bool clockwiseRotation = true;

void setup() {
  motor1.begin(bay1); // Module is inserted into bay1 (chip select D5)
  
  // Optional settings
  motor1.setMaxSpeed(maxSpeed); //Set speed to 2 revolutions per second.
  motor1.setAcceleration(maxAccel); // set acceleration to 4 revolutions per second per second.
  motor1.setCurrent(motorRatedCurrent,runCurrent,idleCurrent); //Set the currents of the motor
  motor1.setCurrentPosition(0); // reset the current position to 0.
}

void loop() {
  // Check if the motor has finished traveling to the target position.
  if (motor1.isTargetPositionReached()) {
    if (clockwiseRotation) {
      motor1.setTargetPosition(200); //start the move clockwise position
      clockwiseRotation = false;
    } else {
      motor1.setTargetPosition(-200); //start the move to counter-clockwise position
      clockwiseRotation = true;
    }
  }
}