
#include <stdio.h>
#include <string.h>
#include "../headers/librairie.h"


int main()
{
    //.....................Initialisation.....................
    int valide;

    //Initialisation structure librairie
    Librairie bibliotheque;

    //initialisation nb admin et tab admin
    int nb_identifiant;
    int choix_menu;
    calcul_nb_admin(&nb_identifiant);
    bibliotheque.liste_admin = creer_tab_admin(&(bibliotheque.nb_admin));

    

    //.....................Gestion.librairie.....................

    //Connexion
    connexion(bibliotheque.liste_admin, &(bibliotheque.nb_admin));
    supr_console();

    //Saisie date du jour
    affichage_titre_app();
    printf("Connexion reuissi !\n\n");
    printf("Saisir la date du jour : \n"); 
    saisir_date(&(bibliotheque.date_du_jour));

    //Boucle de consultation de la librairie
    int continuer = TRUE;
    while(continuer == TRUE){
        do{
            supr_console();
            valide = affichage_choix_menu(&(bibliotheque.date_du_jour), &choix_menu);
        }while(valide == FALSE);

        if(choix_menu == 0){ //quitter
            continuer = FALSE;
        }
        else{
            //Membres
            if(choix_menu == 1){ //consulter la liste des membres
                printf("Consulter liste membres\n");
            }
            else if(choix_menu == 2){ //ajouter un membre
                printf("Ajouter un membre\n");
            }
            else if(choix_menu == 3){ //supprimer un membre
                printf("Supprimer un membre\n");
            }

            //Livres
            else if(choix_menu == 4){ //consulter la liste des livres
                printf("Consulter liste livres\n");
            }
            else if(choix_menu == 5){ //ajouter un livre
                printf("Ajouter un livre\n");
            }
            else if(choix_menu == 6){ //supprimer un livre
                printf("Supprimer un livre\n");
            }

            //Prêts
            else if(choix_menu == 7){ //consulter la liste des prets
                printf("Consulter liste prets\n");
            }
            else if(choix_menu == 8){ //ajouter un pret
                printf("Ajouter un pret\n");
            }
            else if(choix_menu == 9){ //supprimer un pret
                printf("Supprimer un pret\n");
            }

            //Administrateurs
            else if(choix_menu == 10){ //consulter la liste des administrateurs
                printf("Consulter liste administarteurs\n");
            }
            else if(choix_menu == 11){ //ajouter un admin
                printf("Ajouter un administarteur\n");
            }
            else if(choix_menu == 12){ //supprimer un admin
                printf("Supprimer un administarteur\n");
            }
            
        }


    

    // tab_identifiant = saisie_nx_admin(bibliotheque.liste_admin, &(bibliotheque.nb_admin));
    // affichage_tab_admin(bibliotheque.liste_admin, &(bibliotheque.nb_admin));
    // tab_identifiant = supr_admin(bibliotheque.liste_admin, &(bibliotheque.nb_admin));

    }

    //.....................Desalocation.memoire.....................
    lib_tab_admin(bibliotheque.liste_admin, &(bibliotheque.nb_admin));
    
    return 0;
}