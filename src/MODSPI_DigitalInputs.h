#ifndef MODSPI_DigitalInputs_h
#define MODSPI_DigitalInputs_h

#include <MCP23S17.h>

class MODSPI_DigitalInputs {
  private:
    MCP23S17* MCPInputs; 

  public:
    void begin(int chipSelect);
    bool read(int pin);
    int readAll();
    bool verbose = false;
};

#endif