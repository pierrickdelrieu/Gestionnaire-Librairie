#ifndef livre_h
#define livre_h

#include <stdio.h>
#include "utile.h"

typedef struct {
    char titre[20];
    char auteur[20];
    int code;
    int nb_exemplaires; //total
    int nb_exemplaires_dispo;
} Livre;

Livre *creer_struct_livre();

Livre **creer_tab_livre(int *nb_livre);

void lib_struct_livre(Livre *livre);

int saisie_securise_livre_tab_livre(Livre *saisie, Livre **tab_livre, int *nb_livre, int *nb_livre_totale);

int saisie_champs_livre(Livre *livre, int *nb_livre);

void ajout_livre_fichier_livre(FILE *fichier_livre, Livre *saisie);

int saisie_id_livre_tab_livre(Livre **tab_livre, int *id_livre, int *nb_livre);

void lib_tab_livre(Livre **tab_livre, int *nb_livre);

void calcul_nb_livre(int *nb_livre);

void rafrachir_tab_livre(Livre ***tab_livre, int *nb_livre);

void afficher_toute_info_livre(Livre *livre);

void afficher_livre(Livre *livre);

//fonction Date
// todo: a supprimer/deplacer
void saisir_date(Date *d);

void afficher_date(Date *d);

int compare_date(Date *d1, Date *d2);

#endif /* livre_h */