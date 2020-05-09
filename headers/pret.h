#ifndef pret_h
#define pret_h

#include <stdio.h>
#include "utile.h"
#include "livre.h"
#include "affichage.h"

#define NB_EMPRUNT_MAX 3

typedef struct
{
    int id_pret;
    int id_utilisateur;
    char code_livre[7];
    int date_pret;   // timestamp
    int date_retour; // timestamp
    int etat_livre;  //1 si livre en retard et 0 sinon
} Pret;

Pret *creer_struct_pret();

void lib_struct_pret(Pret *pret);

void rafrachir_tab_pret(Pret ***tab_pret, int *nb_pret);

Pret **creer_tab_pret(int *nb_pret);

void calcul_nb_pret(int *nb_pret);

void lib_tab_pret(Pret **tab_pret, int *nb_pret);

void ajout_pret_fichier_pret(Pret *saisie);

#endif /* pret_h */