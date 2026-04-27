# Rapport de conception du TP3

Travail présenté par :
Charlie Bouchard (20077301)

Dans le cadre du cours :
IFT1166 - Programmation orientée objet en C++

Offert à l'Université de Montréal
À la session d'hiver 2026

---

## 1. Introduction

Ce travail pratique reprend le programme de gestion d'inventaire développé dans le TP2 et le transforme
en une application orientée objet en C++23. L'objectif principal est d'introduire une hiérarchie de classes
pour représenter les articles de l'inventaire, de permettre leur manipulation polymorphique, et d'ajouter
les nouvelles fonctionnalités demandées : retrait d'article (`-ret`), tri personnalisé (`-tri`) et
statistiques détaillées par type (`-stat`).

Le format du fichier d'inventaire a également évolué. Chaque ligne contient maintenant six champs :

```
code;nom;prix;quantite;type;extra
```

Où `extra` est interprété différemment selon le type :
- `consommable` → date d'expiration au format `AAAA-MM-JJ`
- `equipement`  → durée de garantie en mois (entier > 0)
- `medicament`  → dosage (texte non vide)

Les modifications s'appliquent aux cinq fichiers suivants du projet :
- `scr/articles/article.h`
- `scr/articles/article.cpp`
- `scr/inventaire/inventaire.h`
- `scr/inventaire/inventaire.cpp`
- `scr/main.cpp`

---

## 2. Hiérarchie de classes retenue

### 2.1 Choix de conception

Dans le TP2, un article était représenté par une structure `struct Article` avec quatre champs plats
(`code`, `nom`, `prix`, `quantite`). Cette représentation ne permettait pas de distinguer les types
d'articles ni de gérer le champ `extra` de façon propre.

Pour le TP3, une hiérearchie à deux niveaux a été retenue :

```txt
Article (classe de base abstraite)
├── Consommable — champ extra : dateExpiration (char[16])
├── Equipement — champ extra : garantieMois (int)
└── Medicament — champ extra : dosage (char[32])
```

**Article comme classe abstraite**
La classe `Article` déclare six méthodes virtuelles pures (`getType`, `getTypeTexte`, `afficherExtra`,
`parseExtra`, `exporterExtra`, `clone`). Cela garantit que tout objet manipulé via un pointeur
`Article*` se comportera correctement selon son type concret, sans que l'inventaire ait besoin de
connaître les détails de chaque type.

**Utilisation de `clone()`**
Le tableau d'inventaire stocke des pointeurs (`Article**`). Quand on copie un article — lors d'un ajout
ou d'un redimensionnement — il faut créer une copie polymorphique du bon type dérivé. La méthode
`clone()` retourne un `new DeriveX(*this)`, ce qui permet cette copie sans `dynamic_cast`.

**Validation virtuelle de `parseExtra()` et de `exporterExtra()`**
Le champ `extra` du fichier CSV n'a pas le même sens selon le type. Déléguer la validation et l'écriture à chaque classe dérivée évite un bloc `if/else` centalisé fragile.

### 2.2 Enum TypeArticle

```cpp
// Identifie le type concret d'un article sans recourir a dynamic_cast.
enum TypeArticle {
    TYPE_CONSOMMABLE,
    TYPE_EQUIPEMENT,
    TYPE_MEDICAMENT,
    TYPE_INVALIDE   // valeur de garde pour les types non reconnus
};
```

---

## 3. Démarche d'implémentation

### Étape 1 — Remplacement de `struct Article` par une hiérarchie POO (`article.h`)

En premier lieu, on remplace la structure plate du TP2 par une classe de base abstraite et trois
classes dérivées. La séparation `.h`/`.cpp` est conservée.

