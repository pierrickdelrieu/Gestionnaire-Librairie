

#ifndef librairie_h
#define librairie_h

#include <stdio.h>
#include "livre.h"
#include "membre.h"
#include "utile.h"


typedef struct 
{
    Date date_du_jour;
    Livre* liste_livre;
    int nb_livre;
    Membre* liste_membre;
    int nb_membre;
    Pret* liste_pret;
    int nb_pret;
}Librairie;



#endif /* librairie_h */