

#ifndef membre_h
#define membre_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "livre.h"
#include "utile.h"


typedef struct {
    char adresse[50]; //numéro + nom rue
    char code_postal[6];
    char ville[20];
    char pays[20];
} Adresse;

int saisie_adresse(Adresse *a);

void afficher_adresse(Adresse *a);


typedef struct {
    char prenom[20];
    char nom[20];
    int identifiant; //id à 8 chiffres générer de manière aléatoire lors de l'inscription d'un nouveau membre
    Adresse adresse;
    char email[40];
    char metier[30];
    Pret liste_emprunt[3];
} Membre;

// void generateur_identifiant(int* identifiant, Librairie* librairie);
Membre *creer_struct_membre();
void lib_struct_membre(Membre *membre);

void calcul_nb_membre(int *nb_membre);

Membre **creer_tab_membre(int *nb_membre);
void lib_tab_membre(Membre **tab_membre, int *nb_membres);

int saisie_id_membre(int* id_membre, int* nb_membre);
int saisie_champs_membre(Membre *membre, int* nb_membres);
void afficher_membre(Membre *membre);

#endif /* membre_h */

