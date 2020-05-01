
#include "../headers/membre.h"


void saisie_adresse(Adresse* a){
    int valide;


    do{
        printf("          Numéro et rue : ");
        valide = saisie_chaine_caractere(a->adresse,50);
    }while(valide == FALSE);

    do{
        printf("          Code postal : ");
        valide = saisie_chaine_caractere(a->code_postal,6);
    }while(valide == FALSE);

    do{
        printf("          Ville : ");
        valide = saisie_chaine_caractere(a->ville,20);
    }while(valide == FALSE);

    do{
        printf("          Pays : ");
        valide = saisie_chaine_caractere(a->pays,20);
    }while(valide == FALSE);
}

void afficher_adresse(Adresse* a){
    printf("     %s\n     %s %s\n     %s\n",a->adresse, a->code_postal, a->ville, a->pays);
}

void generateur_identifiant(int* identifiant, Librairie* librairie){

    int i, valide;

    do{
        valide = TRUE;
        *identifiant = 10000000 + (rand()%99999999);

        for(i=0; i<librairie->nb_membre; i++)
        {
            if(*identifiant == librairie->liste_membre[i].identifiant){
                valide = FALSE;
            }
        }

    }while(valide == FALSE);

}

void saisir_membre(Membre* membre){
    int valide;

    do{
        printf("     Prenom : ");
        saisie_chaine_caractere(membre->prenom,20);
    }while(valide == FALSE);

    do{
        printf("     Nom : ");
        saisie_chaine_caractere(membre->nom,20);
    }while(valide == FALSE);

    do{
        printf("     Adresse : \n");
        saisie_adresse(&(membre->adresse));
    }while(valide == FALSE);


    char* position_cara_arobase = NULL;
    do{
        printf("     Email : ");
        saisie_chaine_caractere(membre->email,40);
        position_cara_arobase = strchr(membre->email, '@');
    }while((valide == FALSE) || (position_cara_arobase == NULL));

    do{
        printf("     Metier : ");
        saisie_chaine_caractere(membre->metier,30);
    }while(valide == FALSE);
}


void afficher_membre(Membre* membre){

    printf("%s %s\n", membre->prenom, membre->nom);

    printf("Identifiant : %d\n", membre->identifiant);

    printf("Adresse : \n");
    afficher_adresse(&(membre->adresse));

    printf("Email : %s\n", membre->email);

    printf("Metier : %s\n", membre->metier);
}