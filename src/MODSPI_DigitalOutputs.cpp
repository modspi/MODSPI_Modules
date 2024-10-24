#include "MODSPI_DigitalOutputs.h"

void MODSPI_DigitalOutputs::begin(int chipSelect) {
  IOExpander = new MCP23S17(chipSelect);
  SPI.begin();
  IOExpander->begin(); 
  delay(20);
  IOExpander->pinMode8(0, 0x00);  //  0 = output , 1 = input
  writeAll(0);
}

bool MODSPI_DigitalOutputs::write(int pin, bool state) {
  //todo: check if begin
  if (pin < 0 || pin > 7) { //Check if pin is out of range for the module
    if (verbose) {
      Serial.println("Digital output out of range. Value must be between 0-7");
    }
    return false;
  }

  IOExpander->write1(pin, state);
  bool readState = IOExpander->read1(pin);
  bool error = readState != state;

  if (verbose) {
    Serial.print("Digital Output ");
    Serial.print(pin);
    Serial.print(" set ");
    Serial.print(state ? "ON" : "OFF");
    Serial.print(".  readback:");
    Serial.print(readState ? "ON" : "OFF");
    Serial.print(".   SPI Speed:");
    Serial.print(IOExpander->getSPIspeed());
    Serial.println();
  }
  return readState == state;
}

bool MODSPI_DigitalOutputs::writeAll(int8_t states) {
  IOExpander->write8(0,states);
  int8_t readStates = IOExpander->read8(0);
  bool error = readStates != states;

  if (verbose) {
    Serial.print("Digital Outputs set to ");
    Serial.print(states);
    Serial.print(".  readback:");
    Serial.println(readStates);
  }

  return readStates == states;
}
