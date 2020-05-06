#include "../headers/utile.h"

void supr_console(void) {
    system(strcmp(SYSTEME_EXPLOITATION, "win") == 0 ? "cls" : "clear");
}



int saisie_chaine_caractere(char *chaine, int nb_cara_max) {

    //renvoie 1 si pas d'erreur et 0 sinon

    char *position_cara_entree = NULL;
    fflush(stdin);

    // On lit le texte saisi au clavier
    if (fgets(chaine, nb_cara_max, stdin) != NULL)  // Verification si il y a une erreur de saisie
    {
        position_cara_entree = strchr(chaine, '\n'); // On recherche le caractère 'entrée' de validation de saisie
        if (position_cara_entree != NULL) {
            *position_cara_entree = '\0'; // On remplace ce caractère par \0
        }

        return TRUE; // On renvoie 1 si la fonction s'est déroulée sans erreur
    } else {
        return FALSE; // On renvoie 0 s'il y a eu une erreur
    }
}

int compare_chaine_caractere(char *chaine1, char *chaine2) {

    //retroune 0 si chaine1= chaine2 et 1 si chaine chaine1>chaine2 et -1 si chaine chaine1<chaine2

    int retour = TRUE;

    retour = strcmp(chaine1, chaine2);

    if (retour < 0) {
        return (-1);
    } else if (retour > 0) {
        return (1);
    } else {
        return (0);
    }
}

int lecture_chaine_cara_fichier(FILE *fichier, char *chaine, int taille_max) {
    int valide;

    char *position_cara_entree = NULL;

    if (fgets(chaine, taille_max, fichier) != NULL)  // Verification si il y a une erreur de saisie
    {
        position_cara_entree = strchr(chaine, '\n'); // On recherche le caractère 'entrée' de validation de saisie
        if (position_cara_entree != NULL) {
            *position_cara_entree = '\0'; // On remplace ce caractère par \0
        }

        return TRUE; // On renvoie 1 si la fonction s'est déroulée sans erreur
    } else {
        return FALSE; // On renvoie 0 s'il y a eu une erreur
    }
}

void affichage_date_du_jour(void) {
    system(strcmp(SYSTEME_EXPLOITATION, "win") == 0 ? "echo  %date%-%time%" : "date");
}
