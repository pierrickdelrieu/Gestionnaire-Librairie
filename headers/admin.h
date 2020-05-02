

#ifndef admin_h
#define admin_h

#include "utile.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    long identifiant;
    char mot_de_passe[30];
}Admin;

//recup données sauvegardées
void calcul_nb_admin(int* nb_identifiant);

Admin* creer_struct_admin();
void lib_struct_admin(Admin* admin);

Admin** creer_tab_admin(int* nb_identifiant);
void lib_tab_admin(Admin** tab_admin, int* nb_identifiant);
void affichage_tab_admin(Admin** tab_identifiant, int* nb_identifiant);

void saisie_identifiant(Admin* admin);
void saisie_nx_admin();
void connexion(Admin** tab_admin, int* nb_identifiant);


#endif /* admin_h */

