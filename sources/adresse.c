#include "../headers/adresse.h"


int saisie_adresse(Adresse *a) {

    //renvoie 1 si pas d'erreur et 0 sinon

    int valide_tot = 0; //4 si ok
    int valide;

    printf("          Numéro et rue : ");
    valide = saisie_chaine_caractere(a->rue, 50);
    valide_tot = valide_tot + valide;

    printf("          Code postal : ");
    valide = saisie_chaine_caractere(a->code_postal, 6);
    valide_tot = valide_tot + valide;

    printf("          Ville : ");
    valide = saisie_chaine_caractere(a->ville, 20);
    valide_tot = valide_tot + valide;

    printf("          Pays : ");
    valide = saisie_chaine_caractere(a->pays, 20);
    valide_tot = valide_tot + valide;

    if (valide_tot == 4) {
        return (TRUE);
    } else {
        return (FALSE);
    }
}

void afficher_adresse(Adresse *a) {
    printf("%s %s %s %s", a->rue, a->code_postal, a->ville, a->pays);
}