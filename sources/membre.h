

#ifndef membre_h
#define membre_h

#include <stdio.h>

#include "livre.h"

typedef struct 
{
    char adresse[50]; //numéro + nom rue
    int code_postal;
    char ville[20];
}Adresse;


typedef struct 
{
    char prenom[20];
    char nom [20];
    Adresse adresse;
    char email[40];
    char metier [30];
    Emprunt liste_emprunt[3];
}Membre;

#endif /* membre_h */

