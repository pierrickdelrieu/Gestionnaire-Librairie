#ifndef pret_h
#define pret_h

#include <stdio.h>
#include "utile.h"
#include "affichage.h"
#include "livre.h"
#include "membre.h"

#define NB_EMPRUNT_MAX 3

typedef struct
{
    int id_pret;
    int id_membre;
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

int saisie_securise_pret_tab_pret(Pret *saisie, Pret **tab_pret, int *nb_pret);

int saisie_champs_pret(Pret *pret);

int saisie_champ_pret_securise(Pret *saisie, Membre **tab_membre, Livre **tab_livre, int *nb_membre, int *nb_livre);

void ajout_pret_fichier_pret(FILE *fichier_pret, Pret *saisie);

void afficher_pret(Pret *pret);

void afficher_toute_info_pret(Pret *pret);


void ajout_pret_struct_membre(Pret *pret, Membre **tab_membre);
void ajout_pret_struct_livre(Pret *pret, Livre **tab_livre);

#endif /* pret_h */