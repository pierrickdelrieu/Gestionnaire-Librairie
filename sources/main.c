#include "../headers/librairie.h"


int main() {
    //.....................Initialisation.....................

    //Initialisation structure librairie
    Librairie bibliotheque;

    //initialisation du choix de l'utilisateur dans le menu
    int choix_menu;

    //Recupération des sauvegardes
    calcul_nb_admin(&(bibliotheque.gestion_admin.nb_admin));
    bibliotheque.gestion_admin.liste_admin = creer_tab_admin(&(bibliotheque.gestion_admin.nb_admin));

    calcul_nb_membre(&(bibliotheque.gestion_membre.nb_membre));
    bibliotheque.gestion_membre.liste_membre = creer_tab_membre(&(bibliotheque.gestion_membre.nb_membre));

    calcul_nb_livre(&(bibliotheque.gestion_livre.nb_livre));
    bibliotheque.gestion_livre.liste_livre = creer_tab_livre(&(bibliotheque.gestion_livre.nb_livre));

    calcul_nb_pret(&(bibliotheque.gestion_pret.nb_pret));
    bibliotheque.gestion_pret.liste_pret = creer_tab_pret(&(bibliotheque.gestion_pret.nb_pret));

    creer_tab_donnee(bibliotheque.donnee, &bibliotheque.donne_livre);
    actualisation_pret_en_retard(bibliotheque.gestion_pret.liste_pret, &(bibliotheque.gestion_pret.nb_pret));


    //.....................Gestion.librairie.....................

    //Connexion
    connexion(bibliotheque.gestion_admin.liste_admin, &(bibliotheque.gestion_admin.nb_admin));
    supr_console();

    affichage_titre_app();
    printf("Connexion reuissi !\n\n");
    sleep(2);

    //Boucle de consultation et modification de la librairie
    int continuer = TRUE;
    while (continuer == TRUE) {
        affichage_choix_menu(&choix_menu);

        if (choix_menu == 0) { //quitter
            continuer = FALSE;
            supr_console();
        } else {
            //Membres
            if (choix_menu == 1) { //Information sur un membre
                affichage_info_membre(&(bibliotheque.gestion_membre), &(bibliotheque.gestion_pret), &(bibliotheque.gestion_livre));
            } else if (choix_menu == 2) { //consulter la liste des membres
                affichage_liste_membre(bibliotheque.gestion_membre.liste_membre, &(bibliotheque.gestion_membre.nb_membre));
            } else if (choix_menu == 3) { //ajouter un membre
                saisie_nx_membre(&(bibliotheque.gestion_membre.liste_membre), &(bibliotheque.gestion_membre.nb_membre), bibliotheque.donnee, &bibliotheque.donne_livre);
            } else if (choix_menu == 4) { //supprimer un membre
                supr_membre(&(bibliotheque.gestion_membre.liste_membre), &(bibliotheque.gestion_membre.nb_membre));
            }

                //Livres
            else if (choix_menu == 5) { //Information sur un livre
                affichage_info_livre(&bibliotheque.gestion_livre, &bibliotheque.gestion_membre, &bibliotheque.gestion_pret);
            } else if (choix_menu == 6) { //consulter la liste des livres
                affichage_liste_livre(bibliotheque.gestion_livre.liste_livre, &bibliotheque.gestion_livre.nb_livre);
            } else if (choix_menu == 7) { //ajouter un livre
                saisie_nx_livre(&(bibliotheque.gestion_livre.liste_livre), &(bibliotheque.gestion_livre.nb_livre), &bibliotheque.donne_livre, bibliotheque.donnee);
            } else if (choix_menu == 8) { //supprimer un livre
                supr_livre(&(bibliotheque.gestion_livre.liste_livre), &(bibliotheque.gestion_livre.nb_livre), bibliotheque.donnee, &bibliotheque.donne_livre);
            }

                //Prêts
            else if (choix_menu == 9) { //information sur un pret
                affichage_info_pret(&bibliotheque.gestion_pret, &bibliotheque.gestion_membre, &bibliotheque.gestion_livre);
            } else if (choix_menu == 10) { //consulter la liste des prets
                affichage_liste_pret(&bibliotheque.gestion_pret, &bibliotheque.gestion_livre, &bibliotheque.gestion_membre);
            } else if (choix_menu == 11) { //ajouter un pret
                saisie_nx_pret(&(bibliotheque.gestion_membre), &(bibliotheque.gestion_livre), &(bibliotheque.gestion_pret), bibliotheque.donnee, &bibliotheque.donne_livre);
            } else if (choix_menu == 12) { //supprimer un pret
                supr_pret(&bibliotheque.gestion_pret, &bibliotheque.gestion_livre, &bibliotheque.gestion_membre);
            }

                //Administrateurs
            else if (choix_menu == 13) { //consulter la liste des administrateurs
                affichage_liste_admin(&(bibliotheque.gestion_admin.liste_admin), &(bibliotheque.gestion_admin.nb_admin));
            } else if (choix_menu == 14) { //ajouter un admin
                saisie_nx_admin(&(bibliotheque.gestion_admin.liste_admin), &(bibliotheque.gestion_admin.nb_admin));
            } else if (choix_menu == 15) { //supprimer un admin
                supr_admin(&(bibliotheque.gestion_admin.liste_admin), &(bibliotheque.gestion_admin.nb_admin));
            } 
            
                //Autres
            else if (choix_menu == 16) { //information sur la librairie
                affichage_toute_info_librairie(&bibliotheque);
            }else if (choix_menu == 17) { //reinitialisé la librairie
                reinitialise_librairie(bibliotheque.donnee, &bibliotheque.donne_livre, &(bibliotheque.gestion_admin), &(bibliotheque.gestion_membre), &(bibliotheque.gestion_livre), &(bibliotheque.gestion_pret));
            }else if (choix_menu == 18) { //notice de l'application
                affichage_notice();
            }else if (choix_menu == 19) { //a propos
                affichage_a_propos();
            }
        }
    }

    //.....................Desalocation.memoire.....................
    lib_tab_admin(bibliotheque.gestion_admin.liste_admin, &(bibliotheque.gestion_admin.nb_admin));
    lib_tab_membre(bibliotheque.gestion_membre.liste_membre, &(bibliotheque.gestion_membre.nb_membre));
    lib_tab_livre(bibliotheque.gestion_livre.liste_livre, &bibliotheque.gestion_livre.nb_livre);
    lib_tab_pret(bibliotheque.gestion_pret.liste_pret, &bibliotheque.gestion_pret.nb_pret);

    return 0;
}