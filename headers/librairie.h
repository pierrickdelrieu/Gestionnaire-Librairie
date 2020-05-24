#ifndef librairie_h
#define librairie_h

#include <stdio.h>
#include <string.h>
#include "livre.h"
#include "pret.h"
#include "utile.h"
#include "admin.h"
#include "membre.h"
#include "affichage.h"

typedef struct
{
    Membre **liste_membre;
    int nb_membre;
} Liste_membre;

typedef struct
{
    Admin **liste_admin;
    int nb_admin;
} Liste_admin;

typedef struct
{
    Livre **liste_livre;
    int nb_livre;
} Liste_livre;

typedef struct
{
    Pret **liste_pret;
    int nb_pret;
} Liste_pret;

void reinitialise_librairie(int tab_donnee[2], Donnee_livre *donnee_livre, Liste_admin *gestion_admin, Liste_membre *gestion_membre, Liste_livre *gestion_livre, Liste_pret *gestion_pret);

typedef struct
{
    int donnee[2];  // donnee[0] = nombre de membre depuis l'ouverture de la librairie
                    // donnee[1] = nombre de pret depuis l'ouverture de la librairie
    Donnee_livre donne_livre;
    Liste_admin gestion_admin;
    Liste_membre gestion_membre;
    Liste_livre gestion_livre;
    Liste_pret gestion_pret;
} Librairie;

void connexion(Admin **tab_admin, int *nb_identifiant);

void creer_tab_donnee(int tab[2], Donnee_livre *donne_livre);

void rafrachir_fichier_donnee(int *tab, Donnee_livre *donne_livre);

// Admin
void saisie_nx_admin(Admin ***tab_admin, int *nb_identifiant);
void supr_admin(Admin ***tab_admin, int *nb_identifiant);
void affichage_liste_admin(Admin ***tab_identifiant, int *nb_identifiant);

// Membre
void saisie_nx_membre(Membre ***tab_membre, int *nb_membre, int tab_donnee[2], Donnee_livre *donnee_livre);
void supr_membre(Membre ***tab_membre, int *nb_membre);
void affichage_liste_membre(Membre **tab_membre, int *nb_membre);
void affichage_info_membre(Liste_membre *gestion_membre, Liste_pret *gestion_pret, Liste_livre *gestion_livre);

// Livre
void saisie_nx_livre(Livre ***tab_livre, int *nb_livre, Donnee_livre *donnee_livre, int *donnee);
void supr_livre(Livre ***tab_livre, int *nb_livre, int *donnee, Donnee_livre *donnee_livre);
void affichage_info_livre(Liste_livre *gestion_livre, Liste_membre *gestion_membre, Liste_pret *gestion_pret);
void affichage_liste_livre(Livre **tab_livre, int *nb_livre);

// Pret
void saisie_nx_pret(Liste_membre *gestion_membre, Liste_livre *gestion_livre, Liste_pret *gestion_pret, int tab_donnee[2], Donnee_livre *donne_livre);
void supr_pret(Liste_pret *gestion_pret, Liste_livre* gestion_livre, Liste_membre *gestion_membre);
void affichage_liste_pret(Liste_pret *gestion_pret, Liste_livre *gestion_livre, Liste_membre *gestion_membre);
void affichage_info_pret(Liste_pret *gestion_pret, Liste_membre *gestion_membre, Liste_livre *gestion_livre);

#endif /* librairie_h */