#include "../headers/pret.h"
#include "../headers/utile.h"

#include <time.h>


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
        erreur_ouverture_fichier();
    }

    return liste_prets;
}

void calcul_nb_pret(int *nb_pret) {
    FILE *fichier_pret = NULL;

    fichier_pret = fopen("sauvegardes/prets.txt", "r"); //"w" correspond a la ecriture seul (permet de limiter les erreurs) - fopen renvoie un pointeur sur le fichier

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
        erreur_ouverture_fichier();
    }
}

void rafrachir_tab_pret(Pret ***tab_pret, int *nb_pret) {
    lib_tab_pret(*tab_pret, nb_pret);
    calcul_nb_pret(nb_pret);
    *tab_pret = creer_tab_pret(nb_pret);
}

int saisie_securise_pret_tab_pret(Pret *saisie, Pret **tab_pret, int *nb_pret, int *nb_pret_totale) {
    return saisie_champs_pret(saisie, nb_pret_totale);
}

int saisie_champs_pret(Pret *pret, int *nb_prets_totale) {
    int valide;
    int valide_tot = 0; //5 si pas d'erreur
    int timestamp = (int) time(NULL);

    printf("     ID utilisateur : ");
//    saisie_entier(&(pret->id_utilisateur));
    valide_tot = valide_tot + valide;
    scanf("%d", &(pret->id_utilisateur));

    printf("     ID livre : ");
//    valide = saisie_chaine_caractere(pret->code_livre, 7);
    valide_tot = valide_tot + valide;
    scanf("%s", pret->code_livre);

    pret->etat_livre = 1;
    pret->date_pret = timestamp;
    pret->date_retour = timestamp + 1 * 3600 * 24 * 7 * 3;

    if (valide_tot == 1) {
        return (TRUE);
    } else {
        return (FALSE);
    }
}

void ajout_pret_fichier_pret(FILE *fichier_pret, Pret *saisie) {
    /*
     * id : int
     * id_utilisateur : int
     * code_livre : int
     * date_pret int (timestamp)
     * date_retour int (timestamp + 3semaines)
     * etat_livre : int
     */
    fichier_pret = fopen("sauvegardes/prets.txt", "a"); //"a" correspond a l'ajout - fopen renvoie un pointeur sur le fichier

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
                saisie->date_retour
                // 1 * 3600 * 24 * 7 * 3 -> 1sec * 3600 (donc heure) * 24 (donc jour) * 7 (donc semaine) * 3 (donc 3 semaines)
        );
        fprintf(
                fichier_pret,
                "etat_livre : %d \n",
                saisie->etat_livre
        );

        //Fermeture du fichier
        fclose(fichier_pret);

    } else { //le pointeur sur le fichier est toujours = NULL soit le fichier n'a pas était ouvert
        erreur_ouverture_fichier();
    }
}

void afficher_pret(Pret *pret) {
    printf("     %d: %d -> %s \n", pret->id_pret, pret->id_utilisateur, pret->code_livre);
}

void afficher_toute_info_pret(Pret *pret) {
    printf("     id : %d     id membre : %d     code livre : %s \n", pret->id_pret, pret->id_utilisateur, pret->code_livre);
    printf("     Date d'emprunt : ");
    afficher_date(definir_date(pret->date_pret));
    printf("\n     Date de retour : ");
    afficher_date(definir_date(pret->date_pret));
}