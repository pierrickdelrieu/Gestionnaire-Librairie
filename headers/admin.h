

#ifndef admin_h
#define admin_h

#include "utile.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct 
{
    int identifiant;
    char mot_de_passe[30];
}Admin;

//recup données sauvegardées
void recup_admin(Admin** tab_identifiant, int* nb_identifiant);
void affichage_tab_admin(Admin* tab_identifiant, int* nb_identifiant);


void saisie_identifiant(Admin* admin);


#endif /* admin_h */

