/* 
Fichier: article.cpp
Auteure: Charlie Bouchard
Cours: IFT1166 - Programmation orientee objet en C++
Trimestre: Hiver 2026
But: Implementation de la hierarchie de Article (TP3)
Notes:
    - afficher() delegue afficherExtra() au type derive
    - parserLigneArticle sur 6 champs (code;nom;prix;qte;type;extra)
Derniere mise a jour : 2026-04-26
*/

#include "article.h"
#include <cstring>
#include <cstdlib>
#include <cstdio> // snprintf
// std::print / std::println provient de article.h (via <print> ou fallback)

// Utilitaires internes

/*
Centralise la gestion new[]/delete[] du champ nom pour tous les constructeurs.
*/
static void copierTexte(char*& dest, const char* src) 
{
    delete[] dest;
    if (!src) 
	{
        src = "";
    }
    size_t n = std::strlen(src);
    dest = new char[n + 1];
    std::strcpy(dest, src);
}

/* 
Avance dans source jusqu'au prochain ';' ou fin de ligne.
*/

static const char* extraireChamp(const char* source, char* dest, size_t tailleMax) 
{
    size_t i = 0;
    while (*source != '\0' && *source != ';' && *source != '\n' && *source != '\r') 
	{
        if (i < tailleMax - 1) dest[i++] = *source;
        source++;
    }
    dest[i] = '\0';
    if (*source == ';') return source + 1;
    return (*source == '\0' || *source == '\n' || *source == '\r') ? nullptr : source;
}


// Article

Article::Article() : nom(nullptr), prix(0.0), quantite(0) 
{
    code[0] = '\0';
}

Article::Article(const char* code_, const char* nom_, double prix_, int qte_)
    : nom(nullptr), prix(prix_), quantite(qte_) 
{
    std::strncpy(code, code_, 15);
    code[15] = '\0'; // garantit la terminaison meme si code_ est plus long
    copierTexte(nom, nom_);
}

Article::Article(const Article& autre) : nom(nullptr), prix(autre.prix), quantite(autre.quantite) 
{
    std::strncpy(code, autre.code, 16);
    copierTexte(nom, autre.nom ? autre.nom : "");
}

Article::~Article() // Le destructeur est virtuel : delete sur un Article* en appelant le destructeur de la classe derivee.
{
    delete[] nom;
}

Article& Article::operator=(const Article& autre) 
{
    if (this != &autre) 
	{
        std::strncpy(code, autre.code, 16);
        prix = autre.prix;
        quantite = autre.quantite;
        copierTexte(nom, autre.nom ? autre.nom : "");
    }
    return *this;
}

const char* Article::getCode() const { return code; }
const char* Article::getNom() const { return nom ? nom : ""; }
double Article::getPrix() const { return prix; }
int Article::getQuantite() const { return quantite; }
void Article::setPrix(double p) { prix = p; }
void Article::setQuantite(int q) { quantite = q; }

/* 
Les champs communs sont affiches ici ; afficherExtra() est delegue au type derive pour eviter un if/else centralise.
*/
void Article::afficher() const 
{
    char prixTexte[32];
    std::snprintf(prixTexte, sizeof(prixTexte), "%.2f", getPrix());
    std::print("{} | {} | {} $ | qte={} | type={} | ", getCode(), getNom(), 
		prixTexte, getQuantite(), getTypeTexte());
    afficherExtra();
    std::println();
}

// Consommable

Consommable::Consommable() : Article() 
{
    dateExpiration[0] = '\0';
}

Consommable::Consommable(const char* code_, const char* nom_, double prix_, 
	int qte_, const char* date_) : Article(code_, nom_, prix_, qte_) 
{
    std::strncpy(dateExpiration, date_, 15);
    dateExpiration[15] = '\0';
}

TypeArticle Consommable::getType() const { return TYPE_CONSOMMABLE; }
const char* Consommable::getTypeTexte() const { return "consommable"; }
void Consommable::afficherExtra() const { std::print("exp={}", dateExpiration); }
Article* Consommable::clone() const { return new Consommable(*this); }

bool Consommable::parseExtra(const char* extra) 
{
    if (!extra || extra[0] == '\0' || std::strlen(extra) > 10) return false;
    std::strncpy(dateExpiration, extra, 15);
    dateExpiration[15] = '\0';
    return true;
}

void Consommable::exporterExtra(char* buffer, size_t n) const 
{
    std::strncpy(buffer, dateExpiration, n - 1);
    buffer[n - 1] = '\0';
}

// Equipement

Equipement::Equipement() : Article(), garantieMois(0) {}

Equipement::Equipement(const char* code_, const char* nom_, double prix_, int qte_, 
	int garantie_) : Article(code_, nom_, prix_, qte_), garantieMois(garantie_) {}

