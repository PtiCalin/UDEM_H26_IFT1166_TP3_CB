/* 
Fichier: inventaire.cpp
Auteure: Charlie Bouchard
Cours: IFT1166 - Programmation orientee objet en C++
Trimestre: Hiver 2026
But: Fonctions pour gerer l'inventaire (ajout, recherche, import/export, stats)
Notes:
	- Le tableau est redimensionne (x2) quand il est plein
	- L'import saute la premiere ligne (en-tete du CSV)
Derniere mise a jour : 2026-04-25
*/

#include "inventaire.h"
#include <cstring>
#include <fstream>
#include <limits>
#include <cstdio>

static int comparerArticles(const Article& a, const Article& b, ChampTri champ, bool ascendant) 
{
    int cmp = 0;
    if (champ == TRI_CODE) 
	{
        cmp = std::strcmp(a.getCode(), b.getCode());
    } 
	else if (champ == TRI_NOM) 
	{
        cmp = std::strcmp(a.getNom(), b.getNom());
    } 
	else if (champ == TRI_PRIX)
	{
        if (a.getPrix() < b.getPrix()) cmp = -1;
        else if (a.getPrix() > b.getPrix()) cmp = 1;
        else cmp = 0;
    } 
	else 
	{
        if (a.getQuantite() < b.getQuantite()) cmp = -1;
        else if (a.getQuantite() > b.getQuantite()) cmp = 1;
        else cmp = 0;
    }
    return ascendant ? cmp : -cmp;
}

static void ecrireDeuxDecimales(double valeur, char* buffer, size_t tailleBuffer) 
{
    std::snprintf(buffer, tailleBuffer, "%.2f", valeur);
}

void initInventaire(Inventaire& inv, size_t capaciteInitiale) 
{
    if (capaciteInitiale == 0) 
	{
        capaciteInitiale = 1;
    }
    inv.cap = capaciteInitiale;
    inv.size = 0;
    inv.data = new Article*[inv.cap];
    for (size_t i = 0; i < inv.cap; ++i) 
	{
        inv.data[i] = nullptr;
    }
}

void libererInventaire(Inventaire& inv) 
{
    if (!inv.data) 
	{
        inv.size = 0;
        inv.cap = 0;
        return;
    }
    for (size_t i = 0; i < inv.size; ++i) 
	{
        delete inv.data[i];
        inv.data[i] = nullptr;
    }
    delete[] inv.data;
    inv.data = nullptr;
    inv.size = 0;
    inv.cap = 0;
}

void agrandirInventaire(Inventaire& inv) 
{
    const size_t nouvelleCapacite = (inv.cap == 0) ? 1 : (inv.cap * 2);
    Article** nouveauTableau = new Article*[nouvelleCapacite];
    for (size_t i = 0; i < nouvelleCapacite; ++i) 
	{
        nouveauTableau[i] = nullptr;
    }
    for (size_t i = 0; i < inv.size; ++i) 
	{
        nouveauTableau[i] = inv.data[i];
    }
    delete[] inv.data;
    inv.data = nouveauTableau;
    inv.cap = nouvelleCapacite;
}

bool ajouterArticle(Inventaire& inv, const Article& article) 
{
    if (chercherArticle(inv, article.getCode()) >= 0) 
	{
        return false;
    }
    if (inv.size >= inv.cap) 
	{
        agrandirInventaire(inv);
    }
    Article* copie = article.clone();
    if (!copie) 
	{
        return false;
    }
    inv.data[inv.size] = copie;
    inv.size++;
    return true;
}

int chercherArticle(const Inventaire& inv, const char* code) 
{
    for (size_t i = 0; i < inv.size; ++i) 
	{
        if (inv.data[i] && std::strcmp(inv.data[i]->getCode(), code) == 0) 
		{
            return static_cast<int>(i);
        }
    }
    return -1;
}

bool mettreAJour(Inventaire& inv, const char* code, double prix, int quantite) 
{
    const int index = chercherArticle(inv, code);
    if (index < 0) 
	{
        return false;
    }
    inv.data[index]->setPrix(prix);
    inv.data[index]->setQuantite(quantite);
    return true;
}

bool retirerArticle(Inventaire& inv, const char* code) 
{
    const int index = chercherArticle(inv, code);
    if (index < 0) 
	{
        return false;
    }
    delete inv.data[index];
    for (size_t i = static_cast<size_t>(index); i + 1 < inv.size; ++i) 
	{
        inv.data[i] = inv.data[i + 1];
    }
    inv.size--;
    inv.data[inv.size] = nullptr;
    return true;
}

void trierInventaire(Inventaire& inv, ChampTri champ, bool ascendant) 
{
    if (inv.size < 2) 
	{
        return;
    }
    for (size_t i = 0; i + 1 < inv.size; ++i) 
	{
        if (!inv.data[i]) 
		{
            continue;
        }
        size_t meilleur = i;
        for (size_t j = i + 1; j < inv.size; ++j) 
		{
            if (!inv.data[j] || !inv.data[meilleur]) 
			{
                continue;
            }
            if (comparerArticles(*inv.data[j], *inv.data[meilleur], champ, ascendant) < 0) 
			{
                meilleur = j;
            }
        }
        if (meilleur != i) 
		{
            Article* tmp = inv.data[i];
            inv.data[i] = inv.data[meilleur];
            inv.data[meilleur] = tmp;
        }
    }
}

