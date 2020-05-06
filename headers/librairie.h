#ifndef librairie_h
#define librairie_h

#include <stdio.h>
#include "livre.h"
#include "pret.h"
#include "utile.h"
#include "admin.h"
#include "membre.h"
#include "affichage.h"

typedef struct {
    Membre **liste_membre;
    int nb_membre;
} Liste_membre;

typedef struct {
    Admin **liste_admin;
    int nb_admin;
} Liste_admin;

typedef struct {
    Livre **liste_livre;
    int nb_livre;
} Liste_livre;

typedef struct {
    Pret **liste_pret;
    int nb_pret;
} Liste_pret;

void reinitialise_librairie(int tab_donnee[2], Membre ***tab_membre, int *nb_membre, Admin ***tab_admin, int *nb_admin);

typedef struct {
    int donnee[2];  //donnee[0] = nombre de membre depuis l'ouverture de la librairie
    // donnee[1] = nombre de livre depuis l'ouverture de la librairie
    Liste_admin gestion_admin;
    Liste_membre gestion_membre;
    Liste_livre gestion_livre;
    Liste_pret gestion_pret;
} Librairie;

void connexion(Admin **tab_admin, int *nb_identifiant);

void creer_tab_donnee(int tab[2]);

void rafrachir_fichier_donnee(int tab[2]);


// Admin

void saisie_nx_admin(Admin ***tab_admin, int *nb_identifiant);

void supr_admin(Admin ***tab_admin, int *nb_identifiant);

void affichage_liste_admin(Admin ***tab_identifiant, int *nb_identifiant);


// Membre

void saisie_nx_membre(Membre ***tab_membre, int *nb_membre, int tab_donnee[2]);

void supr_membre(Membre ***tab_membre, int *nb_membre);

void affichage_liste_membre(Membre **tab_membre, int *nb_membre);

void affichage_info_membre(Membre **tab_membre, int *nb_membre);


// Livre

void affichage_info_livre(Livre **tab_livre, int *nb_livre);

void affichage_liste_livre(Livre **tab_livre, int *nb_livre);

void saisie_nx_livre(Livre ***tab_livre, int *nb_livre, int tab_donnee[2]);

#endif /* librairie_h */