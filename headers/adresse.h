#ifndef adresse_h
#define adresse_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utile.h"


typedef struct {
    char rue[70];
    char code_postal[20];
    char ville[50];
    char pays[50];
} Adresse;

int saisie_adresse(Adresse *a);

void afficher_adresse(Adresse *a);


#endif /* adresse_h */

