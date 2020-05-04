
#include <stdio.h>
#include <string.h>
#include "../headers/librairie.h"


int main() {
    //.....................Initialisation.....................
    int valide;

    //Initialisation structure librairie
    Librairie bibliotheque;

    //initialisation nb admin et tab admin
    int choix_menu;

    //Recupération des sauvegardes
    calcul_nb_admin(&(bibliotheque.gestion_admin.nb_admin));
    bibliotheque.gestion_admin.liste_admin = creer_tab_admin(&(bibliotheque.gestion_admin.nb_admin));

    // calcul_nb_membre(&(bibliotheque.gestion_membre.nb_membre));
    // bibliotheque.gestion_membre.liste_membre = creer_tab_membre(&(bibliotheque.gestion_membre.nb_membre));
    // bibliotheque.gestion_membre.tri_membre = creer_tri_tab_membre(bibliotheque.gestion_membre.liste_membre, &(bibliotheque.gestion_membre.nb_membre));



    //.....................Gestion.librairie.....................

    //Connexion
    connexion(bibliotheque.gestion_admin.liste_admin, &(bibliotheque.gestion_admin.nb_admin));
    supr_console();

    //Saisie date du jour
    affichage_titre_app();
    printf("Connexion reuissi !\n\n");
    sleep(2);

    //Boucle de consultation de la librairie
    int continuer = TRUE;
    while (continuer == TRUE) {
        do {
            supr_console();
            valide = affichage_choix_menu(&choix_menu);
        } while (valide == FALSE);

        if (choix_menu == 0) { //quitter
            continuer = FALSE;
            supr_console();
        } else {
            //Membres
            if (choix_menu == 1) { //consulter la liste des membres
                // affichage_liste_membre(bibliotheque.gestion_membre.liste_membre, bibliotheque.gestion_membre.tri_membre, &(bibliotheque.gestion_membre.nb_membre));
            } else if (choix_menu == 2) { //ajouter un membre
                saisie_nx_membre(&(bibliotheque.gestion_membre.liste_membre),&(bibliotheque.gestion_membre.nb_membre));
            } else if (choix_menu == 3) { //supprimer un membre
                printf("Supprimer un membre\n");
            }

                //Livres
            else if (choix_menu == 4) { //consulter la liste des livres
                printf("Consulter liste livres\n");
            } else if (choix_menu == 5) { //ajouter un livre
                printf("Ajouter un livre\n");
            } else if (choix_menu == 6) { //supprimer un livre
                printf("Supprimer un livre\n");
            }

                //Prêts
            else if (choix_menu == 7) { //consulter la liste des prets
                printf("Consulter liste prets\n");
            } else if (choix_menu == 8) { //ajouter un pret
                printf("Ajouter un pret\n");
            } else if (choix_menu == 9) { //supprimer un pret
                printf("Supprimer un pret\n");
            }

                //Administrateurs
            else if (choix_menu == 10) { //consulter la liste des administrateurs
                affichage_liste_admin(&(bibliotheque.gestion_admin.liste_admin), &(bibliotheque.gestion_admin.nb_admin));
            } else if (choix_menu == 11) { //ajouter un admin
                saisie_nx_admin(&(bibliotheque.gestion_admin.liste_admin), &(bibliotheque.gestion_admin.nb_admin));
            } else if (choix_menu == 12) { //supprimer un admin
                supr_admin(&(bibliotheque.gestion_admin.liste_admin), &(bibliotheque.gestion_admin.nb_admin));
            }
        }
    }


    //.....................Desalocation.memoire.....................
    lib_tab_admin(bibliotheque.gestion_admin.liste_admin, &(bibliotheque.gestion_admin.nb_admin));
    lib_tab_membre(bibliotheque.gestion_membre.liste_membre,&(bibliotheque.gestion_membre.nb_membre));

    return 0;
}