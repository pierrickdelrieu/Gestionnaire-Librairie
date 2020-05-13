#include "../headers/affichage.h"

void affichage_titre_app()
{
    printf("                        .......................................\n");
    printf("                        .     GESTIONAIRE DE BIBLIOTHEQUE     .\n");
    printf("                        .......................................\n\n\n");
}

void affichage_choix_menu(int *choix)
{
    int valide;

    do
    {
        supr_console();
        valide = TRUE;
        affichage_titre_app();
        affichage_date_du_jour();

        printf("\n\n\n");
        printf("     +===========================================================================+\n");
        printf("     |     1- Information sur un membre                                          |\n");
        printf("     |     2- Consulter la liste des membres                                     |\n");
        printf("     |     3- Ajouter un membre                                                  |\n");
        printf("     |     4- Supprimer un membre                                                |\n");
        printf("     |                                                                           |\n");
        printf("     |     5- Information sur un livre                                           |\n");
        printf("     |     6- Consulter la listes des livres                                     |\n");
        printf("     |     7- Ajouter un livre                                                   |\n");
        printf("     |     8- Supprimer un livre                                                 |\n");
        printf("     |                                                                           |\n");
        printf("     |     9- Consulter la liste des prêts                                       |\n");
        printf("     |    10- Ajouter le pret d'un livre                                         |\n");
        printf("     |    11- Restituer un livre (supprimer le pret)                             |\n");
        printf("     |                                                                           |\n");
        printf("     |    12- Consulter la liste des administrateurs de la librairie             |\n");
        printf("     |    13- Ajouter un administrateur de la librairie                          |\n");
        printf("     |    14- Supprimer un administrateur de la librairie                        |\n");
        printf("     |                                                                           |\n");
        printf("     |    15- Reinitialisé toutes les données de la librairie                    |\n");
        printf("     |                                                                           |\n");
        printf("     |     0- Quitter                                                            |\n");
        printf("     +===========================================================================+\n\n");

        printf("                            Choix : ");
        saisie_entier(choix);

        if ((*choix != 0) && (*choix != 1) && (*choix != 2) && (*choix != 3) && (*choix != 4) && (*choix != 5) && (*choix != 6) && (*choix != 7) && (*choix != 8) && (*choix != 9) && (*choix != 10) &&
            (*choix != 11) && (*choix != 12) && (*choix != 13) && (*choix != 14) && (*choix != 15))
        {
            valide = FALSE;
        }

    } while (valide == FALSE);
}

/*affichage des sous titre de l'application*/
void affichage_sous_titre(char *sous_titre)
{
    printf("                    ----- %s -----\n\n\n", sous_titre);
}

/*affichage message d'erreur lors de l'ouverture et fin du programme car pas possible de continuer
les valeurs n'ont pas réussi a etre recupérées ou sauvegardées*/
void erreur_ouverture_fichier()
{
    printf("Erreur au niveau de l'ouverture du fichier\n");
    printf("Le programme n'a pas les autorisations nécessaire pour acceder aux fichiers de votre ordinateur\n");
    printf("Gerer ceci dans les préférence de votre ordinateur\n");
    exit(0); //Fin du programme
}