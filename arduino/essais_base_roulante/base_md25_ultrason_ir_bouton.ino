#include <Wire.h>

#define MD25ADDRESS         0x58
#define SPEED1              0x00
#define SPEED2              0x01
#define ENCODERONE          0x02
#define ENCODERTWO          0x06
#define VOLTREAD            0x0A
#define INFRARED_PIN        4     // Infrared sensor pin          brown
#define BUTTON_PIN          6     // Button pin

#define trigPin             2     // Trigger pin for ultrasonic sensor          red
#define echoPin             3     // Echo pin for ultrasonic sensor             green 
#define maxDistance         100   // Maximum distance to consider an object is not detected
#define slowdownDistance    20    // Distance at which motors should start to slow down
  int  incomingByte;
void setup() {
  Wire.begin(); // Initialize I2C communication
  Serial.begin(9600); // Initialize serial communication for debugging
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(INFRARED_PIN, INPUT); // Set infrared pin as input
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Set button pin as input with pull-up resistor
}

void loop() {
  int  incomingByte;
  if (digitalRead(BUTTON_PIN) == LOW) { // Check if button is pressed
    controlRobot(); // Function to control the robot
  } else {
    stopRobot(); // Stop the robot when button is not pressed
  }
}

void controlRobot() {
  long encoder1Value, encoder2Value; // Declare encoder variables
  int speed = 150; // Set initial motor speed
  
  // Trigger ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read ultrasonic sensor echo
  long duration = pulseIn(echoPin, HIGH);
  // Calculate distance in centimeters
  long distance = (duration * 0.0343) / 2;

  // Print distance on serial port
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Check if object is detected within a certain range
  moveMotorsForward();
  if (distance < slowdownDistance) {
    slowDownMotors(); // Slow down motors if object detected
    delay(1000); // Delay for 1 second
  }
  
  
incomingByte = digitalRead(INFRARED_PIN);

  // Check if infrared sensor detects something
  if (incomingByte != HIGH) {
    Serial.println("Object Detected");  // Send a message to the slave Arduino
    stopRobot(); // Stop the robot if infrared sensor detects something
    delay(5000); // Delay for 5 seconds
    moveMotorsForward(); // Continue moving forward after 5 seconds
  }

  // Print encoder values, battery voltage, and motor speed on serial port
  encoder1Value = readEncoder(ENCODERONE);
  encoder2Value = readEncoder(ENCODERTWO);
  float batteryVoltage = readBatteryVoltage();
  Serial.print("Encoder 1: ");
  Serial.println(encoder1Value);
  Serial.print("Encoder 2: ");
  Serial.println(encoder2Value);
  Serial.print("Battery Voltage: ");
  Serial.println(batteryVoltage);
  Serial.print("Motor Speed: ");
  Serial.println(speed);
  delay(1000); // Adjust delay based on application needs
}

void slowDownMotors() {
  Wire.beginTransmission(MD25ADDRESS);
  Wire.write(SPEED2);
  Wire.write(175); // Set speed to maximum (255) for motor 2 (adjust as needed for your setup)
  Wire.endTransmission();

  Wire.beginTransmission(MD25ADDRESS);
  Wire.write(SPEED1);
  Wire.write(175); // Set speed to maximum (255) for motor 1 (adjust as needed for your setup)
  Wire.endTransmission();
}

void moveMotorsForward() {
  Wire.beginTransmission(MD25ADDRESS);
  Wire.write(SPEED2);
  Wire.write(200); // Set speed to maximum (255) for motor 2 (adjust as needed for your setup)
  Wire.endTransmission();

  Wire.beginTransmission(MD25ADDRESS);
  Wire.write(SPEED1);
  Wire.write(200); // Set speed to maximum (255) for motor 1 (adjust as needed for your setup)
  Wire.endTransmission();
}

void stopRobot() {
  Wire.beginTransmission(MD25ADDRESS);
  Wire.write(SPEED2);
  Wire.write(128); // Set speed to stop (128) for motor 2
  Wire.endTransmission();

  Wire.beginTransmission(MD25ADDRESS);
  Wire.write(SPEED1);
  Wire.write(128); // Set speed to stop (128) for motor 1
  Wire.endTransmission();
}

long readEncoder(byte encoder) {
  Wire.beginTransmission(MD25ADDRESS);
  Wire.write(encoder);
  Wire.endTransmission();
  
  Wire.requestFrom(MD25ADDRESS, 4);
  while (Wire.available() < 4);
  
  long encoderValue = (long)Wire.read() << 24 | (long)Wire.read() << 16 | (long)Wire.read() << 8 | (long)Wire.read();
  
  // Adjust for signed long (two's complement)
  if (encoderValue & 0x80000000) {
    encoderValue |= 0xFFFFFFFF00000000;
  }
  
  return encoderValue;
}

float readBatteryVoltage() {
  Wire.beginTransmission(MD25ADDRESS);
  Wire.write(VOLTREAD);
  Wire.endTransmission();
  
  Wire.requestFrom(MD25ADDRESS, 1);
  while (Wire.available() < 1);
  int batteryVoltage = Wire.read();
  
  return batteryVoltage / 10.0; // Convert to volts
}
