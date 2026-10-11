#include <Servo.h>

const int servoPin = 9;    // Servo control pin
Servo myservo; // Create servo object to control a servo

void setup() {
  Serial.begin(9600);
  myservo.attach(servoPin); // Attach the servo on pin 9 to the servo object
  myservo.write(0); // Move the servo to 0 degrees
}

void loop() {
  if (Serial.available() > 0) {
    String message = Serial.readStringUntil('\n');
    if (message == "Object Detected") {
      myservo.write(180); // Move the servo to 180 degrees
      delay(2000); // Wait for a second
      myservo.write(0); // Move the servo back to 0 degrees
    }
  }
}
