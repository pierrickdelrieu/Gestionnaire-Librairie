

#ifndef librairie_h
#define librairie_h

#include <stdio.h>
#include "livre.h"
#include "membre.h"

typedef struct 
{
    Date date_du_jour;
    Livre* liste_livre;
    Membre* liste_membre;
    Pret* liste__prets;
}Librairie;


#endif /* librairie_h */