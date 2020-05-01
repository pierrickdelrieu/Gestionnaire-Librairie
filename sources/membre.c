
#include "../headers/membre.h"


void saisie_adresse(Adresse* a){

    printf("Adresse : ");

    printf("     Numéro et rue : ");
    gets(a->adresse);

    printf("     Code postal : ");
    scanf(" %d",&(a->code_postal));

    printf("     Ville : ");
    gets(a->ville);

    printf("     Pays : ");
    gets(a->pays);
}
