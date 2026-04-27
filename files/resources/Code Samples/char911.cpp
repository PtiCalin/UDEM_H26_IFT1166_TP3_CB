/*


IFT1166 -

22-février  -2026 v1.02         M.Lokbani  gcc-15.2
30-mai      -2007 v1.01         M.Lokbani  normalisation itoa + gcc-4.0.2
16-octobre  -2005 v1.00         M.Lokbani  code + gcc-3.4.2, +comments

contact: lokbani@iro.umontreal.ca


    Copyright (C) 2005-2026 Université de Montréal
            Département d'informatique et de Recherche Opérationnelle
    Mohamed Lokbani
    -- Tous Droits Réservés -- All Rights Reserved --


Remarques:
    Plusieurs commentaires ont été extraits texto de:
        - Notes de cours de A. Dancel (Le Langage C)
        - Guide de référence de Borland

Description:

    Ce fichier décrit l'utilisation de plusieurs fonctions permettant de manipuler
    des caractères ou des chaînes de caractères.
    
    Nous avons défini ces fonctionnalités dans 5 fonctions:

        Traitement_de_chaines(): Décrit les fonctions nécessaires pour manipuler des chaînes de caractères.
        
        Test_de_caracteres():  Décrit les fonctions nécessaires pour tester la nature d'un caractère.
        
        Conversion_de_caracteres(): Décrit les fonctions nécessaires pour convertir un caractère.
        
        Conversion_de_chaines(): Décrit les fonctions nécessaires pour convertir une chaîne de caractères.
        
        Conversion_d1_entier(): Décrit les fonctions nécessaires pour convertir un entier.
    

    Chaque fonction contient le fichier d'en-tête qui va avec et qui contient les prototypes de fonctions
    utilisées dans les exemples.


*/

#include <iostream>
#include <string.h>
#include <cctype>
#include <cstdlib>
#include <cmath>


using namespace std;



