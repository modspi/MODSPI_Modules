#include <MODSPI.h>

//MODSPI - Homing Routine Example
// This is an example of how todo advanced homing with the MODSPI system
// The routine looks for a rising edge of a homing switch, moving the motor towards it
// Once a rising edge is found, it backs away at a slower speed to find the falling edge
// The axis then moves towards a park position. Once parked it moves to a far away position and then 
// back towards the homing switch where it repeats the loop.
//
// Note: this code is also in MM and converts to Steps. 
// This routine requires a stepper motor module & a digital inputs module
// It is only intended as a guide to help you test and structure your code. 
// ---------------------------------------------------------------------------------------------

// Create an instance of the MODSPI_StepperController class named "motor1".
MODSPI_StepperController motor1;
//Create an instance of the MODSPI_DigitalInputs class named "inputs1"
MODSPI_DigitalInputs inputs1;

const float motorRatedCurrent = 1.0;  //The maximum current of the motor specified.
const float runCurrent = 0.8;         //The current used when the motor is moving
const float idleCurrent = 0.2;        //The current used when the motor is idle.

float stepsPerRotation = 200;  //Most motors have 200 steps per revolution
float mmPerRotation = 40;      //20tooth x 2mm pitch
float stepsPerMM = stepsPerRotation / mmPerRotation;

float speedMM = 200;      //Move at 200mm per second
float accelMM = 200;      //Accelerate at 200mm per second
float homeSpeedMM = 40;   //Home at 80mm per second
float homeAccelMM = 200;  //Home accel at 200mm per second

float travelLimitMM = 300;  // max travel of 300mm
float parkPositionMM = 5;   // parked poisition of 5mm
float OutPositionMM = 250;  // move motor to out position
float MidPositionMM = 50;  // Position near the homing

float speedSteps = (speedMM / mmPerRotation) * stepsPerRotation;
float accelSteps = (accelMM / mmPerRotation) * stepsPerRotation;
float homeSpeedSteps = (homeSpeedMM / mmPerRotation) * stepsPerRotation;
float homeAccelSteps = (accelMM / mmPerRotation) * stepsPerRotation;
float travelLimitSteps = (travelLimitMM / mmPerRotation) * stepsPerRotation;
float parkPositionSteps = (parkPositionMM / mmPerRotation) * stepsPerRotation;
float OutPositionSteps = (OutPositionMM / mmPerRotation) * stepsPerRotation;
float MidPositionSteps = (MidPositionMM / mmPerRotation) * stepsPerRotation;

enum HomingState {
  UNKNOWN,
  LOOKING_FOR_RISING_EDGE,
  LOOKING_FOR_FALLING_EDGE,
  PARKING,
  HOMED,
  FAILED
}; 
HomingState homingState1;


enum MovingState {
  NONE,
  MovingOut,
  MovingIn
}; 
MovingState movingState1;


void setup() {
  motor1.begin(bay1);   // Stepper Motor module is inserted into bay1 (chip select D5)
  inputs1.begin(bay2);  // Digital Input module is inserted into bay2 (chip select D6)

  // Optional settings
  motor1.setMaxSpeed(speedSteps);                                   //Set speed to 2 revolutions per second.
  motor1.setAcceleration(accelSteps);                               // set acceleration to 4 revolutions per second per second.
  motor1.setCurrent(motorRatedCurrent, runCurrent, idleCurrent);  //Set the currents of the motor
  motor1.setCurrentPosition(0);                                   // reset the current position to 0.
}

void loop() {
  delay(1);  //Wait 1ms

  if (homingState1 != HOMED) {
    homeMotor1();  //Home Motor routine
  } else {
    if (motor1.isTargetPositionReached()) { 
      homingState1 = UNKNOWN;
    }
  }
}

void homeMotor1() {
  bool motor1HomeSwitchState = debounceSwitch(7);

  switch (homingState1) {
    case UNKNOWN:
      motor1.fastStop(); //Quickly stops the motor
      motor1.setCurrentPosition(0);  //reset the current position
      Serial.println("Starting homing.");
      motor1.setMaxSpeed(homeSpeedSteps); //Set speed to homing speed
      motor1.setAcceleration(homeAccelSteps); // set acceleration to homing accleration
      motor1.setTargetPosition(-travelLimitSteps);  //move backwards towards homing switch
      homingState1 = LOOKING_FOR_RISING_EDGE;
      break;

    case LOOKING_FOR_RISING_EDGE:
      if (motor1HomeSwitchState == HIGH) {
        Serial.println("Rising Edge found! Now looking for falling edge.");
        motor1.fastStop(); //quickly stop the motor
        motor1.setCurrentPosition(0); //reset the current position
        motor1.setMaxSpeed(homeSpeedSteps / 5);  //set speed to 1/5th speed of homing
        motor1.setAcceleration(homeAccelSteps / 5); //set acceleration to 1/5th the homing accel
        motor1.setTargetPosition(travelLimitSteps);  //move forwards slowly away from homing switch
        homingState1 = LOOKING_FOR_FALLING_EDGE;
      } else if (motor1.isTargetPositionReached()) {
        Serial.println("Failed to find homing switch rising edge within travel limit");
        homingState1 = FAILED;
      }
      break;

    case LOOKING_FOR_FALLING_EDGE:
      if (motor1HomeSwitchState == LOW) {
        Serial.println("Falling Edge found! Now parking.");
        motor1.fastStop(); //Quickly stop the motor
        motor1.setCurrentPosition(0); //reset the position
        motor1.setMaxSpeed(speedSteps); //set speed to normal speed
        motor1.setAcceleration(accelSteps); //set acceleration to normal acceleration
        motor1.setTargetPosition(parkPositionSteps);  //move forwards to park position away from homing switch
        homingState1 = PARKING;
      } else if (motor1.isTargetPositionReached()) {
        Serial.println("Failed to find homing switch falling edge within travel limit");
        homingState1 = FAILED;
      }
      break;

    case PARKING:
      if (motor1.isTargetPositionReached()) {
        Serial.println("Homing Finished");
        homingState1 = HOMED;
      }
      break;
  }
}

void moveMotor1() {
  if (motor1.isTargetPositionReached()) {
    switch (movingState1) {
      case NONE:
        motor1.setTargetPosition(OutPositionSteps); //move to out position
        movingState1 = MovingOut;
        break;
      case MovingOut:
        motor1.setTargetPosition(MidPositionSteps); //move to mid position near homing
        movingState1 = MovingIn;
        break;
      case MovingIn:
        movingState1 = NONE; //stop moving and start homing
        homingState1 = UNKNOWN; //reset routine to start homing again
        break;
    }
  }
}

bool debounceSwitch(int Din) {
  //Sometimes the digital input is a little noisy. This function just adds a delay before reading again. 
  //Optional, but helps with reliability of homing.
  bool startState = inputs1.read(Din);
  delay(5);
  return inputs1.read(Din);
}