```cpp
#include <print>   // std::print / std::println (C++23)

// Identifie le type concret sans recourir a dynamic_cast.
enum TypeArticle {
    TYPE_CONSOMMABLE,
    TYPE_EQUIPEMENT,
    TYPE_MEDICAMENT,
    TYPE_INVALIDE   // garde : type non reconnu dans le fichier CSV
};

// Classe de base abstraite. Contient les champs communs a tous les types d'articles.
// Les methodes virtuelles pures obligent chaque type derive a fournir
// sa propre logique pour l'affichage, le parsing et la copie du champ extra.
class Article {
protected:
    char   code[16];  // code unique de l'article (max 15 caracteres + '\0')
    char*  nom;       // alloue dynamiquement (new/delete)
    double prix;
    int    quantite;

public:
    Article();
    Article(const char* code_, const char* nom_, double prix_, int qte_);
    Article(const Article& autre);       // constructeur de copie (copie profonde du nom)
    virtual ~Article();                  // destructeur virtuel : garantit la liberation correcte
    Article& operator=(const Article& autre);

    // Accesseurs
    const char* getCode()     const;
    const char* getNom()      const;
    double      getPrix()     const;
    int         getQuantite() const;
    void        setPrix(double p);
    void        setQuantite(int q);

    // Interface polymorphique : chaque derive implemente ces six methodes.
    virtual TypeArticle getType()                              const = 0;
    virtual const char* getTypeTexte()                        const = 0;
    virtual void        afficherExtra()                       const = 0;
    virtual bool        parseExtra(const char* extra)               = 0;
    virtual void        exporterExtra(char* buffer, size_t n) const = 0;
    virtual Article*    clone()                               const = 0; // copie polymorphique

    // Affiche une ligne complete : champs communs + extra delegue au derive.
    void afficher() const;
};

// Consommable : extra = date d'expiration au format AAAA-MM-JJ
class Consommable : public Article {
private:
    char dateExpiration[16]; // format strict : AAAA-MM-JJ
public:
    Consommable();
    Consommable(const char* code_, const char* nom_, double prix_, int qte_, const char* date_);
    TypeArticle getType()                              const override;
    const char* getTypeTexte()                        const override;
    void        afficherExtra()                       const override;
    bool        parseExtra(const char* extra)               override; // refuse une date vide
    void        exporterExtra(char* buffer, size_t n) const override;
    Article*    clone()                               const override;
};

// Equipement : extra = garantie en mois (entier > 0)
class Equipement : public Article {
private:
    int garantieMois;
public:
    Equipement();
    Equipement(const char* code_, const char* nom_, double prix_, int qte_, int garantie_);
    TypeArticle getType()                              const override;
    const char* getTypeTexte()                        const override;
    void        afficherExtra()                       const override;
    bool        parseExtra(const char* extra)               override; // refuse 0 ou negatif
    void        exporterExtra(char* buffer, size_t n) const override;
    Article*    clone()                               const override;
};

// Medicament : extra = dosage (texte non vide)
class Medicament : public Article {
private:
    char dosage[32];
public:
    Medicament();
    Medicament(const char* code_, const char* nom_, double prix_, int qte_, const char* dosage_);
    TypeArticle getType()                              const override;
    const char* getTypeTexte()                        const override;
    void        afficherExtra()                       const override;
    bool        parseExtra(const char* extra)               override; // refuse un dosage vide
    void        exporterExtra(char* buffer, size_t n) const override;
    Article*    clone()                               const override;
};

// Factory : centralise la creation polymorphique selon le champ type du CSV.
// Retourne nullptr si le type est inconnu ou si extra est invalide.
Article* creerArticleDepuisChamps(
    const char* code, const char* nom, double prix, int qte,
    const char* typeTexte, const char* extra);

// Parse une ligne CSV TP3 (6 champs) et alloue l'article cible.
bool parserLigneArticleV2(const char* ligne, Article*& resultat);

// Ecrit un article au format CSV 6 champs dans le buffer fourni.
int formaterArticleV2(const Article& article, char* buffer, size_t tailleBuffer);
```

### Étape 2 — Implémentation POO et parsing 6 champs (`article.cpp`)

Le fichier `article.cpp` contient l'implémentation de la classe de base `Article` (constructeurs,
opérateur d'affectation, destructeur, accesseurs et méthode `afficher`) ainsi que les implémentations
concrètes des trois types dérivés.

