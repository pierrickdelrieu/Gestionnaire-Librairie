

#ifndef livre_h
#define livre_h

#include <stdio.h>

typedef struct 
{
    int jour;
    int mois;
    int annee;
}Date;


typedef struct 
{
    char titre[20];
    char auteur[20];
    char code[7];
    int nb_exemplaires; //total
    int nb_exemplaires_dispo;
}Livre;

typedef struct 
{
    char code[7];
    Date date_pret;
}Emprunt;


#endif /* livre_h */