void Traitement_de_chaines(){
    
    /*
        Pour pouvoir utiliser les différentes fonctions décrites dans la fonction "Traitement_de_chaines",
        il faudra penser à inclure le fichier d'en-tête <string.h>
    
        Il est important de ne pas confondre entre « string.h » et « string ». Le premier contient les prototypes
        des fonctions permettant de manipuler des chaînes de caractères déclarées comme « char * » alors que
        le second pour des chaînes de caractères du type « string ».
    */
    
    char Allemagne[100] = "Organisateur de la coupe du monde de football 2006";
    char Bresil[100] = "Champion du monde de football";
    char Tempo[100] = "";
    

    /*
        Pour calculer la longueur d'une chaîne
            size_t strlen(const char* str)
        1- Valeur retournée est le nombre de caractères de la chaîne str. Le caractère nul de fin de chaîne
	   n'étant pas compté.
    */
    cout << "La taille de la chaine Allemagne: " << strlen(Allemagne) <<endl;
    cout << "La taille de la chaine Bresil: " << strlen(Bresil) <<endl;

    /*
        Pour déterminer la taille d'une variable ou d'un type
            sizeof(variable) ou sizeof(type)
        1- Dans le cas d'une chaîne de caractères, la valeur retournée est la taille de la chaîne (la taille
	   du tableau contenant la chaîne).
    */
    cout << "La taille reelle de la chaine Allemagne: " << sizeof(Allemagne) <<endl;
    
    
    /*
        Pour copier une chaîne dans une autre
            char* strcpy(char* destination, const char* source)
        1- Copie la chaîne source dans la chaîne destination y compris le caractère nul de fin de chaîne.
        2- La chaîne destination doit être préalablement allouée statiquement ou dynamiquement.
        3- Valeur retournée est l'adresse de destination.
    */
    cout << "Copie Bresil dans Tempo. La chaine resultante est: " << strcpy (Tempo,Bresil) << endl;
    
    cout << "Reinitialisation de Tempo avec la chaine Allemagne. La chaine resultante est: " << strcpy (Tempo,Allemagne) << endl; 

    /*
        Pour copier partiellement une chaîne dans une autre
            char* strncpy(char* destination, const char* source, size_t maxlen)
        1- Copie jusqu'à maxlen caractères de la chaîne source dans la chaîne destination.
        2- La chaîne destination doit être préalablement allouée statiquement ou dynamiquement.
        3- Si le caractère nul de fin de chaîne n'est pas copié, il n'est pas ajouté à la fin de la chaîne
	   destination. Il faudra donc l'ajouter manuellement.
        4- Valeur retournée est l'adresse de destination.
    */


    cout << "Copie partielle des 2 premiers caracteres de Bresil dans Tempo.\n";
    strncpy (Tempo,Bresil,2);
    Tempo[2]='\0';
    cout << "La chaine resultante est:" << Tempo << endl;
        
    /*
        Pour concaténer deux chaînes de caractères
            char* strcat(char* destination, const char* source)
        1- Copie la chaîne source à la fin de la chaîne destination (concaténation).
        2- La longueur de la chaîne résultante est: strlen(source) + strlen(destination).
        3- La chaîne destination doit avoir une taille suffisante pour recevoir tous les caractères de
	   la chaîne concaténée.
        4- Valeur retournée est l'adresse de destination.
    */
    
    strcpy(Tempo,Allemagne); // On copie d'abord la chaîne Allemagne dans la chaîne Tempo,
			     // histoire de mieux voir la concaténation

    cout << "Le resultat final de concatenation de chaines est: " << strcat(Tempo,": Allemagne.") << endl;



    /*
        Pour comparer deux chaînes de caractères
            int strcmp(const char* s1, const char* s2)
        1- Compare les chaînes s1 et s2.
        2- La comparaison débute avec le premier caractère de chaque chaîne et continue avec les suivants,
	   jusqu'à ce que des caractères de même rang soient différents ou que l'une des chaînes soit terminée.
        3- Valeur retournée:
            - Valeur négative si s1 < s2
            - Valeur nulle si les deux chaînes sont égales
            - Valeur positive si s1 > s2
    */
    
    cout << "Le resultat de la comparaison des chaines Allemagne et Bresil est: " << strcmp(Allemagne,Bresil) << endl;


       /*
        Pour comparer partiellement deux chaînes de caractères
            int strncmp(const char* s1, const char* s2, size_t maxlen)
        1- Compare les chaînes s1 et s2, en cherchant au plus maxlen caractères
        2- La comparaison débute avec le premier caractère de chaque chaîne et continue avec les suivants,
	   jusqu'à ce que des caractères de même rang soient différents ou que maxlen soit atteint ou que
	   l'une des chaînes soit terminée.
        3- Valeur retournée:
            - Valeur négative si s1 < s2
            - Valeur nulle si les deux chaînes sont égales
            - Valeur positive si s1 > s2
    */
    
    cout << "Le resultat de la comparaison des chaines Allemagne et Bresil est avec maxlen=2: " << strncmp(Allemagne,Bresil,2) << endl;
    
    /*
        Pour rechercher un caractère en particulier dans une chaîne
            char* strchr(const char* s, int c)
        1- Recherche la première occurrence du caractère c dans la chaîne de caractères s.
        2- Le caractère de fin de chaîne est considéré comme en faisant partie; ainsi l'expression
	   strcchr(str,0) renvoie un pointeur vers celui ci.
        3- Valeur retournée:
            - En cas de succès: un pointeur sur la première occurrence du caractère c.
            - En cas d'échec: c ne figure pas dans la chaîne s, la fonction retourne un pointeur NULL.
        4- Il faudra tester contre un pointeur NULL pour éviter l'arrêt subit du programme (un plantage).
    */

    char* ptr;
    if ( (ptr = strchr(Allemagne,'o')) != NULL){
        cout << "Le (premier) caractere o est dans la chaine Allemagne?: " << ptr << endl;
    }else{
        cout << "La chaine [" << Allemagne << "] ne contient pas le caractere [" << 'o' << endl;
    }
 
    /*
        Pour effectuer une recherche à rebours d'un caractère en particulier dans une chaîne
            char* strrchr(const char* s, int c)
        1- Recherche la dernière occurrence du caractère c dans la chaîne de caractères s.
        2- Le caractère de fin de chaîne est considéré comme en faisant partie; ainsi l'expression
	   strcchr(str,0) renvoie un pointeur vers celui ci.
        3- Valeur retournée:
            - En cas de succès: un pointeur sur la dernière occurrence du caractère c.
            - En cas d'échec: c ne figure pas dans la chaîne s, la fonction retourne un pointeur NULL.
        4- Il faudra tester contre un pointeur NULL pour éviter l'arrêt subit du programme (un plantage).

    */

    if ( (ptr = strrchr(Allemagne,'o')) != NULL){
        cout << "Le (dernier) caractere o est dans la chaine Allemagne?: " << ptr << endl;
    }else{
        cout << "La chaine [" << Allemagne << "] ne contient pas le caractere [" << 'o' << endl;
    }
    

    /*
        Pour effectuer une recherche d'un caractère d'un ensemble
            char* strpbrk(const char* s1, const char* s2)
        1- Recherche dans s1 la première occurrence d'un caractère figurant dans la chaîne s2.
        2- Valeur retournée:
            - En cas de succès: un pointeur sur la première occurrence dans s1 d'un caractère de s2.
            - En cas d'échec: si aucun caractère de s2 ne figure pas dans la chaîne s1, la fonction
	    retourne un pointeur NULL.
        3- Il faudra tester contre un pointeur NULL pour éviter l'arrêt subit du programme (un plantage).
    */

    if ( (ptr = strpbrk(Allemagne,"xy6")) != NULL){
        cout << "Trouve le caractere [" << ptr << "] en position [" << ptr-Allemagne << "]" << endl;
    }else{
        cout << "pas Trouve!" << endl;
    }
    
    
    /*
        Pour cloner une chaîne
            char* strdup(const char* s)
        1- Fait un double de la chaîne s en allouant de la place.
        2- L'espace alloué pour taille (strlen(s) + 1) octets.
        3- Quand la mémoire allouée n'est plus nécessaire, il faudra la libérer par un appel à la fonction
	   free (et non pas delete) car la chaîne a été allouée par un appel de la fonction malloc (langage C)
	   et non pas new (langage C++).
        4- Valeur retournée:
            - En cas de succès: un pointeur sur l'emplacement de mémoire contenant le clone de la chaîne s.
            - En cas d'échec: la fonction retourne un pointeur NULL et l'espace nécessaire pour contenir
	      le clone n'a pas été alloué. Il ne faut pas libérer un espace non alloué!
    */

    if ( (ptr = strdup(Allemagne)) != NULL){
        cout << "Clonage reussi et la copie de Allemagne se trouve a cette adresse:" << &ptr << endl;
        free(ptr);
    }else{
        cout << "Echec lors du clonage!" << endl;
    }
    
    /*
        Pour rechercher une sous chaîne -1-
            char* strstr(const char* s1, const char* s2)
        1- Recherche la première occurrence de la chaîne s2 dans la chaîne s1.
        2- Valeur retournée:
            - En cas de succès: un pointeur sur l'élément de s1 où commence s2.
            - En cas d'échec: s2 n'est pas dans s1, la fonction retourne un pointeur NULL!
    */

    if ( (ptr = strstr(Allemagne,"foot")) != NULL){
        cout << "La premiere occurrence de la chaine [foot] dans la chaine Allemagne:" << ptr << endl;
    }else{
        cout << "La chaine [foot] ne se trouve pas dans la chaine Allemagne!" << endl;
    }

    
    /*
        Pour rechercher une sous chaîne -2-
            size_t strspn(const char* s1, const char* s2)
    
        1- Cherche la première partie d'une chaîne qui soit le sous-ensemble d'un ensemble donné de caractères.
        2- Recherche donc la première partie de s1 formée uniquement des caractères figurant dans s2.
        3- Renvoie la longueur du premier segment répondant à la condition énoncée en -2-.
        
            size_t strcspn(const char* s1, const char* s2)
    
        1- Isole la partie d'une chaîne qui ne contient aucun caractères d'un ensemble de caractères donnés.
        2- Renvoie la longueur de la partie s1 formée uniquement de caractères ne figurant pas dans s2.
    */

    cout << "La longueur du premier segment [nst]: " << strspn(Allemagne,"nst") << endl;

    cout << "La longueur du premier segment [nst]: " << strcspn(Allemagne,"nst") << endl;
    
    /*
        Pour rechercher un lexèmes dans une chaîne
            char* strtok(const char* s1, const char* s2)
    
        1- Cette fonction décompose s1 en sous-chaînes appelés lexèmes (tokens). Ces lexèmes sont délimités
	   par des caractères (séparateurs) figurant dans la chaîne s2.
        2- Le premier appel à strtok:
            - retourne un pointeur sur le premier lexème de s1
            - écrit un caractère nul dans sans s1 immédiatement après ce lexème.
        3- Les autres appels à strtok avec NULL comme premier argument traitant de la même manière,
	   et jusqu'à épuisement, les autres lexèmes de s1.
        4- La chaîne des séparateurs, s2, peut-être différente d'un appel à l'autre.
        5- Valeur de retour:
            - En cas de succès: un pointeur sur le lexème trouvé dans la chaîne s1.
            - Quand il ne reste plus de lexème dans s1, strtok retourne le pointeur NULL.
        6- La chaîne s1 sera transformée et donc perdue à jamais. Il faudra donc penser à faire une copie.
    */
    
    
    char sep[] = " o";
    strcpy(Tempo,Allemagne);
    ptr = strtok(Tempo,sep);
    while(ptr != NULL){
        cout << "Token: " << ptr << endl;
        ptr = strtok(NULL,sep);
    }
    cout << "Allemagne apres traitement: " << Tempo <<endl;
    
    
    return;    
}


