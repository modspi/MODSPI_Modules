#include "MODSPI_AnalogInputs.h"

void MODSPI_AnalogInputs::begin(int chipSelect) {
  ADC = new MCP3202();
  SPI.begin();
  ADC->begin(chipSelect);
}

int MODSPI_AnalogInputs::readValue(int channel) {
  //todo: check if begin
  if (channel < 0 || channel > 1) { //Check if channel is out of range for the module
    if (verbose) {
      Serial.println("Analog input channel out of range. Value must be between 0-1");
    }
    return false;
  }

  int value = ADC->read(channel);
  
  if (verbose) {
    Serial.print("Analog Input Channel ");
    Serial.print(channel);
    Serial.print(" reads ");
    Serial.print(value);
    Serial.print(".");
    Serial.println();
  }
  return value;
}

float MODSPI_AnalogInputs::readVoltage(int channel) {
  //todo: check if begin
  if (channel < 0 || channel > 1) { //Check if channel is out of range for the module
    if (verbose) {
      Serial.println("Analog itput channel out of range. Value must be between 0-1");
    }
    return false;
  }

  int value = ADC->read(channel); 
  float voltage = (float(value) / float(maxValue)) * maxVoltage;

  if (verbose) {
    Serial.print("Analog Input Channel ");
    Serial.print(channel);
    Serial.print(". value is ");
    Serial.print(value);
    Serial.print(". Voltage is ");
    Serial.print(voltage);    
    Serial.print("V.");
    Serial.println();
  }
  return voltage;
}

