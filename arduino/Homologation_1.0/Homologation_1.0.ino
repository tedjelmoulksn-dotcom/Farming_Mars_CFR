// ----- VERSION - 1.0 ----- //

// ----- HOMOLOGATION ----- //

#include <Wire.h>

#define MD25ADDRESS 0x58
#define SPEED1 0x00
#define SPEED2 0x01
#define ENCODERONE 0x02
#define ENCODERTWO 0x06
#define VOLTREAD 0x0A
#define INFRARED_PIN 4  // Infrared sensor pin          brown
#define BUTTON_PIN 6    // Button pin
#define trigPin 2            // Trigger pin for ultrasonic sensor
#define echoPin 3            // Echo pin for ultrasonic sensor
#define Trig2Pin 8            // Trigger pin for ultrasonic sensor
#define Echo2Pin 9            // Echo pin for ultrasonic sensor
#define SIG_TrigEcho3Pin 10       // SIG pin for ultrasonic sensor
#define maxDistance 100      // Maximum distance to consider an object is not detected
#define slowdownDistance 20  // Distance at which motors should start to slow down
#define STOP_DISTANCE 20     // Distance at which motors should stop
#define FALSE 0
#define TRUE 1
#define NB_ITERATIONS_LIGNE_DROITE 25
#define NB_ITERATIONS_TOURNER 70
#define LED_PIN 13

int button_pressed = 0;
int demarrage = 0 ;
int incomingByte;
int iterations = 0;
int angle = 90;
int Right = FALSE, Left = TRUE;
// int Right = TRUE, Left = FALSE;
int compteur = 0;

void setup() {
  Wire.begin();        // Initialize I2C communication
  Serial.begin(9600);  // Initialize serial communication for debugging
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(Trig2Pin, OUTPUT);
  pinMode(Echo2Pin, INPUT);
  pinMode(SIG_TrigEcho3Pin, OUTPUT);
  pinMode(INFRARED_PIN, INPUT);       // Set infrared pin as input
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // Set button pin as input with pull-up resistor
  pinMode(INFRARED_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  cordetirer();
  delay(100);
  while(demarrage == 1) {
    if(compteur == 0) {
      compteur = 1;
      digitalWrite(13, HIGH);
      delay(100);
      digitalWrite(13, LOW);
      iterations = 0;
    }
    
    if((digitalRead(BUTTON_PIN) == LOW) && (button_pressed == FALSE)) {
      if(iterations < NB_ITERATIONS_LIGNE_DROITE) {
        if(digitalRead(BUTTON_PIN) == LOW) {  // Check if button is pressed
          controlRobot();                      // Function to control the robot
        } 
        else {
          stopRobot();  // Stop the robot when button is not pressed
        }
        iterations++;
      }
      else if((iterations < NB_ITERATIONS_TOURNER) && (iterations > NB_ITERATIONS_LIGNE_DROITE) && (button_pressed == FALSE)) {
        if ((digitalRead(BUTTON_PIN) == LOW)) {  // Check if button is pressed
          turnRobot(angle, Right, Left);         // Function to turn the robot
        } 
        else {
          stopRobot();  // Stop the robot when button is not pressed
        }
        if(iterations == (NB_ITERATIONS_TOURNER - 1)) {
          iterations = -1;
        }
        iterations++;
      }
      else {
        stopRobot();
        iterations++;
      }
    }
    else {
      stopRobot();
      if(iterations >= NB_ITERATIONS_TOURNER) {
          iterations = -1;
        }
    }

    Serial.println(iterations); 
  }
  delay(100);
}

void cordetirer() {
  int sensorValue = digitalRead(INFRARED_PIN);
  if (sensorValue == HIGH)
  {
    char caractereC = 'C';
    Serial.println(caractereC); // Corde enlevée ! afficher sur l'OLED de la pince.
    demarrage = 1 ;
  }
}

// Function to measure distance for a given sensor
long measureDistance(int TrigPin, int EchoPin) {
  // Trigger the sensor
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);

  // Read the echo
  long duration = pulseIn(EchoPin, HIGH);

  // Calculate the distance in centimeters
  long distance = (duration * 0.0343) / 2;

  return distance;
}

