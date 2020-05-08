#include "../headers/librairie.h"

/*Reinitialisation de toute les valeurs dans librairie
- le nombre de pret (donnee[1]) et de le nombre de membre (donnee[0]) depuis l'ouverture de la librairie
- tous les administrateurs sauf celui du programmeur
- tous les membres
- tous les prets
- tous les livres*/
void reinitialise_librairie(int tab_donnee[2], Membre ***tab_membre, int *nb_membre, Admin ***tab_admin, int *nb_admin) {
    int choix;

    do {
        supr_console();
        affichage_sous_titre("REINITIALISATION DONNEE LIBRAIRIE");
        printf("     Cette opération est irréversible\n\n\n");
        printf("Saisir 1 pour valider et 0 pour quitter : ");
        saisie_entier(&choix);
    } while ((choix != 0) && (choix != 1));

    if (choix == 1) {
        tab_donnee[0] = 0; //reinitialisation des membres
        tab_donnee[1] = 0; //reinitialisation des livres

        FILE *fichier_membre = NULL;
        fichier_membre = fopen("sauvegardes/membres.txt", "w"); //ouvre le fichier en mode ecriture et supprime tous sont contenue au préalable
        fclose(fichier_membre);

        // FILE *fichier_prets = NULL;
        // fichier_membre = fopen("sauvegardes/prets.txt", "w"); //ouvre le fichier en mode ecriture et supprime tous sont contenue au préalable
        // fclose(fichier_prets);

        // FILE *fichier_livres = NULL;
        // fichier_membre = fopen("sauvegardes/livres.txt", "w"); //ouvre le fichier en mode ecriture et supprime tous sont contenue au préalable
        // fclose(fichier_livres);

        FILE *fichier_admin = NULL;
        fichier_admin = fopen("sauvegardes/admin.txt", "w"); //ouvre le fichier en mode ecriture et supprime tous sont contenue au préalable
        fprintf(fichier_admin, "id : %d mp : %s\n", ID_PROGRAMMEUR, MP_PROGRAMMEUR);
        fclose(fichier_admin);

        rafrachir_fichier_donnee(tab_donnee);
        rafrachir_tab_membre(tab_membre, nb_membre);
        rafrachir_tab_admin(tab_admin, nb_admin);

        //ajout des fonctions rafraichir tab livres et tab pret

        supr_console();
        printf("Toutes les données (membres, admin, livres, prets) de la librairies ont été supprimés\n");

        sleep(2);
        supr_console();
    }
}


/*recuperation des donnes se situant dans le fichier donnee.txt et modification du tableau en memoire
cad la recuperation du nombre de pret et de membre depuis l'ouverture de la librairie*/
void creer_tab_donnee(int tab[2]) {
    FILE *fichier_donnee = NULL;
    fichier_donnee = fopen("sauvegardes/donnee.txt", "r"); //"r" correspond a la lecture seul - fopen renvoie un pointeur sur le fichier

    if (fichier_donnee != NULL) {

        fscanf(fichier_donnee, "nombre de membres total : %d\n", &(tab[0]));
        fscanf(fichier_donnee, "nombre de prets total : %d\n", &(tab[1]));

        //Fermeture du fichier
        fclose(fichier_donnee);

    } else { //le pointeur sur le fichier est toujours = NULL soit le fichier n'a pas était ouvert
        erreur_ouverture_fichier();
    }
}


/*modification du tableau de donnée en fonction du fichier donne.txt*/
void rafrachir_fichier_donnee(int *tab) {
    FILE *fichier_donnee = NULL;
    fichier_donnee = fopen("sauvegardes/donnee.txt", "w"); //"w" correspond a l'ecriture seul - fopen renvoie un pointeur sur le fichier

    if (fichier_donnee != NULL) {

        fprintf(fichier_donnee, "nombre de membres total : %d\n", tab[0]);
        fprintf(fichier_donnee, "nombre de prets total : %d\n", tab[1]);

        //Fermeture du fichier
        fclose(fichier_donnee);

    } else { //le pointeur sur le fichier est toujours = NULL soit le fichier n'a pas était ouvert
        erreur_ouverture_fichier();
    }
}


