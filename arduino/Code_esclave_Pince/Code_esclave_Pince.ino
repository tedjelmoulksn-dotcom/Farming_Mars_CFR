#include <Servo.h>

Servo myservo1; 
Servo myservo2; 
Servo myservo3; 
Servo myservo4; 
Servo myservo5;

void setup() {
  Serial.begin(9600); // Initialize serial communication at 9600 baud
  delay(1000); // Wait for a second
}

void loop() {
  // Read serial input and trim any whitespace
  String message = readSerialMessage();
  message.trim(); // Remove any leading/trailing whitespace
  
  Serial.println(message); // Print the message for debugging
  delay(100);

  if (message == "Object Detected") {
    Serial.println("Object Detected, Servo turning");
    
    Serial.print("Mettre pince à position de défaut\n");
    pince_position_defaut();

    Serial.print("Détachage des servomoteurs\n");
    detachage_servos();
  }
}

String readSerialMessage() {
  String message = "";
  while (Serial.available()) {
    char ch = (char)Serial.read();
    if (ch == '\n') {
      break;
    }
    message += ch;
  }
  return message;
}

void pince_position_defaut() {
  myservo5.attach(11);
  Serial.print("servo 5_1\n");
  myservo5.write(135);
  delay(1000);
  myservo4.attach(3);
  Serial.print("servo 4\n");
  myservo4.write(40);
  delay(1000);
  myservo3.attach(5);
  Serial.print("servo 3\n");
  myservo3.write(0);
  delay(1000);
  myservo2.attach(6);
  Serial.print("servo 2\n");
  myservo2.write(0);
  delay(1000);
  Serial.print("servo 1\n");
  myservo1.attach(9);
  myservo1.write(135);
  delay(1000);
  
  delay(2000);
}

void detachage_servos() {
  myservo1.detach();
  myservo2.detach();
  myservo3.detach();
  myservo4.detach();
  myservo5.detach();

  delay(5000);
}