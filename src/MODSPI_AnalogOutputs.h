#ifndef MODSPI_AnalogOutputs_h
#define MODSPI_AnalogOutputs_h

#include <MCP_DAC.h>

class MODSPI_AnalogOutputs {
  private:
    MCP4922* DAC;
    const float maxVoltage = 10.0;
    const int maxValue = 4095;

  public:
    void begin(int chipSelect);
    bool writeValue(int channel, int value);
    bool writeVoltage(int channel, float voltage);
    bool verbose = false;
};

#endif