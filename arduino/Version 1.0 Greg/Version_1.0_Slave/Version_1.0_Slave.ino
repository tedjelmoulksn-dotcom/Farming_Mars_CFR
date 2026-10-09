// ----- VERSION - 1.0 ----- //

// ----- SLAVE ----- //

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET     4
#include <Servo.h>

Servo myservo1; 
Servo myservo2; 
Servo myservo3; 
Servo myservo4; 
Servo myservo5;
Adafruit_SSD1306 display(128, 64, &Wire, OLED_RESET);


void setup() {
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(WHITE);//Sets the font display color
  display.clearDisplay();//cls
}

void loop() {
  //Set the font size
  display.setTextSize(2);
  //Set the display location
  display.setCursor(30,30);
  char receivedValue = Serial.read();
  delay(500);
  if(receivedValue == 'A')
  {
    display.clearDisplay();//cls
    display.print("Alumee");  // Allume la LED
    display.display();
    delay(5000);             // Attend 5 secondes
  }
  if(receivedValue == 'E'){
    display.clearDisplay();//cls
    display.print("Eteinte");
    display.display();
    delay(1000);             // Attend 1 seconde
  }
  if(receivedValue == 'O'){
    display.clearDisplay();//cls
    display.print("Object");
    display.display();
    delay(1000);             // Attend 1 seconde
    
    Serial.println("Object Detected, Servo turning");
    
    Serial.print("Mettre pince à position de défaut\n");
    pince_position_defaut();

    Serial.print("Détachage des servomoteurs\n");
    detachage_servos();
  }
  display.clearDisplay();//cls Clear
  //String displayed
  display.display();
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