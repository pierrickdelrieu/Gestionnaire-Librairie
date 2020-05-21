#ifndef livre_h
#define livre_h

#include <stdio.h>
#include <stdlib.h>

#include "utile.h"
#include "affichage.h"

typedef struct {
    char titre[40];
    char auteur[40];
    char code[9]; //XXX-YYY\0
    int nb_exemplaires; //total
    int nb_exemplaires_dispo;
} Livre;

Livre *creer_struct_livre();
void lib_struct_livre(Livre *livre);

//Tableau de livre
Livre **creer_tab_livre(int *nb_livre);
void lib_tab_livre(Livre **tab_livre, int *nb_livres);
void calcul_nb_livre(int *nb_livre);
void rafrachir_tab_livre(Livre ***tab_livre, int *nb_livre);
int verif_code_livre_in_tab_libre(Livre **tab_livre, char* code_livre, int *nb_livre);
int saisie_securise_livre_not_in_tab_livre(Livre *saisie, Livre **tab_livre, int *nb_livre);

//Saisie et affichage livre
int saisie_code_livre(char code[8]);
int verif_code_livre(char* code);
int saisie_champs_livre(Livre *livre);
void afficher_livre(Livre *livre);
void afficher_toute_info_livre(Livre *livre);

//Fichier livres.txt
void ajout_livre_fichier_livre(FILE *fichier_livre, Livre *saisie);
void supr_livre_fichier_livre(FILE *fichier_livre, char *code, Livre **tab_livre, int *nb_livre);

void rafraichir_fichier_livre(FILE *fichier_livre, Livre **tab_livre, int *nb_livre);

void affichage_titre_auteur_code_livre(char *code_livre, Livre **tab_livre);

#endif /* livre_h */