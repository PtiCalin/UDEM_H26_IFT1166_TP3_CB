# argcv911.cpp

Exemple fourni par le professeur qui montre comment lire les arguments de la ligne de commande en C++ avec `argc` et `argv`.

## À propos de la ressource

1. Affiche le nom du programme (`argv[0]`).
2. Vérifie qu'on a reçu exactement 3 arguments (sinon affiche un message d'erreur et quitte).
3. Affiche chaque argument un par un.

## Utilité pour le TP

Dans le TP2, le `main` doit lire des options comme `-i`, `-o`, `-ajout`, etc. depuis la ligne de commande. Ce fichier montre le mécanisme de base :

- `argc` = combien d'arguments il y a (le nom du programme compte comme le premier).
- `argv` = tableau de chaînes contenant chaque argument.
- On parcourt `argv` avec une boucle `for` pour lire les valeurs.

C'est le point de départ pour comprendre comment parser les options dans `main.cpp`.