**Différences clés par rapport au TP2 :**
- Le nom est toujours alloué dynamiquement, mais la gestion est centralisée dans la fonction interne
  `copierTexte`.
- La méthode `afficher` délègue la partie `extra` à la méthode virtuelle `afficherExtra()`, ce qui
  permet un affichage uniforme sans `if/else` sur le type.
- `parserLigneArticleV2` extrait **six** champs au lieu de quatre.

```cpp
#include "article.h"
#include <cstring>
#include <cstdlib>
#include <print>    // std::print / std::println (C++23)

// Utilitaire interne : realloue dest et copie src.
// Centralise la gestion memoire du champ nom pour eviter les repetitions.
static void copierTexte(char*& dest, const char* src) {
    delete[] dest;                          // libere l'ancienne allocation si elle existe
    size_t n = std::strlen(src);
    dest = new char[n + 1];
    std::strcpy(dest, src);
}

// Constructeur par defaut : article vide, sans nom alloue.
Article::Article() : nom(nullptr), prix(0.0), quantite(0) {
    code[0] = '\0';
}

// Constructeur complet : copie le code (tronque a 15 car.) et alloue le nom.
Article::Article(const char* code_, const char* nom_, double prix_, int qte_)
    : nom(nullptr), prix(prix_), quantite(qte_) {
    std::strncpy(code, code_, 15);
    code[15] = '\0';         // garantit la terminaison meme si code_ est trop long
    copierTexte(nom, nom_);
}

// Constructeur de copie : copie profonde du nom pour eviter le partage de pointeur.
Article::Article(const Article& autre)
    : nom(nullptr), prix(autre.prix), quantite(autre.quantite) {
    std::strncpy(code, autre.code, 16);
    copierTexte(nom, autre.nom ? autre.nom : "");
}

// Destructeur virtuel : libere le nom alloue.
// Le mot-cle virtual est indispensable pour que delete sur un Article* appelle
// bien le destructeur de la classe derivee.
Article::~Article() {
    delete[] nom;
}

// Operateur d'affectation : verifie l'auto-affectation, puis copie profonde.
Article& Article::operator=(const Article& autre) {
    if (this != &autre) {
        std::strncpy(code, autre.code, 16);
        prix     = autre.prix;
        quantite = autre.quantite;
        copierTexte(nom, autre.nom ? autre.nom : "");
    }
    return *this;
}

const char* Article::getCode()     const { return code; }
const char* Article::getNom()      const { return nom ? nom : ""; }
double      Article::getPrix()     const { return prix; }
int         Article::getQuantite() const { return quantite; }
void        Article::setPrix(double p)   { prix = p; }
void        Article::setQuantite(int q)  { quantite = q; }

// Affiche une ligne complete.
// Les champs communs sont affiches ici ; afficherExtra() est delegue au derive
// pour eviter un if/else sur le type.
void Article::afficher() const {
    std::print("{} | {} | {:.2f} $ | qte={} | type={} | ",
               getCode(), getNom(), getPrix(), getQuantite(), getTypeTexte());
    afficherExtra();   // polymorphisme : chaque derive affiche son propre champ extra
    std::println("");
}
```

Les implémentations des classes dérivées (`Consommable`, `Equipement`, `Medicament`) suivent le même patron :
- Constructeur par défaut et constructeur complet (délègue à `Article(...)`).
- `parseExtra` : valide et stocke le champ extra propre au type ; retourne `false` si invalide.
- `exporterExtra` : écrit le champ dans un buffer pour le format CSV.
- `clone` : retourne `new DeriveX(*this)`, permettant la copie polymorphique sans `dynamic_cast`.

Exemples de validation dans `parseExtra` :
- `Consommable` : refuse une date vide ou plus longue que 10 caractères.
- `Equipement`  : `atoi(extra) > 0` — refuse zéro ou négatif.
- `Medicament`  : refuse un dosage vide.

La factory `creerArticleDepuisChamps` instancie le bon dérivé selon `typeTexte`, appelle `parseExtra`,
et retourne `nullptr` si le type est inconnu ou si la validation échoue.

