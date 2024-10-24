#include <MODSPI.h>

// Create an instance of the MODSPI_DigitalInputs class named "inputs1".
// If you have multiple Digital Input modules, you'll need to create multiple instances.
MODSPI_DigitalInputs inputs1;

void setup() {
  Serial.begin(115200); // Initialize serial communication at a baud rate of 115200.
  inputs1.begin(D5);    // Initialize the inputs1 instance with D5 as the chip select pin.
}

void loop() {
  // Loop through digital inputs 0 to 7 and read their values.
  for (int a = 0; a <= 7; a++) {
    bool readInput = inputs1.read(a); // Read the value of input 'a'.
    Serial.print("Input");
    Serial.print(a);                  // Print the input number.
    Serial.print(": ");
    Serial.println(readInput);        // Print the value of the input (HIGH or LOW).
  }

  // Read the values of all inputs simultaneously.
  int8_t readAllInputs = inputs1.readAll(); // Read all inputs and return a byte with each bit representing an input.
  Serial.print("readAll: ");
  Serial.println(readAllInputs);            // Print the combined value of all inputs.

  delay(500); // Wait for 500 milliseconds before repeating the loop.
}
