

#ifndef librairie_h
#define librairie_h

#include <stdio.h>
#include "livre.h"
#include "utile.h"
#include "admin.h"
#include "membre.h"
#include "affichage.h"


typedef struct 
{
    Admin** liste_admin;
    Livre** liste_livre;
    Membre** liste_membre;
    Pret** liste_pret;
    int nb_admin;
    int nb_livre;
    int nb_membre;
    int nb_pret;
}Librairie;

void connexion();
void saisie_nx_admin(Admin*** tab_admin, int* nb_identifiant);
void supr_admin(Admin*** tab_admin, int* nb_identifiant);
void affichage_liste_admin(Admin** tab_identifiant, int* nb_identifiant);


#endif /* librairie_h */