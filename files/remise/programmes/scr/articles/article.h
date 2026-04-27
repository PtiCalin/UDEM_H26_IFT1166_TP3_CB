/* 
Fichier: article.h
Auteure: Charlie Bouchard
Cours: IFT1166 - Programmation orientee objet en C++
Trimestre: Hiver 2026
But: Declaration de la hierarchie de classes Article (TP3)
Notes:
    - Article est une classe de base abstraite (6 methodes virtuelles pures)
    - Consommable, Equipement et Medicament en derivent
    - Le champ nom est alloue dynamiquement (new/delete)
    - Le champ extra est type-dependant : date / garantie / dosage
Derniere mise a jour : 2026-04-26
*/

#ifndef ARTICLE_H
#define ARTICLE_H

#include <cstddef>
#include <cstdio>
#include <sstream>
#include <string>
#include <utility>

#if defined(__cpp_lib_print) && (__cpp_lib_print >= 202207L)
#include <print>
#define TP3_HAS_STD_PRINT 1
#endif

#ifndef TP3_HAS_STD_PRINT
namespace tp3_print_detail 
{
    inline void ecrireFormat(const char* format) 
	{
        std::fputs(format, stdout);
    }

    template <typename T>
    std::string versTexte(const T& valeur) 
	{
        std::ostringstream os;
        os << valeur;
        return os.str();
    }

    template <typename T, typename... Rest>
    void ecrireFormat(const char* format, T&& valeur, Rest&&... suite) 
	{
        const char* p = format;
        while (*p != '\0') 
		{
            if (p[0] == '{' && p[1] == '}') 
			{
                const std::string texte = versTexte(std::forward<T>(valeur));
                std::fputs(texte.c_str(), stdout);
                ecrireFormat(p + 2, std::forward<Rest>(suite)...);
                return;
            }
            std::fputc(*p, stdout);
            ++p;
        }
    }
}

namespace std 
{
    template <typename... Args>
    inline void print(const char* format, Args&&... args) 
	{
        tp3_print_detail::ecrireFormat(format, std::forward<Args>(args)...);
    }

    template <typename... Args>
    inline void println(const char* format, Args&&... args) 
	{
        tp3_print_detail::ecrireFormat(format, std::forward<Args>(args)...);
        std::fputc('\n', stdout);
    }

    inline void println() 
	{
        std::fputc('\n', stdout);
    }
}
#endif

// Identifie le type concret d'un article sans recourir a dynamic_cast.
enum TypeArticle 
{
    TYPE_CONSOMMABLE,
    TYPE_EQUIPEMENT,
    TYPE_MEDICAMENT,
    TYPE_INVALIDE // valeur pour les types non reconnus dans le CSV
};

// Article

/*
Classe de base abstraite contenant les champs communs (code, nom, prix, quantite) 
et l'interface polymorphique que chaque type derive doit implementer.
*/
class Article 
{
protected:
    char code[16]; // code unique, max 15 car. + '\0'
    char* nom; // alloue dynamiquement (new[]/delete[])
    double prix;
    int quantite;

public:
    Article();
    Article(const char* code_, const char* nom_, double prix_, int qte_);
    Article(const Article& autre); // copie profonde du nom
    virtual ~Article(); // destructeur virtuel pour delete Article*
    Article& operator=(const Article& autre);

    // Accesseurs
    const char* getCode() const;
    const char* getNom() const;
    double getPrix() const;
    int getQuantite() const;
    void setPrix(double p);
    void setQuantite(int q);

    // Polymorphie de la classe Article
    virtual TypeArticle getType() const = 0;
    virtual const char* getTypeTexte() const = 0;
    virtual void afficherExtra() const = 0; // affichage du champ extra
    virtual bool parseExtra(const char* extra) = 0; // validation et stockage du champ extra
    virtual void exporterExtra(char* buffer, size_t n) const = 0; // exportation du champ extra en CSV
    virtual Article* clone() const = 0;

    // Affiche une ligne complete ; delegue afficherExtra() au type derive.
    void afficher() const;
};

// Consommable

/*
Champ specifique a la classe derivee = date d'expiration au format AAAA-MM-JJ
*/
class Consommable : public Article 
{
private:
    char dateExpiration[16]; // Date d'expiration au format AAAA-MM-JJ
public:
    Consommable();
    Consommable(const char* code_, const char* nom_, double prix_, int qte_,
        const char* date_);
    TypeArticle getType() const override;
    const char* getTypeTexte() const override;
    void afficherExtra() const override;
    bool parseExtra(const char* extra) override; // refuse date invalide
    void exporterExtra(char* buffer, size_t n) const override;
    Article* clone() const override;
};

// Equipement

/*
Champ specifique a la classe derivee = garantie en mois (entier strictement positif)
*/
class Equipement : public Article {
private:
    int garantieMois;
public:
    Equipement();
    Equipement(const char* code_, const char* nom_, double prix_, int qte_, int garantie_);
    TypeArticle getType() const override;
    const char* getTypeTexte() const override;
    void afficherExtra() const override;
    bool parseExtra(const char* extra) override; // refuse les valeurs <= 0
    void exporterExtra(char* buffer, size_t n) const override;
    Article* clone() const override;
};

// Medicament

/*
Champ specifique a la classe derivee = dosage (texte non vide, ex. "500mg")
*/
class Medicament : public Article {
private:
    char dosage[32];
public:
    Medicament();
    Medicament(const char* code_, const char* nom_, double prix_, int qte_, const char* dosage_);
    TypeArticle getType() const override;
    const char* getTypeTexte() const override;
    void afficherExtra() const override;
    bool parseExtra(const char* extra) override; // Oblige une valeur pour la dose
    void exporterExtra(char* buffer, size_t n) const override;
    Article* clone() const override;
};

// Factory

/*
Cree l'instance selon la classe derivee
Retourne null si le type est invalide.
*/
Article* creerArticleDepuisChamps(
    const char* code, const char* nom, double prix, int qte,
    const char* typeTexte, const char* extra);

/* 
Parse une ligne CSV TP3 a 6 champs (code;nom;prix;qte;type;extra).
Alloue l'article via creerArticleDepuisChamps.
*/
bool parserLigneArticleV2(const char* ligne, Article*& resultat);

/* 
Ecrit un article au format CSV 6 champs dans buffer.
*/
int formaterArticleV2(const Article& article, char* buffer, size_t tailleBuffer);

#endif
