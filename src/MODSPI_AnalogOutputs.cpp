#include "MODSPI_AnalogOutputs.h"

void MODSPI_AnalogOutputs::begin(int chipSelect) {
  DAC = new MCP4922();
  SPI.begin();
  DAC->begin(chipSelect);
}

bool MODSPI_AnalogOutputs::writeValue(int channel, int value) {
  //todo: check if begin
  if (channel < 0 || channel > 1) { //Check if channel is out of range for the module
    if (verbose) {
      Serial.println("Analog output channel out of range. Value must be between 0-1");
    }
    return false;
  }

  if (value < 0 || value > maxValue) { //Check if value is out of range for the module
    if (verbose) {
      Serial.println("Analog output value out of range. Value must be between 0-4095");
    }
    return false;
  }

  DAC->write(value, channel);

  if (verbose) {
    Serial.print("Analog Output Channel ");
    Serial.print(channel);
    Serial.print(" set to ");
    Serial.print(value);
    Serial.print(".");
    Serial.println();
  }
  return true;
}

bool MODSPI_AnalogOutputs::writeVoltage(int channel, float voltage) {
  //todo: check if begin
  if (channel < 0 || channel > 1) { //Check if channel is out of range for the module
    if (verbose) {
      Serial.println("Analog output channel out of range. Value must be between 0-1");
    }
    return false;
  }

  if (voltage < 0 || voltage > maxVoltage) { //Check if value is out of range for the module
    if (verbose) {
      Serial.println("Analog output voltage out of range. Value must be between 0-10v");
    }
    return false;
  }

  int value = floor ((voltage / maxVoltage) * maxValue);

  DAC->write(value, channel);

  if (verbose) {
    Serial.print("Analog Output Channel ");
    Serial.print(channel);
    Serial.print(" set to ");
    Serial.print(voltage);
    Serial.print("V.");
    Serial.println();
  }
  return true;
}

