/*


IFT1166 -

22-février   -2026 v1.02              M.Lokbani  gcc-15.2
30-mai       -2007 v1.01              M.Lokbani  gcc-4.0.2
12-novembre  -2005 v1.00              M.Lokbani  code + gcc-3.4.2, +comments

contact: lokbani@iro.umontreal.ca


    Copyright (C) 2005 - 2026 Université de Montréal
            Département d'informatique et de Recherche Opérationnelle
            Mohamed Lokbani
    -- Tous Droits Réservés -- All Rights Reserved --


Description:

    Ce fichier décrit l'utilisation de argc et argv pour la lecture des arguments
    se trouvant sur la ligne de commande.

Remarques:

    Dans les langages C et C++, l'argument 0 est le nom du programme (ce n'est pas
    le cas pour le langage java où le nom du programme n'est pas pris en compte).
    Il faut déclarer la fonction main de la manière suivante pour pouvoir accéder à
    ces arguments :
    
    int main (int argc, char *argv[]) { //etc.}
    
    argc : contient le nombre d'arguments de la ligne de commande.
    argv : est un tableau de pointeurs sur les arguments de la ligne de commande.    

*/

#include <iostream>

using namespace std;

void test_nbre_args(int nbre_args, char **list_args){

    /*
        Attention dans le calcul du nombre d'arguments, on prend en compte
        le nom du programme executable.
        On s'attend a recevoir 3 arguments sur la ligne de commande + le nom
        du programme donc 4 au total.
    */
    
    if (nbre_args!=4){
        cerr << "\n\nAttention, on s'attendait a avoir 3 arguments sur la ligne de commande\n";
        cerr << "Il n'y avait que " << (nbre_args-1) << " argument(s) sur la ligne de commande\n";
        cerr << "La ligne de commandes doit etre sous cette forme: argcv(.exe) argument_1 argument_2 argument_3\n\n";
        cerr << "Et nous avons recu plutot cette ligne: " << list_args[0];
        for (int i=1;i<nbre_args;i++)
            cout << " " << list_args[i];
        cout << endl;
        exit(1);
    }
}

void affiche_args(int nbre_args, char** list_args){
    
    cout << "Le nombre d'arguments sur la ligne de commande est: " << (nbre_args-1) << endl;

    if (nbre_args!=1){
        cout << "Les arguments du programme " << list_args[0] << " sont: " << endl;
        
        for (int i=1;i<nbre_args;i++)
            cout << "argv[" << i << "]: " << list_args[i] << endl;
    }

}

int main(int argc, char* argv[]){

    cout << "Le nom du programme executable est: " << argv[0] << endl;
  
    test_nbre_args(argc,argv);
    affiche_args(argc,argv);
    
    
    return 0;
}
