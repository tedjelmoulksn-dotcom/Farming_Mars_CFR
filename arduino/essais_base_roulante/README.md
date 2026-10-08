# Essais de la base roulante

Croquis de mise au point écrits par le sous-groupe « base roulante » avant le programme de match. Ils sont conservés pour montrer la progression ; le programme utilisé en match est dans `../Match_1.0/`.

| Fichier | Date | Ce qu'il fait |
|---|---|---|
| `essai_ultrason_hcsr04.ino` | février 2024 | Mesure de distance au HC-SR04 : impulsion de 10 µs sur TRIG (broche 2), durée de l'écho sur broche 3 avec `pulseIn`, `distance = durée × 0,034 / 2`, affichage série toutes les 500 ms |
| `essai_infrarouge.ino` | février 2024 | Lecture tout ou rien du capteur infrarouge (broche 2) et message série |
| `essai_md25_encodeurs.ino` | février 2024 | Premier dialogue I2C avec la carte MD25 (adresse `0x58`) : écriture d'une consigne de vitesse, lecture d'un registre d'encodeur. Schéma de câblage : `../../assets/cablage_arduino_md25.png` |
| `base_md25_ultrason_ir.ino` | mai 2024 | Intégration : avance, ralentit sous 20 cm d'un obstacle, s'arrête 20 s quand l'infrarouge détecte un objet et envoie `Object Detected` sur la liaison série ; lit les deux encodeurs (4 octets) et la tension batterie |
| `base_md25_ultrason_ir_bouton.ino` | mai 2024 | Même logique, déclenchée par un bouton (broche 6, résistance de tirage interne) ; arrêt quand le bouton est relâché |

## Points à connaître

- **Registres MD25** : `SPEED1 = 0x00`, `SPEED2 = 0x01`, encodeurs `0x02` et `0x06`, tension `0x0A` (en dixièmes de volt). La valeur 128 correspond à l'arrêt.
- **Limite de `essai_md25_encodeurs.ino`** : il lit 2 octets par encodeur alors que le compteur de la MD25 en fait 4, et calcule l'adresse du second encodeur avec un pas de 2 au lieu de 4. Les versions suivantes lisent bien 4 octets à `0x02` et `0x06`.
- **Limite des versions d'intégration** : `Wire.write(-200)` et `Wire.write(-255)` envoient un octet tronqué, pas une vitesse négative ; les temporisations sont bloquantes (`delay`).
- Ces croquis n'ont pas été recompilés lors de la mise en forme du dépôt.

La note `docs/note_choix_capteurs_et_roues.docx` justifie le choix de deux HC-SR04 (5 V, 2 à 450 cm, angle ≤ 15°) et de roues omnidirectionnelles.
