#ifndef livre_h
#define livre_h

#include <stdio.h>
#include "utile.h"

typedef struct {
    char titre[20];
    char auteur[20];
    char code[7];
    int nb_exemplaires; //total
    int nb_exemplaires_dispo;
} Livre;

//fonction Date
void saisir_date(Date *d);

void afficher_date(Date *d);

int compare_date(Date *d1, Date *d2);

#endif /* livre_h */