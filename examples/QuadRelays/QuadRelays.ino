#include <MODSPI.h>

// Create an instance of the MODSPI_QuadRelays class named "relays1".
// If you have multiple relay modules, you'll need to create multiple instances.
MODSPI_QuadRelays relays1;

void setup() {
  relays1.begin(D5); // D5 is the chip select pin.
}

void loop() {
  for (int a = 1; a <= 4; a++) {
    relays1.write(a,HIGH); // Set the relay 'a' to HIGH.
    delay(100); // Wait for 100 milliseconds.
    relays1.write(a,LOW); // Set the relay 'a' to LOW.
    delay(100); // Wait for 100 milliseconds.
  }
}