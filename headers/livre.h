#ifndef livre_h
#define livre_h

#include <stdio.h>
#include <stdlib.h>

#include "utile.h"
#include "affichage.h"

#define NB_GENRE_LIVRE 14

typedef struct 
{
    char liste_code[14][4]; //contient tout les genres de livres
    int nb_livre[14]; //contient le nombre de livre du genre
}Donnee_livre;

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
int saisie_securise_livre_not_in_tab_livre(Livre *saisie, Livre **tab_livre, int *nb_livre, Donnee_livre *donnee_livre);

//Saisie et affichage livre
int saisie_code_livre(char code[8]);
int verif_code_livre(char* code);
int saisie_champs_livre(Livre *livre, Donnee_livre *donne_livre);
void afficher_livre(Livre *livre);
void afficher_toute_info_livre(Livre *livre);

//Fichier livres.txt
void ajout_livre_fichier_livre(FILE *fichier_livre, Livre *saisie);
void supr_livre_fichier_livre(FILE *fichier_livre, char *code, Livre **tab_livre, int *nb_livre);

void rafraichir_fichier_livre(FILE *fichier_livre, Livre **tab_livre, int *nb_livre);

void affichage_titre_auteur_code_livre(char *code_livre, Livre **tab_livre);

int saisie_genre_livre_securise(char *code_livre, Donnee_livre *donne_livre);



//fonction de tri
void creation_tab_tri_livre(int type_tri, int* tab_tri, Livre **tab_livre, int *nb_livre);
void init_tab_tri_livre_code(int* tab_tri, Livre **tab_livre, int *nb_livre);
void init_tab_tri_livre_titre(int* tab_tri, Livre **tab_livre, int *nb_livre);
void init_tab_tri_livre_auteur(int* tab_tri, Livre **tab_livre, int *nb_livre);


// fonction de securisation pour info sur livre
int saisie_info_livre_critere(int type_tri, char *recherche, Livre **tab_livre, int *nb_livre);
int saisie_securise_titre(char *recherche, Livre **tab_livre, int *nb_livre);
int saisie_securise_code(char *recherche, Livre **tab_livre, int *nb_livre);

#endif /* livre_h */