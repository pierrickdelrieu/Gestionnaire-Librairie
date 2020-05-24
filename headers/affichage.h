#ifndef affichage_h
#define affichage_h

#include "date.h"
#include "utile.h"
#include <stdio.h>
#include <time.h>


void affichage_titre_app();

void affichage_sous_titre(char *sous_titre);

void affichage_choix_menu(int *choix);

void erreur_ouverture_fichier();

void affichage_date_du_jour();

void affichage_notice();

void affichage_a_propos();

#endif /* affichage_h */