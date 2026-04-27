/* 
Fichier: inventaire.h
Auteure: Charlie Bouchard
Cours: IFT1166 - Programmation orientee objet en C++
Trimestre: Hiver 2026
But: Declaration de la structure Inventaire et de ses fonctions
Notes:
	- Le tableau d'articles est redimensionnable dynamiquement
	- Import/export en format CSV avec ';' comme separateur
Derniere mise a jour: 2026-03-25
*/

#ifndef INVENTAIRE_H
#define INVENTAIRE_H
#include "../articles/article.h"
#include <cstddef>

struct Inventaire 
{
	Article** data; // tableau de pointeurs
	size_t size; // nombre d'articles actuellement stock
	size_t cap; // capacite du tableau
};

enum ChampTri 
{
	TRI_CODE,
	TRI_NOM,
	TRI_PRIX,
	TRI_QTE
};

void initInventaire (Inventaire& inv, size_t capaciteInitiale = 16);
void libererInventaire (Inventaire& inv);
void agrandirInventaire(Inventaire& inv);  // double la capacite de l'inventaire

bool ajouterArticle (Inventaire& inv, const Article& article); // copie et insert un nouvel article
int chercherArticle(const Inventaire& inv, const char* code); 
bool retirerArticle (Inventaire& inv, const char* code); // suppression et decalage de ligne
bool mettreAJour (Inventaire& inv, const char* code, double prix, int quantite);

bool importerInventaire (Inventaire& inv, const char* nomFichier);
bool exporterInventaire (const Inventaire& inv, const char* nomFichier);

void afficherInventaire  (const Inventaire& inv);
void afficherStatistiques(const Inventaire& inv); // global et detail par type

// Tri demande
void trierInventaire(Inventaire& inv, ChampTri champ, bool ascendant);

#endif