### Étape 3 — Tableau de pointeurs polymorphes (`inventaire.h`)

Dans le TP2, `Inventaire` stockait un tableau d'objets `Article` par valeur (`Article* data`).
Ce modèle est incompatible avec le polymorphisme : stocker un `Consommable` dans un slot `Article`
provoque le **slicing** (les champs spécifiques au dérivé sont perdus).

La solution est de stocker des **pointeurs** vers des objets alloués sur le tas (`Article** data`).
L'inventaire ne connaît que l'interface `Article*` ; le comportement concret est résolu à l'exécution
via la table de fonctions virtuelles.

```cpp
// Tableau de pointeurs : chaque slot pointe vers un Article alloue sur le tas.
// Ce modele evite le slicing et permet le polymorphisme a l'execution.
struct Inventaire {
    Article** data;  // tableau de pointeurs (redimensionnable)
    size_t    size;  // nombre d'articles actuellement stockes
    size_t    cap;   // capacite allouee du tableau
};

// Champs disponibles pour le tri ; passes comme parametre a trierInventaire.
enum ChampTri {
    TRI_CODE,
    TRI_NOM,
    TRI_PRIX,
    TRI_QTE
};

void initInventaire    (Inventaire& inv, size_t capaciteInitiale = 16);
void libererInventaire (Inventaire& inv);
void agrandirInventaire(Inventaire& inv);  // double la capacite

bool ajouterArticle (Inventaire& inv, const Article& article); // clone + insertion
int  chercherArticle(const Inventaire& inv, const char* code);  // retourne index ou -1
bool retirerArticle (Inventaire& inv, const char* code);        // suppression + decalage
bool mettreAJour    (Inventaire& inv, const char* code, double prix, int quantite);

bool importerInventaire  (Inventaire& inv, const char* nomFichier);
bool exporterInventaire  (const Inventaire& inv, const char* nomFichier);

void afficherInventaire  (const Inventaire& inv);
void afficherStatistiques(const Inventaire& inv); // global + detail par type

// Tri maison impose par l'enonce (sans algorithmes STL).
void trierInventaire(Inventaire& inv, ChampTri champ, bool ascendant);
```

### Étape 4 — Opérations sur l'inventaire (`inventaire.cpp`)

Cette étape implémente les six opérations principales modifiées ou ajoutées pour le TP3 :

**Libération** : `libererInventaire` appelle `delete inv.data[i]` sur chaque pointeur, ce qui
déclenche le destructeur virtuel correct (TP2 utilisait `libererArticle` sur des valeurs).

**Ajout** : `ajouterArticle` appelle `article.clone()` pour stocker une copie polymorphique
indépendante. Retourne `false` si le code existe déjà.

**Retrait** (`-ret`, nouveau en TP3)** : après avoir libéré le pointeur à l'index trouvé, on
décale tous les pointeurs suivants d'une position vers la gauche.