void Test_de_caracteres(){

    /*
        Pour pouvoir utiliser les différentes fonctions décrites dans la fonction "Test_de_caracteres",
        il faudra penser à inclure le fichier d'en-tête <cctype>
    */
    
    /*
        Un caractère alphanumérique?
            int isalnum(int c)
    
        1- Cette fonction teste si le caractère c est un caractère alphanumérique.
        2- Valeur de retour:
            - une valeur non nulle si c est une lettre (A-Z ou a-z) ou un chiffre (0-9)
    */

    isalnum('W')? cout << "[W] est un caractere alphanumerique.\n": cout << "[W] n'est un caractere alphanumerique.\n";    

    /*
        Un caractère alphabétique?
            int isalpha(int c)
    
        1- Cette fonction teste si le caractère c est un caractère alphabétique.
        2- Valeur de retour:
            - une valeur non nulle si c est une lettre (A-Z ou a-z)
    */

    isalpha(9)? cout << "[9] est un caractere alphabetique.\n":cout << "[9] n'est pas un caractere alphabetique.\n";

    /*
        Un caractère ASCII?
            int isascii(int c)
    
        1- Cette fonction teste si le caractère c est un caractère ASCII.
        2- Valeur de retour:
            - une valeur non nulle si l'octet de poids faible de c est compris entre 0 et 127 (0x00 - 0x7F)
    */

    isascii('é')? cout << "[e accent grave] est un caractere ascii (non etendu).\n":cout << "[e accent grave] n'est pas un caractere ascii (non etendu).\n";


    /*
        Un caractère de contrôle
            int iscntrl(int c)
    
        1- Cette fonction teste si le caractère c est un caractère de contrôle.
        2- Valeur de retour:
            - une valeur non nulle si c est un caractère de contrôle ou le caractère "delete"
	    (0x7F ou 0x00 - 0x1F)
    */

    iscntrl('')? cout << "[C] est un caractere de controle.\n":cout << "[C] n'est pas un caractere de controle.\n";

    /*
        Un chiffre?
            int isdigit(int c)
    
        1- Cette fonction teste si le caractère c est un chiffre.
        2- Valeur de retour:
            - une valeur non nulle si c est un chiffre (0-9)
    */

    isdigit(7)? cout << "[7] est un chiffre.\n": cout << "[7] n'est pas un chiffre.\n";


    /*
        Affichable? -1-
            int isgraph(int c)
    
        1- Cette fonction teste si le caractère c est affichable (sauf l'espace).
        2- Valeur de retour:
            - une valeur non nulle si c est un caractère affichable (0x21 - 0x7E. Ne prend pas donc
	    le ASCII étendu).
    */

    isgraph('é')? cout << "[e accent grave] est un caractere affichable.\n":cout << "[e accent grave] n'est pas un caractere affichable.\n";

    /*
        Affichable? -2-
            int isprint(int c)
    
        1- Cette fonction teste si le caractère c est affichable.
        2- Elle est identique à isgraph sauf que ici on prend en considération le caractère d'espacement.
        3- Valeur de retour:
            - une valeur non nulle si c est un caractère affichable (0x20 - 0x7E. Ne prend pas donc
	    le ASCII étendu).
    */

    isprint(' ')? cout << "[ ] est un caractere affichable.\n":cout << "[ ] n'est pas un caractere affichable.\n";


    /*
        Minuscule?
            int islower(int c)
    
        1- Cette fonction teste si le caractère c est un caractère minuscule.
        2- Valeur de retour:
            - une valeur non nulle si c est un caractère minuscule (a-z).
    */

    islower('T')? cout << "[T] est une lettre minuscule.\n":cout << "[T] n'est pas une lettre minuscule.\n";


    /*
        Majuscule?
            int isupper(int c)
    
        1- Cette fonction teste si le caractère c est un caractère majuscule.
        2- Valeur de retour:
            - une valeur non nulle si c est un caractère minuscule (A-Z).
    */

    isupper('T')? cout << "[T] est une lettre majuscule.\n":cout << "[T] n'est pas une lettre majuscule.\n";


    /*
        Ponctuation?
            int ispunct(int c)
    
        1- Cette fonction teste si le caractère c est un caractère de ponctuation.
        2- Valeur de retour:
            - une valeur non nulle si c est un caractère de ponctuation.
    */

    ispunct('?')? cout << "[?] est un caractere de ponctuation.\n":cout << "[?] n'est pas un caractere de ponctuation.\n";

    /*
        Espace?
            int isspace(int c)
    
        1- Cette fonction teste si le caractère c est un caractère d'espacement.
        2- Valeur de retour:
            - une valeur non nulle si c est un espace, une tabulation, un retour chariot, un passage
            à la ligne, une tabulation verticale ou un saut de page (0x09-0x0D, 0x20).
    */

    isspace('\t')? cout << "[\t] est une tabulation.\n":cout << "[\t] n'est pas une tabulation.\n";

    /*
        Hexadécimal?
            int isxdigit(int c)
    
        1- Cette fonction teste si le caractère c est un caractère hexadécimal.
        2- Valeur de retour:
            - une valeur non nulle si c est un un chiffre (0-9, A-F, a-f).
    */

    isxdigit('f')? cout << "[f] est un chiffre hexadecimal.\n":cout << "[f] n'est pas un chiffre hexadecimal.\n";

    return;
}


