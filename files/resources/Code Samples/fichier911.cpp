/*


IFT1166 -

22-février   -2026 v1.02              M.Lokbani  gcc-15.2
30-mai       -2007 v1.01              M.Lokbani  gcc-4.0.2
12-novembre  -2005 v1.00              M.Lokbani  code + gcc-3.4.2, +comments

contact: lokbani@iro.umontreal.ca


    Copyright (C) 2005-2026 Université de Montréal
            Département d'informatique et de Recherche Opérationnelle
            Mohamed Lokbani
    -- Tous Droits Réservés -- All Rights Reserved --


Description:

    Ce fichier décrit l'utilisation de plusieurs fonctions permettant d'ouvrir un fichier,
    de lire le contenu d'un fichier et finalement d'écrire dans un fichier.
    
    Nous avons défini ces fonctionnalités dans 3 fonctions:

        void ouv_ferm_fic(const char* nom_fic); Décrit toutes les méthodes connues pour ouvrir un fichier
        afin de lire son contenu ou bien afin d'y écrire des données.
        
        void lire_fic(const char* nom_fic); Décrit comment lire des données à partir d'un fichier.

        void ecrire_fic(const char* nom_fic); Décrit comment écrire des données dans un fichier.
        
    La méthode main contient 3 appels:
    
        ouv_ferm_fic: juste pour valider la fonction.
        ecrire_fic: on ouvre un fichier pour y écrire un court texte.
        lire_fic: on ouvre un fichier pour y lire le court texte écrit dans la 2e étape.
        
Remarques:
----------

    L'appel "cin.getline" peut-être écrit sous la forme "fic.getline" sachant que "fic" est un "ifstream".
    
    
    À noter que pour pouvoir manipuler des fichiers, il faut impérativement inclure un des fichiers:
    
    <ifstream> pour la lecture uniquement. ifstream: fichier en mode lecture (InputFileSTREAM)
    <ofstream> pour l'écriture uniquement. ofstream: fichier en mode d'écriture (OutputFileSTREAM)
    <fstream> pour la lecture et l'écriture. fstream: fichier en mode lecture/écriture (FileSTREAM)

*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/*
    Ouverture/Fermeture d'un fichier
    

    open(fic_nom):  ouvre le fichier dont le nom est fic_nom, en utilisant
                    les options par défaut,

    open(fic_nom,flags):    ouvre le fichier fic_nom, en utilisant les options
                            spécifiées par l'argument flags,

    open(fic_nom,flags,prot):   ouvre le fichier fic_nom, en utilisant les options
                                spécifiées par l'argument flags, et en modifiant,
                                grâce à l'argument prot, les paramètres de protection
                                associés au fichier.

    close(): ferme le fichier

    is_open():  retourne vrai (true) si le fichier a été ouvert, sinon
                faux (false) en cas d'échec.


*/

void ouv_ferm_fic(const char* nom_fic){

    /*
        Première manière de l'écrire 
            - On définit une instance
            - On appelle la méthode open (pour ouvrir le fichier)
            - On ferme le fichier
    */
    
    // Fichier par défaut en mode de lecture.
    ifstream f1;
    f1.open (nom_fic);
    f1.close();
    
    // Fichier par défaut en mode d'écriture.
    ofstream f2;
    f2.open(nom_fic);
    f2.close();
    
    // Fichier ouvert en mode de lecture et écriture.
    fstream f3;
    f3.open (nom_fic,ios::in | ios::out);
    f3.close();
    
    // Fichier ouvert en mode de lecture.
    fstream f4;
    f4.open (nom_fic,ios::in);
    f4.close();

    // Fichier ouvert en mode écriture.
    fstream f5;
    f5.open (nom_fic,ios::out);
    f5.close();

    /*
        Deuxième manière de l'écrire
            - On définit une instance et on appelle (implicitement) la méthode open.
            - On ferme le fichier
    */

    // Une seconde forme d'écriture, sur une seule ligne de commande.
    ifstream f6(nom_fic);
    f6.close();

    ofstream f7(nom_fic);
    f7.close();
    
    fstream f8(nom_fic,ios::in | ios::out);
    f8.close();
    
    // Fichier ouvert en mode de lecture.
    fstream f9(nom_fic,ios::in);
    f9.close();

    // Fichier ouvert en mode écriture.
    fstream f10(nom_fic,ios::out);
    f10.close();

    /* 
        On pouvait aussi écrire directement le nom du fichier (déconseillé)
        Par exemple, ici on veut ouvrir le fichier test.txt en mode de lecture
        uniquement.
        Il est déconseillé de forcer le nom de la sorte ... même si vous n'avez
        qu'un seul fichier à ouvrir et son nom est connu!
    */
    
    ifstream f12("test.txt");
    f12.close();


    /*
        Vérification:
        et si le fichier n'est pas présent?
    
        Avant d'ouvrir le fichier, on teste s'il est présent dans le répertoire,
        sinon on sort avec un  message d'erreur.
        
        Ce test s'applique aussi aux exemples précédents
    
    */
    
    ifstream f11(nom_fic);

    if (!f11.is_open()) {
        cerr << "ne peut pas ouvrir le fichier: " << nom_fic << "\n";
        exit (1);
    }
    f11.close();
    
}

/*
    Lire le contenu d'un fichier

    - On ouvre d'abord le fichier.
    - On teste que l'ouverture est ok.
    - On lit le contenu tant que la fin n'a pas été atteinte.
    - Si c'est le cas c'est fini, on ferme le fichier.

*/

void lire_fic(const char* nom_fic){

    ifstream fic(nom_fic);
    string entree;
    
    if (!fic.is_open()) {
        cerr << "ne peut pas ouvrir le fichier: " << nom_fic << "\n";
        exit (1);
    }
    
    // Lecture du contenu du fichier.
    // La méthode eof(): (EndOfFile i.e. Fin de Fichier) retourne vrai (true)
    // si la fin de fichier a été atteinte, sinon elle retourne faux (false).
    
    while (!fic.eof()) {
        fic >> entree;
        cout  << entree << endl;
        entree=""; // On nettoye le contenu de la chaîne après chaque lecture/écriture, pour éviter des doublons.
    }
    fic.close();

}

void ecrire_fic(const char* nom_fic){

    ofstream fic(nom_fic);
    
    if (!fic.is_open()) {
        cerr << "ne peut pas ouvrir le fichier: " << nom_fic << "\n";
        exit (1);
    }
    
    // Écriture dans le fichier.
    // Utiliser le "handler" fic à la place de "cout"
    
    fic << "Debut du fichier ...." << endl;
    fic << "Ceci est un exemple comment ecrire dans un fichier\n";
    fic << "Fin de l'exemple ... au revoir!\n";
    
    // Attention, il faudra fermer le fichier pour valider l'écriture, sinon elle
    // risque d'être perdue et vous avez écrit votre texte dans le "vide"!
    
    fic.close();
}


int main() {
    const char *fic = "./fichier.txt";

    ouv_ferm_fic(fic);
    
    ecrire_fic(fic);
    lire_fic(fic);
    
    return 0;
}
