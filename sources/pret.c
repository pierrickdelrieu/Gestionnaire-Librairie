
#include "../headers/pret.h"
#include "../headers/utile.h"


Pret *creer_struct_pret() {
    return (Pret *) malloc(sizeof(Pret));
}

void lib_struct_pret(Pret *pret) {
    free(pret);
}

void lib_tab_pret(Pret **tab_pret, int *nb_prets) {
    int i;

    for (i = 0; i < *nb_prets; i++) {
        lib_struct_pret(tab_pret[i]);
    }

    free(tab_pret);
}

Pret **creer_tab_pret(int *nb_pret) {
    Pret **liste_prets;
    FILE *fichier_pret = NULL;

    fichier_pret = fopen("sauvegardes/prets.txt", "r");

    if (fichier_pret != NULL) {
        liste_prets = (Pret **) malloc((*nb_pret) * sizeof(Pret *));
        int i;

        for (i = 0; i < (*nb_pret); i++) {
            liste_prets[i] = creer_struct_pret();
            fscanf(
                    fichier_pret,
                    "id : %d | ", &liste_prets[i]->id_pret
            );
            fscanf(
                    fichier_pret,
                    "id_utilisateur : %d | ",
                    &liste_prets[i]->id_utilisateur
            );
            fscanf(
                    fichier_pret,
                    "code_livre : %s | ",
                    liste_prets[i]->code_livre
            );
            fscanf(
                    fichier_pret,
                    "date_pret : %d | ",
                    &(liste_prets[i]->date_pret)
            );
            fscanf(
                    fichier_pret,
                    "date_retour : %d | ",
                    &(liste_prets[i]->date_retour)
            );
            fscanf(
                    fichier_pret,
                    "etat_livre : %d | ",
                    &(liste_prets[i]->etat_livre)
            );
        }

        fclose(fichier_pret);

    } else { //le pointeur sur le fichier est toujours = NULL soit le fichier n'a pas était ouvert
        printf("Erreur au niveau de l'ouverture du fichier\n");
        printf("Le programme n'a pas les autorisations nécessaire pour acceder aux fichiers de votre ordinateur\n");
        printf("Gerer ceci dans les préférence de votre ordinateur\n");
        exit(0); //Fin du programme
    }

    return liste_prets;
}

void calcul_nb_pret(int *nb_pret) {
    FILE *fichier_pret = NULL;

    fichier_pret = fopen("sauvegardes/pret.txt", "r"); //"w" correspond a la ecriture seul (permet de limiter les erreurs) - fopen renvoie un pointeur sur le fichier

    if (fichier_pret != NULL) {
        int cara;
        *nb_pret = 0;

        do {
            cara = fgetc(fichier_pret);
            if (cara == '\n') {
                (*nb_pret)++;
            }
        } while (cara != EOF);

        //Fermeture du fichier
        fclose(fichier_pret);

    } else { //le pointeur sur le fichier est toujours = NULL soit le fichier n'a pas était ouvert
        printf("Erreur au niveau de l'ouverture du fichier\n");
        printf("Le programme n'a pas les autorisations nécessaire pour acceder aux fichiers de votre ordinateur\n");
        printf("Gerer ceci dans les préférence de votre ordinateur\n");
        exit(0); //Fin du programme
    }
}

void rafrachir_tab_pret(Pret ***tab_pret, int *nb_pret) {
    lib_tab_pret(*tab_pret, nb_pret);
    calcul_nb_pret(nb_pret);
    *tab_pret = creer_tab_pret(nb_pret);
}

void ajout_pret_fichier_pret(Pret *saisie) {
    /*
     * id : int
     * id_utilisateur : int
     * code_livre : int
     * date_pret int (timestamp)
     * date_retour int (timestamp + 3semaines)
     * etat_livre : int
     */
    FILE *fichier_pret = fopen("sauvegardes/prets.txt", "a"); //"a" correspond a l'ajout - fopen renvoie un pointeur sur le fichier

    if (fichier_pret != NULL) {
        fprintf(
                fichier_pret,
                "id : %d | ",
                saisie->id_pret
        );
        fprintf(
                fichier_pret,
                "id_utilisateur : %d | ",
                saisie->id_utilisateur
        );
        fprintf(
                fichier_pret,
                "code_livre : %s | ",
                saisie->code_livre
        );
        fprintf(
                fichier_pret,
                "date_pret : %d | ",
                saisie->date_pret
        );
        fprintf(
                fichier_pret,
                "date_retour : %d | ",
                saisie->date_retour + 1 * 3600 * 24 * 7 * 3
                // 1 * 3600 * 24 * 7 * 3 -> 1sec * 3600 (donc heure) * 24 (donc jour) * 7 (donc semaine) * 3 (donc 3 semaines)
        );
        fprintf(
                fichier_pret,
                "etat_livre : %d ",
                saisie->etat_livre
        );

        //Fermeture du fichier
        fclose(fichier_pret);

    } else { //le pointeur sur le fichier est toujours = NULL soit le fichier n'a pas était ouvert
        printf("Erreur au niveau de l'ouverture du fichier\n");
        printf("Le programme n'a pas les autorisations nécessaire pour acceder aux fichiers de votre ordinateur\n");
        printf("Gerer ceci dans les préférence de votre ordinateur\n");
        exit(0); //Fin du programme
    }
}
