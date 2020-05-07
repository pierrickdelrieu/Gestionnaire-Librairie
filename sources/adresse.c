#include "../headers/adresse.h"

/*fonction de saisie des champs de la sturcture adresse
elle renvoie 1 si la saisie s'est déroulé correctement sans erreur, et 0 sinon*/
int saisie_adresse(Adresse *a) {

    int valide_tot = 0; //4 si ok
    int valide;

    printf("          Numéro et rue : ");
    valide = saisie_chaine_caractere(a->rue, 70);
    valide_tot = valide_tot + valide;

    printf("          Code postal : ");
    valide = saisie_chaine_caractere(a->code_postal, 20);
    valide_tot = valide_tot + valide;

    printf("          Ville : ");
    valide = saisie_chaine_caractere(a->ville, 50);
    valide_tot = valide_tot + valide;

    printf("          Pays : ");
    valide = saisie_chaine_caractere(a->pays, 50);
    valide_tot = valide_tot + valide;

    if (valide_tot == 4) {
        return (TRUE);
    } else {
        return (FALSE);
    }
}


/*fonction d'affichage des champs de la sturcture adresse*/
void afficher_adresse(Adresse *a) {
    printf("%s %s %s %s", a->rue, a->code_postal, a->ville, a->pays);
}