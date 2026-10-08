// ----- VERSION - 1.0 ----- //

// ----- MATCH_PINCE_SLAVE ----- //

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4
#include <Servo.h>

Servo myservo1; //create servo object to control a servo
Servo myservo2; //create servo object to control a servo
Servo myservo3; //create servo object to control a servo
Servo myservo4; //create servo object to control a servo
Servo myservo5; //create servo object to control a servo
Servo myservo6; //create servo object to control le bras solaire
Adafruit_SSD1306 display(128, 64, &Wire, OLED_RESET);

int compteur = 0;

void setup()
{
  Serial.begin(9600); // initialise la communication série à 9600 bauds
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(WHITE);//Sets the font display color
  display.clearDisplay();//cls
  delay(1000); // wait for a second
}

void loop()
{
  //Set the font size
  display.setTextSize(2);
  //Set the display location
  display.setCursor(0,30);
  delay(100);
  if(Serial.available() > 0)
  {
    char incomingByte = Serial.read();
    Serial.println(incomingByte);

    if(incomingByte == 'H') // tout début pour l'homologation statique.
    {
      display.clearDisplay();//cls
      display.setCursor(0,30);
      display.print("Homologation");
      display.display();

      pince_position_defaut();

      display.clearDisplay();//cls
      display.display();
    }

    if(incomingByte == 'G') // Départ du robot.
    {
      display.clearDisplay();//cls
      display.setCursor(0,30);
      display.print("Go !");
      display.display();

      delay(200);

      display.clearDisplay();//cls
      display.display();
    }

    if(incomingByte == 'E') // Départ du robot.
    {
      display.clearDisplay();//cls
      display.setCursor(0,30);
      display.print("End");
      display.display();

      delay(500);

      display.clearDisplay();//cls
      display.display();
    }

    if(incomingByte == 'O') // Position pince défaut.
    { 
      display.clearDisplay();//cls
      display.setCursor(0,30);
      display.print("Defaut");
      display.display();

      pince_position_defaut();

      display.clearDisplay();//cls
      display.display();
    }

    if(incomingByte == 'R') // repos
    {
      display.clearDisplay();//cls
      display.setCursor(0,30);
      display.print("Repos");
      display.display();

      detachage_servos();

      display.clearDisplay();//cls
      display.display();
    }

    if(incomingByte == 'B') // bleu
    {
      display.clearDisplay();//cls
      display.setCursor(0,30);
      display.print("Panneaux B");
      display.display();

      pince_tourner_panneau_solaire_bleu();

      display.clearDisplay();//cls
      display.display();
    }

    if(incomingByte == 'J') // jaune
    {
      display.clearDisplay();//cls
      display.setCursor(0,30);
      display.print("Panneaux J");
      display.display();

      pince_tourner_panneau_solaire_jaune();

      display.clearDisplay();//cls
      display.display();
    }

    if(incomingByte == 'A') // attraper plante
    {
      display.clearDisplay();//cls
      display.setCursor(0,30);
      display.print("Attraper");
      display.display();

      pince_attraper_plante();

      display.clearDisplay();//cls
      display.display();
    }

    if(incomingByte == 'D') // deposer plante
    {
      display.clearDisplay();//cls
      display.setCursor(0,30);
      display.print("Deposer");
      display.display();

      pince_deposer_plante();

      display.clearDisplay();//cls
      display.display();
    }
  }
  display.clearDisplay();//cls
  display.display();
}

void pince_position_defaut()
{
  // bras solaire
  myservo6.attach(10);
  myservo6.write(90);

  // pince
  myservo5.attach(11); // attachs the servo 5 on pin 11 to servo object
  myservo5.write(135);
  delay(500);
  myservo4.attach(3); // attachs the servo 4 on pin 3 to servo object
  myservo4.write(40);
  delay(500);
  myservo3.attach(5); // attachs the servo 3 on pin 5 to servo object
  myservo3.write(0);
  delay(500);
  //myservo2.attach(6); // attachs the servo 2 on pin 6 to servo object
  //myservo2.write(0);
  delay(500);
  myservo1.attach(9); // attachs the servo 1 on pin 9 to servo object
  myservo1.write(135);
  delay(500);
}

void pince_attraper_plante() // doit toujours etre suivi de pince_deposer_plante()
{
  // ouvrir pince
  myservo5.attach(11);
  myservo5.write(90);
  delay(500);
  // tourner base pince
  myservo1.attach(9);
  myservo1.write(0);
  delay(500);
  // baisser pince
  myservo3.attach(5);
  for (int i=0; i<80; i++)
  {
    myservo3.write(i);
    delay(20);
  }
  delay(500);

  // fermer pince
  myservo5.attach(11);
  myservo5.write(135);
  delay(500);

  // soulever pince
  myservo3.attach(5);
  for (int i=75; i>0; i--)
  {
    myservo3.write(i);
    delay(20);
  }
  myservo3.write(0);
  delay(200);
}

void pince_deposer_plante() // doit toujours etre précédé de pince_attraper_plante()
{
  // baisser pince doucement
  myservo3.attach(5);
  for (int i=0; i<80; i++)
  {
    myservo3.write(i);
    delay(20);
  }

  delay(500);
/*  
  myservo3.attach(5);
  
  myservo3.write(20);
  delay(200);
  myservo3.write(30);
  delay(200);
  myservo3.write(40);
  delay(200);
  myservo3.write(50);
  delay(200);
  myservo3.write(60);
  delay(200);
  myservo3.write(70);
  delay(200);
  myservo3.write(75);
  delay(200);
  myservo3.write(80);
  delay(500);
*/
  // ouvrir pince
  myservo5.attach(11);
  myservo5.write(90);
  delay(500);
  // rebaisser le bras
  myservo3.attach(5);
  for (int i=80; i<90; i++)
  {
    myservo3.write(i);
    delay(20);
  }
  myservo3.write(90);
  delay(500);
/*  
  myservo3.write(90);
  delay(500);
*/
  // tourner base pince
  //myservo1.attach(9);
  //myservo1.write(25);
  //delay(500);

  // remonter le bras
  myservo3.attach(5);
  for (int i=90; i>0; i--)
  {
    myservo3.write(i);
    delay(20);
  }
  myservo3.write(0);
  delay(200);
/*
  myservo3.attach(5);
  myservo3.write(80);
  delay(200);
  myservo3.write(70);
  delay(200);
  myservo3.write(60);
  delay(200);
  myservo3.write(0);
  delay(500);
*/

  // remise a zero
  pince_position_defaut();
}

void pince_tourner_panneau_solaire_bleu()
{
  // baisser le bras
  myservo6.attach(10);
  myservo6.write(90);
  myservo6.write(30);
  delay(100);
  myservo6.write(0); // à droite pour l'équipe bleue
}

void pince_tourner_panneau_solaire_jaune()
{
  // baisser le bras
  myservo6.attach(10);
  myservo6.write(90);
  myservo6.write(150);
  delay(100);
  myservo6.write(180); // à droite pour l'équipe jaune
}

void detachage_servos()
{
  // Détachage des servomoteurs : //
    myservo1.detach();
    myservo2.detach();
    myservo3.detach();
    myservo4.detach();
    myservo5.detach();
    myservo6.detach();
    
    delay(5000);
}