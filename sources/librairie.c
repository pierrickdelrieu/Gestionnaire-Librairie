
#include "../headers/librairie.h"

void reinitialise_librairie(int tab_donnee[2], Membre ***tab_membre,int *nb_membre, Admin ***tab_admin, int *nb_admin) {
    int choix;

    do{
        supr_console();
        affichage_sous_titre("REINITIALISATION DONNEE LIBRAIRIE");
        printf("     Cette opération est irréversible\n\n\n");
        printf("Saisir 1 pour valider et 0 pour quitter : ");
        scanf(" %d", &choix);
    }while((choix != 0) && (choix != 1));

    if(choix == 1){
        FILE *fichier_donnee = NULL;
        fichier_donnee = fopen("sauvegardes/donnee.txt", "w"); //"W" correspond a la lecture seul - fopen renvoie un pointeur sur le fichier
        fprintf(fichier_donnee, "nombre de membres total : 0\n");
        fprintf(fichier_donnee, "nombre de livres total : 0\n");
        fclose(fichier_donnee);

        FILE *fichier_membre = NULL;
        fichier_membre = fopen("sauvegardes/membres.txt", "w"); //"r" correspond a la lecture seul - fopen renvoie un pointeur sur le fichier
        fclose(fichier_membre);

        FILE *fichier_admin = NULL;
        fichier_admin = fopen("sauvegardes/admin.txt", "w"); //"r" correspond a la lecture seul - fopen renvoie un pointeur sur le fichier
        fprintf(fichier_admin, "id : %d mp : %s\n",ID_PROGRAMMEUR,MP_PROGRAMMEUR);
        fclose(fichier_admin);

        rafrachir_tab_donnee(tab_donnee);
        rafrachir_tab_membre(tab_membre, nb_membre);
        rafrachir_tab_admin(tab_admin, nb_admin);

        supr_console();
        printf("Toutes les données (membres, admin, livres, prets) de la librairies ont été supprimés\n");

        sleep(2);
        supr_console();
    }
}

void creer_tab_donnee(int tab[2]) {
    FILE *fichier_donnee = NULL;
    fichier_donnee = fopen("sauvegardes/donnee.txt", "r"); //"r" correspond a la lecture seul - fopen renvoie un pointeur sur le fichier

    if (fichier_donnee != NULL) {

        fscanf(fichier_donnee, "nombre de membres total : %d\n", &(tab[0]));
        fscanf(fichier_donnee, "nombre de livres total : %d\n", &(tab[1]));

        //Fermeture du fichier
        fclose(fichier_donnee);

    } else { //le pointeur sur le fichier est toujours = NULL soit le fichier n'a pas était ouvert
        printf("Erreur au niveau de l'ouverture du fichier\n");
        printf("Le programme n'a pas les autorisations nécessaire pour acceder aux fichiers de votre ordinateur\n");
        printf("Gerer ceci dans les préférence de votre ordinateur\n");
        exit(0); //Fin du programme
    }
}

void rafrachir_tab_donnee(int tab[2]){
    FILE *fichier_donnee = NULL;
    fichier_donnee = fopen("sauvegardes/donnee.txt", "r"); //"r" correspond a l'ecriture seul - fopen renvoie un pointeur sur le fichier

    if (fichier_donnee != NULL) {

        fscanf(fichier_donnee, "nombre de membres total : %d\n", &(tab[0]));
        fscanf(fichier_donnee, "nombre de livres total : %d\n", &(tab[1]));

        //Fermeture du fichier
        fclose(fichier_donnee);

    } else { //le pointeur sur le fichier est toujours = NULL soit le fichier n'a pas était ouvert
        printf("Erreur au niveau de l'ouverture du fichier\n");
        printf("Le programme n'a pas les autorisations nécessaire pour acceder aux fichiers de votre ordinateur\n");
        printf("Gerer ceci dans les préférence de votre ordinateur\n");
        exit(0); //Fin du programme
    }   
}

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

void affichage_liste_admin(Admin ***tab_identifiant, int *nb_identifiant) {
    int choix;

    do {
        supr_console();
        affichage_sous_titre("AFFICHAGE DES ADMINISTRATEURS");
        affichage_tab_admin(*tab_identifiant, nb_identifiant);
        printf("     Saisir 1 pour revenir au menu : ");
        scanf(" %d", &choix);
    } while (choix != 1);
}

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
    printf("L'administrateur %ld a bien était ajouté\n", saisie.identifiant);

    sleep(2);
    supr_console();
}

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
        rafrachir_tab_admin(tab_admin, nb_identifiant);

        supr_console();
        printf("L'administrateur %ld a bien était suprimer\n", saisie.identifiant);

        sleep(2);
        supr_console();
    }
}


void saisie_nx_membre(Membre ***tab_membre, int *nb_membre, int tab_donnee[2]){
    
    int valide = FALSE;
    Membre saisie;

    //saisie du membre a ajouter
    do {
        supr_console();
        affichage_sous_titre("AJOUT NOUVEAU MEMBRE");
        
        if(valide == TRUE){
            printf("ERREUR (membre deja existant ou erreur de saisie)\nReesayer\n\n");
        }

        valide = saisie_securise_membre_tab_membre(&saisie, *tab_membre,nb_membre, &(tab_donnee[0]));
    } while (valide == TRUE);


    //modification du contenu du fichier membre.txt
    FILE *fichier_membre = NULL;
    ajout_membre_fichier_membre(fichier_membre, &(saisie));

    rafrachir_tab_membre(tab_membre, nb_membre); //modif du nombre de membre

    tab_donnee[0] ++;

    rafrachir_tab_donnee(tab_donnee);
    

    supr_console();
    printf("%s %s a bien était ajouté comme nouveau membre\n", saisie.prenom, saisie.nom);

    sleep(2);
    supr_console();
}

void affichage_liste_membre(Membre **tab_membre, int *nb_membre){
    int i;
    int choix;
    
    do{
        supr_console();
        affichage_sous_titre("AFFICHAGE DES MEMBRES");
        for(i=0; i<(*nb_membre); i++)
        {
            afficher_membre(tab_membre[i]);
        }

        printf("     Saisir 1 pour revenir au menu : ");
        scanf(" %d", &choix);
           
    }while(choix!=1);

}

void affichage_info_membre(Membre **tab_membre, int *nb_membre) {
    int i;
    int choix;
    int id_membre;
    int valide = FALSE;
    
    do{
        supr_console();
        affichage_sous_titre("AFFICHAGE DES MEMBRES");

        if(valide == FALSE){
            valide = saisie_id_membre_tab_membre(tab_membre,&id_membre,nb_membre);
        }

        if(valide == TRUE){
            for(i=0; i<(*nb_membre); i++)
            {
                if(tab_membre[i]->identifiant == id_membre){
                    afficher_toute_info_membre(tab_membre[i]);
                }
            }

            printf("     Saisir 1 pour revenir au menu : ");
            scanf(" %d", &choix);
        }
           
    }while((choix!=1) && (valide == FALSE));
}