bool importerInventaire(Inventaire& inv, const char* nomFichier) 
{
    std::ifstream fichier(nomFichier);
    if (!fichier.is_open()) 
	{
        std::println("Erreur: impossible d'ouvrir le fichier {}", nomFichier);
        return false;
    }
    char ligne[512];
    if (!fichier.getline(ligne, sizeof(ligne))) 
	{
        return true;
    }
    while (fichier.getline(ligne, sizeof(ligne))) 
	{
        if (ligne[0] == '\0' || ligne[0] == '\n' || ligne[0] == '\r') 
		{
            continue;
        }
        Article* article = nullptr;
        if (!parserLigneArticleV2(ligne, article) || !article) 
		{
            continue;
        }
        const bool ok = ajouterArticle(inv, *article);
        delete article;
        if (!ok) 
		{
            continue;
        }
    }
    return true;
}

bool exporterInventaire(const Inventaire& inv, const char* nomFichier) 
{
    std::ofstream fichier(nomFichier);
    if (!fichier.is_open()) 
	{
        std::println("Erreur: impossible d'ecrire dans le fichier {}", nomFichier);
        return false;
    }
    fichier << "code;nom;prix;quantite;type;extra\n";
    char buffer[512];
    for (size_t i = 0; i < inv.size; ++i) 
	{
        if (!inv.data[i]) {
            continue;
        }
        formaterArticleV2(*inv.data[i], buffer, sizeof(buffer));
        fichier << buffer << "\n";
    }

    return true;
}

void afficherInventaire(const Inventaire& inv) 
{
    for (size_t i = 0; i < inv.size; ++i) 
	{
        if (!inv.data[i]) 
		{
            continue;
        }
        inv.data[i]->afficher();
    }
}

void afficherStatistiques(const Inventaire& inv) 
{
    if (inv.size == 0) 
	{
        std::println("Articles: 0");
        std::println("Qte totale: 0");
        std::println("Valeur totale: 0.00");
        std::println("Prix min: 0.00");
        std::println("Prix max: 0.00");
        return;
    }
    int qteTotale = 0;
    double valeurTotale = 0.0;
    double prixMin = std::numeric_limits<double>::max();
    double prixMax = std::numeric_limits<double>::lowest();
    int nbType[3] = {0, 0, 0};
    int qteType[3] = {0, 0, 0};
    double valeurType[3] = {0.0, 0.0, 0.0};
    double minType[3] = 
	{
        std::numeric_limits<double>::max(),
        std::numeric_limits<double>::max(),
        std::numeric_limits<double>::max()
    };
    double maxType[3] = 
	{
        std::numeric_limits<double>::lowest(),
        std::numeric_limits<double>::lowest(),
        std::numeric_limits<double>::lowest()
    };
    for (size_t i = 0; i < inv.size; ++i) 
	{
        if (!inv.data[i]) 
		{
            continue;
        }
        const Article& a = *inv.data[i];
        const double prix = a.getPrix();
        const int qte = a.getQuantite();
        
		qteTotale += qte;
        valeurTotale += (prix * qte);
        
		if (prix < prixMin) prixMin = prix;
        if (prix > prixMax) prixMax = prix;
        
		const TypeArticle type = a.getType();
        if (type >= TYPE_CONSOMMABLE && type <= TYPE_MEDICAMENT) 
		{
            const int t = static_cast<int>(type);
            nbType[t] += 1;
            qteType[t] += qte;
            valeurType[t] += (prix * qte);
            if (prix < minType[t]) minType[t] = prix;
            if (prix > maxType[t]) maxType[t] = prix;
        }
    }

    char texteValeurTotale[32];
    char textePrixMin[32];
    char textePrixMax[32];
    ecrireDeuxDecimales(valeurTotale, texteValeurTotale, sizeof(texteValeurTotale));
    ecrireDeuxDecimales(prixMin, textePrixMin, sizeof(textePrixMin));
    ecrireDeuxDecimales(prixMax, textePrixMax, sizeof(textePrixMax));

    std::println("Articles: {}", inv.size);
    std::println("Qte totale: {}", qteTotale);
    std::println("Valeur totale: {}", texteValeurTotale);
    std::println("Prix min: {}", textePrixMin);
    std::println("Prix max: {}", textePrixMax);

    const char* noms[3] = {"consommable", "equipement", "medicament"};
    for (int t = 0; t < 3; ++t) 
	{
        char texteValeur[32];
        char texteMin[32];
        char texteMax[32];

        if (nbType[t] == 0) 
		{
            std::println("Type {} -> nb=0, qte=0, valeur=0.00, min=0.00, max=0.00", noms[t]);
            continue;
        }

        ecrireDeuxDecimales(valeurType[t], texteValeur, sizeof(texteValeur));
        ecrireDeuxDecimales(minType[t], texteMin, sizeof(texteMin));
        ecrireDeuxDecimales(maxType[t], texteMax, sizeof(texteMax));
        std::println("Type {} -> nb={}, qte={}, valeur={}, min={}, max={}", noms[t], nbType[t], 
			qteType[t], texteValeur, texteMin, texteMax);
    }
}
