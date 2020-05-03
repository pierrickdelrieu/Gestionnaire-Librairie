
#include "../headers/membre.h"


Membre *creer_struct_membre() {
    Membre *x;

    x = (Membre *) malloc(sizeof(Membre));

    return (x);
}

void lib_struct_membre(Membre *membre) {
    free(membre);
}

void calcul_nb_membre(int *nb_membre) {
    FILE *fichier_membre = NULL;

    fichier_membre = fopen("sauvegardes/membre.txt", "r"); //"w" correspond a la ecriture seul (permet de limiter les erreurs) - fopen renvoie un pointeur sur le fichier

    if (fichier_membre != NULL) {

        //nombres d'identifiant
        int cara;
        *nb_membre = 0;
        do {
            cara = fgetc(fichier_membre);
            if (cara == '\n') {
                (*nb_membre)++;
            }
        } while (cara != EOF);

        //Fermeture du fichier
        fclose(fichier_membre);

    } else { //le pointeur sur le fichier est toujours = NULL soit le fichier n'a pas était ouvert
        printf("Erreur au niveau de l'ouverture du fichier\n");
        printf("Le programme n'a pas les autorisations nécessaire pour acceder aux fichiers de votre ordinateur\n");
        printf("Gerer ceci dans les préférence de votre ordinateur\n");
        exit(0); //Fin du programme
    }
}

Membre **creer_tab_membre(int *nb_membre) {
    Membre **liste_membres;
    FILE *fichier_membre = NULL;

    fichier_membre = fopen("sauvegardes/membre.txt", "r"); //"r" correspond a la lecture seul (permet de limiter les erreurs) - fopen renvoie un pointeur sur le fichier

    if (fichier_membre != NULL) {

        //allocation du tableau d'identifiant
        liste_membres = (Membre **) malloc((*nb_membre) * sizeof(Membre *));

        //recup des identifiants
        fseek(fichier_membre, 0, SEEK_SET); //remise du curseur au début du fichier
        int i;

        for (i = 0; i < (*nb_membre); i++) {
            liste_membres[i] = creer_struct_membre();
            fscanf(fichier_membre, "%s %s %d\n", &(liste_membres[i]->prenom), &(liste_membres[i]->nom), &(liste_membres[i]->identifiant));
            fscanf(fichier_membre, "adresse : %s %d %s %s\n", &(liste_membres[i]->adresse.adresse), &(liste_membres[i]->adresse.code_postal), &(liste_membres[i]->adresse.ville), &(liste_membres[i]->adresse.pays));
            fscanf(fichier_membre, "email : %s\n", &(liste_membres[i]->email));
            fscanf(fichier_membre, "metier : %s\n", &(liste_membres[i]->metier));
            //ajouter gestion des prets
        }

        //Fermeture du fichier
        fclose(fichier_membre);

    } else { //le pointeur sur le fichier est toujours = NULL soit le fichier n'a pas était ouvert
        printf("Erreur au niveau de l'ouverture du fichier\n");
        printf("Le programme n'a pas les autorisations nécessaire pour acceder aux fichiers de votre ordinateur\n");
        printf("Gerer ceci dans les préférence de votre ordinateur\n");
        exit(0); //Fin du programme
    }

    return (liste_membres);
}


int saisie_adresse(Adresse *a) {

    //renvoie 1 si pas d'erreur et 0 sinon

    int valide_tot = 0; //4 si ok
    int valide;

    printf("          Numéro et rue : ");
    valide = saisie_chaine_caractere(a->adresse, 50);
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
    
    if(valide_tot == 4){
        return (TRUE);
    }
    else{
        return (FALSE);
    }
}

void afficher_adresse(Adresse *a) {
    printf("     %s\n     %s %s\n     %s\n", a->adresse, a->code_postal, a->ville, a->pays);
}



int saisie_champs_membre(Membre *membre, int* nb_membres) {
    int valide;
    int valide_tot = 0; //5 si pas d'erreur

    printf("     Prenom : ");
    valide = saisie_chaine_caractere(membre->prenom, 20);
    valide_tot = valide_tot + valide;

    printf("     Nom : ");
    valide = saisie_chaine_caractere(membre->nom, 20);
    valide_tot = valide_tot + valide;

    printf("     Adresse : \n");
    valide = saisie_adresse(&(membre->adresse));
    valide_tot = valide_tot + valide;


    char *position_cara_arobase = NULL;
    printf("     Email : ");
    valide = saisie_chaine_caractere(membre->email, 40);
    position_cara_arobase = strchr(membre->email, '@');
    if(valide == TRUE){
        if(position_cara_arobase == NULL){
            valide = FALSE;
        }
    }
    valide_tot = valide_tot + valide;

    printf("     Metier : ");
    valide = saisie_chaine_caractere(membre->metier, 30);
    valide_tot = valide_tot + valide;

    membre->identifiant = *nb_membres + 1;

    if(valide_tot == 5){
        return (TRUE);
    }
    else{
        return (FALSE);
    }
}


void afficher_membre(Membre *membre) {

    printf("%s %s\n", membre->prenom, membre->nom);

    printf("Identifiant : %d\n", membre->identifiant);

    printf("Adresse : \n");
    afficher_adresse(&(membre->adresse));

    printf("Email : %s\n", membre->email);

    printf("Metier : %s\n", membre->metier);
}


void lib_tab_membre(Membre **tab_membre, int *nb_membres) {
    int i;

    for (i = 0; i < *nb_membres; i++) {
        lib_struct_membre(tab_membre[i]);
    }

    free(tab_membre);
}

int saisie_id_membre(int* id_membre, int* nb_membre) {
    printf("     Saisir l'identifiant du membre : ");
    scanf(" %d", id_membre);
    
    if(*id_membre <= nb_membre){
        return (TRUE);
    }
    else{
        return (FALSE);
    }
}

int saisie_securise_membre_tab_membre(Membre *saisie, Membre **tab_membre, int *nb_membre) {

    //retourne 1 (TRUE) si valeur saisie correspond a un membre deja existant et 0 sinon
    int valide = FALSE;
    int i;

    valide = saisie_membre(saisie, nb_membre);

    if (valide == TRUE) {
        valide = FALSE;

        //verif identifiant
        int indice_id_valide = 0;
        for (i = 0; i < (*nb_membre); i++) {
            if (saisie->identifiant == tab_membre[i]->identifiant) {
                valide = TRUE;
                indice_id_valide = i;
            }
        }

        //verif nom, prenom, adresse, metier
        if (valide == TRUE) {
            if (compare_chaine_caractere(saisie->prenom, tab_membre[indice_id_valide]->prenom) == FALSE) {
                valide = FALSE;
            }
        }
    }

    return (valide);
}
