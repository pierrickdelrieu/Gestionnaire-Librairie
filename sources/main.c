
#include <stdio.h>
#include <string.h>
#include "../headers/librairie.h"


int main()
{
    Admin** tab_identifiant = NULL;
    int nb_identifiant = 1;

    tab_identifiant = creer_tab_admin(&nb_identifiant);

    affichage_tab_admin(tab_identifiant, &nb_identifiant);
    
    return 0;
}