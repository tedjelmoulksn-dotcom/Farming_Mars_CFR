#include <SoftwareSerial.h>

// Define software serial pins
const int rxPin = 10;
const int txPin = 11;

// Create a SoftwareSerial object
SoftwareSerial mySerial(rxPin, txPin);

void setup() {
  Serial.begin(9600);     // Initialize USB serial communication for debugging
  mySerial.begin(9600);   // Initialize software serial communication
}

void loop() {
  mySerial.println("Hello from Nano Every!");  // Send data over software serial
  delay(1000);  // Wait for 1 second
}