/*ecran de connexion*/
void connexion(Admin **tab_admin, int *nb_identifiant) {
    Admin saisie;
    int valide = TRUE;

    do {
        supr_console();
        affichage_titre_app();
        affichage_sous_titre("CONNEXION");
        if (valide == FALSE) {
            printf("          Identifiant ou mot de passe incorrect\n");
        }
        valide = saisie_securise_id_tab_admin(&saisie, tab_admin, nb_identifiant);
    } while (valide == FALSE);
}


/***********************************************FONCTION ADMIN***********************************************/

/*affichage de la liste des admins*/
void affichage_liste_admin(Admin ***tab_identifiant, int *nb_identifiant) {
    int choix;

    do {
        supr_console();
        affichage_sous_titre("AFFICHAGE DES ADMINISTRATEURS");
        affichage_tab_admin(*tab_identifiant, nb_identifiant);
        printf("     Saisir 1 pour revenir au menu : ");
        saisie_entier(&choix);
    } while (choix != 1);
}


/*saisie d'un nouveau admin dans le tableau en memoire et dans le fichier*/
void saisie_nx_admin(Admin ***tab_admin, int *nb_identifiant) {

    //Saise de l'administrateur a supprimer
    int valide;
    Admin saisie;

    //saisie de l'administrateur a ajouter
    do {
        supr_console();
        affichage_sous_titre("AJOUT NOUVEAU ADMINISTRATEUR");
        printf("L'identifiant doit comporter 8 chiffres\n\n");
        valide = saisie_identifiant(&saisie);
    } while (valide == FALSE);


    //modification du contenu du fichier admin.txt
    FILE *fichier_admin = NULL;
    ajout_admin_fichier_admin(fichier_admin, &(saisie));

    rafrachir_tab_admin(tab_admin, nb_identifiant); //modif du nombre d'identifiant

    supr_console();
    printf("L'administrateur %d a bien était ajouté\n", saisie.identifiant);

    sleep(2);
    supr_console();
}


/*supression d'un admin dans le tableau en memoire et dans le fichier*/
void supr_admin(Admin ***tab_admin, int *nb_identifiant) {

    //Saisie de l'administrateur a supprimer
    int valide = TRUE;
    Admin saisie;

    if (*nb_identifiant == 1) {
        supr_console();
        affichage_sous_titre("SUPRESSION ADMINISTRATEUR");
        affichage_tab_admin(*tab_admin, nb_identifiant);
        printf("     !!!Vous ne pouvez pas supprimer d'administarteur!!!\n");
        printf(" L'administrateur de référence (programmeur) ne peut pas etre supprimer\n");
        sleep(3);
        supr_console();
    } else {
        do {
            supr_console();
            affichage_sous_titre("SUPRESSION ADMINISTRATEUR");
            affichage_tab_admin(*tab_admin, nb_identifiant);

            printf("Il n'est pas possible de supprimer les identifiants du programmeur :\n");
            printf("          id : %d mp : %s\n\n", ID_PROGRAMMEUR, MP_PROGRAMMEUR);

            if (valide == FALSE) {
                printf("     ERREUR\n");
            }
            valide = saisie_securise_id_tab_admin(&saisie, *tab_admin, nb_identifiant);

            //pas possible de supprimer l'administrateur de référence
            if ((saisie.identifiant == ID_PROGRAMMEUR) && (compare_chaine_caractere(saisie.mot_de_passe, MP_PROGRAMMEUR) == 0)) {
                valide = FALSE;
            }
        } while (valide == FALSE);

        //supression et recréation du contenu du fichier admin.txt
        FILE *fichier_admin = NULL;
        supr_admin_fichier_admin(fichier_admin, *(tab_admin), &saisie, nb_identifiant);
        rafrachir_tab_admin(tab_admin, nb_identifiant); //modif de la valeur de nb_id

        supr_console();
        printf("L'administrateur %d a bien était suprimer\n", saisie.identifiant);

        sleep(2);
        supr_console();
    }
}


/**********************************************FONCTION MEMBRE**********************************************/

