#ifndef adresse_h
#define adresse_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utile.h"


typedef struct {
    char rue[50];
    char code_postal[6];
    char ville[30];
    char pays[20];
} Adresse;

int saisie_adresse(Adresse *a);

void afficher_adresse(Adresse *a);


#endif /* adresse_h */

