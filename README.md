# Farming Mars — Coupe de France de Robotique

Projet robotique réalisé autour du thème **Farming Mars** de la Coupe de France de Robotique.

## Objectif

Concevoir plusieurs fonctions robotiques capables d'exécuter de manière autonome les actions demandées par le règlement : se déplacer sur l'aire de jeu, détecter l'environnement, manipuler des éléments et enchaîner les missions dans le temps imparti.

## Compétences mobilisées

- programmation embarquée ;
- commande de moteurs ;
- lecture de capteurs ;
- automatisation par machine à états ;
- conception mécanique et électronique ;
- intégration et essais d'un système complet ;
- travail en équipe et stratégie de match.

## Architecture fonctionnelle

```text
Capteurs
   |
   v
Décision / machine à états
   |
   +----> Navigation
   |
   +----> Actionneurs et mécanismes
   |
   v
Suivi de mission
```

## Organisation recommandée

```text
firmware/       # Programmes embarqués
electronics/    # Schémas et câblage
mechanics/      # CAO et pièces mécaniques
strategy/       # Séquences et stratégie de match
tests/          # Procédures et résultats d'essais
media/          # Photos et vidéos du robot
```

## Démarche de développement

1. analyser le règlement et les contraintes de l'aire de jeu ;
2. répartir les missions entre les sous-systèmes ;
3. tester séparément les capteurs, moteurs et mécanismes ;
4. intégrer les fonctions dans une machine à états ;
5. réaliser des essais chronométrés en conditions de match ;
6. corriger les défaillances observées et fiabiliser le robot.

## État du dépôt

Le dépôt contient actuellement la présentation initiale du projet. Les programmes, schémas, modèles mécaniques et résultats d'essais seront ajoutés lorsqu'ils seront prêts à être publiés.

## Auteure

Tedj El Moulk Sinacer
