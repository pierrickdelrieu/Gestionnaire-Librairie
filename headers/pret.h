#ifndef pret_h
#define pret_h

#include <stdio.h>
#include "utile.h"
#include "affichage.h"
#include "livre.h"
#include "membre.h"

#define NB_EMPRUNT_MAX 3 




//Structure d'un pret
typedef struct{
    int id_pret;
    int id_membre;
    char code_livre[7]; //genre - num livre dans le genre
    Date date_pret;   // timestamp
    Date date_retour; // timestamp + 3 semaines
    int etat_livre;  //1 si livre a jour et 0 sinon 
} Pret;


//Structure du tableau de pret
typedef struct{
    Pret **liste_pret;
    int nb_pret;
} Liste_pret;

Pret *creer_struct_pret();
void lib_struct_pret(Pret *pret);


//Fontion du tableau de pret
void rafrachir_tab_pret(Pret ***tab_pret, int *nb_pret);
Pret **creer_tab_pret(int *nb_pret);
void calcul_nb_pret(int *nb_pret);
void lib_tab_pret(Pret **tab_pret, int *nb_pret);


//Fontion relative a la structure pret
int saisie_champs_pret(Pret *pret, int *donnee);
void afficher_pret(Pret *pret, Membre **tab_membre, Livre **tab_livre, int *nb_membre, int *nb_livre);
void afficher_toute_info_pret(int *id_pret, Pret **tab_pret, int *nb_pret, Livre **tab_livre, int *nb_livre, Membre **tab_membre, int *nb_membre);


//Fonction de sauveagrde dans le fichiers
void ajout_pret_fichier_pret(FILE *fichier_pret, Pret *saisie);
void rafraichir_fichier_pret(Pret **tab_pret, int *nb_pret);
void supr_pret_fichier_pret(FILE *fichier_pret, int *id_pret, Pret **tab_pret, int *nb_pret);


//Fontion de saisie securise pour l'ajout, la consultation ou l'affichage d'un pret
int saisie_champ_pret_securise_ajout(Pret *saisie, Membre **tab_membre, Livre **tab_livre, Pret **tab_pret, int *nb_membre, int *nb_livre, int *nb_pret, int *donnee);;
int saisie_id_pret_securise(int *id_pret, Pret **tab_pret, int *nb_pret);


//Pret en retard
int membre_nb_pret_retard(Pret **tab_pret, int *nb_pret, Membre **tab_membre, int *id_membre);
void actualisation_pret_en_retard(Pret **tab_pret, int *nb_pret);
int calcul_nb_pret_total_retard(Pret **tab_pret, int *nb_pret);


//Affichage, ajout et supression des prets pour les membres et pour les livres
void affichage_info_pret_membre(Membre *membre, Pret **tab_pret, int *nb_pret, Livre **tab_livre, int *nb_livre);
void affichage_info_pret_livre(Livre *livre, Pret **tab_pret, int *nb_pret, Membre **tab_membre, int *nb_membre);
void ajout_pret_struct_membre(Pret *pret, Membre **tab_membre);
void ajout_pret_struct_livre(Pret *pret, Livre **tab_livre);
void supr_pret_struct_membre(Pret *pret, Membre **tab_membre);
void supr_pret_struct_livre(Pret *pret, Livre **tab_livre);


#endif /* pret_h */