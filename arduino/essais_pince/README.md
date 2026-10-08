# Essais de la pince

Premières versions de la commande de la pince (travail du sous-groupe « pince »), antérieures à `../Pince_arduino_uno_2_0_0/`. Voir `../VERSIONS_PINCE.md` pour la comparaison de toutes les versions.

| Fichier | Ce qu'il fait |
|---|---|
| `arduino_slave.ino` | Tout premier essai maître/esclave (mai 2024) : un seul servomoteur (broche 9) ; à la réception de la ligne `Object Detected` sur la liaison série, il passe à 180° pendant 2 s puis revient à 0° |
| `Code_maitre_Pince.ino` | Carte maître : lit le capteur infrarouge (broche 4) et envoie `Object Detected` ou `Object Not Detected` sur la liaison série, une seule fois par changement d'état |
| `Code_esclave_Pince.ino` | Carte esclave : lit une ligne sur la liaison série ; à réception de `Object Detected`, place les cinq servomoteurs en position par défaut puis les détache |
| `Pince_servos.ino` | Séquences élémentaires : desserrer, descendre, attraper, position par défaut, détachement des servomoteurs. Dans `loop()`, la position par défaut est déclenchée automatiquement au 200e passage de boucle (compteur), sans commande extérieure |

Brochage des servomoteurs relevé dans le code : 9, 6, 5, 3 et 11.

`Pince_servos.ino` dérive de l'exemple `servo.ino` du kit de bras robotisé Adeept (en-tête d'origine conservé). Le kit lui-même et ses bibliothèques ne sont pas redistribués ici.
