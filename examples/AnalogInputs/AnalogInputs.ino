#include <MODSPI.h>

// Create an instance of the MODSPI_AnalogInputs class named "analogInputs1".
// If you have multiple Analog Input modules, you'll need to create multiple instances.
MODSPI_AnalogInputs analogInputs1;

void setup() {
  // Initialize the analogInputs1 instance with D5 as the chip select pin.
  analogInputs1.begin(D5); // D5 is the chip select pin.
}

void loop() {
  // Loop through analog inputs 0 to 1 and read their values and voltages.
  for (int a = 0; a <= 1; a++) {
    int readADCValue = analogInputs1.readValue(a);   // Read the raw ADC value of input 'a'.
    float readADCVoltage = analogInputs1.readVoltage(a); // Read the voltage of input 'a'.
    
    // Print the ADC value and voltage to the serial monitor.
    Serial.print("Analog Input ");
    Serial.print(a);
    Serial.print(": ADC Value = ");
    Serial.print(readADCValue);
    Serial.print(", Voltage = ");
    Serial.println(readADCVoltage);
  }
  
  delay(500); // Wait for 500 milliseconds before repeating the loop.
}
