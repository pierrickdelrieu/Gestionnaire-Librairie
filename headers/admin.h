#ifndef admin_h
#define admin_h

#include "utile.h"
#include "affichage.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//id et mp programmeur
#define ID_PROGRAMMEUR 20190551
#define MP_PROGRAMMEUR "pierrick"

//Structure administrateur
typedef struct
{
    int identifiant; //entier a 8 chiffres
    char mot_de_passe[30];
} Admin;

Admin *creer_struct_admin();
void lib_struct_admin(Admin *admin);

int saisie_identifiant(Admin *admin);
int saisie_securise_id_tab_admin(Admin *saisie, Admin **tab_admin, int *nb_identifiant);

//Creation, libération, modification et affichage du tableau d'admin
Admin **creer_tab_admin(int *nb_identifiant);
void lib_tab_admin(Admin **tab_admin, int *nb_identifiant);
void rafrachir_tab_admin(Admin ***tab_admin, int *nb_identifiant);
void affichage_tab_admin(Admin **tab_identifiant, int *nb_identifiant);

//Ajout et suppresion admin dans le fichier admin.txt
void ajout_admin_fichier_admin(FILE *fichier_admin, Admin *saisie);
void supr_admin_fichier_admin(FILE *fichier_admin, Admin **tab_admin, Admin *saisie, int *nb_identifiant);
void calcul_nb_admin(int *nb_identifiant);

#endif /* admin_h */
