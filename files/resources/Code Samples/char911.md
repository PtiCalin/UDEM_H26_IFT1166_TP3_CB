# char911.cpp

Guide de référence fourni par le professeur qui montre comment manipuler des caractères et des chaînes `char*` en C++.

## À propos de la ressource

Le programme regroupe 5 fonctions :

| Fonction | Ce qu'elle montre |
|---|---|
| `Traitement_de_chaines()` | `strlen`, `strcpy`, `strncpy`, `strcat`, `strcmp`, `strchr`, `strstr`, `strtok`, etc. |
| `Test_de_caracteres()` | `isalnum`, `isalpha`, `isdigit`, `islower`, `isupper`, `isspace`, etc. |
| `Conversion_de_caracteres()` | `tolower`, `toupper`, `toascii` |
| `Conversion_de_chaines()` | `atof`, `atoi`, `atol` (conversion texte → nombre) |
| `Conversion_d1_entier()` | Conversion nombre → texte (implémentation maison de `itoa`) |

## Utilité pour le TP

Dans le TP2, on manipule beaucoup de `char*` sans la STL. Ce fichier sert de aide-mémoire pour les fonctions qu'on utilise directement dans le code :

- `strlen` / `strcpy` / `strncpy` → copier le code et le nom d'un article
- `strcmp` → comparer deux codes lors de la recherche
- `atof` / `atoi` → convertir les arguments prix et quantité de la ligne de commande
- `strncpy` + `'\0'` manuel → tronquer le code à 15 caractères

C'est un catalogue d'exemples à consulter quand on hésite sur le comportement d'une fonction `<cstring>` ou `<cstdlib>`.