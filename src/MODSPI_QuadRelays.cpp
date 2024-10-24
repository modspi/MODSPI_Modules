#include "MODSPI_QuadRelays.h"

void MODSPI_QuadRelays::begin(int chipSelect) {
  IOExpander = new MCP23S17(chipSelect);
  SPI.begin();
  IOExpander->begin(); 
  delay(20);
  IOExpander->pinMode8(0, 0x00);  //  0 = output , 1 = input
  write(1,0);
  write(2,0);
  write(3,0);
  write(4,0);

}

bool MODSPI_QuadRelays::write(int relay, bool state) {
  //todo: check if begin
  int pin = relay-1; //Relays are 1-4, pins are 0-3

  if (pin < 0 || pin > 3) { //Check if pin is out of range for the module
    if (verbose) {
      Serial.println("relay out of range. Value must be between 1-4");
    }
    return false;
  }

  IOExpander->write1(pin, state);
  bool readState = IOExpander->read1(pin);
  bool error = readState != state;

  if (verbose) {
    Serial.print("Relay ");
    Serial.print(relay);
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