void Conversion_de_caracteres(){

    /*
        Pour pouvoir utiliser les différentes fonctions décrites dans la fonction "Conversion_de_caracteres",
        il faudra penser à inclure le fichier d'en-tête <cctype>
    */


    /*
        Vers l'ASCII
            int toascii(int c)
    
        1- Cette fonction convertit l'entier c vers l'ASCII.
        2- Une valeur comprise entre 0 et 127.
        3- Valeur de retour:
            - La valeur convertie de l'argument c.
    */

    cout << "La valeur ASCII de [49] est: " << toascii(49) << endl;
    
    /*
        En minuscule
            int tolower(int c)
    
        1- Cette fonction convertit le caractère c en minuscule.
        3- Valeur de retour:
            - La valeur convertie de l'argument c si celui-ci est une lettre majuscule, autrement,
            elle renvoie la valeur inchangée.
    */

    cout << "Minuscule de [G] est: " << (char) tolower('G') << endl;

    /*
        En majuscule
            int toupper(int c)
    
        1- Cette fonction convertit le caractère c en majuscule.
        2- Valeur de retour:
            - La valeur convertie de l'argument c si celui-ci est une lettre minuscule, autrement,
            elle renvoie la valeur inchangée.
    */

    cout << "Majuscule de [g] est: " << (char) toupper('g') << endl;

    
    
    return;
    

}

