/***********************************************************
File name: Pince_arduino_uno.ino
Description:   The servo motor circulates to 180 degrees, 90 degrees
               Degrees, 0 degrees,
Website: www.adeept.com
E-mail: support@adeept.com
Author: Tom
Date: 2020/05/22 
***********************************************************/

#include <Servo.h>

Servo myservo1; //create servo object to control a servo
Servo myservo2; //create servo object to control a servo
Servo myservo3; //create servo object to control a servo
Servo myservo4; //create servo object to control a servo
Servo myservo5; //create servo object to control a servo
Servo myservo6; //create servo object to control le bras solaire
Servo myservo5_bis; //create servo object to control a servo
int compteur = 0;

void setup()
{
  Serial.begin(9600); // initialise la communication série à 9600 bauds
  delay(1000); // wait for a second
}

void loop()
{
  if(Serial.available() > 0)
  {
    char incomingByte = Serial.read();
    Serial.println(incomingByte);

    if(incomingByte == 'O') // défaut
    { 
      Serial.print("Mettre pince à position de défaut\n");
      pince_position_defaut();
    }

    if(incomingByte == 'R') // repos
    {
      Serial.print("Détachage des servomoteurs\n");
      detachage_servos();
    }

    if(incomingByte == 'B') // bleu
    {
      Serial.print("Panneau solaire vers bleu\n");
      pince_tourner_panneau_solaire_bleu();
    }

    if(incomingByte == 'J') // jaune
    {
      Serial.print("Panneau solaire vers jaune\n");
      pince_tourner_panneau_solaire_jaune();
    }

    if(incomingByte == 'A') // attraper plante
    {
      Serial.print("Attraper plante\n");
      pince_attraper_plante();
    }

    if(incomingByte == 'D') // deposer plante
    {
      Serial.print("Déposer plante\n");
      pince_deposer_plante();
    }

    if(incomingByte == 'T') // défaut
    { 
      Serial.print("Mettre pince à position de défaut\n");
      test();
    }
  }
}

void pince_position_defaut()
{
  // bras solaire
  myservo6.attach(10);
  myservo6.write(90);

  // pince
  myservo5.attach(11); // attachs the servo 5 on pin 11 to servo object
  myservo5.write(95); // VALEUR MODIFIÉE
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
  myservo5.write(50); // VALEUR MODIFIÉE
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
  for (int i=50; i<95; i++) //VALEUR MODIFIÉES
  {
    myservo5.write(i);
    delay(20);
  }
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
  // ouvrir pince
  myservo5.attach(11);
  for (int i=95; i>50; i--) //VALEUR MODIFIÉES
  {
    myservo5.write(i);
    delay(20);
  }
  myservo5.write(40); // VALEUR MODIFIÉE
  delay(500);
  // rebaisser le bras
  myservo3.write(90);
  delay(500);
  // tourner base pince
  //myservo1.attach(9);
  //myservo1.write(25);
  //delay(500);
  // remonter le bras
  myservo3.attach(5);
  myservo3.write(80);
  delay(200);
  myservo3.write(70);
  delay(200);
  myservo3.write(60);
  delay(200);
  myservo3.write(0);
  delay(500);

  // remise a zero
  pince_position_defaut();
}

void pince_tourner_panneau_solaire_bleu()
{
  // baisser le bras
  myservo6.attach(10);
  myservo6.write(90);
  myservo6.write(0); // à droite pour l'équipe bleue
}

void pince_tourner_panneau_solaire_jaune()
{
  // baisser le bras
  myservo6.attach(10);
  myservo6.write(90);
  delay(1000);
  myservo6.write(180); // à droite pour l'équipe jaune
}

void test()
{
   // ouvrir pince
  myservo5.attach(11);
  myservo5.write(95);
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