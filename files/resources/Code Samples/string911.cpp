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

    Ce fichier décrit l'utilisation du type string à la place des char*
    
    En C++ la classe string permet de manipuler les chaînes de caractères
    sans trop se soucier de la gestion de pointeurs qui est faite par derrière.
    Le programme suivant présente quelques exemples d'utilisation du type string.
    
    À noter que pour pouvoir utiliser string il faut impérativement inclure le
    fichier d'entête « <string> ».

    Bye bye les pointeurs ....

*/

#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int main() {

    // définition de 2 variables du type string
    string chaine, deuxchaines; 

    // une chaîne de chars sous la forme d'un tableau
    char tab[5]={'a','b','c','d','\0'};
    
    // initialisation d'une chaîne du type string
    chaine = "ceci";
    cout << "chaine au depart: " << chaine << endl;

    // définition et initialisation les 2 à la fois
    string uneautre = " est un exemple";
    cout << "une autre chaine: " << uneautre << endl;

    // on ajoute deux chaînes, une addition classique
    chaine = chaine + uneautre;
    cout << "chaine apres ajout: " << chaine << endl;
    
    // la taille de la chaine
    cout << "la taille de ma chaine: " << chaine.length() << endl;
    
    // définition et initialisation à l'aide d'une chaine char*
    // Donc comment passer du char* vers string ... bye bye les pointeurs!
    string untableau(tab);
    cout << "untableau: " << untableau << endl;
    
    // Et si vous etes en precense de méthodes qui doivent recevoir comme argument un char*!
    // Vous ne pouvez pas modifier les méthodes pour faire passer un string. Que faire alors?
    // Convertir le string en char* ... les pointeurs nous hantent encore!
    // Donc comment passer du string vers char* ....
    // On utilise pour cela la méthode c_str de la classe string
    // Attention penser à allouer l'espace mémoire ...

    string encore("ceci alors");
    char* test = new char[encore.length()+1];
    strcpy(test,encore.c_str());
    cout << "test: " << test << endl;
    
    // si vous voulez travailler sur la même chaîne:
    // ici on ne fait que recopier l'adresse du pointeur.
    
    char* second_test = (char *) encore.c_str();
    second_test[0]='Z'; // On remplace le premier caractere c par le caractere Z
    cout << encore << " : " << second_test << endl;
    
    return 0;
}
