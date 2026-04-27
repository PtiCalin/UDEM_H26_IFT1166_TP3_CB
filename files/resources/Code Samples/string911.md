# string911.cpp

Exemple fourni par le professeur qui montre comment utiliser le type `std::string` en C++ et comment convertir entre `string` et `char*`.

## À propos de la ressource

- Créer et initialiser un `string` (avec `=` ou dans le constructeur)
- Concaténer deux `string` avec `+`
- Obtenir la longueur avec `.length()`
- Convertir un `char[]` en `string` (passer le tableau dans le constructeur)
- Convertir un `string` en `char*` avec `.c_str()` + `strcpy`

## Pourquoi c'est utile pour le TP

L'énoncé autorise `std::string` « si nécessaire ». Ce fichier montre comment passer de l'un à l'autre :

- `string` → `char*` : avec `.c_str()` (utile si on a besoin d'appeler des fonctions C comme `strcmp`)
- `char*` → `string` : directement au constructeur

Dans le TP2 on travaille principalement en `char*`, mais on peut utiliser `string` comme alternative plus simple pour certaines opérations.