```cpp
// Retire l'article identifie par code : libere sa memoire, puis decale
// tous les pointeurs suivants d'un cran pour combler le trou.
bool retirerArticle(Inventaire& inv, const char* code) {
    int idx = chercherArticle(inv, code);
    if (idx < 0) return false;  // code introuvable

    delete inv.data[idx];       // destructeur virtuel appele automatiquement

    // Decalage vers la gauche : O(n) en pire cas, acceptable pour cet usage.
    for (size_t i = (size_t)idx; i + 1 < inv.size; ++i) {
        inv.data[i] = inv.data[i + 1];
    }
    inv.data[inv.size - 1] = nullptr;  // derniere case laissee a nullptr
    inv.size--;
    return true;
}

// Comparateur interne : retourne un entier negatif, nul ou positif selon l'ordre.
// Le parametre asc inverse le signe pour obtenir l'ordre descendant.
static int comparerArticles(const Article* a, const Article* b,
                             ChampTri champ, bool asc) {
    int s = 0;
    if      (champ == TRI_CODE) s = std::strcmp(a->getCode(), b->getCode());
    else if (champ == TRI_NOM)  s = std::strcmp(a->getNom(),  b->getNom());
    else if (champ == TRI_PRIX)
        s = (a->getPrix() < b->getPrix()) ? -1 : ((a->getPrix() > b->getPrix()) ? 1 : 0);
    else
        s = (a->getQuantite() < b->getQuantite()) ? -1
          : ((a->getQuantite() > b->getQuantite()) ? 1 : 0);
    return asc ? s : -s;
}

// Tri par selection : conforme a l'enonce (aucun algorithme STL).
// A chaque iteration, on cherche l'element minimal dans [i..n-1]
// et on l'echange avec la position i.  Complexite : O(n²).
void trierInventaire(Inventaire& inv, ChampTri champ, bool ascendant) {
    for (size_t i = 0; i < inv.size; ++i) {
        size_t meilleur = i;
        for (size_t j = i + 1; j < inv.size; ++j) {
            if (comparerArticles(inv.data[j], inv.data[meilleur], champ, ascendant) < 0) {
                meilleur = j;
            }
        }
        if (meilleur != i) {
            // Echange de pointeurs uniquement : aucune copie d'objet n'est effectuee.
            Article* tmp        = inv.data[i];
            inv.data[i]         = inv.data[meilleur];
            inv.data[meilleur]  = tmp;
        }
    }
}
```

**Import/Export** : `importerInventaire` saute la ligne d'en-tête, puis appelle
`parserLigneArticleV2` pour extraire les 6 champs et créer l'objet polymorphique.
`exporterInventaire` écrit l'en-tête `code;nom;prix;quantite;type;extra` puis appelle
`formaterArticleV2` pour chaque article.

**Statistiques** : `afficherStatistiques` effectue un seul parcours du tableau.
Quatre paires d'accumulateurs sont maintenues en parallèle (global + une par type).
Ce choix évite trois parcours séparés par type.

### Étape 5 — Nouvelles options dans `main.cpp`

Les nouvelles variables, le parsing des arguments, et le traitement des options
`-ret`, `-tri` et l'ajout TP3 (`-ajout ... type extra`) sont ajoutés dans `main.cpp`.

