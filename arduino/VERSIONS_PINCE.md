# Versions du code de la pince

Toutes les versions tournent sur la carte Arduino Uno qui commande la pince. Sauf `Pince_servos.ino`, elles reçoivent leurs ordres par la liaison série à 9600 bauds. Les quatre sont gardées pour montrer l'évolution du code. Les trois dernières partent de l'exemple `servo.ino` du kit Adeept (en-tête conservé).

| Ordre | Fichier | Déclenchement | Servomoteurs | Fonctions |
|---|---|---|---|---|
| 1 | `essais_pince/arduino_slave.ino` | Ligne `Object Detected` reçue | 1 (broche 9) | 0° → 180° pendant 2 s → 0° |
| 2 | `essais_pince/Pince_servos.ino` | Automatique : au 200e passage de `loop()` | 5 (broches 9, 6, 5, 3, 11) | desserrer, descendre, attraper, test, position par défaut, détachement |
| 3 | `Asservissement_pince/Asservissement_pince.ino` | Caractère `O` reçu | 5 (mêmes broches) | mêmes fonctions que la version 2 ; sur `O` : position par défaut puis détachement |
| 4 | `Pince_arduino_uno_2_0_0/Pince_arduino_uno_2_0_0.ino` | Un caractère par commande | 6 (+ broche 10 pour le bras du panneau solaire) | voir ci-dessous |

## Différences entre les versions 2 et 3

`Pince_servos.ino` et `Asservissement_pince.ino` ont les **mêmes fonctions de mouvement** (`pince_desserer`, `pince_descendre`, `pince_attraper`, `fonction_test`, `pince_position_defaut`, `detachage_servos`) avec les mêmes angles. Seule la boucle principale change :

- `Pince_servos.ino` : aucune commande extérieure ; un compteur incrémenté à chaque passage de `loop()` lance la position par défaut quand il vaut 200. C'est un **banc d'essai autonome** des servomoteurs.
- `Asservissement_pince.ino` : la pince attend le caractère `O` sur la liaison série, puis se met en position par défaut et détache ses servomoteurs. C'est la **première version pilotée par une autre carte**. Le bloc du compteur y est encore présent, mais commenté. Le détachement se termine par une pause de 5 s.

Malgré son nom, `Asservissement_pince.ino` ne contient pas d'asservissement en boucle fermée : les servomoteurs sont commandés en position.

## Version 4 : `Pince_arduino_uno_2_0_0.ino` (la plus complète)

Protocole à un caractère :

| Caractère | Action |
|---|---|
| `O` | position par défaut de tous les servomoteurs (dont le bras du panneau solaire à 90°) |
| `R` | repos : détachement des 6 servomoteurs |
| `B` | tourner le panneau solaire pour l'équipe bleue (servomoteur de la broche 10 à 0°) |
| `J` | tourner le panneau solaire pour l'équipe jaune (servomoteur de la broche 10 à 180°) |
| `A` | attraper une plante : ouvrir, tourner la base, descendre progressivement, refermer, remonter |
| `D` | déposer la plante : descendre doucement, ouvrir, remonter, revenir en position par défaut |
| `T` | test : servomoteur de la pince (broche 11) à 95° |

Par rapport aux versions 2 et 3, les mouvements sont progressifs (boucles `for`, 20 ms par degré) au lieu de sauts directs, et plusieurs angles sont marqués `VALEUR MODIFIÉE` (réglages faits sur le robot). Le servomoteur de la broche 6 n'est plus utilisé (lignes commentées).

Quelle version a tourné pendant les matchs : à confirmer.

Le fichier de même nom ré-uploadé sur le Drive le 8 octobre 2026 est identique à celui-ci.
