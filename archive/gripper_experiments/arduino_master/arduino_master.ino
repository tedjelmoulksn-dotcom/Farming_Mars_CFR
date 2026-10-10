#include <Wire.h>

const int irSensorPin = 2;    // Infrared sensor pin

void setup() {
  Serial.begin(9600);
  pinMode(irSensorPin, INPUT);
}

void loop() {
  int irSensorValue;

  // Read infrared sensor value
  irSensorValue = digitalRead(irSensorPin);

  // Check if an object is detected by HW201 sensor
  if (irSensorValue == HIGH) {
    Serial.println("Object Detected"); // Send a message to the receiver Arduino
    delay(3000); // Delay for 3 seconds before sending the next message
  }

  delay(1000); // Adjust the delay based on your application needs
}