```cpp
// --- Variables ajoutees pour les nouvelles options TP3 ---

bool        faireRet  = false;
const char* retCode   = nullptr;

bool        faireTri  = false;
const char* triChamp  = nullptr;
bool        triAsc    = true;   // defaut : ordre ascendant

const char* ajoutType  = nullptr;  // champ type du CSV (consommable/equipement/medicament)
const char* ajoutExtra = nullptr;  // champ extra, interprete selon le type

// --- Parsing -ajout (TP3 : 7 arguments au lieu de 5) ---

else if (std::strcmp(argv[i], "-ajout") == 0) {
    // Verifier que les 6 arguments obligatoires sont presents
    if (i + 6 >= argc) {
        std::println("Arguments manquants: -ajout <code> <nom> <prix> <qte> <type> <extra>");
        return 1;
    }
    faireAjout = true;
    ajoutCode  = argv[i + 1];
    ajoutNom   = argv[i + 2];
    ajoutPrix  = std::atof(argv[i + 3]);
    ajoutQte   = std::atoi(argv[i + 4]);
    ajoutType  = argv[i + 5];
    ajoutExtra = argv[i + 6];
    i += 7;
}

// --- Parsing -ret (nouvelle option TP3) ---

else if (std::strcmp(argv[i], "-ret") == 0) {
    if (i + 1 >= argc) {
        std::println("Arguments manquants: -ret <code>");
        return 1;
    }
    faireRet = true;
    retCode   = argv[i + 1];
    i += 2;
}

// --- Parsing -tri (nouvelle option TP3) ---

else if (std::strcmp(argv[i], "-tri") == 0) {
    if (i + 1 >= argc) {
        std::println("Arguments manquants: -tri <champ> [asc|desc]");
        return 1;
    }
    faireTri = true;
    triChamp  = argv[i + 1];
    // Le second argument asc/desc est optionnel ; defaut = asc
    if (i + 2 < argc &&
        (std::strcmp(argv[i + 2], "asc") == 0 || std::strcmp(argv[i + 2], "desc") == 0)) {
        triAsc = (std::strcmp(argv[i + 2], "asc") == 0);
        i += 3;
    } else {
        triAsc = true;
        i += 2;
    }
}

// --- Traitement -ajout : factory polymorphique ---

if (faireAjout) {
    // creerArticleDepuisChamps alloue le bon type derive et valide extra.
    Article* a = creerArticleDepuisChamps(
        ajoutCode, ajoutNom, ajoutPrix, ajoutQte, ajoutType, ajoutExtra);
    if (!a) {
        std::println("Erreur: type ou extra invalide.");
    } else {
        if (!ajouterArticle(inv, *a)) {
            std::println("Erreur: code deja existant.");
        }
        delete a;   // ajouterArticle a fait son propre clone
    }
}

// --- Traitement -ret ---

if (faireRet) {
    if (!retirerArticle(inv, retCode)) {
        std::println("Introuvable.");
    }
}

// --- Traitement -tri ---

if (faireTri) {
    // Convertir la chaine de caracteres en enum pour eviter les comparaisons dans tri.
    ChampTri champ = TRI_CODE;
    if      (std::strcmp(triChamp, "code") == 0) champ = TRI_CODE;
    else if (std::strcmp(triChamp, "nom")  == 0) champ = TRI_NOM;
    else if (std::strcmp(triChamp, "prix") == 0) champ = TRI_PRIX;
    else if (std::strcmp(triChamp, "qte")  == 0) champ = TRI_QTE;
    else {
        std::println("Champ tri invalide: {}", triChamp);
        libererInventaire(inv);
        return 1;
    }
    // Le tri agit sur l'inventaire en memoire uniquement (pas sur le fichier).
    trierInventaire(inv, champ, triAsc);
}
```

---

## 4. Organisation des fichiers

```
scr/
├── main.cpp                  Point d'entree : lecture argv, orchestration des options
├── articles/
│   ├── article.h             Hierarchie de classes (Article + 3 derives + factory)
│   └── article.cpp           Implementations, parsing CSV 6 champs, formatage
└── inventaire/
    ├── inventaire.h          Structure Inventaire, enum ChampTri, declarations
    └── inventaire.cpp        Gestion memoire, tri, import/export, statistiques
```

Les fichiers `article.h/.cpp` sont indépendants : ils ne connaissent pas `Inventaire`.
`inventaire.h` inclut `article.h` et utilise les pointeurs polymorphes `Article*`.
`main.cpp` inclut uniquement `inventaire/inventaire.h`.

---

## 5. Tests

Les commandes ci-dessous constituent le scénario de démonstration à exécuter dans la vidéo de remise.
Elles couvrent chacune des options requises par l'énoncé.

### 5.1 Compilation

- [ ] Compiler le projet avec le standard C++23 sans avertissements :
  ```powershell
  cl.exe /std:c++latest /EHsc /W4 scr/main.cpp scr/articles/article.cpp scr/inventaire/inventaire.cpp /Fe:main.exe
  ```
  Ou utiliser la tâche de build configurée dans VS Code.

### 5.2 Aide (`-aide`)

- [ ] Afficher l'aide et vérifier que toutes les options sont listées :
  ```powershell
  .\main.exe -aide
  ```

### 5.3 Import et affichage (`-i`)

- [ ] Charger le fichier d'inventaire et afficher toutes les entrées :
  ```powershell
  .\main.exe -i input\inventaire_tp3.txt
  ```
  Résultat attendu : liste des articles avec le champ `extra` visible pour chaque type.

### 5.4 Statistiques (`-stat`)

- [ ] Afficher le bloc global suivi des trois blocs par type :
  ```powershell
  .\main.exe -i input\inventaire_tp3.txt -stat
  ```
  Résultat attendu : nombre, quantité totale, valeur totale, prix min/max — d'abord global, puis
  séparément pour `consommable`, `equipement` et `medicament`.

