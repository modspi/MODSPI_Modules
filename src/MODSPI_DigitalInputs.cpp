#include "MODSPI_DigitalInputs.h"

void MODSPI_DigitalInputs::begin(int chipSelect) {
  MCPInputs = new MCP23S17(chipSelect);
  SPI.begin();
  MCPInputs->begin(); 
  delay(20);
  MCPInputs->pinMode8(0, 0xFF);  //  Port, 0xFF all Inputs
  //MCPInputs->setPullup8(0,0x00); //Disable pullup 
}

bool MODSPI_DigitalInputs::read(int pin) {
  //todo: check if begin
  if (pin < 0 || pin > 7) { //Check if pin is out of range for the module
    if (verbose) {
      Serial.println("Digital Input out of range. Value must be between 0-7");
    }

    return false;
  }

  bool readState = MCPInputs->read1(pin);

  if (verbose) {
    Serial.print("Digital Input ");
    Serial.print(pin);
    Serial.print(" is ");
    Serial.print(readState ? "ON" : "OFF");
    Serial.print(".   SPI Speed:");
    Serial.print(MCPInputs->getSPIspeed());
    Serial.println();
  }
  return readState;
}

int MODSPI_DigitalInputs::readAll() {
  int readStates = MCPInputs->read8(0);

  if (verbose) {
    Serial.print("Digital Inputs read ");
    Serial.println(readStates);
  }

  return readStates;
}
