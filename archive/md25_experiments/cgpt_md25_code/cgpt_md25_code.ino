#include <Wire.h>

#define MD25_ADDRESS 0x58 // Default I2C address for MD25
#define SPEED_REG     0x00 // Register for setting motor speed
#define ENCODER_REG   0x02 // Register for reading encoder values

void setup() {
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  // Set motor speed (replace 100 with the desired speed)
  setMotorSpeed(200, 200);

  // Read encoder values
  int encoder1 = readEncoder(1);
  int encoder2 = readEncoder(2);

  // Display encoder values
  Serial.print("Encoder 1: ");
  Serial.print(encoder1);
  Serial.print("\tEncoder 2: ");
  Serial.println(encoder2);

  delay(1000); // Delay for 1 second
}

void setMotorSpeed(int speedMotor1, int speedMotor2) {
  Wire.beginTransmission(MD25_ADDRESS);
  Wire.write(SPEED_REG);
  Wire.write(speedMotor1);
  Wire.write(speedMotor2);
  Wire.endTransmission();
}

int readEncoder(int motorNumber) {
  Wire.beginTransmission(MD25_ADDRESS);
  Wire.write(ENCODER_REG + (motorNumber - 1) * 2); // Calculate the register address based on motor number
  Wire.endTransmission();

  Wire.requestFrom(MD25_ADDRESS, 2);
  if (Wire.available() >= 2) {
    int value = Wire.read() << 8 | Wire.read();
    return value;
  }

  return -1; // Return -1 in case of error
}
