#ifndef MODSPI_StepperController_h
#define MODSPI_StepperController_h

#include <TMC5160.h>

class MODSPI_StepperController {
  private:
    TMC5160_SPI* motor; 
    const int defaultSpeed = 400;
    const int defaultAcceleration = 400;

  public:
  
  void begin(int chipSelect);
  void setCurrent(float MotorRatedCurrent, float runCurrent, float idleCurrent);
  String getDriverStatus();
  bool isLastReadSuccessful();

  float getCurrentPosition(); // Return the current internal position (steps)
  float getEncoderPosition(); // Return the current position according to the encoder counter (steps)
  float getLatchedPosition(); // Return the position that was latched on the last ref switch / encoder event (steps)
  float getLatchedEncoderPosition(); // Return the encoder position that was latched on the last encoder event (steps)
  float getTargetPosition(); // Get the target position (steps)
  float getCurrentSpeed(); // Return the current speed (steps / second)
  
  void setCurrentPosition(float position, bool updateEncoderPos = false); // Set the current internal position (steps) and optionally update the encoder counter as well to keep them in sync.
  void setTargetPosition(float position); // Set the target position /!\ Set all other motion profile parameters before
  void setMaxSpeed(float speed); // Set the max speed VMAX (steps/second)
	void setRampSpeeds(float startSpeed, float stopSpeed, float transitionSpeed); // Set the ramp start speed VSTART, ramp stop speed VSTOP, acceleration transition speed V1 (steps / second). /!\ Set VSTOP >= VSTART, VSTOP >= 0.1
	void setAcceleration(float maxAccel); // Set the ramp acceleration / deceleration (steps / second^2)
	void setAccelerations(float maxAccel, float maxDecel, float startAccel, float finalDecel); // Set the ramp accelerations AMAX, DMAX, A1, D1 (steps / second^2) /!\ Do not set finalDecel to 0 even if transitionSpeed = 0

  bool isTargetPositionReached(void); // Return true if the target position has been reached
	bool isTargetVelocityReached(void); // Return true if the target velocity has been reached


  void fastStop(); //Stops the motor fast, ignoring the deceleration ramp set. 
  void stop(); // Stop the current motion according to the set ramp mode and motion parameters. The max speed and start speed are set to 0 but the target position stays unchanged.
	void disable(); //Disable the driver, all bridges off
	void enable(); //Enable the driver

  bool setEncoderResolution(int32_t motorSteps, int32_t encResolution, bool inverted = false);
	void setEncoderIndexConfiguration(TMC5160_Reg::ENCMODE_sensitivity_Values sensitivity, bool nActiveHigh = true, bool ignorePol = true, bool aActiveHigh = false, bool bActiveHigh = false);
	void setEncoderLatching(bool enabled);
	void setEncoderAllowedDeviation(int steps);
	bool isEncoderDeviationDetected();
	void clearEncoderDeviationFlag();

  void setShortProtectionLevels(int s2vsLevel, int s2gLevel, int shortFilter, int shortDelay = 0);

  bool verbose = true;
};

#endif