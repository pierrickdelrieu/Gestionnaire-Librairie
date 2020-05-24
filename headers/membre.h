#ifndef membre_h
#define membre_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "livre.h"
#include "adresse.h"
#include "utile.h"
#include "affichage.h"

#define NB_EMPRUNT_MAX 3



//Stucture d'un membre
typedef struct {
    char prenom[40];
    char nom[40];
    int identifiant; //id créé automatiquement a partir du fichier donnée 
    Adresse adresse;
    char email[40];
    char metier[40];
    int liste_emprunt[3];
} Membre;


//Structure de tableau de membre
typedef struct{
    Membre **liste_membre;
    int nb_membre;
} Liste_membre;


Membre *creer_struct_membre();
void lib_struct_membre(Membre *membre);
int saisie_champs_membre(Membre *membre, int *nb_membres);
void afficher_membre(Membre *membre);
void afficher_toute_info_membre(Membre *membre);
int calcul_nb_pret_membre(Membre *membre);
void affichage_prenom_nom_id_membre(int *id_membre, Membre **tab_membre);


//Creation, libération, modification et affichage du tableau de membre
Membre **creer_tab_membre(int *nb_membre);
void lib_tab_membre(Membre **tab_membre, int *nb_membres);
void rafrachir_tab_membre(Membre ***tab_membre, int *nb_membre);


//Fonction de saisie securisé pour l'ajout ou la supression d'un membre
int saisie_id_membre_tab_membre(Membre **tab_membre, int *id_membre, int *nb_membre);
int saisie_securise_membre_tab_membre(Membre *saisie, Membre **tab_membre, int *nb_membre, int *nb_membre_totale);


//Fontion de tri pour l'affichage des membres dans l'ordre alphabétique
void init_tab_tri_ordre_alpha(Membre **tab_membre, int *tab, int *nb_membre);


//Ajout et suppresion membre dans le fichier membre.txt
void ajout_membre_fichier_membre(FILE *fichier_membre, Membre *saisie);
void supr_membre_fichier_membre(FILE *fichier_membre, int *id_membre, Membre **tab_membre, int *nb_membre);
void calcul_nb_membre(int *nb_membre);
void rafraichir_fichier_membre(FILE *fichier_membre, Membre **tab_membre, int *nb_membre);

#endif /* membre_h */

