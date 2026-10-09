/***********************************************************
File name: servo.ino
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
Servo myservo5_bis; //create servo object to control a servo
int compteur = 0;

void setup()
{
  Serial.begin(9600); // initialise la communication série à 9600 bauds
  delay(1000); // wait for a second
}

void loop()
{
  // ---------- Permet de copier-coller facilement attach() ------------- //
  // -------------------------------------------------------------------- //
  // myservo1.attach(9); // attachs the servo 1 on pin 9 to servo object
  // myservo2.attach(6); // attachs the servo 2 on pin 6 to servo object
  // myservo3.attach(5); // attachs the servo 3 on pin 5 to servo object
  // myservo4.attach(3); // attachs the servo 4 on pin 3 to servo object
  // myservo5.attach(11); // attachs the servo 5 on pin 11 to servo object
  // myservo5_bis.attach(11); // attachs the servo 5 on pin 11 to servo object
  // -------------------------------------------------------------------- //

  Serial.println(compteur);
  if(compteur == 200)
  {
    Serial.print("Mettre pince à position de défaut\n");
    pince_position_defaut();


    Serial.print("Détachage des servomoteurs\n");
    detachage_servos();
  }

  compteur++;
  Serial.println(compteur);
}

void pince_desserer()
{
  Serial.print("servo 5\n");
  myservo5.attach(11); // attachs the servo 5 on pin 11 to servo object
  myservo5.write(60);
  delay(1000);
  myservo5.detach(); // detachs the servo 5
  
  delay(1000);
}

void pince_descendre()
{ 
  Serial.print("servo 3\n");
  myservo3.attach(5); // attachs the servo 3 on pin 5 to servo object
  myservo3.write(75);
  delay(1000);
  myservo3.detach(); // detachs the servo 3
}

void pince_attraper()
{
  Serial.print("servo 5bis\n");
  myservo5_bis.attach(11); // attachs the servo 5_bis on pin 11 to servo object
  myservo5_bis.write(130);
  delay(1000);
  Serial.println(myservo5_bis.attached());
  myservo5_bis.detach(); // detachs the servo 5_bis
  
  delay(1000);
}

void fonction_test()
{
  // Ecriture du code : //
  myservo5.attach(11); // attachs the servo 5 on pin 11 to servo object
  Serial.print("servo 5_1\n");
  myservo5.write(60);
  delay(2000);
  myservo4.attach(3); // attachs the servo 4 on pin 3 to servo object
  Serial.print("servo 4\n");
  myservo4.write(15);
  delay(2000);
  myservo3.attach(5); // attachs the servo 3 on pin 5 to servo object
  Serial.print("servo 3\n");
  myservo3.write(5);
  delay(2000);
  myservo2.attach(6); // attachs the servo 2 on pin 6 to servo object
  Serial.print("servo 2\n");
  myservo2.write(30);
  delay(2000);
  Serial.print("servo 1\n");
  myservo1.attach(9); // attachs the servo 1 on pin 9 to servo object
  myservo1.write(25);
  delay(500);
  Serial.print("servo 5_2\n");
  myservo5.write(110);
  delay(10000);


  // Détachage des servomoteurs : //
  myservo1.detach();
  myservo2.detach();
  myservo3.detach();
  myservo4.detach();
  myservo5.detach();

  delay(1000);
}

void pince_position_defaut()
{
  // Ecriture du code : //
  myservo5.attach(11); // attachs the servo 5 on pin 11 to servo object
  Serial.print("servo 5_1\n");
  myservo5.write(135);
  delay(1000);
  myservo4.attach(3); // attachs the servo 4 on pin 3 to servo object
  Serial.print("servo 4\n");
  myservo4.write(40);
  delay(1000);
  myservo3.attach(5); // attachs the servo 3 on pin 5 to servo object
  Serial.print("servo 3\n");
  myservo3.write(0);
  delay(1000);
  myservo2.attach(6); // attachs the servo 2 on pin 6 to servo object
  Serial.print("servo 2\n");
  myservo2.write(0);
  delay(1000);
  Serial.print("servo 1\n");
  myservo1.attach(9); // attachs the servo 1 on pin 9 to servo object
  myservo1.write(135);
  delay(1000);
  
  delay(10000);
}

void detachage_servos()
{
  // Détachage des servomoteurs : //
    myservo1.detach();
    myservo2.detach();
    myservo3.detach();
    myservo4.detach();
    myservo5.detach();
}