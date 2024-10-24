#ifndef MODSPI_QuadRelays_h
#define MODSPI_QuadRelays_h

#include <MCP23S17.h>

class MODSPI_QuadRelays {
  private:
    MCP23S17* IOExpander; 

  public:
    void begin(int chipSelect);
    bool write(int relay, bool state);
    bool verbose = true;
};

#endif