void Conversion_de_chaines(){
    
    /*
        Pour pouvoir utiliser les différentes fonctions décrites dans la fonction "Conversion_de_chaines",
        il faudra penser à inclure le fichier d'en-tête <cstdlib> et <cmath>
    */

    
    /*
        En virgule flottante
            double atof(const char* s)
    
        1- Cette fonction convertit la chaîne de caractères s en un nombre de type double.
        2- Valeur de retour:
            - Le résultat de la conversion de la chaîne passée en argument.
    */

    const char* s = "Une drole de cuisine!";
    cout << "Le resultat de la conversion de la chaine [Une drole de cuisine!] en virgule flottante est: " << atof(s) << endl;

    /*
        En un entier
            int atoi(const char* s)
    
        1- Cette fonction convertit la chaîne de caractères s en un nombre de type int.
        2- Valeur de retour:
            - Le résultat de la conversion de la chaîne passée en argument.
            - Si la chaîne ne peut pas être convertie en un nombre de type correspondant (int),
	    la valeur renvoyée est 0.
    */

    cout << "Le resultat de la conversion de la chaine [Une drole de cuisine!] en int est: " << atoi(s) << endl;


    /*
        En un long
            long atol(const char* s)
    
        1- Cette fonction convertit la chaîne de caractères s en un nombre de type long.
        2- Valeur de retour:
            - Le résultat de la conversion de la chaîne passée en argument.
            - Si la chaîne ne peut pas être convertie en un nombre de type correspondant (long),
	    la valeur renvoyée est 0.
    */

    cout << "Le resultat de la conversion de la chaine [Une drole de cuisine!] en long est: " << atol(s) << endl;
    cout << "Le resultat de la conversion de la chaine [67548] en long est: " << atol("67548") << endl;

    return;
    
    
}