TypeArticle Equipement::getType() const { return TYPE_EQUIPEMENT; }
const char* Equipement::getTypeTexte() const { return "equipement"; }
void Equipement::afficherExtra() const { std::print("garantie={} mois", garantieMois); }
Article* Equipement::clone() const { return new Equipement(*this); }

bool Equipement::parseExtra(const char* extra) {
    if (!extra || extra[0] == '\0') return false;
    int val = std::atoi(extra);
    if (val <= 0) return false; // 0 ou negative n'est pas valide
    garantieMois = val;
    return true;
}

void Equipement::exporterExtra(char* buffer, size_t n) const 
{
    std::snprintf(buffer, n, "%d", garantieMois);
}

// Medicament

Medicament::Medicament() : Article() 
{
    dosage[0] = '\0';
}

Medicament::Medicament(const char* code_, const char* nom_,
                        double prix_, int qte_, const char* dosage_)
    : Article(code_, nom_, prix_, qte_) 
{
    std::strncpy(dosage, dosage_, 31);
    dosage[31] = '\0';
}

TypeArticle Medicament::getType() const { return TYPE_MEDICAMENT; }
const char* Medicament::getTypeTexte() const { return "medicament"; }
void Medicament::afficherExtra() const { std::print("dosage={}", dosage); }
Article* Medicament::clone() const { return new Medicament(*this); }

bool Medicament::parseExtra(const char* extra) 
{
    if (!extra || extra[0] == '\0') return false;
    std::strncpy(dosage, extra, 31);
    dosage[31] = '\0';
    return true;
}

void Medicament::exporterExtra(char* buffer, size_t n) const 
{
    std::strncpy(buffer, dosage, n - 1);
    buffer[n - 1] = '\0';
}

// Factory et parsing

/* 
Instancie le bon type derive, valide extra, retourne null si echec.
*/

Article* creerArticleDepuisChamps(
    const char* code, const char* nom, double prix, int qte,
    const char* typeTexte, const char* extra) 
{

    Article* a = nullptr;

    if (std::strcmp(typeTexte, "consommable") == 0) 
	{
        Consommable* c = new Consommable(code, nom, prix, qte, "");
        if (!c->parseExtra(extra)) { delete c; return nullptr; }
        a = c;
    } 
	else if (std::strcmp(typeTexte, "equipement") == 0) 
	{
        Equipement* e = new Equipement(code, nom, prix, qte, 0);
        if (!e->parseExtra(extra)) { delete e; return nullptr; }
        a = e;
    } 
	else if (std::strcmp(typeTexte, "medicament") == 0) 
	{
        Medicament* m = new Medicament(code, nom, prix, qte, "");
        if (!m->parseExtra(extra)) { delete m; return nullptr; }
        a = m;
    }
    // null si invalide
    return a;
}

/* 
Parse une ligne CSV a 6 champs : code;nom;prix;qte;type;extra
*/
bool parserLigneArticleV2(const char* ligne, Article*& resultat) 
{
    char champCode[16];
    char champNom[256];
    char champPrix[32];
    char champQte[32];
    char champType[32];
    char champExtra[64];

    const char* pos = extraireChamp(ligne,  champCode,  sizeof(champCode));
    if (!pos) return false;
    pos = extraireChamp(pos, champNom,  sizeof(champNom));
    if (!pos) return false;
    pos = extraireChamp(pos, champPrix, sizeof(champPrix));
    if (!pos) return false;
    pos = extraireChamp(pos, champQte,  sizeof(champQte));
    if (!pos) return false;
    pos = extraireChamp(pos, champType, sizeof(champType));
    if (!pos) return false;

    /* 
	Lecture du dernier champ jusqu'a la fin de ligne (pas de ";")
    */
    size_t j = 0;
    while (pos[j] != '\0' && pos[j] != '\n' && pos[j] != '\r' &&
           j < sizeof(champExtra) - 1) 
	{
        champExtra[j] = pos[j];
        j++;
    }
    champExtra[j] = '\0';

    if (champCode[0] == '\0' || champNom[0] == '\0' || champType[0] == '\0')
        return false;

    resultat = creerArticleDepuisChamps(
        champCode, champNom,
        std::atof(champPrix), std::atoi(champQte),
        champType, champExtra);
    return resultat != nullptr;
}

/*
Ecrit l'article au format CSV avec 6 champs.
*/

int formaterArticleV2(const Article& article, char* buffer, size_t tailleBuffer) 
{
    char extra[64] = {};
    article.exporterExtra(extra, sizeof(extra));
    return std::snprintf(buffer, tailleBuffer, "%s;%s;%.2f;%d;%s;%s", 
	article.getCode(), article.getNom(), article.getPrix(), article.getQuantite(),
    article.getTypeTexte(), extra);
}
