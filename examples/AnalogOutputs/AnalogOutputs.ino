#include <MODSPI.h>

// Create an instance of the MODSPI_AnalogOutputs class named "analogOutputs1".
// If you have multiple Analog Output modules, you'll need to create multiple instances.
MODSPI_AnalogOutputs analogOutputs1;

void setup() {
  // Initialize the analogOutputs1 instance with D5 as the chip select pin.
  analogOutputs1.begin(D5); // D5 is the chip select pin.
}

void loop() {
  // Ramp up from 0.0V to 10.0V on channel 0 by setting raw values (0 to 4095).
  for (int a = 0; a <= 4095; a++) {
    analogOutputs1.writeValue(0, a); // Set channel 0 to value 'a'.
    delay(1); // Wait for 1 millisecond before setting the next value.
  }

  delay(2000); // Wait for 1 second before continuing.

  // Ramp up from 0.0V to 10.0V on channel 0 by setting a voltage.
  for (float a = 0; a <= 10; a += 0.2) {
    analogOutputs1.writeVoltage(0, a); // Set channel 0 to voltage 'a'.
    delay(100); // Wait for 100 milliseconds before setting the next voltage.
  }

  delay(2000); // Wait for 2 seconds before repeating the loop.
}
