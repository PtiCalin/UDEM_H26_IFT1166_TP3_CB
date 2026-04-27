# IFT1166 – TRAVAIL PRATIQUE #3 – 29 mars 2026

# « Gestion de l’inventaire, version P.O.O »

# Mohamed Lokbani

Mise à jour
29-03-2026 diffusion de l’énoncé.

```
Équipes : le travail est à faire en monôme uniquement.
```
Remise : une seule remise est à effectuer par voie électronique au plus tard le dimanche 26 avril 2026 à 23h59. Aucune
prorogation ne sera accordée.

```
Conseils : n’attendez pas le dernier jour pour commencer votre travail. Vous n’aurez pas le temps nécessaire pour le
réaliser.
```
But : ce TP a pour but de vous faire pratiquer classes et objets, fonctions membres, héritage & fonctions virtuelles,
structures de données de base (sans STL), algorithmique (tri/recherche).

Énoncé : vous allez reprendre le travail déjà réalisé dans le TP#02 en lui apportant une série de modifications.

Programmation orientée objet : intégrer dans ce travail une représentation orientée objet de manière structurée et efficace.
La gestion de l’inventaire doit permettre la manipulation polymorphique des articles. Le rapport doit expliquer et
développer la hiérarchie retenue.

Ajout du type et du champ extra : nous avons légèrement modifié le format du fichier d'inventaire en y ajoutant le type de
l’élément. Trois types sont utilisés: {consommable, equipement, medicament}. Chaque type a une valeur supplémentaire
représentée par le champ « extra », comme suit :

consommable → extra = dateExpiration (AAAA-MM-JJ)
equipement → extra = garantie en mois
medicament → extra = dosage

Au final, le fichier d’inventaire a la forme suivante:

code;nom;prix;quantite;type;extra

Le champ « extra » est obligatoire. Son interprétation dépend du type utilisé.

De ce fait, l’option « -ajout » doit-être ajustée en conséquence.

Ajout de l’option « -ret » : elle permet de retirer un article à partir de son code, comme suit:

-ret <code>

Tri personnalisé : il s’agit de trier en fonction d'un champ {code, nom, prix, qte}, de manière ascendante (asc) ou
descendante (desc). L'option est comme suit:

-tri <champ> [asc|desc] avec <champ> {code, nom, prix, qte}

Écrire votre propre tri (sélection, insertion ou bulle). Le tri agit sur l’inventaire en mémoire, pas sur le fichier.

Par défaut le tri est ascendant.


Statistiques avec répartition par type : vous allez ajuster l'affichage des statistiques en y incluant une répartition par type.
Format des fichiers :

Les fichiers sont au format texte « UTF-8 ». Chaque article est sur une ligne. Le « ; » est utilisé comme séparateur entre les
éléments d’un article. Par rapport au TP#02, comme il a été mentionné, nous avons ajouté deux champs supplémentaires :
« type » et « extra ».

code;nom;prix;quantite;type;extra
A001;Gants nitrile XS blanc Mod-100;0.2;20;consommable;2026-01-
A002;Tensiometre bleu Mod-201;16.9;2;equipement;

La première ligne du fichier d’inventaire contient le nom de chaque colonne dans le fichier. Elle est toujours présente dans
le fichier. Les articles dans le fichier sont toujours au bon format. Ils ne vont pas contenir dans le nom le séparateur « ; ».

Le fichier « inventaire.txt » accompagnant l’énoncé de ce travail pratique, contient 200 articles. À noter que le nombre
d’articles dans le fichier est variable.

La ligne de commande :

Le programme supporte les modes suivants via la ligne de commande :

-i <fichier> : importer un inventaire depuis un fichier texte.
-o <fichier> : exporter l’inventaire vers un fichier texte.
-ajout <code> <nom> <prix> <qte> <type> [extras ...]: ajouter un article.
-ret <code> : retirer un article.
-maj <code> <prix> <qte> : mettre à jour prix et quantité d’un article existant.
-cherche <code> : rechercher et afficher un article.
-tri <champ> [asc|desc] : trier avec <champ> {code, nom, prix, qte}, défaut [asc].
-stat : afficher des statistiques.
-aide : afficher l’aide.

