#include "../headers/affichage.h"
#include <time.h>

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

        printf("Date du jour : ");
        affichage_date_du_jour();

        printf("\n\n\n");
        printf("     +===========================================================================+\n");
        printf("     | MEMBRES                                                                   |\n");
        printf("     |     1- Information sur un membre (par identifiant)                        |\n");
        printf("     |     2- Consulter la liste des membres                                     |\n");
        printf("     |     3- Ajouter un membre                                                  |\n");
        printf("     |     4- Supprimer un membre                                                |\n");
        printf("     |                                                                           |\n");
        printf("     | LIVRES                                                                    |\n");
        printf("     |     5- Information sur un livre (par code, titre ou auteur)               |\n");
        printf("     |     6- Consulter la listes des livres (par code, titre ou auteur)         |\n");
        printf("     |     7- Ajouter un livre                                                   |\n");
        printf("     |     8- Supprimer un livre                                                 |\n");
        printf("     |                                                                           |\n");
        printf("     | PRETS                                                                     |\n");
        printf("     |     9- Information sur un pret (par id pret)                              |\n");
        printf("     |    10- Consulter la liste des prêts (en retard, en cours)                 |\n");
        printf("     |    11- Ajouter le pret d'un livre                                         |\n");
        printf("     |    12- Restituer un livre (supprimer le pret)                             |\n");
        printf("     |                                                                           |\n");
        printf("     | ADMINISTRATEURS                                                           |\n");
        printf("     |    13- Consulter la liste des administrateurs                             |\n");
        printf("     |    14- Ajouter un administrateur                                          |\n");
        printf("     |    15- Supprimer un administrateur                                        |\n");
        printf("     |                                                                           |\n");
        printf("     |    16 - Toutes les informations de la librairie                           |\n");
        printf("     |                                                                           |\n");
        printf("     | AUTRES                                                                    |\n");
        printf("     |    17- Reinitialisé toutes les données de la librairie                    |\n");
        printf("     |    18- Notice de l'application (code theme livre, pénalité ...)           |\n");
        printf("     |    19- A propos (créateur ...)                                            |\n");
        printf("     |                                                                           |\n");
        printf("     |     0- Quitter                                                            |\n");
        printf("     +===========================================================================+\n\n");

        printf("                            Choix : ");
        saisie_entier(choix);

        if ((*choix != 0) && (*choix != 1) && (*choix != 2) && (*choix != 3) && (*choix != 4) && (*choix != 5) && (*choix != 6) && (*choix != 7) && (*choix != 8) && (*choix != 9) && (*choix != 10) &&
            (*choix != 11) && (*choix != 12) && (*choix != 13) && (*choix != 14) && (*choix != 15) && (*choix != 16) && (*choix != 17) && (*choix != 18) && (*choix != 19))
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


void affichage_date_du_jour(void)
{
    // system(strcmp(SYSTEME_EXPLOITATION, "win") == 0 ? "echo  %date%-%time%" : "date");

    Date date_du_jour;

    //recuperation de la date du jour
    long int timestamp = (int) time(NULL);

    date_du_jour = definir_date(timestamp);

    afficher_date(&date_du_jour);
}



void affichage_notice() {
    int choix;
    do{
        supr_console();
        affichage_sous_titre("NOTICE DE L'APPLICATION");

        printf("     Cette application est conçu seulement pour les bibliothécaires\n\n");

        printf(" • Comment gerer un membre : \n");
        printf("        Un membre est gerer par son identifiant qui est créé automatiquement lors de l'ajout\n");
        printf("        Un membre peut etre ajouter si l'adresse mail n'est pas deja existante\n");
        printf("        Un membre peut réaliser au maximum trois prets\n");
        printf("        Un membre ne peut pas emprunté de livre s'il a un emprunt en retard\n\n");

        printf(" • Comment gerer un livre : \n");
        printf("        Un livre peut etre ajouter s'il n'est pas existant (c'est a dire si il n'existe pas un livre ayant le meme titre et le meme auteur dans la meme catégorie)\n");
        printf("        Le genre du livre doit correspondre a un des genres enregistrés (sous dorme de XXX comme ci-dessous) :\n");
        printf("                  SFI, ROM, BAD, THE, ESS, MAN, GUI, POE, FAB, NOU, JOU, BIO, CON, TEM (cf : information librairie)\n");
        printf("        Un livre ne peut plus etre enprunté si il n'y a plus d'exemplaire disponible\n");
        printf("        A noter : pour l'ajout d'un genre, contacter le programmeur\n\n");

        printf(" • Comment gerer un pret : \n");
        printf("        Un pret est gerer par son numéro qui est créé automatiquement lors de l'ajout\n");
        printf("        Pour saisie un pret il faut que toutes les caractèristiques evoquées précedemment soit valide\n\n");

        printf(" • Comment gerer les administrateurs : \n");
        printf("        Il est possible d'ajouter et de supprimer autant d'administrateurs que vous désiré\n");
        printf("         Il n'est pas possible de supprimer l'administarteur de référence qui est celui du programmeur\n\n");

        printf(" Il est poissible de reinitialisé toute la librairie (attention cette opération est irréversible\n\n");

        printf(" La sauvegarde des informations ce fait de manière instantannée\n\n");
    
        printf("                  Saisir 1 pour retourner au menu : ");
        saisie_entier(&choix);
    } while (choix != 1);


}