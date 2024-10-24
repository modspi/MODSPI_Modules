#include "MODSPI_StepperController.h"

void MODSPI_StepperController::begin(int chipSelect) {
  SPI.begin();
  motor = new TMC5160_SPI(chipSelect);

  TMC5160::PowerStageParameters powerStageParams;  // defaults.
  TMC5160::MotorParameters motorParams;
  motorParams.globalScaler = 32;
  motorParams.irun = 15;
  motorParams.ihold = 5;

  motor->begin(powerStageParams, motorParams, TMC5160::NORMAL_MOTOR_DIRECTION);
  motor->setRampMode(TMC5160::POSITIONING_MODE);

  motor->setMaxSpeed(defaultSpeed);
  motor->setAcceleration(defaultAcceleration);
}

void begin(int chipSelect);

String MODSPI_StepperController::getDriverStatus() {
  return motor->getDriverStatusDescription(motor->getDriverStatus());
}

bool MODSPI_StepperController::isLastReadSuccessful() {
  return motor->isLastReadSuccessful();
}

float MODSPI_StepperController::getCurrentPosition() {
  return motor->getCurrentPosition();
}

float MODSPI_StepperController::getEncoderPosition() {
  return motor->getEncoderPosition();
}

float MODSPI_StepperController::getLatchedPosition() {
  return motor->getLatchedPosition();
}

float MODSPI_StepperController::getLatchedEncoderPosition() {
  return motor->getLatchedEncoderPosition();
}

float MODSPI_StepperController::getTargetPosition() {
  return motor->getTargetPosition();
}

float MODSPI_StepperController::getCurrentSpeed() {
  return motor->getCurrentSpeed();
}

void MODSPI_StepperController::setCurrentPosition(float position, bool updateEncoderPos) {
  motor->setCurrentPosition(position, updateEncoderPos);
}

void MODSPI_StepperController::setTargetPosition(float position) {
  motor->setTargetPosition(position);
}

void MODSPI_StepperController::setMaxSpeed(float speed) {
  motor->setMaxSpeed(speed);
}

void MODSPI_StepperController::setRampSpeeds(float startSpeed, float stopSpeed, float transitionSpeed) {
  motor->setRampSpeeds(startSpeed, stopSpeed, transitionSpeed);
}

void MODSPI_StepperController::setAcceleration(float maxAccel) {
  motor->setAcceleration(maxAccel);
}

bool MODSPI_StepperController::isTargetPositionReached(void) {
  return motor->isTargetPositionReached();
}

bool MODSPI_StepperController::isTargetVelocityReached(void) {
  return motor->isTargetVelocityReached();
}

void MODSPI_StepperController::stop() {
  motor->stop();
}

void MODSPI_StepperController::fastStop() {
  motor->writeRegister(TMC5160_Reg::VSTOP,1000000);
  motor->writeRegister(TMC5160_Reg::DMAX,1000000);

  float currentPos = motor->getCurrentPosition();
  motor->setTargetPosition(currentPos);

  int16_t readAMAX = motor->readRegister(TMC5160_Reg::AMAX);
  motor->writeRegister(TMC5160_Reg::VSTOP,100);
  motor->writeRegister(TMC5160_Reg::DMAX,readAMAX);
  }

void MODSPI_StepperController::disable() {
  motor->disable();
}

void MODSPI_StepperController::enable() {
  motor->enable();
}

void MODSPI_StepperController::setCurrent(float MotorRatedCurrent, float runCurrent, float idleCurrent) {
  TMC5160::PowerStageParameters powerStageParams;  // defaults.
  TMC5160::MotorParameters motorParams;
  float senseResistor = 0.075;
  float maxRmsCurrent = 0.33 / (senseResistor * sqrt(2.0));
  motorParams.globalScaler = constrain(floor(MotorRatedCurrent * 256.0 / maxRmsCurrent), 32, 256);
  motorParams.irun = constrain(floor(runCurrent * 31.0 / (maxRmsCurrent * (float)motorParams.globalScaler / 256.0)), 0, 31);
  float motorCurrentReduction = idleCurrent / runCurrent;
  motorParams.ihold = constrain(floor((float)motorParams.irun * motorCurrentReduction), 0, 31);
  
  motor->begin(powerStageParams, motorParams, TMC5160::NORMAL_MOTOR_DIRECTION);
}

bool MODSPI_StepperController::setEncoderResolution(int32_t motorSteps, int32_t encResolution, bool inverted) {
  return motor->setEncoderResolution(motorSteps, encResolution, inverted);
}

void MODSPI_StepperController::setEncoderLatching(bool enabled) {
  motor->setEncoderLatching(enabled);
}

void MODSPI_StepperController::setEncoderAllowedDeviation(int steps) {
  motor->setEncoderAllowedDeviation(steps);
}

bool MODSPI_StepperController::isEncoderDeviationDetected() {
  return motor->isEncoderDeviationDetected();
}

void MODSPI_StepperController::clearEncoderDeviationFlag() {
  motor->clearEncoderDeviationFlag();
}

void MODSPI_StepperController::setShortProtectionLevels(int s2vsLevel, int s2gLevel, int shortFilter, int shortDelay) {
  motor->setShortProtectionLevels(s2vsLevel, s2gLevel, shortFilter);
}