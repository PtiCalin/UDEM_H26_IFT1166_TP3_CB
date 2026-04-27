# fichier911.cpp

Exemple fourni par le professeur qui montre comment ouvrir, lire et écrire dans un fichier texte en C++.

## À propos de la ressource

Trois fonctions, chacune illustrant une étape :

| Fonction | Ce qu'elle montre |
|---|---|
| `ouv_ferm_fic()` | Les différentes façons d'ouvrir un fichier (`ifstream`, `ofstream`, `fstream`, avec `open()` ou directement au constructeur), et comment vérifier que l'ouverture a réussi avec `is_open()` |
| `ecrire_fic()` | Écrire dans un fichier avec `<<` (même syntaxe que `cout`, mais sur un `ofstream`) |
| `lire_fic()` | Lire un fichier mot par mot avec `>>` dans une boucle `while (!fic.eof())` |

Le `main` appelle les trois dans l'ordre : ouvrir → écrire → relire ce qui a été écrit.

## Utilité pour le TP

Dans le TP2, les fonctions `importerInventaire` et `exporterInventaire` :

- Ouvrir un fichier avec `std::ifstream` / `std::ofstream`
- Vérifier `is_open()` avant de continuer
- Lire ligne par ligne avec `getline()`
- Écrire avec `<<`
- Fermer avec `close()`

Ce fichier montre le mécanisme de base de la lecture/écriture fichier qu'on adapte ensuite pour le format CSV du TP.