/*ajout d'un membre dans le tableau en memoire et dans le fichier*/
void saisie_nx_membre(Membre ***tab_membre, int *nb_membre, int tab_donnee[2]) {

    int valide = FALSE;
    Membre saisie;

    //saisie du membre a ajouter
    do {
        supr_console();
        affichage_sous_titre("AJOUT NOUVEAU MEMBRE");

        if (valide == TRUE) {
            printf("ERREUR (adresse mail deja existante)\nReesayer\n\n");
        }

        valide = saisie_securise_membre_tab_membre(&saisie, *tab_membre, nb_membre, &(tab_donnee[0]));
    } while (valide == TRUE);


    //modification du contenu du fichier membre.txt
    FILE *fichier_membre = NULL;
    ajout_membre_fichier_membre(fichier_membre, &(saisie));

    rafrachir_tab_membre(tab_membre, nb_membre); //modif du nombre de membre

    tab_donnee[0]++;

    rafrachir_fichier_donnee(tab_donnee);


    supr_console();
    printf("%s %s a bien était ajouté comme nouveau membre\n", saisie.prenom, saisie.nom);

    sleep(2);
    supr_console();
}


/*supression d'un membre dans le tableau en memoire et dans le fichier*/
void supr_membre(Membre ***tab_membre, int *nb_membre) {

    if (*nb_membre == 0) {
        supr_console();
        affichage_sous_titre("SUPRESSION D'UN MEMBRE");
        printf("                        !!!Il y a aucun membre!!!\n");
        sleep(2);
        supr_console();
    } 
    else {
        int i;
        int id_membre;
        int valide = FALSE;

        do {
            supr_console();
            affichage_sous_titre("SUPRESSION D'UN MEMBRE");
            printf("     Saisir l'identifiant du membre a supprimer ou 0 pour retourner au menu : ");

            valide = saisie_id_membre_tab_membre(*tab_membre, &id_membre, nb_membre);
        } while (valide == FALSE);

        int choix;
        do{
            supr_console();
            affichage_sous_titre("SUPRESSION D'UN MEMBRE");
            if(id_membre != 0){
                for(i=0; i<(*nb_membre); i++)
                {
                    if((*tab_membre)[i]->identifiant == id_membre){
                        afficher_toute_info_membre((*tab_membre)[i]);
                    }
                }
            }

            printf("Voulez vous supprimer ce membre (1 : OUI - 0 : NON (retour au menu)): ");
            saisie_entier(&choix);
        }while((choix != 1) && (choix != 0));

        if(choix == 1){
            //supression et recréation du contenu du fichier membre.txt
            FILE *fichier_membre = NULL;
            supr_membre_fichier_membre(fichier_membre, &id_membre, *tab_membre, nb_membre);
            rafrachir_tab_membre(tab_membre, nb_membre); //modif de la valeur de nb_membre

            supr_console();
            printf("Le membre %d a bien était suprimer\n", id_membre);

            sleep(2);
            supr_console();
        }
    }
}


/*afichage de la liste des membre en ligne par ordre alphabétique*/
void affichage_liste_membre(Membre **tab_membre, int *nb_membre) {

    if (*nb_membre == 0) {
        supr_console();
        affichage_sous_titre("AFFICHAGE DES MEMBRES");
        printf("                        !!!Il y a aucun membre!!!\n");
        sleep(2);
        supr_console();
    } else {
        int i;
        int choix;
        int *tab_tri;
        tab_tri = (int*) calloc(1,sizeof(int)); //les valeurs du tableau sont initialisé a 0

        do {
            supr_console();
            affichage_sous_titre("AFFICHAGE DES MEMBRES");
            printf("     La librairie contient %d membres\n\n", *nb_membre);

            //affichage dans l'ordre alphabétique
            init_tab_tri_ordre_alpha(tab_membre, tab_tri, nb_membre);
            for (i = 0; i < (*nb_membre); i++) {
                afficher_membre(tab_membre[tab_tri[i]]);
            }

            for (i = 0; i < (*nb_membre); i++) {
                printf("%d, ", tab_tri[i]);
            }

            printf("     Saisir 1 pour revenir au menu : ");
            saisie_entier(&choix);
        } while (choix != 1);

        free(tab_tri);
    }


}


