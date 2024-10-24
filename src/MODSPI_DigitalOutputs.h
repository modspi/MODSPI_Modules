#ifndef MODSPI_DigitalOutputs_h
#define MODSPI_DigitalOutputs_h

#include <MCP23S17.h>

class MODSPI_DigitalOutputs {
  private:
    MCP23S17* IOExpander; 

  public:
    void begin(int chipSelect);
    bool write(int pin, bool state);
    bool writeAll(int8_t states);
    bool verbose = false;
};

#endif