/* 
Fichier: main.cpp
Auteure: Charlie Bouchard
Cours: IFT1166 - Programmation orientee objet en C++
Trimestre: Hiver 2026
But: Point d'entree - lecture des arguments et execution des commandes
Notes:
	- L'option -aide a priorite sur toutes les autres
	- L'option -i est obligatoire pour toute operation sur l'inventaire
Derniere mise a jour: 2026-04-26
*/
#include "articles/article.h"
#include "inventaire/inventaire.h"
#include <cstring>
#include <cstdlib>
#include <cerrno>
#include <clocale>

static bool parserDouble(const char* texte, double& resultat) 
{
    if (!texte || texte[0] == '\0') 
	{
        return false;
    }
    char* fin = nullptr;
    errno = 0;
    const double valeur = std::strtod(texte, &fin);
    if (errno != 0 || fin == texte || *fin != '\0') 
	{
        return false;
    }
    resultat = valeur;
    return true;
}

static bool parserEntier(const char* texte, int& resultat) 
{
    if (!texte || texte[0] == '\0') 
	{
        return false;
    }
    char* fin = nullptr;
    errno = 0;
    const long valeur = std::strtol(texte, &fin, 10);
    if (errno != 0 || fin == texte || *fin != '\0') 
	{
        return false;
    }
    if (valeur < -2147483648L || valeur > 2147483647L) 
	{
        return false;
    }
    resultat = static_cast<int>(valeur);
    return true;
}

static void afficherAide() 
{
    std::println("Usage: gestion-inventaire.exe [options]");
    std::println("-i <fichier> Importer texte");
    std::println("-o <fichier> Exporter texte");
    std::println("-ajout <code> <nom> <prix> <qte> <type> <extra>");
    std::println("-ret <code>");
    std::println("-maj <code> <prix> <qte>");
    std::println("-cherche <code>");
    std::println("-tri <champ> [asc|desc] champ: code|nom|prix|qte");
    std::println("-stat");
    std::println("-aide");
}

