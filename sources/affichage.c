
#include "../headers/affichage.h"


void affichage_titre_app(){
    printf("                               .......................................\n");
    printf("                               .     GESTIONAIRE DE BIBLIOTHEQUE     .\n");
    printf("                               .......................................\n\n\n");
}

int affichage_choix_menu(Date* date_du_jour, int* choix){
    int valide = TRUE;

    affichage_titre_app();
    printf("La date du jour est : ");
    afficher_date(date_du_jour);

    printf("\n\n\n");
    printf("     =============================================================================\n");
    printf("     |    1- Consulter la liste des membres                                      |\n");
    printf("     |    2- Ajouter un membre                                                   |\n");
    printf("     |    3- Supprimer un membre                                                 |\n");
    printf("     |                                                                           |\n");
    printf("     |    4- Consulter la liste des livres                                       |\n");
    printf("     |    5- Ajouter un livre                                                    |\n");
    printf("     |    6- Supprimer un livre                                                  |\n");
    printf("     |                                                                           |\n");
    printf("     |    7- Consulter la liste des prêts                                        |\n");
    printf("     |    8- Ajouter le pret d'un livre                                          |\n");
    printf("     |    9- Restituer un livre (supprimer le pret)                              |\n");
    printf("     |                                                                           |\n");
    printf("     |    10- Consulter la liste des administrateurs de la librairie             |\n");
    printf("     |    11- Ajouter un administrateur de la librairie                          |\n");
    printf("     |    12- Supprimer un administrateur de la librairie                        |\n");
    printf("     |                                                                           |\n");
    printf("     |    0- Quitter                                                             |\n");
    printf("     =============================================================================\n\n");
    
    printf("                            Choix : ");
    scanf(" %d", choix);

    if((*choix != 0) && (*choix != 1) && (*choix != 2) && (*choix != 3) && (*choix != 4) && (*choix != 5) && (*choix != 6) && (*choix != 7) && (*choix != 8) && (*choix != 9) && (*choix != 10) && (*choix != 11) && (*choix != 12)){
        valide = FALSE;
    }

    return (valide);

}


void affichage_sous_titre(char* sous_titre){
    printf("          ----- %s -----\n\n\n",sous_titre);
}