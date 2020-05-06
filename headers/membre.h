#ifndef membre_h
#define membre_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "livre.h"
#include "adresse.h"
#include "utile.h"
#include "affichage.h"


typedef struct {
    char prenom[40];
    char nom[40];
    int identifiant; //id à 8 chiffres générer de manière aléatoire lors de l'inscription d'un nouveau membre
    Adresse adresse;
    char email[40];
    char metier[40];
    int liste_emprunt[3];
} Membre;

// void generateur_identifiant(int* identifiant, Librairie* librairie);
Membre *creer_struct_membre();

void lib_struct_membre(Membre *membre);

void calcul_nb_membre(int *nb_membre);

Membre **creer_tab_membre(int *nb_membre);

void lib_tab_membre(Membre **tab_membre, int *nb_membres);

int saisie_id_membre_tab_membre(Membre **tab_membre, int *id_membre, int *nb_membre);

int saisie_champs_membre(Membre *membre, int *nb_membres);

void afficher_membre(Membre *membre);

void afficher_toute_info_membre(Membre *membre);

int saisie_securise_membre_tab_membre(Membre *saisie, Membre **tab_membre, int *nb_membre, int *nb_membre_totale);

void ajout_membre_fichier_membre(FILE *fichier_membre, Membre *saisie);

void supr_membre_fichier_membre(FILE *fichier_membre, int *id_membre, Membre **tab_membre, int *nb_membre);

void rafrachir_tab_membre(Membre ***tab_membre, int *nb_membre);

int *creer_tri_tab_membre(Membre **liste_membre, int *nb_membre);


#endif /* membre_h */

