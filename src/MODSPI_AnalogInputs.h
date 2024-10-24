#ifndef MODSPI_AnalogInputs_h
#define MODSPI_AnalogInputs_h

#include <MCP_ADC.h>

class MODSPI_AnalogInputs {
  private:
    MCP3202* ADC;
    const float maxVoltage = 10.0;
    const int maxValue = 4095;

  public:
    void begin(int chipSelect);
    int readValue(int channel);
    float readVoltage(int channel);
    bool verbose = false;
};

#endif