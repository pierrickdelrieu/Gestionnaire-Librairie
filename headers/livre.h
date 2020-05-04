

#ifndef livre_h
#define livre_h

#include <stdio.h>
#include "utile.h"

#define NB_EMPRUNT_MAX 3;


typedef struct {
    int jour;
    int mois;
    int annee;
} Date;


typedef struct {
    char titre[20];
    char auteur[20];
    char code[7];
    int nb_exemplaires; //total
    int nb_exemplaires_dispo;
} Livre;

typedef struct {
    int id_pret;
    int id_utilisateur;
    char code_livre[7];
    Date date_pret;
    Date date_retour;
    int etat_livre; //1 si livre en retard et 0 sinon
} Pret;


//fonction Date
void saisir_date(Date *d);

void afficher_date(Date *d);

int compare_date(Date *d1, Date *d2);

#endif /* livre_h */