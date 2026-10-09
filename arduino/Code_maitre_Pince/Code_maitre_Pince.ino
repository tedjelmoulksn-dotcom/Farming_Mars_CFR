// Code pour la carte maître

const int infraredSensorPin = 4; // Pin du capteur infrarouge
bool objectDetected = false;

void setup() {
  pinMode(infraredSensorPin, INPUT);
  Serial.begin(9600); // Initialiser la communication série à 9600 bauds
  delay(1000); // Attendre une seconde
}

void loop() {
  int sensorValue = digitalRead(infraredSensorPin); // Lire l'état du capteur

  if (sensorValue != HIGH && !objectDetected) {
    // Si l'objet est détecté et que ce n'est pas déjà signalé
    objectDetected = true;
    Serial.println("Object Detected"); // Envoyer un message à l'esclave
  } else if (sensorValue != LOW && objectDetected) {
    // Si l'objet n'est plus détecté
    objectDetected = false;
    Serial.println("Object Not Detected"); // Envoyer un message à l'esclave (optionnel)
  }

  delay(100); // Petite pause pour éviter les détections répétées rapides
}