

#ifndef librairie_h
#define librairie_h

#include <stdio.h>
#include "livre.h"
#include "membre.h"

typedef struct 
{
    Livre* liste_livre;
    Membre* liste_membre;
}Libraire;


#endif /* librairie_h */