// ----- VERSION - 1.0 ----- //

// ----- MATCH ----- //

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
#define LED_PIN 13

// Define the durations in milliseconds
#define MATCH_DURATION 100000   // 100 seconds
#define TIME_END_ROBOT_FROM_END_MATCH 10000 // Make the robot off at 90 seconds max.
#define SEC_10 10000
#define SEC_2 2000
#define SEC_1 1000
#define SEC_7 7000
#define SEC_5 5000
#define SEC_6 6000
#define SEC_3 3000
#define SEC_TURN_90 5000   // A définir
#define SEC_TURN_180 10000 // A définir
#define TIME_CATCH_PLANT 6000
#define TIME_PUT_PLANT 3000

int button_pressed = 0;
int demarrage = 0 ;
int incomingByte;
int angle = 90;
int Right = FALSE, Left = TRUE;
// int Right = TRUE, Left = FALSE;
int compteur = 0;
unsigned long currentGlobalTime = 0, startGlobalTime = 0, currentTimeLoop = 0, startTime = 0;
unsigned long accumulatedPathTime = 0, pauseStartTime = 0, totalPausedTime = 0;
bool isPaused = false;
int position_pince_defaut = 1;
int bleue = TRUE;

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
  char caractereH = 'H'; // Homologation
  if(position_pince_defaut == 1) {
    position_pince_defaut = 0;
    Serial.println(caractereH);
    delay(500);
  }

  cordetirer();
  delay(100);

  if(demarrage == 1) {
    main_function();
  }
}