// Function to measure distance for sensors with a single SIG pin
long measureDistanceSinglePinSIG(int SIGPin) {
  // Set SIGPin as output to trigger the sensor
  pinMode(SIGPin, OUTPUT);
  digitalWrite(SIGPin, LOW);
  delayMicroseconds(2);
  digitalWrite(SIGPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(SIGPin, LOW);

  // Set SIGPin as input to read the echo
  pinMode(SIGPin, INPUT);
  long duration = pulseIn(SIGPin, HIGH);

  // Calculate the distance in centimeters
  long distance = (duration * 0.0343) / 2;

  return distance;
}

void controlRobot() {
  long encoder1Value, encoder2Value;  // Declare encoder variables
  int speed = 150;                    // Set initial motor speed
  char caractereS = 'S';
  char caractereO = 'O';

  // Calculate all distances in centimeters
  long distance1 = measureDistance(trigPin, echoPin);
  long distance2 = measureDistance(Trig2Pin, Echo2Pin);
  long distance3 = measureDistanceSinglePinSIG(SIG_TrigEcho3Pin);

  // Check if object is detected within a certain range
  if ((distance1 < STOP_DISTANCE) || (distance2 < STOP_DISTANCE) || (distance3 < STOP_DISTANCE)) {
    Serial.println(caractereS);
    delay(100);
    stopRobot();  // Stop motors if object detected
    delay(1000);       // Delay for 1 second
  }
  else {
    moveMotorsForward();
  }

  incomingByte = digitalRead(INFRARED_PIN);

  // Check if infrared sensor detects something
  if (incomingByte != HIGH) {
    Serial.println(caractereO);
    delay(100);
    stopRobot();                        // Stop the robot if infrared sensor detects something
    delay(1000);                        // Delay for 5 seconds
  }

  // Print encoder values, battery voltage, and motor speed on serial port
  /*encoder1Value = readEncoder(ENCODERONE);
  encoder2Value = readEncoder(ENCODERTWO);
  float batteryVoltage = readBatteryVoltage();*/

  if (digitalRead(BUTTON_PIN) == HIGH) {  // Check if button is pressed
    stopRobot();  // Stop the robot when button is not pressed
    button_pressed = TRUE;
  }
  delay(100);  // Adjust delay based on application needs
}

void turnRobot(int angle, int Right, int Left) {
  long encoder1Value, encoder2Value;  // Declare encoder variables
  int speed = 150;                    // Set initial motor speed
  char caractereS = 'S';
  char caractereO = 'O';

  // Calculate all distances in centimeters
  long distance1 = measureDistance(trigPin, echoPin);
  long distance2 = measureDistance(Trig2Pin, Echo2Pin);
  long distance3 = measureDistanceSinglePinSIG(SIG_TrigEcho3Pin);

  // Check if object is detected within a certain range
  if ((distance1 < STOP_DISTANCE) || (distance2 < STOP_DISTANCE) || (distance3 < STOP_DISTANCE)) {
    Serial.println(caractereS);
    delay(100);
    stopRobot();  // Stop motors if object detected
    delay(1000);       // Delay for 1 second
  }
  else {
    moveMotorsTurning(angle, Right, Left);
  }

  incomingByte = digitalRead(INFRARED_PIN);

  // Print encoder values, battery voltage, and motor speed on serial port
  /*encoder1Value = readEncoder(ENCODERONE);
  encoder2Value = readEncoder(ENCODERTWO);
  float batteryVoltage = readBatteryVoltage();*/

  if (digitalRead(BUTTON_PIN) == HIGH) {  // Check if button is pressed
    stopRobot();  // Stop the robot when button is not pressed
    button_pressed = TRUE;
  }
  delay(100);  // Adjust delay based on application needs
}

void slowDownMotors() {
  Wire.beginTransmission(MD25ADDRESS);
  Wire.write(SPEED2);
  Wire.write(150);  // Set speed to maximum (255) for motor 2 (adjust as needed for your setup)
  Wire.endTransmission();

  Wire.beginTransmission(MD25ADDRESS);
  Wire.write(SPEED1);
  Wire.write(150);  // Set speed to maximum (255) for motor 1 (adjust as needed for your setup)
  Wire.endTransmission();
}

void moveMotorsForward() {
  Wire.beginTransmission(MD25ADDRESS);
  Wire.write(SPEED2);
  Wire.write(175);  // Set speed to maximum (255) for motor 2 (adjust as needed for your setup)
  Wire.endTransmission();

  Wire.beginTransmission(MD25ADDRESS);
  Wire.write(SPEED1);
  Wire.write(175);  // Set speed to maximum (255) for motor 1 (adjust as needed for your setup)
  Wire.endTransmission();
}

void moveMotorsTurning(int angle, int Right, int Left) {
  if((Right == FALSE) && (Left == TRUE)) {
    Wire.beginTransmission(MD25ADDRESS);
    Wire.write(SPEED2);
    Wire.write(128);  // Set speed to minimum (128 = Motor stops) for motor 2 (adjust as needed for your setup)
    Wire.endTransmission();

    Wire.beginTransmission(MD25ADDRESS);
    Wire.write(SPEED1);
    Wire.write(140);  // Set speed to 175 for motor 1 (adjust as needed for your setup)
    Wire.endTransmission();
  }
  else if((Right == TRUE) && (Left == FALSE)) {
    Wire.beginTransmission(MD25ADDRESS);
    Wire.write(SPEED2);
    Wire.write(140);  // Set speed to 175 for motor 2 (adjust as needed for your setup)
    Wire.endTransmission();

    Wire.beginTransmission(MD25ADDRESS);
    Wire.write(SPEED1);
    Wire.write(128);  // Set speed to minimum (128 = Motor stops) for motor 1 (adjust as needed for your setup)
    Wire.endTransmission();
  }
}

void stopRobot() {
  Wire.beginTransmission(MD25ADDRESS);
  Wire.write(SPEED2);
  Wire.write(128);  // Set speed to stop (128) for motor 2
  Wire.endTransmission();

  Wire.beginTransmission(MD25ADDRESS);
  Wire.write(SPEED1);
  Wire.write(128);  // Set speed to stop (128) for motor 1
  Wire.endTransmission();
}

long readEncoder(byte encoder) {
  Wire.beginTransmission(MD25ADDRESS);
  Wire.write(encoder);
  Wire.endTransmission();

  Wire.requestFrom(MD25ADDRESS, 4);
  while (Wire.available() < 4)
    ;

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
  while (Wire.available() < 1)
    ;
  int batteryVoltage = Wire.read();

  return batteryVoltage / 10.0;  // Convert to volts
}