#include "../headers/admin.h"


//creer la structure admin de maniere dynamique
Admin *creer_struct_admin() {
    Admin *x;

    x = (Admin *) malloc(sizeof(Admin));

    return (x);
}


/*Libere la structure admin de maniere dynamique*/
void lib_struct_admin(Admin *admin) {
    free(admin);
}


/*Recuperation des sauvegardes faites dans le fichier admin*/
Admin **creer_tab_admin(int *nb_identifiant) {
    Admin **tab_identifiant;
    FILE *fichier_admin = NULL;

    fichier_admin = fopen("sauvegardes/admin.txt", "r"); //"r" correspond a la lecture seul (permet de limiter les erreurs) - fopen renvoie un pointeur sur le fichier

    if (fichier_admin != NULL) { //si le fichier est bien ouvert

        //allocation du tableau d'identifiant (dynamique)
        tab_identifiant = (Admin **) malloc((*nb_identifiant) * sizeof(Admin *));

        //recup des identifiants (parcours du fichier)
        int i;

        for (i = 0; i < (*nb_identifiant); i++) {
            tab_identifiant[i] = creer_struct_admin();
            fscanf(fichier_admin, "id : %d mp : %s\n", &(tab_identifiant[i]->identifiant), tab_identifiant[i]->mot_de_passe);
        }

        //Fermeture du fichier
        fclose(fichier_admin);

    } else { //le pointeur sur le fichier est toujours = NULL soit le fichier n'a pas était ouvert
        erreur_ouverture_fichier();
    }

    return (tab_identifiant);
}


/*Liberation du tableau contenant tous les admin*/
void lib_tab_admin(Admin **tab_admin, int *nb_identifiant) {
    int i;

    //liberation des structures
    for (i = 0; i < *nb_identifiant; i++) {
        lib_struct_admin(tab_admin[i]);
    }

    free(tab_admin);
}


/*Affichage de tous les administrateurs de la librairie*/
void affichage_tab_admin(Admin **tab_identifiant, int *nb_identifiant) {
    int i;

    printf("Les identifiants et mot de passe des administrateurs sont : \n");

    for (i = 0; i < (*nb_identifiant); i++) {
        printf("     id : %d mp : %s\n", tab_identifiant[i]->identifiant, tab_identifiant[i]->mot_de_passe);
    }

    printf("\nSeul ces personnes ont les autoirisations pour gérer la bibliothèque\n\n");
}


/*Permet de calculer le nombre d'administrateur a partir du fichier admin.txt
Elle parcour le fichier et compte le nombre d'admin qu'il contient (sachant que un admin = 1 ligne)*/
void calcul_nb_admin(int *nb_identifiant) {
    FILE *fichier_admin = NULL;

    fichier_admin = fopen("sauvegardes/admin.txt", "r"); //"r" correspond a la lecture seul (permet de limiter les erreurs) - fopen renvoie un pointeur sur le fichier

    if (fichier_admin != NULL) { //si le fichier est bien ouvert

        //nombres d'identifiant
        int cara;
        *nb_identifiant = 0;
        do {
            cara = fgetc(fichier_admin);
            if (cara == '\n') {
                (*nb_identifiant)++;
            }
        } while (cara != EOF); //EOF signifie fin du fichier

        //Fermeture du fichier
        fclose(fichier_admin);

    } else { //le pointeur sur le fichier est toujours = NULL soit le fichier n'a pas était ouvert
        erreur_ouverture_fichier();
    }
}


/* Modifie le tableau d'admin en fonction des modifications (ajout et supression) qui ont eu lieu sur le fichier
Cette fonction suprimme et recrer le tableau, la realocation est trop dangeureuse*/
void rafrachir_tab_admin(Admin ***tab_admin, int *nb_identifiant) {

    lib_tab_admin(*tab_admin, nb_identifiant);

    calcul_nb_admin(nb_identifiant);

    *tab_admin = creer_tab_admin(nb_identifiant);
}


/*Saisie d'un identifiant
avec verif d'un nombre et pas d'un caractere, et verif d'un id a 8 chiffres*/
int saisie_identifiant(Admin *admin) {
    printf("          Identifiant : ");
//    saisie_entier(&(admin->identifiant));
    scanf("%d", &(admin->identifiant));
    printf("          Mot de passe : ");
//    saisie_chaine_caractere(admin->mot_de_passe,30);
    scanf("%s", admin->mot_de_passe);

    if ((admin->identifiant < 10000000) || (admin->identifiant > 99999999)) {
        return FALSE;
    }
    return TRUE;
}


/*Saisie securise d'un identifint valide
cad d'un identifiant pouvant acceder a la librairie*/
int saisie_securise_id_tab_admin(Admin *saisie, Admin **tab_admin, int *nb_identifiant) {

    //retourne 1 (TRUE) si valeur saisie corresponde a une valeur du fichier admin.txt et retourne 0 (FALSE) sinon
    int valide = FALSE;
    int i;

    valide = saisie_identifiant(saisie);

    if (valide == TRUE) {
        valide = FALSE;

        //verif identifiant
        int indice_id_valide = 0;
        for (i = 0; i < (*nb_identifiant); i++) {
            if (saisie->identifiant == tab_admin[i]->identifiant) {
                valide = TRUE;
                indice_id_valide = i;
            }
        }

        //verif mot de passe correspondant a l'identifiant
        if (valide == TRUE) {
            if (compare_chaine_caractere(saisie->mot_de_passe, tab_admin[indice_id_valide]->mot_de_passe) != 0) {
                valide = FALSE;
            }
        }
    }

    return (valide);
}


/*Modification du fichier admin lors de l'ajout d'un admin
apres la modification il faudra rafraichir les valeurs du tab admin et nb_admin
ouverture du fichier en mode ajout pour ne pas modifier le contenue qui est deja dans le fichier*/
void ajout_admin_fichier_admin(FILE *fichier_admin, Admin *saisie) {
    fichier_admin = fopen("sauvegardes/admin.txt", "a"); //"a" correspond a l'ajout - fopen renvoie un pointeur sur le fichier

    if (fichier_admin != NULL) { //fichier ouvert

        fprintf(fichier_admin, "id : %d mp : %s\n", saisie->identifiant, saisie->mot_de_passe);

        //Fermeture du fichier
        fclose(fichier_admin);

    } else { //le pointeur sur le fichier est toujours = NULL soit le fichier n'a pas était ouvert
        erreur_ouverture_fichier();
    }
}


/*Modification du fichier admin lors de la supression d'un admin
ouverture du fichier en mode ecriture pour suprimmer tous les elements du fichier
les admins seront ensuite tous reinsérré sauf dont on demande la suppression
apres la modification il faudra rafraichir les valeurs du tab admin et nb_admin*/
void supr_admin_fichier_admin(FILE *fichier_admin, Admin **tab_admin, Admin *saisie, int *nb_identifiant) {
    fichier_admin = fopen("sauvegardes/admin.txt", "w"); //"w" correspond a l'ecriture - fopen renvoie un pointeur sur le fichier

    if (fichier_admin != NULL) { //fichier ouvert

        int i;
        for (i = 0; i < (*nb_identifiant); i++) {
            if (tab_admin[i]->identifiant != saisie->identifiant) {
                fprintf(fichier_admin, "id : %d mp : %s\n", tab_admin[i]->identifiant, tab_admin[i]->mot_de_passe);
            }
        }

        //Fermeture du fichier
        fclose(fichier_admin);

    } else { //le pointeur sur le fichier est toujours = NULL soit le fichier n'a pas était ouvert
        erreur_ouverture_fichier();
    }
}