void cordetirer() {
  char caractereB = 'B', caractereJ = 'J'; // Pour les panneaux solaires.

  int sensorValue = digitalRead(INFRARED_PIN);
  if (sensorValue == HIGH)
  {
    char caractereC = 'C';
    Serial.println(caractereC); // Corde enlevée ! afficher sur l'OLED de la pince.
    demarrage = 1 ;
    delay(100);

    // Place le bras solaire selon l'équipe.
    if((bleue == TRUE) && (compteur == 0)) {
      Serial.println(caractereB);
      delay(1000);
    }
    else if ((bleue == FALSE) && (compteur == 0)) {
      Serial.println(caractereJ);
      delay(1000);
    }
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

// MAIN_FUNCTION //
void main_function() {
  char caractereG = 'G'; // Start Robot
  char caractereE = 'E'; // End Robot.

  if(compteur == 0) {
      compteur = 1;
      digitalWrite(13, HIGH);
      delay(100);
      digitalWrite(13, LOW);
    }
    
  if((digitalRead(BUTTON_PIN) == LOW) && (button_pressed == FALSE)) {
    Serial.println(caractereG);
    delay(50);
    startGlobalTime = millis();
    currentGlobalTime = startGlobalTime;

    if(bleue == TRUE) {
      // Algorithme du match pour l'équipe BLEUE //
      path_1_forward_for_10s();
      path_2_turn_90_left();
      path_3_forward_for_2s();
      path_4_turn_90_left();
      path_5_forward_for_1s_catch();
      path_6_forward_for_7s();
      path_7_turn_90_left();
      path_8_forward_for_1s_put();
      path_9_turn_180_right();
      path_10_forward_for_5s();
      path_11_turn_90_right();
      path_12_forward_for_6s_catch();
      path_13_turn_180_left();
      path_14_forward_for_6s();
      path_15_turn_90_right();
      path_16_forward_for_3s();
      path_17_turn_90_right_put();
    }
    else if (bleue == FALSE) {
      // Algorithme du match pour l'équipe JAUNE //
      path_1_forward_for_10s();
      path_2_turn_90_right();
      path_3_forward_for_2s();
      path_4_turn_90_right();
      path_5_forward_for_1s_catch();
      path_6_forward_for_7s();
      path_7_turn_90_right();
      path_8_forward_for_1s_put();
      path_9_turn_180_left();
      path_10_forward_for_5s();
      path_11_turn_90_left();
      path_12_forward_for_6s_catch();
      path_13_turn_180_right();
      path_14_forward_for_6s();
      path_15_turn_90_left();
      path_16_forward_for_3s();
      path_17_turn_90_left_put();
    }

    /*
      Départ coccinelles
    */

    stopRobot();
    button_pressed = TRUE; // Ne pourra plus exécuter l'algorithme de cette main_function.
    // Car nous avons terminer notre parcours (ou on a pris plus de 98 sec) et nous ne devons donc plus bouger.
    Serial.println(caractereE);
    delay(100);
  }
}

/*
  FONCTIONS EQUIPE BLEUE ET JAUNE POUR LES FONCTIONS QUI FONT AVANCER LE ROBOT.
  FONCTIONS EQUIPE BLEUE (UNIQUEMENT) POUR LES FONCTIONS QUI FONT TOURNER LE ROBOT.
*/

void path_1_forward_for_10s() {
  Serial.println("Path_1");
  int speed_robot = 175;
  char caractereS = 'S'; // Affiche Stop sur l'OLED de la pince.
  char caractereO = 'O'; // Pour remettre le bras solaire dans la position par défaut.

  startTime = millis();
  accumulatedPathTime = 0;
  pauseStartTime = 0;
  totalPausedTime = 0;
  isPaused = false;

  while((accumulatedPathTime < SEC_10) && (digitalRead(BUTTON_PIN) == LOW) && ((currentGlobalTime - startGlobalTime) < (MATCH_DURATION - TIME_END_ROBOT_FROM_END_MATCH))) {
    /*currentGlobalTime = millis();  // Update the global time
    currentTimeLoop = currentGlobalTime;*/
    currentTimeLoop = millis();
    currentGlobalTime = millis();

    // Calculate all distances in centimeters
    long distance1 = measureDistance(trigPin, echoPin);
    long distance2 = measureDistance(Trig2Pin, Echo2Pin);
    long distance3 = measureDistanceSinglePinSIG(SIG_TrigEcho3Pin);

    // Check if object is detected within a certain range
    if ((distance1 < STOP_DISTANCE) || (distance2 < STOP_DISTANCE) || (distance3 < STOP_DISTANCE)) {
      if (!isPaused) {
        pauseStartTime = millis(); // Start pause timing
        isPaused = true;
        Serial.println(caractereS);
        delay(100);
        stopRobot();  // Stop motors if object detected
      }
      delay(100);  // Delay for 0.1 second while checking the distances again
    }
    else {
      if (isPaused) {
        totalPausedTime += millis() - pauseStartTime; // Adjust total paused time
        isPaused = false;
      }
      moveMotorsForward(speed_robot); // Resume or keep moving forward
      unsigned long elapsedTime = millis() - startTime - totalPausedTime;
      accumulatedPathTime = (elapsedTime > SEC_10) ? SEC_10 : elapsedTime; // Update accumulated path time, ensuring it doesn't exceed 10 seconds
    }

    if (digitalRead(BUTTON_PIN) == HIGH) {  // Check if button is pressed
      stopRobot();  // Stop the robot when button is not pressed
      button_pressed = TRUE;
    }
    delay(100);  // Adjust delay based on application needs
  }

  Serial.println(caractereO);
  delay(100);
}

void path_2_turn_90_left() {
  Serial.println("Path_2");
  char caractereS = 'S';

  startTime = millis();
  accumulatedPathTime = 0;
  pauseStartTime = 0;
  totalPausedTime = 0;
  isPaused = false;
  
  while((accumulatedPathTime < SEC_TURN_90) && (digitalRead(BUTTON_PIN) == LOW) && ((currentGlobalTime - startGlobalTime) < (MATCH_DURATION - TIME_END_ROBOT_FROM_END_MATCH))) {
    currentTimeLoop = millis();
    currentGlobalTime = millis();

    // Calculate all distances in centimeters
    long distance1 = measureDistance(trigPin, echoPin);
    long distance2 = measureDistance(Trig2Pin, Echo2Pin);
    long distance3 = measureDistanceSinglePinSIG(SIG_TrigEcho3Pin);

    // Check if object is detected within a certain range
    if ((distance1 < STOP_DISTANCE) || (distance2 < STOP_DISTANCE) || (distance3 < STOP_DISTANCE)) {
      if (!isPaused) {
        pauseStartTime = millis(); // Start pause timing
        isPaused = true;
        Serial.println(caractereS);
        delay(100);
        stopRobot();  // Stop motors if object detected
      }
      delay(100);  // Delay for 0.1 second while checking the distances again
    }
    else {
      if (isPaused) {
        totalPausedTime += millis() - pauseStartTime; // Adjust total paused time
        isPaused = false;
      }
      moveMotorsTurning(90, FALSE, TRUE); // Resume or keep turning
      unsigned long elapsedTime = millis() - startTime - totalPausedTime;
      accumulatedPathTime = (elapsedTime > SEC_TURN_90) ? SEC_TURN_90 : elapsedTime; // Update accumulated path time, ensuring it doesn't exceed 90 seconds
    }

    if (digitalRead(BUTTON_PIN) == HIGH) {  // Check if button is pressed
      stopRobot();  // Stop the robot when button is not pressed
      button_pressed = TRUE;
    }
    delay(100);  // Adjust delay based on application needs
  }
}

void path_3_forward_for_2s() {
  Serial.println("Path_3");
  int speed_robot = 175;
  char caractereS = 'S';

  startTime = millis();
  accumulatedPathTime = 0;
  pauseStartTime = 0;
  totalPausedTime = 0;
  isPaused = false;

  while((accumulatedPathTime < SEC_3) && (digitalRead(BUTTON_PIN) == LOW) && ((currentGlobalTime - startGlobalTime) < (MATCH_DURATION - TIME_END_ROBOT_FROM_END_MATCH))) {
    currentTimeLoop = millis();
    currentGlobalTime = millis();

    // Calculate all distances in centimeters
    long distance1 = measureDistance(trigPin, echoPin);
    long distance2 = measureDistance(Trig2Pin, Echo2Pin);
    long distance3 = measureDistanceSinglePinSIG(SIG_TrigEcho3Pin);

    // Check if object is detected within a certain range
    if ((distance1 < STOP_DISTANCE) || (distance2 < STOP_DISTANCE) || (distance3 < STOP_DISTANCE)) {
      if (!isPaused) {
        pauseStartTime = millis(); // Start pause timing
        isPaused = true;
        Serial.println(caractereS);
        delay(100);
        stopRobot();  // Stop motors if object detected
      }
      delay(100);  // Delay for 0.1 second while checking the distances again
    }
    else {
      if (isPaused) {
        totalPausedTime += millis() - pauseStartTime; // Adjust total paused time
        isPaused = false;
      }
      moveMotorsForward(speed_robot); // Resume or keep moving forward
      unsigned long elapsedTime = millis() - startTime - totalPausedTime;
      accumulatedPathTime = (elapsedTime > SEC_10) ? SEC_10 : elapsedTime; // Update accumulated path time, ensuring it doesn't exceed 10 seconds
    }

    if (digitalRead(BUTTON_PIN) == HIGH) {  // Check if button is pressed
      stopRobot();  // Stop the robot when button is not pressed
      button_pressed = TRUE;
    }
    delay(100);  // Adjust delay based on application needs
  }
}

void path_4_turn_90_left() {
  Serial.println("Path_4");
  char caractereS = 'S';

  startTime = millis();
  accumulatedPathTime = 0;
  pauseStartTime = 0;
  totalPausedTime = 0;
  isPaused = false;

  while((accumulatedPathTime < SEC_TURN_90) && (digitalRead(BUTTON_PIN) == LOW) && ((currentGlobalTime - startGlobalTime) < (MATCH_DURATION - TIME_END_ROBOT_FROM_END_MATCH))) {
    currentTimeLoop = millis();
    currentGlobalTime = millis();

    // Calculate all distances in centimeters
    long distance1 = measureDistance(trigPin, echoPin);
    long distance2 = measureDistance(Trig2Pin, Echo2Pin);
    long distance3 = measureDistanceSinglePinSIG(SIG_TrigEcho3Pin);

    // Check if object is detected within a certain range
    if ((distance1 < STOP_DISTANCE) || (distance2 < STOP_DISTANCE) || (distance3 < STOP_DISTANCE)) {
      if (!isPaused) {
        pauseStartTime = millis(); // Start pause timing
        isPaused = true;
        Serial.println(caractereS);
        delay(100);
        stopRobot();  // Stop motors if object detected
      }
      delay(100);  // Delay for 0.1 second while checking the distances again
    }
    else {
      if (isPaused) {
        totalPausedTime += millis() - pauseStartTime; // Adjust total paused time
        isPaused = false;
      }
      moveMotorsTurning(90, FALSE, TRUE); // Resume or keep turning
      unsigned long elapsedTime = millis() - startTime - totalPausedTime;
      accumulatedPathTime = (elapsedTime > SEC_TURN_90) ? SEC_TURN_90 : elapsedTime; // Update accumulated path time, ensuring it doesn't exceed 90 seconds
    }

    if (digitalRead(BUTTON_PIN) == HIGH) {  // Check if button is pressed
      stopRobot();  // Stop the robot when button is not pressed
      button_pressed = TRUE;
    }
    delay(100);  // Adjust delay based on application needs
  }
}

void path_5_forward_for_1s_catch() {
  Serial.println("Path_5");
  int speed_robot = 175;
  char caractereS = 'S', caractereA = 'A';

  startTime = millis();
  accumulatedPathTime = 0;
  pauseStartTime = 0;
  totalPausedTime = 0;
  isPaused = false;

  while((accumulatedPathTime < SEC_1) && (digitalRead(BUTTON_PIN) == LOW) && ((currentGlobalTime - startGlobalTime) < (MATCH_DURATION - TIME_END_ROBOT_FROM_END_MATCH))) {
    currentTimeLoop = millis();
    currentGlobalTime = millis();

    // Calculate all distances in centimeters
    long distance1 = measureDistance(trigPin, echoPin);
    long distance2 = measureDistance(Trig2Pin, Echo2Pin);
    long distance3 = measureDistanceSinglePinSIG(SIG_TrigEcho3Pin);

    // Check if object is detected within a certain range
    if ((distance1 < STOP_DISTANCE) || (distance2 < STOP_DISTANCE) || (distance3 < STOP_DISTANCE)) {
      if (!isPaused) {
        pauseStartTime = millis(); // Start pause timing
        isPaused = true;
        Serial.println(caractereS);
        delay(100);
        stopRobot();  // Stop motors if object detected
      }
      delay(100);  // Delay for 0.1 second while checking the distances again
    }
    else {
      if (isPaused) {
        totalPausedTime += millis() - pauseStartTime; // Adjust total paused time
        isPaused = false;
      }

      // Check if infrared sensor detects something
      incomingByte = digitalRead(INFRARED_PIN);
      if (incomingByte != HIGH) {
        Serial.println(caractereA);
        delay(100);
        stopRobot();                        // Stop the robot if infrared sensor detects something
        delay(TIME_CATCH_PLANT);            // Delay to catch the plant.
        
        break;
      }

      moveMotorsForward(speed_robot); // Resume or keep moving forward
      unsigned long elapsedTime = millis() - startTime - totalPausedTime;
      accumulatedPathTime = (elapsedTime > SEC_10) ? SEC_10 : elapsedTime; // Update accumulated path time, ensuring it doesn't exceed 10 seconds
    }

    if (digitalRead(BUTTON_PIN) == HIGH) {  // Check if button is pressed
      stopRobot();  // Stop the robot when button is not pressed
      button_pressed = TRUE;
    }
    delay(100);  // Adjust delay based on application needs
  }
}

void path_6_forward_for_7s() {
  Serial.println("Path_6");
  int speed_robot = 175;
  char caractereS = 'S';

  startTime = millis();
  accumulatedPathTime = 0;
  pauseStartTime = 0;
  totalPausedTime = 0;
  isPaused = false;

  while((accumulatedPathTime < SEC_7) && (digitalRead(BUTTON_PIN) == LOW) && ((currentGlobalTime - startGlobalTime) < (MATCH_DURATION - TIME_END_ROBOT_FROM_END_MATCH))) {
    currentTimeLoop = millis();
    currentGlobalTime = millis();

    // Calculate all distances in centimeters
    long distance1 = measureDistance(trigPin, echoPin);
    long distance2 = measureDistance(Trig2Pin, Echo2Pin);
    long distance3 = measureDistanceSinglePinSIG(SIG_TrigEcho3Pin);

    // Check if object is detected within a certain range
    if ((distance1 < STOP_DISTANCE) || (distance2 < STOP_DISTANCE) || (distance3 < STOP_DISTANCE)) {
      if (!isPaused) {
        pauseStartTime = millis(); // Start pause timing
        isPaused = true;
        Serial.println(caractereS);
        delay(100);
        stopRobot();  // Stop motors if object detected
      }
      delay(100);  // Delay for 0.1 second while checking the distances again
    }
    else {
      if (isPaused) {
        totalPausedTime += millis() - pauseStartTime; // Adjust total paused time
        isPaused = false;
      }
      moveMotorsForward(speed_robot); // Resume or keep moving forward
      unsigned long elapsedTime = millis() - startTime - totalPausedTime;
      accumulatedPathTime = (elapsedTime > SEC_10) ? SEC_10 : elapsedTime; // Update accumulated path time, ensuring it doesn't exceed 10 seconds
    }

    if (digitalRead(BUTTON_PIN) == HIGH) {  // Check if button is pressed
      stopRobot();  // Stop the robot when button is not pressed
      button_pressed = TRUE;
    }
    delay(100);  // Adjust delay based on application needs
  }
}

void path_7_turn_90_left() {
  Serial.println("Path_7");
  char caractereS = 'S';

  startTime = millis();
  accumulatedPathTime = 0;
  pauseStartTime = 0;
  totalPausedTime = 0;
  isPaused = false;

  while((accumulatedPathTime < SEC_TURN_90) && (digitalRead(BUTTON_PIN) == LOW) && ((currentGlobalTime - startGlobalTime) < (MATCH_DURATION - TIME_END_ROBOT_FROM_END_MATCH))) {
    currentTimeLoop = millis();
    currentGlobalTime = millis();

    // Calculate all distances in centimeters
    long distance1 = measureDistance(trigPin, echoPin);
    long distance2 = measureDistance(Trig2Pin, Echo2Pin);
    long distance3 = measureDistanceSinglePinSIG(SIG_TrigEcho3Pin);

    // Check if object is detected within a certain range
    if ((distance1 < STOP_DISTANCE) || (distance2 < STOP_DISTANCE) || (distance3 < STOP_DISTANCE)) {
      if (!isPaused) {
        pauseStartTime = millis(); // Start pause timing
        isPaused = true;
        Serial.println(caractereS);
        delay(100);
        stopRobot();  // Stop motors if object detected
      }
      delay(100);  // Delay for 0.1 second while checking the distances again
    }
    else {
      if (isPaused) {
        totalPausedTime += millis() - pauseStartTime; // Adjust total paused time
        isPaused = false;
      }
      moveMotorsTurning(90, FALSE, TRUE); // Resume or keep turning
      unsigned long elapsedTime = millis() - startTime - totalPausedTime;
      accumulatedPathTime = (elapsedTime > SEC_TURN_90) ? SEC_TURN_90 : elapsedTime; // Update accumulated path time, ensuring it doesn't exceed 90 seconds
    }

    if (digitalRead(BUTTON_PIN) == HIGH) {  // Check if button is pressed
      stopRobot();  // Stop the robot when button is not pressed
      button_pressed = TRUE;
    }
    delay(100);  // Adjust delay based on application needs
  }
}

void path_8_forward_for_1s_put() {
  Serial.println("Path_8");
  int speed_robot = 175;
  char caractereS = 'S', caractereD = 'D';

  startTime = millis();
  accumulatedPathTime = 0;
  pauseStartTime = 0;
  totalPausedTime = 0;
  isPaused = false;

  while((accumulatedPathTime < SEC_1) && (digitalRead(BUTTON_PIN) == LOW) && ((currentGlobalTime - startGlobalTime) < (MATCH_DURATION - TIME_END_ROBOT_FROM_END_MATCH))) {
    currentTimeLoop = millis();
    currentGlobalTime = millis();

    // Calculate all distances in centimeters
    long distance1 = measureDistance(trigPin, echoPin);
    long distance2 = measureDistance(Trig2Pin, Echo2Pin);
    long distance3 = measureDistanceSinglePinSIG(SIG_TrigEcho3Pin);

    // Check if object is detected within a certain range
    if ((distance1 < STOP_DISTANCE) || (distance2 < STOP_DISTANCE) || (distance3 < STOP_DISTANCE)) {
      if (!isPaused) {
        pauseStartTime = millis(); // Start pause timing
        isPaused = true;
        Serial.println(caractereS);
        delay(100);
        stopRobot();  // Stop motors if object detected
      }
      delay(100);  // Delay for 0.1 second while checking the distances again
    }
    else {
      if (isPaused) {
        totalPausedTime += millis() - pauseStartTime; // Adjust total paused time
        isPaused = false;
      }

      moveMotorsForward(speed_robot); // Resume or keep moving forward
      unsigned long elapsedTime = millis() - startTime - totalPausedTime;
      accumulatedPathTime = (elapsedTime > SEC_10) ? SEC_10 : elapsedTime; // Update accumulated path time, ensuring it doesn't exceed 10 seconds
    }

    if (digitalRead(BUTTON_PIN) == HIGH) {  // Check if button is pressed
      stopRobot();  // Stop the robot when button is not pressed
      button_pressed = TRUE;
    }
    delay(100);  // Adjust delay based on application needs
  }
  
  if(digitalRead(BUTTON_PIN) == LOW) {
    Serial.println(caractereD);
    delay(100);
    stopRobot();                        // Stop the robot if infrared sensor detects something
    delay(TIME_PUT_PLANT);              // Delay to put the plant.
  }
}

void path_9_turn_180_right() {
  Serial.println("Path_9");
  char caractereS = 'S';

  startTime = millis();
  accumulatedPathTime = 0;
  pauseStartTime = 0;
  totalPausedTime = 0;
  isPaused = false;

  while((accumulatedPathTime < SEC_TURN_90) && (digitalRead(BUTTON_PIN) == LOW) && ((currentGlobalTime - startGlobalTime) < (MATCH_DURATION - TIME_END_ROBOT_FROM_END_MATCH))) {
    currentTimeLoop = millis();
    currentGlobalTime = millis();

    // Calculate all distances in centimeters
    long distance1 = measureDistance(trigPin, echoPin);
    long distance2 = measureDistance(Trig2Pin, Echo2Pin);
    long distance3 = measureDistanceSinglePinSIG(SIG_TrigEcho3Pin);

    // Check if object is detected within a certain range
    if ((distance1 < STOP_DISTANCE) || (distance2 < STOP_DISTANCE) || (distance3 < STOP_DISTANCE)) {
      if (!isPaused) {
        pauseStartTime = millis(); // Start pause timing
        isPaused = true;
        Serial.println(caractereS);
        delay(100);
        stopRobot();  // Stop motors if object detected
      }
      delay(100);  // Delay for 0.1 second while checking the distances again
    }
    else {
      if (isPaused) {
        totalPausedTime += millis() - pauseStartTime; // Adjust total paused time
        isPaused = false;
      }
      moveMotorsTurning(90, TRUE, FALSE); // Resume or keep turning
      unsigned long elapsedTime = millis() - startTime - totalPausedTime;
      accumulatedPathTime = (elapsedTime > SEC_TURN_180) ? SEC_TURN_180 : elapsedTime; // Update accumulated path time, ensuring it doesn't exceed 90 seconds
    }

    if (digitalRead(BUTTON_PIN) == HIGH) {  // Check if button is pressed
      stopRobot();  // Stop the robot when button is not pressed
      button_pressed = TRUE;
    }
    delay(100);  // Adjust delay based on application needs
  }
}

void path_10_forward_for_5s() {
  Serial.println("Path_10");
  int speed_robot = 175;
  char caractereS = 'S';

  startTime = millis();
  accumulatedPathTime = 0;
  pauseStartTime = 0;
  totalPausedTime = 0;
  isPaused = false;

  while((accumulatedPathTime < SEC_5) && (digitalRead(BUTTON_PIN) == LOW) && ((currentGlobalTime - startGlobalTime) < (MATCH_DURATION - TIME_END_ROBOT_FROM_END_MATCH))) {
    currentTimeLoop = millis();
    currentGlobalTime = millis();

    // Calculate all distances in centimeters
    long distance1 = measureDistance(trigPin, echoPin);
    long distance2 = measureDistance(Trig2Pin, Echo2Pin);
    long distance3 = measureDistanceSinglePinSIG(SIG_TrigEcho3Pin);

    // Check if object is detected within a certain range
    if ((distance1 < STOP_DISTANCE) || (distance2 < STOP_DISTANCE) || (distance3 < STOP_DISTANCE)) {
      if (!isPaused) {
        pauseStartTime = millis(); // Start pause timing
        isPaused = true;
        Serial.println(caractereS);
        delay(100);
        stopRobot();  // Stop motors if object detected
      }
      delay(100);  // Delay for 0.1 second while checking the distances again
    }
    else {
      if (isPaused) {
        totalPausedTime += millis() - pauseStartTime; // Adjust total paused time
        isPaused = false;
      }
      moveMotorsForward(speed_robot); // Resume or keep moving forward
      unsigned long elapsedTime = millis() - startTime - totalPausedTime;
      accumulatedPathTime = (elapsedTime > SEC_10) ? SEC_10 : elapsedTime; // Update accumulated path time, ensuring it doesn't exceed 10 seconds
    }

    if (digitalRead(BUTTON_PIN) == HIGH) {  // Check if button is pressed
      stopRobot();  // Stop the robot when button is not pressed
      button_pressed = TRUE;
    }
    delay(100);  // Adjust delay based on application needs
  }
}

void path_11_turn_90_right() {
  Serial.println("Path_11");
  char caractereS = 'S';

  startTime = millis();
  accumulatedPathTime = 0;
  pauseStartTime = 0;
  totalPausedTime = 0;
  isPaused = false;

  while((accumulatedPathTime < SEC_TURN_90) && (digitalRead(BUTTON_PIN) == LOW) && ((currentGlobalTime - startGlobalTime) < (MATCH_DURATION - TIME_END_ROBOT_FROM_END_MATCH))) {
    currentTimeLoop = millis();
    currentGlobalTime = millis();

    // Calculate all distances in centimeters
    long distance1 = measureDistance(trigPin, echoPin);
    long distance2 = measureDistance(Trig2Pin, Echo2Pin);
    long distance3 = measureDistanceSinglePinSIG(SIG_TrigEcho3Pin);

    // Check if object is detected within a certain range
    if ((distance1 < STOP_DISTANCE) || (distance2 < STOP_DISTANCE) || (distance3 < STOP_DISTANCE)) {
      if (!isPaused) {
        pauseStartTime = millis(); // Start pause timing
        isPaused = true;
        Serial.println(caractereS);
        delay(100);
        stopRobot();  // Stop motors if object detected
      }
      delay(100);  // Delay for 0.1 second while checking the distances again
    }
    else {
      if (isPaused) {
        totalPausedTime += millis() - pauseStartTime; // Adjust total paused time
        isPaused = false;
      }
      moveMotorsTurning(90, TRUE, FALSE); // Resume or keep turning
      unsigned long elapsedTime = millis() - startTime - totalPausedTime;
      accumulatedPathTime = (elapsedTime > SEC_TURN_90) ? SEC_TURN_90 : elapsedTime; // Update accumulated path time, ensuring it doesn't exceed 90 seconds
    }

    if (digitalRead(BUTTON_PIN) == HIGH) {  // Check if button is pressed
      stopRobot();  // Stop the robot when button is not pressed
      button_pressed = TRUE;
    }
    delay(100);  // Adjust delay based on application needs
  }
}

void path_12_forward_for_6s_catch() {
  Serial.println("Path_12");
  int speed_robot = 175;
  char caractereS = 'S', caractereA = 'A';

  startTime = millis();
  accumulatedPathTime = 0;
  pauseStartTime = 0;
  totalPausedTime = 0;
  isPaused = false;

  while((accumulatedPathTime < SEC_6) && (digitalRead(BUTTON_PIN) == LOW) && ((currentGlobalTime - startGlobalTime) < (MATCH_DURATION - TIME_END_ROBOT_FROM_END_MATCH))) {
    currentTimeLoop = millis();
    currentGlobalTime = millis();

    // Calculate all distances in centimeters
    long distance1 = measureDistance(trigPin, echoPin);
    long distance2 = measureDistance(Trig2Pin, Echo2Pin);
    long distance3 = measureDistanceSinglePinSIG(SIG_TrigEcho3Pin);

    // Check if object is detected within a certain range
    if ((distance1 < STOP_DISTANCE) || (distance2 < STOP_DISTANCE) || (distance3 < STOP_DISTANCE)) {
      if (!isPaused) {
        pauseStartTime = millis(); // Start pause timing
        isPaused = true;
        Serial.println(caractereS);
        delay(100);
        stopRobot();  // Stop motors if object detected
      }
      delay(100);  // Delay for 0.1 second while checking the distances again
    }
    else {
      if (isPaused) {
        totalPausedTime += millis() - pauseStartTime; // Adjust total paused time
        isPaused = false;
      }

      // Check if infrared sensor detects something
      incomingByte = digitalRead(INFRARED_PIN);
      if (incomingByte != HIGH) {
        Serial.println(caractereA);
        delay(100);
        stopRobot();                        // Stop the robot if infrared sensor detects something
        delay(TIME_CATCH_PLANT);            // Delay to catch the plant.
        
        break;
      }

      moveMotorsForward(speed_robot); // Resume or keep moving forward
      unsigned long elapsedTime = millis() - startTime - totalPausedTime;
      accumulatedPathTime = (elapsedTime > SEC_10) ? SEC_10 : elapsedTime; // Update accumulated path time, ensuring it doesn't exceed 10 seconds
    }

    if (digitalRead(BUTTON_PIN) == HIGH) {  // Check if button is pressed
      stopRobot();  // Stop the robot when button is not pressed
      button_pressed = TRUE;
    }
    delay(100);  // Adjust delay based on application needs
  }
}

void path_13_turn_180_left() {
  Serial.println("Path_13");
  char caractereS = 'S';

  startTime = millis();
  accumulatedPathTime = 0;
  pauseStartTime = 0;
  totalPausedTime = 0;
  isPaused = false;

  while((accumulatedPathTime < SEC_TURN_90) && (digitalRead(BUTTON_PIN) == LOW) && ((currentGlobalTime - startGlobalTime) < (MATCH_DURATION - TIME_END_ROBOT_FROM_END_MATCH))) {
    currentTimeLoop = millis();
    currentGlobalTime = millis();

    // Calculate all distances in centimeters
    long distance1 = measureDistance(trigPin, echoPin);
    long distance2 = measureDistance(Trig2Pin, Echo2Pin);
    long distance3 = measureDistanceSinglePinSIG(SIG_TrigEcho3Pin);

    // Check if object is detected within a certain range
    if ((distance1 < STOP_DISTANCE) || (distance2 < STOP_DISTANCE) || (distance3 < STOP_DISTANCE)) {
      if (!isPaused) {
        pauseStartTime = millis(); // Start pause timing
        isPaused = true;
        Serial.println(caractereS);
        delay(100);
        stopRobot();  // Stop motors if object detected
      }
      delay(100);  // Delay for 0.1 second while checking the distances again
    }
    else {
      if (isPaused) {
        totalPausedTime += millis() - pauseStartTime; // Adjust total paused time
        isPaused = false;
      }
      moveMotorsTurning(90, FALSE, TRUE); // Resume or keep turning
      unsigned long elapsedTime = millis() - startTime - totalPausedTime;
      accumulatedPathTime = (elapsedTime > SEC_TURN_180) ? SEC_TURN_180 : elapsedTime; // Update accumulated path time, ensuring it doesn't exceed 90 seconds
    }

    if (digitalRead(BUTTON_PIN) == HIGH) {  // Check if button is pressed
      stopRobot();  // Stop the robot when button is not pressed
      button_pressed = TRUE;
    }
    delay(100);  // Adjust delay based on application needs
  }
}

void path_14_forward_for_6s() {
  Serial.println("Path_14");
  int speed_robot = 175;
  char caractereS = 'S';

  startTime = millis();
  accumulatedPathTime = 0;
  pauseStartTime = 0;
  totalPausedTime = 0;
  isPaused = false;

  while((accumulatedPathTime < SEC_6) && (digitalRead(BUTTON_PIN) == LOW) && ((currentGlobalTime - startGlobalTime) < (MATCH_DURATION - TIME_END_ROBOT_FROM_END_MATCH))) {
    currentTimeLoop = millis();
    currentGlobalTime = millis();

    // Calculate all distances in centimeters
    long distance1 = measureDistance(trigPin, echoPin);
    long distance2 = measureDistance(Trig2Pin, Echo2Pin);
    long distance3 = measureDistanceSinglePinSIG(SIG_TrigEcho3Pin);

    // Check if object is detected within a certain range
    if ((distance1 < STOP_DISTANCE) || (distance2 < STOP_DISTANCE) || (distance3 < STOP_DISTANCE)) {
      if (!isPaused) {
        pauseStartTime = millis(); // Start pause timing
        isPaused = true;
        Serial.println(caractereS);
        delay(100);
        stopRobot();  // Stop motors if object detected
      }
      delay(100);  // Delay for 0.1 second while checking the distances again
    }
    else {
      if (isPaused) {
        totalPausedTime += millis() - pauseStartTime; // Adjust total paused time
        isPaused = false;
      }
      moveMotorsForward(speed_robot); // Resume or keep moving forward
      unsigned long elapsedTime = millis() - startTime - totalPausedTime;
      accumulatedPathTime = (elapsedTime > SEC_10) ? SEC_10 : elapsedTime; // Update accumulated path time, ensuring it doesn't exceed 10 seconds
    }

    if (digitalRead(BUTTON_PIN) == HIGH) {  // Check if button is pressed
      stopRobot();  // Stop the robot when button is not pressed
      button_pressed = TRUE;
    }
    delay(100);  // Adjust delay based on application needs
  }
}

void path_15_turn_90_right() {
  Serial.println("Path_15");
  char caractereS = 'S';

  startTime = millis();
  accumulatedPathTime = 0;
  pauseStartTime = 0;
  totalPausedTime = 0;
  isPaused = false;

  while((accumulatedPathTime < SEC_TURN_90) && (digitalRead(BUTTON_PIN) == LOW) && ((currentGlobalTime - startGlobalTime) < (MATCH_DURATION - TIME_END_ROBOT_FROM_END_MATCH))) {
    currentTimeLoop = millis();
    currentGlobalTime = millis();

    // Calculate all distances in centimeters
    long distance1 = measureDistance(trigPin, echoPin);
    long distance2 = measureDistance(Trig2Pin, Echo2Pin);
    long distance3 = measureDistanceSinglePinSIG(SIG_TrigEcho3Pin);

    // Check if object is detected within a certain range
    if ((distance1 < STOP_DISTANCE) || (distance2 < STOP_DISTANCE) || (distance3 < STOP_DISTANCE)) {
      if (!isPaused) {
        pauseStartTime = millis(); // Start pause timing
        isPaused = true;
        Serial.println(caractereS);
        delay(100);
        stopRobot();  // Stop motors if object detected
      }
      delay(100);  // Delay for 0.1 second while checking the distances again
    }
    else {
      if (isPaused) {
        totalPausedTime += millis() - pauseStartTime; // Adjust total paused time
        isPaused = false;
      }
      moveMotorsTurning(90, TRUE, FALSE); // Resume or keep turning
      unsigned long elapsedTime = millis() - startTime - totalPausedTime;
      accumulatedPathTime = (elapsedTime > SEC_TURN_90) ? SEC_TURN_90 : elapsedTime; // Update accumulated path time, ensuring it doesn't exceed 90 seconds
    }

    if (digitalRead(BUTTON_PIN) == HIGH) {  // Check if button is pressed
      stopRobot();  // Stop the robot when button is not pressed
      button_pressed = TRUE;
    }
    delay(100);  // Adjust delay based on application needs
  }
}

void path_16_forward_for_3s() {
  Serial.println("Path_16");
  int speed_robot = 175;
  char caractereS = 'S';

  startTime = millis();
  accumulatedPathTime = 0;
  pauseStartTime = 0;
  totalPausedTime = 0;
  isPaused = false;

  while((accumulatedPathTime < SEC_3) && (digitalRead(BUTTON_PIN) == LOW) && ((currentGlobalTime - startGlobalTime) < (MATCH_DURATION - TIME_END_ROBOT_FROM_END_MATCH))) {
    currentTimeLoop = millis();
    currentGlobalTime = millis();

    // Calculate all distances in centimeters
    long distance1 = measureDistance(trigPin, echoPin);
    long distance2 = measureDistance(Trig2Pin, Echo2Pin);
    long distance3 = measureDistanceSinglePinSIG(SIG_TrigEcho3Pin);

    // Check if object is detected within a certain range
    if ((distance1 < STOP_DISTANCE) || (distance2 < STOP_DISTANCE) || (distance3 < STOP_DISTANCE)) {
      if (!isPaused) {
        pauseStartTime = millis(); // Start pause timing
        isPaused = true;
        Serial.println(caractereS);
        delay(100);
        stopRobot();  // Stop motors if object detected
      }
      delay(100);  // Delay for 0.1 second while checking the distances again
    }
    else {
      if (isPaused) {
        totalPausedTime += millis() - pauseStartTime; // Adjust total paused time
        isPaused = false;
      }
      moveMotorsForward(speed_robot); // Resume or keep moving forward
      unsigned long elapsedTime = millis() - startTime - totalPausedTime;
      accumulatedPathTime = (elapsedTime > SEC_10) ? SEC_10 : elapsedTime; // Update accumulated path time, ensuring it doesn't exceed 10 seconds
    }

    if (digitalRead(BUTTON_PIN) == HIGH) {  // Check if button is pressed
      stopRobot();  // Stop the robot when button is not pressed
      button_pressed = TRUE;
    }
    delay(100);  // Adjust delay based on application needs
  }
}

void path_17_turn_90_right_put() {
  Serial.println("Path_17");
  char caractereS = 'S', caractereD = 'D';
  startTime = millis();
  accumulatedPathTime = 0;
  pauseStartTime = 0;
  totalPausedTime = 0;
  isPaused = false;

  while((accumulatedPathTime < SEC_TURN_90) && (digitalRead(BUTTON_PIN) == LOW) && ((currentGlobalTime - startGlobalTime) < (MATCH_DURATION - TIME_END_ROBOT_FROM_END_MATCH))) {
    currentTimeLoop = millis();
    currentGlobalTime = millis();

    // Calculate all distances in centimeters
    long distance1 = measureDistance(trigPin, echoPin);
    long distance2 = measureDistance(Trig2Pin, Echo2Pin);
    long distance3 = measureDistanceSinglePinSIG(SIG_TrigEcho3Pin);

    // Check if object is detected within a certain range
    if ((distance1 < STOP_DISTANCE) || (distance2 < STOP_DISTANCE) || (distance3 < STOP_DISTANCE)) {
      if (!isPaused) {
        pauseStartTime = millis(); // Start pause timing
        isPaused = true;
        Serial.println(caractereS);
        delay(100);
        stopRobot();  // Stop motors if object detected
      }
      delay(100);  // Delay for 0.1 second while checking the distances again
    }
    else {
      if (isPaused) {
        totalPausedTime += millis() - pauseStartTime; // Adjust total paused time
        isPaused = false;
      }

      moveMotorsTurning(90, TRUE, FALSE); // Resume or keep turning
      unsigned long elapsedTime = millis() - startTime - totalPausedTime;
      accumulatedPathTime = (elapsedTime > SEC_TURN_90) ? SEC_TURN_90 : elapsedTime; // Update accumulated path time, ensuring it doesn't exceed 90 seconds
    }

    if (digitalRead(BUTTON_PIN) == HIGH) {  // Check if button is pressed
      stopRobot();  // Stop the robot when button is not pressed
      button_pressed = TRUE;
    }
    delay(100);  // Adjust delay based on application needs
  }

  if(digitalRead(BUTTON_PIN) == LOW) {
    Serial.println(caractereD);
    delay(100);
    stopRobot();                        // Stop the robot if infrared sensor detects something
    delay(TIME_PUT_PLANT);              // Delay to put the plant.
  }
}

/*
  FONCTIONS EQUIPE JAUNE (UNIQUEMENT) POUR LES FONCTIONS QUI FONT TOURNER LE ROBOT.
*/

void path_2_turn_90_right() {
  Serial.println("Path_2");
  char caractereS = 'S';

  startTime = millis();
  accumulatedPathTime = 0;
  pauseStartTime = 0;
  totalPausedTime = 0;
  isPaused = false;
  
  while((accumulatedPathTime < SEC_TURN_90) && (digitalRead(BUTTON_PIN) == LOW) && ((currentGlobalTime - startGlobalTime) < (MATCH_DURATION - TIME_END_ROBOT_FROM_END_MATCH))) {
    currentTimeLoop = millis();
    currentGlobalTime = millis();

    // Calculate all distances in centimeters
    long distance1 = measureDistance(trigPin, echoPin);
    long distance2 = measureDistance(Trig2Pin, Echo2Pin);
    long distance3 = measureDistanceSinglePinSIG(SIG_TrigEcho3Pin);

    // Check if object is detected within a certain range
    if ((distance1 < STOP_DISTANCE) || (distance2 < STOP_DISTANCE) || (distance3 < STOP_DISTANCE)) {
      if (!isPaused) {
        pauseStartTime = millis(); // Start pause timing
        isPaused = true;
        Serial.println(caractereS);
        delay(100);
        stopRobot();  // Stop motors if object detected
      }
      delay(100);  // Delay for 0.1 second while checking the distances again
    }
    else {
      if (isPaused) {
        totalPausedTime += millis() - pauseStartTime; // Adjust total paused time
        isPaused = false;
      }
      moveMotorsTurning(90, TRUE, FALSE); // Resume or keep turning
      unsigned long elapsedTime = millis() - startTime - totalPausedTime;
      accumulatedPathTime = (elapsedTime > SEC_TURN_90) ? SEC_TURN_90 : elapsedTime; // Update accumulated path time, ensuring it doesn't exceed 90 seconds
    }

    if (digitalRead(BUTTON_PIN) == HIGH) {  // Check if button is pressed
      stopRobot();  // Stop the robot when button is not pressed
      button_pressed = TRUE;
    }
    delay(100);  // Adjust delay based on application needs
  }
}

void path_4_turn_90_right() {
  Serial.println("Path_4");
  char caractereS = 'S';

  startTime = millis();
  accumulatedPathTime = 0;
  pauseStartTime = 0;
  totalPausedTime = 0;
  isPaused = false;

  while((accumulatedPathTime < SEC_TURN_90) && (digitalRead(BUTTON_PIN) == LOW) && ((currentGlobalTime - startGlobalTime) < (MATCH_DURATION - TIME_END_ROBOT_FROM_END_MATCH))) {
    currentTimeLoop = millis();
    currentGlobalTime = millis();

    // Calculate all distances in centimeters
    long distance1 = measureDistance(trigPin, echoPin);
    long distance2 = measureDistance(Trig2Pin, Echo2Pin);
    long distance3 = measureDistanceSinglePinSIG(SIG_TrigEcho3Pin);

    // Check if object is detected within a certain range
    if ((distance1 < STOP_DISTANCE) || (distance2 < STOP_DISTANCE) || (distance3 < STOP_DISTANCE)) {
      if (!isPaused) {
        pauseStartTime = millis(); // Start pause timing
        isPaused = true;
        Serial.println(caractereS);
        delay(100);
        stopRobot();  // Stop motors if object detected
      }
      delay(100);  // Delay for 0.1 second while checking the distances again
    }
    else {
      if (isPaused) {
        totalPausedTime += millis() - pauseStartTime; // Adjust total paused time
        isPaused = false;
      }
      moveMotorsTurning(90, TRUE, FALSE); // Resume or keep turning
      unsigned long elapsedTime = millis() - startTime - totalPausedTime;
      accumulatedPathTime = (elapsedTime > SEC_TURN_90) ? SEC_TURN_90 : elapsedTime; // Update accumulated path time, ensuring it doesn't exceed 90 seconds
    }

    if (digitalRead(BUTTON_PIN) == HIGH) {  // Check if button is pressed
      stopRobot();  // Stop the robot when button is not pressed
      button_pressed = TRUE;
    }
    delay(100);  // Adjust delay based on application needs
  }
}

void path_7_turn_90_right() {
  Serial.println("Path_7");
  char caractereS = 'S';

  startTime = millis();
  accumulatedPathTime = 0;
  pauseStartTime = 0;
  totalPausedTime = 0;
  isPaused = false;

  while((accumulatedPathTime < SEC_TURN_90) && (digitalRead(BUTTON_PIN) == LOW) && ((currentGlobalTime - startGlobalTime) < (MATCH_DURATION - TIME_END_ROBOT_FROM_END_MATCH))) {
    currentTimeLoop = millis();
    currentGlobalTime = millis();

    // Calculate all distances in centimeters
    long distance1 = measureDistance(trigPin, echoPin);
    long distance2 = measureDistance(Trig2Pin, Echo2Pin);
    long distance3 = measureDistanceSinglePinSIG(SIG_TrigEcho3Pin);

    // Check if object is detected within a certain range
    if ((distance1 < STOP_DISTANCE) || (distance2 < STOP_DISTANCE) || (distance3 < STOP_DISTANCE)) {
      if (!isPaused) {
        pauseStartTime = millis(); // Start pause timing
        isPaused = true;
        Serial.println(caractereS);
        delay(100);
        stopRobot();  // Stop motors if object detected
      }
      delay(100);  // Delay for 0.1 second while checking the distances again
    }
    else {
      if (isPaused) {
        totalPausedTime += millis() - pauseStartTime; // Adjust total paused time
        isPaused = false;
      }
      moveMotorsTurning(90, TRUE, FALSE); // Resume or keep turning
      unsigned long elapsedTime = millis() - startTime - totalPausedTime;
      accumulatedPathTime = (elapsedTime > SEC_TURN_90) ? SEC_TURN_90 : elapsedTime; // Update accumulated path time, ensuring it doesn't exceed 90 seconds
    }

    if (digitalRead(BUTTON_PIN) == HIGH) {  // Check if button is pressed
      stopRobot();  // Stop the robot when button is not pressed
      button_pressed = TRUE;
    }
    delay(100);  // Adjust delay based on application needs
  }
}

void path_9_turn_180_left() {
  Serial.println("Path_9");
  char caractereS = 'S';

  startTime = millis();
  accumulatedPathTime = 0;
  pauseStartTime = 0;
  totalPausedTime = 0;
  isPaused = false;

  while((accumulatedPathTime < SEC_TURN_90) && (digitalRead(BUTTON_PIN) == LOW) && ((currentGlobalTime - startGlobalTime) < (MATCH_DURATION - TIME_END_ROBOT_FROM_END_MATCH))) {
    currentTimeLoop = millis();
    currentGlobalTime = millis();

    // Calculate all distances in centimeters
    long distance1 = measureDistance(trigPin, echoPin);
    long distance2 = measureDistance(Trig2Pin, Echo2Pin);
    long distance3 = measureDistanceSinglePinSIG(SIG_TrigEcho3Pin);

    // Check if object is detected within a certain range
    if ((distance1 < STOP_DISTANCE) || (distance2 < STOP_DISTANCE) || (distance3 < STOP_DISTANCE)) {
      if (!isPaused) {
        pauseStartTime = millis(); // Start pause timing
        isPaused = true;
        Serial.println(caractereS);
        delay(100);
        stopRobot();  // Stop motors if object detected
      }
      delay(100);  // Delay for 0.1 second while checking the distances again
    }
    else {
      if (isPaused) {
        totalPausedTime += millis() - pauseStartTime; // Adjust total paused time
        isPaused = false;
      }
      moveMotorsTurning(90, FALSE, TRUE); // Resume or keep turning
      unsigned long elapsedTime = millis() - startTime - totalPausedTime;
      accumulatedPathTime = (elapsedTime > SEC_TURN_180) ? SEC_TURN_180 : elapsedTime; // Update accumulated path time, ensuring it doesn't exceed 90 seconds
    }

    if (digitalRead(BUTTON_PIN) == HIGH) {  // Check if button is pressed
      stopRobot();  // Stop the robot when button is not pressed
      button_pressed = TRUE;
    }
    delay(100);  // Adjust delay based on application needs
  }
}

void path_11_turn_90_left() {
  Serial.println("Path_11");
  char caractereS = 'S';

  startTime = millis();
  accumulatedPathTime = 0;
  pauseStartTime = 0;
  totalPausedTime = 0;
  isPaused = false;

  while((accumulatedPathTime < SEC_TURN_90) && (digitalRead(BUTTON_PIN) == LOW) && ((currentGlobalTime - startGlobalTime) < (MATCH_DURATION - TIME_END_ROBOT_FROM_END_MATCH))) {
    currentTimeLoop = millis();
    currentGlobalTime = millis();

    // Calculate all distances in centimeters
    long distance1 = measureDistance(trigPin, echoPin);
    long distance2 = measureDistance(Trig2Pin, Echo2Pin);
    long distance3 = measureDistanceSinglePinSIG(SIG_TrigEcho3Pin);

    // Check if object is detected within a certain range
    if ((distance1 < STOP_DISTANCE) || (distance2 < STOP_DISTANCE) || (distance3 < STOP_DISTANCE)) {
      if (!isPaused) {
        pauseStartTime = millis(); // Start pause timing
        isPaused = true;
        Serial.println(caractereS);
        delay(100);
        stopRobot();  // Stop motors if object detected
      }
      delay(100);  // Delay for 0.1 second while checking the distances again
    }
    else {
      if (isPaused) {
        totalPausedTime += millis() - pauseStartTime; // Adjust total paused time
        isPaused = false;
      }
      moveMotorsTurning(90, FALSE, TRUE); // Resume or keep turning
      unsigned long elapsedTime = millis() - startTime - totalPausedTime;
      accumulatedPathTime = (elapsedTime > SEC_TURN_90) ? SEC_TURN_90 : elapsedTime; // Update accumulated path time, ensuring it doesn't exceed 90 seconds
    }

    if (digitalRead(BUTTON_PIN) == HIGH) {  // Check if button is pressed
      stopRobot();  // Stop the robot when button is not pressed
      button_pressed = TRUE;
    }
    delay(100);  // Adjust delay based on application needs
  }
}

void path_13_turn_180_right() {
  Serial.println("Path_13");
  char caractereS = 'S';

  startTime = millis();
  accumulatedPathTime = 0;
  pauseStartTime = 0;
  totalPausedTime = 0;
  isPaused = false;

  while((accumulatedPathTime < SEC_TURN_90) && (digitalRead(BUTTON_PIN) == LOW) && ((currentGlobalTime - startGlobalTime) < (MATCH_DURATION - TIME_END_ROBOT_FROM_END_MATCH))) {
    currentTimeLoop = millis();
    currentGlobalTime = millis();

    // Calculate all distances in centimeters
    long distance1 = measureDistance(trigPin, echoPin);
    long distance2 = measureDistance(Trig2Pin, Echo2Pin);
    long distance3 = measureDistanceSinglePinSIG(SIG_TrigEcho3Pin);

    // Check if object is detected within a certain range
    if ((distance1 < STOP_DISTANCE) || (distance2 < STOP_DISTANCE) || (distance3 < STOP_DISTANCE)) {
      if (!isPaused) {
        pauseStartTime = millis(); // Start pause timing
        isPaused = true;
        Serial.println(caractereS);
        delay(100);
        stopRobot();  // Stop motors if object detected
      }
      delay(100);  // Delay for 0.1 second while checking the distances again
    }
    else {
      if (isPaused) {
        totalPausedTime += millis() - pauseStartTime; // Adjust total paused time
        isPaused = false;
      }
      moveMotorsTurning(90, TRUE, FALSE); // Resume or keep turning
      unsigned long elapsedTime = millis() - startTime - totalPausedTime;
      accumulatedPathTime = (elapsedTime > SEC_TURN_180) ? SEC_TURN_180 : elapsedTime; // Update accumulated path time, ensuring it doesn't exceed 90 seconds
    }

    if (digitalRead(BUTTON_PIN) == HIGH) {  // Check if button is pressed
      stopRobot();  // Stop the robot when button is not pressed
      button_pressed = TRUE;
    }
    delay(100);  // Adjust delay based on application needs
  }
}

void path_15_turn_90_left() {
  Serial.println("Path_15");
  char caractereS = 'S';

  startTime = millis();
  accumulatedPathTime = 0;
  pauseStartTime = 0;
  totalPausedTime = 0;
  isPaused = false;

  while((accumulatedPathTime < SEC_TURN_90) && (digitalRead(BUTTON_PIN) == LOW) && ((currentGlobalTime - startGlobalTime) < (MATCH_DURATION - TIME_END_ROBOT_FROM_END_MATCH))) {
    currentTimeLoop = millis();
    currentGlobalTime = millis();

    // Calculate all distances in centimeters
    long distance1 = measureDistance(trigPin, echoPin);
    long distance2 = measureDistance(Trig2Pin, Echo2Pin);
    long distance3 = measureDistanceSinglePinSIG(SIG_TrigEcho3Pin);

    // Check if object is detected within a certain range
    if ((distance1 < STOP_DISTANCE) || (distance2 < STOP_DISTANCE) || (distance3 < STOP_DISTANCE)) {
      if (!isPaused) {
        pauseStartTime = millis(); // Start pause timing
        isPaused = true;
        Serial.println(caractereS);
        delay(100);
        stopRobot();  // Stop motors if object detected
      }
      delay(100);  // Delay for 0.1 second while checking the distances again
    }
    else {
      if (isPaused) {
        totalPausedTime += millis() - pauseStartTime; // Adjust total paused time
        isPaused = false;
      }
      moveMotorsTurning(90, FALSE, TRUE); // Resume or keep turning
      unsigned long elapsedTime = millis() - startTime - totalPausedTime;
      accumulatedPathTime = (elapsedTime > SEC_TURN_90) ? SEC_TURN_90 : elapsedTime; // Update accumulated path time, ensuring it doesn't exceed 90 seconds
    }

    if (digitalRead(BUTTON_PIN) == HIGH) {  // Check if button is pressed
      stopRobot();  // Stop the robot when button is not pressed
      button_pressed = TRUE;
    }
    delay(100);  // Adjust delay based on application needs
  }
}

void path_17_turn_90_left_put() {
  Serial.println("Path_17");
  char caractereS = 'S', caractereD = 'D';
  startTime = millis();
  accumulatedPathTime = 0;
  pauseStartTime = 0;
  totalPausedTime = 0;
  isPaused = false;

  while((accumulatedPathTime < SEC_TURN_90) && (digitalRead(BUTTON_PIN) == LOW) && ((currentGlobalTime - startGlobalTime) < (MATCH_DURATION - TIME_END_ROBOT_FROM_END_MATCH))) {
    currentTimeLoop = millis();
    currentGlobalTime = millis();

    // Calculate all distances in centimeters
    long distance1 = measureDistance(trigPin, echoPin);
    long distance2 = measureDistance(Trig2Pin, Echo2Pin);
    long distance3 = measureDistanceSinglePinSIG(SIG_TrigEcho3Pin);

    // Check if object is detected within a certain range
    if ((distance1 < STOP_DISTANCE) || (distance2 < STOP_DISTANCE) || (distance3 < STOP_DISTANCE)) {
      if (!isPaused) {
        pauseStartTime = millis(); // Start pause timing
        isPaused = true;
        Serial.println(caractereS);
        delay(100);
        stopRobot();  // Stop motors if object detected
      }
      delay(100);  // Delay for 0.1 second while checking the distances again
    }
    else {
      if (isPaused) {
        totalPausedTime += millis() - pauseStartTime; // Adjust total paused time
        isPaused = false;
      }

      moveMotorsTurning(90, FALSE, TRUE); // Resume or keep turning
      unsigned long elapsedTime = millis() - startTime - totalPausedTime;
      accumulatedPathTime = (elapsedTime > SEC_TURN_90) ? SEC_TURN_90 : elapsedTime; // Update accumulated path time, ensuring it doesn't exceed 90 seconds
    }

    if (digitalRead(BUTTON_PIN) == HIGH) {  // Check if button is pressed
      stopRobot();  // Stop the robot when button is not pressed
      button_pressed = TRUE;
    }
    delay(100);  // Adjust delay based on application needs
  }

  if(digitalRead(BUTTON_PIN) == LOW) {
    Serial.println(caractereD);
    delay(100);
    stopRobot();                        // Stop the robot if infrared sensor detects something
    delay(TIME_PUT_PLANT);              // Delay to put the plant.
  }
}

// CONTROL THE ROBOT //
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
    moveMotorsForward(speed);
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

// TURN THE ROBOT //
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

void moveMotorsForward(int speed) {
  Wire.beginTransmission(MD25ADDRESS);
  Wire.write(SPEED2);
  Wire.write(speed);  // Set speed to maximum (255) for motor 2 (adjust as needed for your setup)
  Wire.endTransmission();

  Wire.beginTransmission(MD25ADDRESS);
  Wire.write(SPEED1);
  Wire.write(speed);  // Set speed to maximum (255) for motor 1 (adjust as needed for your setup)
  Wire.endTransmission();
}

void moveMotorsTurning(int angle, int Right, int Left) {
  if((Right == FALSE) && (Left == TRUE)) {
    Wire.beginTransmission(MD25ADDRESS);
    Wire.write(SPEED2);
    Wire.write(140);  // Set speed to minimum (128 = Motor stops) for motor 2 (adjust as needed for your setup)
    Wire.endTransmission();

    Wire.beginTransmission(MD25ADDRESS);
    Wire.write(SPEED1);
    Wire.write(128);  // Set speed to 175 for motor 1 (adjust as needed for your setup)
    Wire.endTransmission();
  }
  else if((Right == TRUE) && (Left == FALSE)) {
    Wire.beginTransmission(MD25ADDRESS);
    Wire.write(SPEED2);
    Wire.write(128);  // Set speed to 175 for motor 2 (adjust as needed for your setup)
    Wire.endTransmission();

    Wire.beginTransmission(MD25ADDRESS);
    Wire.write(SPEED1);
    Wire.write(140);  // Set speed to minimum (128 = Motor stops) for motor 1 (adjust as needed for your setup)
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