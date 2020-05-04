

#ifndef librairie_h
#define librairie_h

#include <stdio.h>
#include "livre.h"
#include "utile.h"
#include "admin.h"
#include "membre.h"
#include "affichage.h"

typedef struct {
    Membre **liste_membre;
    int *tri_membre;
    int nb_membre;
}Liste_membre;

typedef struct {
    Admin **liste_admin;
    int nb_admin;
}Liste_admin;


typedef struct {
    Liste_admin gestion_admin;
    Liste_membre gestion_membre;

    Livre **liste_livre;
    Pret **liste_pret;
    int nb_livre;
    int nb_pret;
} Librairie;

void connexion();

void saisie_nx_admin(Admin ***tab_admin, int *nb_identifiant);
void supr_admin(Admin ***tab_admin, int *nb_identifiant);
void affichage_liste_admin(Admin ***tab_identifiant, int *nb_identifiant);

void saisie_nx_membre(Membre ***tab_membre, int *nb_membre);
void affichage_liste_membre(Membre **tab_membre, int* tri_tab, int *nb_membre);


#endif /* librairie_h */