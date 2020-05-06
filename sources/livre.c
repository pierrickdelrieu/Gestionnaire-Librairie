#include "../headers/livre.h"

void saisir_date(Date *d) {
    do {
        printf("     jour : ");
        scanf(" %d", &(d->jour));  //(*d).jour <=> &(d->jour)
    } while ((d->jour <= 0) || (d->jour > 31));

    do {
        printf("     mois : ");
        scanf(" %d", &(d->mois));
    } while ((d->mois <= 0) || (d->mois > 12));

    printf("     annee : ");
    scanf(" %d", &(d->annee));
}


void afficher_date(Date *d) {
    printf("%d / %d / %d\n", d->jour, d->mois, d->annee);
}

int compare_date(Date *d1, Date *d2) {
    /*retourne 0 si d1 = d2 
      retourne 1 si d1 > d2 
      retourne −1 si d1 < d2*/

    int retour = -1; //valeur de retour

    if ((d2->annee == d1->annee) && (d2->mois == d1->mois) && (d2->jour == d1->jour)) {
        retour = 0;
    } else {
        if (d2->annee < d1->annee) {
            retour = 1;
        } else {
            if (d2->mois < d1->mois) {
                retour = 1;
            } else {
                if (d2->jour < d1->jour) {
                    retour = 1;
                }
            }
        }
    }

    return (retour);
}

void afficher_livre(Livre *livre) {
    printf("\n                    %s (identifiant : %d)\n", livre->titre, livre->code);
    printf("                    Auteur : %s\n", livre->auteur);
}

void afficher_toute_info_livre(Livre *livre) {
    printf("\n                    %s (identifiant : %d)\n", livre->titre, livre->code);
    printf("                    Auteur : %s\n", livre->auteur);
    printf("                    Nombre d'exemplaire total: %d\n", livre->nb_exemplaires);
    printf("                    Nombre d'exemplaire disponnible : %d\n", livre->nb_exemplaires_dispo);

    if (livre->nb_exemplaires == livre->nb_exemplaires_dispo) {
        printf("                    Pret : Aucun pret en cour\n\n");
    }
}

int saisie_id_livre_tab_livre(Livre **tab_livre, int *id_livre, int *nb_livre) {
    scanf(" %d", id_livre);

    int valide = FALSE;

    if ((*id_livre) == 0) { // retour au menu
        valide = TRUE;
    } else {
        int i;
        for (i = 0; i < *(id_livre); i++) {
            if ((*id_livre) == tab_livre[i]->code) {
                valide = TRUE;
            }
        }
    }

    return (valide);
}

int saisie_champs_livre(Livre *livre, int *nb_livre) {
    int valide;
    int valide_tot = 0; //5 si pas d'erreur

    printf("     Titre : ");
    valide = saisie_chaine_caractere(livre->titre, 20);
    valide_tot = valide_tot + valide;

    printf("     Auteur : ");
    valide = saisie_chaine_caractere(livre->auteur, 20);
    valide_tot = valide_tot + valide;

    livre->code = nb_livre + 1;
    valide_tot = valide_tot + 1;

    if (valide_tot == 3) {
        return (TRUE);
    } else {
        return (FALSE);
    }
}

int saisie_securise_livre_tab_livre(Livre *saisie, Livre **tab_livre, int *nb_livre, int *nb_livre_totale) {

    //retourne 1 (TRUE) si valeur saisie correspond a un livre deja existant et 0 sinon
    int valide = FALSE;
    int i;

    valide = saisie_champs_livre(saisie, nb_livre_totale);

    return (valide);
}

void ajout_livre_fichier_livre(FILE *fichier_livre, Livre *saisie) {
    fichier_livre = fopen("sauvegardes/livre.txt", "a"); //"a" correspond a l'ajout - fopen renvoie un pointeur sur le fichier

    if (fichier_livre != NULL) {
        fprintf(
                fichier_livre,
                "titre : %s | ",
                saisie->titre
        );
        fprintf(
                fichier_livre,
                "auteur : %s | ",
                saisie->auteur
        );
        fprintf(
                fichier_livre,
                "code : %d | ",
                saisie->code
        );
        fprintf(
                fichier_livre,
                "nb_exemplaires : %d | ",
                saisie->nb_exemplaires
        );
        fprintf(
                fichier_livre,
                "nb_exemplaires : %d | ",
                saisie->nb_exemplaires
        );

        //Fermeture du fichier
        fclose(fichier_livre);

    } else { //le pointeur sur le fichier est toujours = NULL soit le fichier n'a pas était ouvert
        printf("Erreur au niveau de l'ouverture du fichier\n");
        printf("Le programme n'a pas les autorisations nécessaire pour acceder aux fichiers de votre ordinateur\n");
        printf("Gerer ceci dans les préférence de votre ordinateur\n");
        exit(0); //Fin du programme
    }
}

void rafrachir_tab_livre(Livre ***tab_livre, int *nb_livre) {

    lib_tab_livre(*tab_livre, nb_livre);

    calcul_nb_livre(nb_livre);

    *tab_livre = creer_tab_livre(nb_livre);
}