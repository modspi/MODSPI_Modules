#include <MODSPI.h>

// Create an instance of the MODSPI_DigitalOutputs class named "outputs1".
// If you have multiple Digital Output modules, you'll need to create multiple instances.
MODSPI_DigitalOutputs outputs1; 

void setup() {
  // Initialize the outputs1 instance with D5 as the chip select pin.
  outputs1.begin(D5); // D5 is the chip select pin.

  outputs1.writeAll(255); // Set all of the output channels to HIGH.
  delay(300); // Wait for 300 milliseconds.
  outputs1.writeAll(0); // Set all of the output channels to LOW.
}

void loop() {
  // Loop through digital outputs 0 to 7, turning each on and off in sequence.
  for (int a = 0; a <= 7; a++) {
    outputs1.write(a, HIGH); // Set the output 'a' to HIGH.
    delay(100); // Wait for 100 milliseconds.
    outputs1.write(a, LOW);  // Set the output 'a' to LOW.
  }  
}