/*affichage de toute les informations sur un membre en particulier*/
void affichage_info_membre(Membre **tab_membre, int *nb_membre) {

    if (*nb_membre == 0) {
        supr_console();
        affichage_sous_titre("INFORMATION SUR UN MEMBRE");
        printf("                        !!!Il y a aucun membre!!!\n");
        sleep(2);
        supr_console();
    } else {
        int i;
        int choix;
        int id_membre;
        int valide = FALSE;

        do {
            supr_console();
            affichage_sous_titre("INFORMATION SUR UN MEMBRE");
            printf("     Saisir l'identifiant du membre ou 0 pour revenir au menu : ");


            valide = saisie_id_membre_tab_membre(tab_membre, &id_membre, nb_membre);


            if ((valide == TRUE) && (id_membre != 0)) {
                for (i = 0; i < (*nb_membre); i++) {
                    if (tab_membre[i]->identifiant == id_membre) {
                        afficher_toute_info_membre(tab_membre[i]);
                    }
                }

                printf("     Saisir 1 pour revenir au menu : ");
                saisie_entier(&choix);
            }

        } while ((choix != 1) && (valide == FALSE));
    }
}


/***********************************************FONCTION LIVRE***********************************************/


void affichage_info_livre(Livre **tab_livre, int *nb_livre) {

    if (*nb_livre == 0) {
        supr_console();
        affichage_sous_titre("INFORMATION SUR UN LIVRE");
        printf("                        !!!Il y a aucun livre!!!\n");
        sleep(2);
        supr_console();
    } else {
        int i;
        int choix;
        int id_livre;
        int valide = FALSE;

        do {
            supr_console();
            affichage_sous_titre("INFORMATION SUR UN LIVRE");
            printf("     Saisir l'identifiant du membre ou 0 pour revenir au menu : ");


            valide = saisie_id_livre_tab_livre(tab_livre, &id_livre, nb_livre);


            if ((valide == TRUE) && (nb_livre != 0)) {
                for (i = 0; i < (*nb_livre); i++) {
                    if (tab_livre[i]->code == id_livre) {
                        afficher_toute_info_livre(tab_livre[i]);
                    }
                }

                printf("     Saisir 1 pour revenir au menu : ");
                saisie_entier(&choix);
            }

        } while ((choix != 1) && (valide == FALSE));
    }
}

void affichage_liste_livre(Livre **tab_livre, int *nb_livre) {
    int i;
    int choix;

    if (*nb_livre == 0) {
        supr_console();
        affichage_sous_titre("AFFICHAGE DES LIVRES");
        printf("                        !!!Il y a aucun livre!!!\n");
        sleep(2);
        supr_console();
    } else {
        do {
            supr_console();
            affichage_sous_titre("AFFICHAGE DES LIVRES");
            printf("     La librairie contient %d livre\n\n", *nb_livre);
            for (i = 0; i < (*nb_livre); i++) {
                afficher_livre(tab_livre[i]);
            }

            printf("     Saisir 1 pour revenir au menu : ");
            scanf(" %d", &choix);
        } while (choix != 1);
    }
}


void saisie_nx_livre(Livre ***tab_livre, int *nb_livre, int tab_donnee[2]) {

    int valide = FALSE;
    Livre saisie;

    //saisie du livre a ajouter
    do {
        supr_console();
        affichage_sous_titre("AJOUT NOUVEAU LIVRE");

        if (valide == TRUE) {
            printf("ERREUR (livre deja existant ou erreur de saisie)\nReesayer\n\n");
        }

        valide = saisie_securise_livre_tab_livre(&saisie, *tab_livre, nb_livre, &(tab_donnee[0]));
    } while (valide == TRUE);


    //modification du contenu du fichier membre.txt
    FILE *fichier_livre = NULL;
    ajout_livre_fichier_livre(fichier_livre, &(saisie));

    rafrachir_tab_livre(tab_livre, nb_livre); //modif du nombre de livre

    tab_donnee[0]++;

    rafrachir_fichier_donnee(tab_donnee);

    supr_console();
    printf("%s de %s a bien était ajouté comme nouveau livre\n", saisie.titre, saisie.auteur);

    sleep(2);
    supr_console();
}



/***********************************************FONCTION PRET***********************************************/