Pour le fichier d’inventaire fourni, l’affichage obtenu par l’option « -stat » est disponible en annexe 1.

Contraintes techniques :

- Utilisation du standard « C++23 » est obligatoire
- Utilisation de « std::print » ou de « std::println » pour l’affichage
- Utilisation de « char* » et « std::string » (si nécessaire)
- Il ne faut pas utiliser la STL, printf, macros ou exceptions
- Utiliser une séparation « .h/.cpp »
- Il ne faut pas utiliser les lettres accentuées dans le texte affiché sur la console
- Nous validerons votre travail sur une machine du département. Assurez-vous d’avoir effectué toutes les validations
    nécessaires sur une telle machine avant de le remettre.

Fichiers à remettre : vous devez remettre le fichier compressé « tp3H26.zip » via le système de remise de « Studium ».
Incluez également :

- Un rapport décrivant les tests effectués, l’organisation de votre programme.
- Une capture vidéo de l’exécution de votre programme avec l’ensemble des options du menu.

Barème

Ce TP est noté sur 14 points, répartis comme suit :

- Organisation du code : 3 points
- P.O.O : 3 points


- Option de tri : 3 points
- Gestion des autres options : 3 points
- Avis global : 2 points (programmation, clarté du code, etc.)

Le plagiat est strictement interdit et sanctionné par le Règlement disciplinaire sur la fraude et le plagiat concernant les

# étudiants. Pour plus d’informations, consultez : http://www.integrite.umontreal.ca

Exigences supplémentaires

Pour le rapport, nous ne vous demandons pas d’expliquer l’utilité de chaque variable « i » ou de chaque boucle « for » ou
« while ». Vos commentaires dans le code doivent être plus pertinents et expliquer leur utilité.

Votre rapport doit être clair. Mettez-vous à la place d’une personne qui connaît l’objectif de votre programme, mais pas
votre code. En lisant votre rapport, elle devra pouvoir naviguer avec aisance dans votre programme.

Pénalités
En plus des points indiqués ci-dessus, vous risquez d’en perdre dans les cas suivants :

- Non-remise électronique : 0 (volontaire ou par erreur)
- Programme qui ne compile pas : 0
- Programme qui compile, mais ne respecte pas les spécifications : 0

# • Avertissements (warnings) non corrigés : la pénalité dépend de la quantité, à partir de -0.25 point.

- Aberrations de codage : même si « tous les chemins mènent à Rome », faites l’effort nécessaire pour éviter de
    prendre le plus long.

Documents fournis

- Le fichier « inventaire.txt »
- Feuille de route « H26Tp3_feuille_de_route.odt »

Communications

- Par courriel : une seule adresse « dift1166@iro.umontreal.ca ».

Pour faciliter le traitement de votre requête, inclure dans le sujet de votre courriel, au moins la chaîne [IFT1166] et une
référence au tp03.

- En personne : à la démo ou sur rendez-vous.


# Annexe 1



STATISTIQUES DE L'INVENTAIRE
----------------------------
Nombre total d'articles : <N>
Quantite totale : <Qt>
Valeur totale du stock : <V> $

Prix minimum global : <Pmin> $
Prix maximum global : <Pmax> $

DETAIL PAR TYPE
---------------

Type : consommable
Articles : <Nc>
Quantite totale : <Qc>
Valeur totale : <Vc> $
Prix minimum : <Pc_min> $
Prix maximum : <Pc_max> $

Type : equipement
Articles : <Ne>
Quantite totale : <Qe>
Valeur totale : <Ve> $
Prix minimum : <Pe_min> $
Prix maximum : <Pe_max> $

Type : medicament
Articles : <Nm>
Quantite totale : <Qm>
Valeur totale : <Vm> $
Prix minimum : <Pm_min> $
Prix maximum : <Pm_max> $