/*
    ************** Début de la cuisine interne ***************************
*/

/*
    Fonction permettant d'inverser une chaîne
    
    void strreverse(char* debut, char* fin)
    
    1- Cette fonction inverse les caractères d'une chaîne donnée
    2- L'argument "debut" est un pointeur vers le début de la chaîne et l'argument "fin" pointe la fin
    de la chaîne.

*/
void strreverse(char* debut, char* fin) {
    char aux;
    while(fin>debut)
        aux=*fin, *fin--=*debut, *debut++=aux;
}

/*

    Certains compilateurs fournissent la fonction [itoa] qui permet de convertir un nombre entier vers une
    chaîne de caractères. Parce que cette fonction ne fait pas parti de la norme, il se peut que certains
    compilateurs la rejettent.
    Pour cette raison, nous allons définir "notre" propre fonction "itoa" pour contourner cette limite.

    Le code de la fonction "intachaine" ci-dessous est basé sur le livre de [Kernighan & Ritchie] dont
    le titre est [Le Langage C, norme Ansi] avec une légère modification apportée par Stuart Lowe & co.
    au niveau de l'optimisation.

    Fonction permettant de convertir un entier en chaîne de caractères.

        void intachaine(int valeur, char* s, int base);
    
        1- Cette fonction convertit le nombre valeur de type int en une chaîne de caractères terminée par
	un caractère nul et place le résultat dans s.
        2- L'argument base indique dans quelle la conversion doit être effectuée. Un entier compris entre
	2 et 36 inclus.
        3- Il faudra allouer statiquement ou dynamiquement s.
        4- La place allouée à l'argument s doit être suffisamment importante pour contenir la chaîne renvoyée
	ainsi que le caractère d'arrêt (\0).
        5- Cette fonction peut envoyer jusqu'à 17 caractères.
        6- Valeur de retour:
            - Rien.
            - Dans la version fournie par certains compilateurs, la valeur retournée est un pointeur sur s.
*/

