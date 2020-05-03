

#ifndef librairie_h
#define librairie_h

#include <stdio.h>
#include "livre.h"
#include "utile.h"
#include "admin.h"
#include "membre.h"
#include "affichage.h"


typedef struct 
{
    Date date_du_jour;
    Admin** liste_admin;
    Livre** liste_livre;
    Membre** liste_membre;
    Pret** liste_pret;
    int nb_admin;
    int nb_livre;
    int nb_membre;
    int nb_pret;
}Librairie;



#endif /* librairie_h */