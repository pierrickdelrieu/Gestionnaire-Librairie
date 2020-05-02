
#include <stdio.h>
#include <string.h>
#include "../headers/librairie.h"


int main()
{
    Admin** tab_identifiant = NULL;
    int nb_identifiant;
    calcul_nb_admin(&nb_identifiant);

    tab_identifiant = creer_tab_admin(&nb_identifiant);
    tab_identifiant = saisie_nx_admin(tab_identifiant, &nb_identifiant);
    affichage_tab_admin(tab_identifiant, &nb_identifiant);
    tab_identifiant = supr_admin(tab_identifiant, &nb_identifiant);

    affichage_tab_admin(tab_identifiant, &nb_identifiant);
    // supr_console();
    // connexion(tab_identifiant, &nb_identifiant);

    lib_tab_admin(tab_identifiant,&nb_identifiant);
    
    return 0;
}