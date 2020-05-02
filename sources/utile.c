
#include "../headers/utile.h"

void supr_console(void) {
    system(SYSTEME_EXPLOITATION == "win" ? "cls" : "clear");
}


int saisie_chaine_caractere(char* chaine, int nb_cara_max){

    //renvoie 1 si pas d'erreur et 0 sinon

    char* position_cara_entree = NULL;
    fflush(stdin);
 
    // On lit le texte saisi au clavier
    if (fgets(chaine, nb_cara_max, stdin) != NULL)  // Verification si il y a une erreur de saisie
    {
        position_cara_entree = strchr(chaine, '\n'); // On recherche le caractère 'entrée' de validation de saisie
        if (position_cara_entree != NULL) 
        {
            *position_cara_entree = '\0'; // On remplace ce caractère par \0
        }

        return TRUE; // On renvoie 1 si la fonction s'est déroulée sans erreur
    }
    else
    {
        return FALSE; // On renvoie 0 s'il y a eu une erreur
    }
}

int compare_chaine_caractere(char* chaine1, char* chaine2){

    //retroune 1 (TRUE) si les deux chaines sont egales et 0 (FALSE) sinon

    int retour = TRUE;

    if(strlen(chaine1) != strlen(chaine2)){
        retour = FALSE;
    }
    else{
        int i;
        for(i=0; i<strlen(chaine1); i++)
        {
            if(chaine1[i] != chaine2[i]){
                retour = FALSE;
            }
        }
    }

    return (retour);
}