### 5.5 Recherche (`-cherche`)

- [ ] Rechercher un article existant et vérifier que le champ `extra` s'affiche :
  ```powershell
  .\main.exe -i input\inventaire_tp3.txt -cherche A001
  ```
- [ ] Rechercher un code inexistant et vérifier le message d'erreur :
  ```powershell
  .\main.exe -i input\inventaire_tp3.txt -cherche XXXX
  ```

### 5.6 Mise à jour (`-maj`)

- [ ] Modifier le prix et la quantité d'un article, puis vérifier avec `-cherche` :
  ```powershell
  .\main.exe -i input\inventaire_tp3.txt -maj A001 9.99 5 -o output.txt
  ```
  Vérifier que le fichier `output.txt` contient A001 avec les nouvelles valeurs.
- [ ] Vérifier la modification directement sans export :
  ```powershell
  .\main.exe -i input\inventaire_tp3.txt -maj A001 9.99 5 -cherche A001
  ```
  ```powershell
  .\main.exe -i input\inventaire_tp3.txt -maj A001 9.99 5 -o output\test_maj.txt
  ```
  Résultat attendu : `A001 | Gants nitrile XS blanc Mod-100 | 9.99 $ | qte=5 | type=consommable | exp=2026-01-31`

### 5.7 Ajout (`-ajout`)

- [ ] Ajouter un consommable et vérifier sa présence :
  ```powershell
  .\main.exe -i input\inventaire_tp3.txt -ajout Z001 Masque 1.50 100 consommable 2027-06-01
  ```
- [ ] Ajouter un équipement :
  ```powershell
  .\main.exe -i input\inventaire_tp3.txt -ajout Z002 Tensiometre 45.00 10 equipement 24
  ```
- [ ] Ajouter un médicament :
  ```powershell
  .\main.exe -i input\inventaire_tp3.txt -ajout Z003 Aspirine 0.80 200 medicament 500mg
  ```

### 5.8 Retrait (`-ret`)

- [ ] Retirer un article existant et vérifier qu'il a disparu :
  ```powershell
  .\main.exe -i input\inventaire_tp3.txt -ret A001 -o output\sortie.txt
  ```
  Vérifier que `A001` est absent de `sortie.txt`.
- [ ] Tenter de retirer un code inexistant et vérifier le message :
  ```powershell
  .\main.exe -i input\inventaire_tp3.txt -ret XXXX
  ```

### 5.9 Tri (`-tri`)

- [ ] Trier par code, ordre ascendant (défaut) :
  ```powershell
  .\main.exe -i input\inventaire_tp3.txt -tri code
  ```
- [ ] Trier par prix, ordre descendant :
  ```powershell
  .\main.exe -i input\inventaire_tp3.txt -tri prix desc
  ```
- [ ] Trier par nom, puis exporter :
  ```powershell
  .\main.exe -i input\inventaire_tp3.txt -tri nom asc -o output\sortie_tri.txt
  ```

### 5.10 Export (`-o`)

- [ ] Exporter l'inventaire et vérifier que le fichier contient l'en-tête et les 6 champs :
  ```powershell
  .\main.exe -i input\inventaire_tp3.txt -o output\sortie.txt
  ```
  Première ligne attendue : `code;nom;prix;quantite;type;extra`

---

## 6. Conclusion

Le TP3 transforme un programme procédural (TP2) en une application orientée objet dont la pièce
centrale est la classe abstraite `Article`. La hiérarchie à deux niveaux (`Article` → `Consommable`,
`Equipement`, `Medicament`) permet de traiter tous les types de façon uniforme à travers des pointeurs
`Article*`, sans `if/else` sur le type dans le code de l'inventaire.

Les principales contraintes techniques de l'énoncé sont respectées :
- Standard C++23 avec `std::print`/`std::println` pour toutes les sorties console.
- Aucune utilisation de la STL pour les structures de données ou le tri.
- Séparation stricte `.h`/`.cpp`.
- Aucune lettre accentuée dans les chaînes affichées sur la console.