int main(int argc, char* argv[]) 
{
    // Forcer la locale C pour garantir que le point est utilise comme separateur decimal
    std::setlocale(LC_ALL, "C");
    
    if (argc < 2) 
	{
        afficherAide();
        return 0;
    }

    // Options de la ligne de commande
    const char* fichierEntree = nullptr;
    const char* fichierSortie = nullptr;
    bool faireAide = false;
    bool faireStat = false;

    // Ajout d'article
    bool faireAjout = false;
    const char* ajoutCode = nullptr;
    const char* ajoutNom = nullptr;
    double ajoutPrix = 0.0;
    int ajoutQte = 0;
    const char* ajoutType = nullptr;
    const char* ajoutExtra = nullptr;

    // Retrait
    bool faireRet = false;
    const char* retCode = nullptr;

    // Mise a jour
    bool faireMaj = false;
    const char* majCode = nullptr;
    double majPrix = 0.0;
    int majQte = 0;

    // Recherche
    bool faireCherche = false;
    const char* chercheCode = nullptr;

    // Tri
    bool faireTri = false;
    const char* triChamp = nullptr;
    bool triAsc = true;

    /*
    Verifier que Aide est present
    */
    for (int i = 1; i < argc; i++) 
	{
        if (std::strcmp(argv[i], "-aide") == 0) 
		{
            faireAide = true;
        }
    }

    /*
	Prioriser -aide
	*/
    if (faireAide) 
	{
        afficherAide();
        return 0;
    }

    /*
    Lecture des options
    */
    int i = 1;
    while (i < argc) 
	{
        if (std::strcmp(argv[i], "-i") == 0) 
		{
            if (i + 1 >= argc) 
			{
                std::println("Option inconnue ou arguments manquants: -i");
                afficherAide();
                return 1;
            }
            fichierEntree = argv[i + 1];
            i += 2;
        }
        else if (std::strcmp(argv[i], "-o") == 0) 
		{
            if (i + 1 >= argc) 
			{
                std::println("Option inconnue ou arguments manquants: -o");
                afficherAide();
                return 1;
            }
            fichierSortie = argv[i + 1];
            i += 2;
        }
        else if (std::strcmp(argv[i], "-ajout") == 0) 
		{
            if (i + 6 >= argc) 
			{
                std::println("Arguments manquants: -ajout <code> <nom> <prix> <qte> <type> <extra>");
                return 1;
            }

            double prixTmp = 0.0;
            int qteTmp = 0;
            if (!parserDouble(argv[i + 3], prixTmp) || !parserEntier(argv[i + 4], qteTmp)) 
			{
                std::println("Arguments invalides: -ajout <code> <nom> <prix> <qte> <type> <extra>");
                return 1;
            }

            faireAjout = true;
            ajoutCode = argv[i + 1];
            ajoutNom = argv[i + 2];
            ajoutPrix = prixTmp;
            ajoutQte = qteTmp;
            ajoutType = argv[i + 5];
            ajoutExtra = argv[i + 6];
            i += 7;
        }
        else if (std::strcmp(argv[i], "-ret") == 0) 
		{
            if (i + 1 >= argc) 
			{
                std::println("Arguments manquants: -ret <code>");
                return 1;
            }
            faireRet = true;
            retCode = argv[i + 1];
            i += 2;
        }
        else if (std::strcmp(argv[i], "-maj") == 0) 
		{
            if (i + 3 >= argc) 
			{
                std::println("Option inconnue ou arguments manquants: -maj");
                afficherAide();
                return 1;
            }

            double prixTmp = 0.0;
            int qteTmp = 0;
            if (!parserDouble(argv[i + 2], prixTmp) || !parserEntier(argv[i + 3], qteTmp)) 
			{
                std::println("Arguments invalides: -maj <code> <prix> <qte>");
                return 1;
            }
            faireMaj = true;
            majCode = argv[i + 1];
            majPrix = prixTmp;
            majQte = qteTmp;
            i += 4;
        }
        else if (std::strcmp(argv[i], "-cherche") == 0) 
		{
            if (i + 1 >= argc) 
			{
                std::println("Option inconnue ou arguments manquants: -cherche");
                afficherAide();
                return 1;
            }
            faireCherche = true;
            chercheCode = argv[i + 1];
            i += 2;
        }
        else if (std::strcmp(argv[i], "-tri") == 0) 
		{
            if (i + 1 >= argc) 
			{
                std::println("Arguments manquants: -tri <champ> [asc|desc]");
                return 1;
            }
            faireTri = true;
            triChamp = argv[i + 1];

            if (i + 2 < argc &&
                (std::strcmp(argv[i + 2], "asc") == 0 || std::strcmp(argv[i + 2], "desc") == 0)) 
				{
                triAsc = (std::strcmp(argv[i + 2], "asc") == 0);
                i += 3;
            } 
			else 
			{
                triAsc = true;
                i += 2;
            }
        }
        else if (std::strcmp(argv[i], "-stat") == 0) {
            faireStat = true;
            i += 1;
        }
        else {
            std::println("Option inconnue ou arguments manquants: {}", argv[i]);
            afficherAide();
            return 1;
        }
    }

    /* 
	Obliger -i pour les autres options
	*/
    if (!fichierEntree && (fichierSortie || faireAjout || faireRet || faireMaj || faireCherche || faireTri || faireStat)) 
	{
        std::println("Erreur: l'option -i est obligatoire.");
        afficherAide();
        return 1;
    }

    /*
    Ne rien retourner si aucun fichier
    */
    if (!fichierEntree) 
	{
        afficherAide();
        return 0;
    }

    // --- Traitement ---

    Inventaire inv;
    initInventaire(inv);

    /* 
	Importation du fichier
	*/
    if (!importerInventaire(inv, fichierEntree)) 
	{
        libererInventaire(inv);
        return 1;
    }

    /* 
	Ajout d'article
	*/
    if (faireAjout) 
	{
        Article* a = creerArticleDepuisChamps(
            ajoutCode, ajoutNom, ajoutPrix, ajoutQte, ajoutType, ajoutExtra);
        if (!a) 
		{
            std::println("Erreur: type ou extra invalide.");
        } 
		else 
		{
            if (!ajouterArticle(inv, *a)) 
			{
                std::println("Erreur: code deja existant.");
            }
            delete a;
        }
    }

    /* 
	Retrait d'article
	*/
    if (faireRet) 
	{
        if (!retirerArticle(inv, retCode)) 
		{
            std::println("Introuvable.");
        }
    }

    /*
	Mise a jour d'article
	*/
    if (faireMaj) 
	{
        if (!mettreAJour(inv, majCode, majPrix, majQte)) 
		{
            std::println("Introuvable.");
        }
    }

    /*
	Trier l'inventaire
	*/
    if (faireTri) 
	{
        ChampTri champ = TRI_CODE;
        if      (std::strcmp(triChamp, "code") == 0) champ = TRI_CODE;
        else if (std::strcmp(triChamp, "nom")  == 0) champ = TRI_NOM;
        else if (std::strcmp(triChamp, "prix") == 0) champ = TRI_PRIX;
        else if (std::strcmp(triChamp, "qte")  == 0) champ = TRI_QTE;
        else 
		{
            std::println("Champ tri invalide: {}", triChamp);
            libererInventaire(inv);
            return 1;
        }
        trierInventaire(inv, champ, triAsc);
    }

    /*
	Recherche d'article
	*/
    if (faireCherche) 
	{
        int index = chercherArticle(inv, chercheCode);
        if (index >= 0) 
		{
            inv.data[index]->afficher();
        } 
		else 
		{
            std::println("Introuvable.");
        }
    }

    /* 
	Affichage des statistiques
	*/
    if (faireStat) 
	{
        afficherStatistiques(inv);
    }

    /* 
	Exportation/affichage
    */
    if (fichierSortie) 
	{
        exporterInventaire(inv, fichierSortie);
    } 
	else if (!faireCherche && !faireStat && !faireMaj) 
	{
        afficherInventaire(inv);
    }

    libererInventaire(inv);
    return 0;
}