void intachaine(int value, char* str, int base) {

    static char num[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    char* wstr=str;
    int sign;
    div_t res;
    
    // On valide la base
    if (base<2 || base>35){
        *wstr='\0'; return;
    }
    
    // On prend soin du signe
    if ((sign=value) < 0) value = -value;
    
    // CConversion. Le nombre est inversé.
    do {
        res = div(value,base);
        *wstr++ = num[res.rem];
    }while((value=res.quot));
    
    if(sign<0) *wstr++='-';
        *wstr='\0';
    
    // On inverse la chaîne
    strreverse(str,wstr-1);

}

/*
    ************** Fin de la cuisine interne ***************************
*/

void Conversion_d1_entier(){
    
    /*
        Pour pouvoir utiliser les différentes fonctions décrites dans la fonction "Conversion_d1_entier",
        il faudra penser à inclure le fichier d'en-tête <cstdlib>
    */

    
    /*
        Vers une chaîne de caractères
            char* itoa(int valeur, char* s, int base);
    
        1- Cette fonction convertit le nombre valeur de type int en une chaîne de caractères terminée par
	un caractère nul et place le résultat dans s.
        2- L'argument base indique dans quelle la conversion doit être effectuée. Un entier compris entre
	2 et 36 inclus.
        3- Il faudra allouer statiquement ou dynamiquement s.
        4- La place allouée à l'argument s doit être suffisamment importante pour contenir la chaîne renvoyée
	ainsi que le caractère d'arrêt (\0).
        5- Cette fonction peut envoyer jusqu'à 17 caractères.
        6- Valeur de retour:
            - Un pointeur sur s.
    */

    int nombre = 12345;
    char unechaine[25];
   
    intachaine(nombre,unechaine,10);  
    cout << "La conversion de [12345] en chaine de caracteres, en base 10, est: " << unechaine << endl;
    
    return;

    
}

int main() {
    
    Traitement_de_chaines();
    Test_de_caracteres();
    Conversion_de_caracteres();
    Conversion_de_chaines();
    Conversion_d1_entier();
    
    return 0;
}



/*

    >char911
    La taille de la chaine Allemagne: 50
    La taille de la chaine Bresil: 29
    La taille reelle de la chaine Allemagne: 100
    Copie Bresil dans Tempo. La chaine resultante est: Champion du monde de football
    Reinitialisation de Tempo avec la chaine Allemagne. La chaine resultante est: Organisateur de la coupe du monde de football 2006
    Copie partielle des 2 premiers caracteres de Bresil dans Tempo.
    La chaine resultante est:Ch
    Le resultat final de concatenation de chaines est: Organisateur de la coupe du monde de football 2006: Allemagne.
    Le resultat de la comparaison des chaines Allemagne et Bresil est: 1
    Le resultat de la comparaison des chaines Allemagne et Bresil est avec maxlen=2: 1
    Le (premier) caractere o est dans la chaine Allemagne?: oupe du monde de football 2006
    Le (dernier) caractere o est dans la chaine Allemagne?: otball 2006
    Trouve le caractere [6] en position [49]
    Clonage reussi et la copie de Allemagne se trouve a cette adresse:0x44a33ff7b8
    La premiere occurrence de la chaine [foot] dans la chaine Allemagne:football 2006
    La longueur du premier segment [nst]: 0
    La longueur du premier segment [nst]: 4
    Token: Organisateur
    Token: de
    Token: la
    Token: c
    Token: upe
    Token: du
    Token: m
    Token: nde
    Token: de
    Token: f
    Token: tball
    Token: 2006
    Allemagne apres traitement: Organisateur
    [W] est un caractere alphanumerique.
    [9] n'est pas un caractere alphabetique.
    [e accent grave] n'est pas un caractere ascii (non etendu).
    [C] est un caractere de controle.
    [7] n'est pas un chiffre.
    [e accent grave] n'est pas un caractere affichable.
    [ ] est un caractere affichable.
    [T] n'est pas une lettre minuscule.
    [T] est une lettre majuscule.
    [?] est un caractere de ponctuation.
    [	] est une tabulation.
    [f] est un chiffre hexadecimal.
    La valeur ASCII de [49] est: 49
    Minuscule de [G] est: g
    Majuscule de [g] est: G
    Le resultat de la conversion de la chaine [Une drole de cuisine!] en virgule flottante est: 0
    Le resultat de la conversion de la chaine [Une drole de cuisine!] en int est: 0
    Le resultat de la conversion de la chaine [Une drole de cuisine!] en long est: 0
    Le resultat de la conversion de la chaine [67548] en long est: 67548
    La conversion de [12345] en chaine de caracteres, en base 10, est: 12345
    >Exit code: 0

*/
