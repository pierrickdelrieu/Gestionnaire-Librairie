#include "../headers/membre.h"


Membre *creer_struct_membre() {
    Membre *x;

    x = (Membre *) malloc(sizeof(Membre));

    return (x);
}

void lib_struct_membre(Membre *membre) {
    free(membre);
}

void rafrachir_tab_membre(Membre ***tab_membre, int *nb_membre) {

    lib_tab_membre(*tab_membre, nb_membre);

    calcul_nb_membre(nb_membre);

    *tab_membre = creer_tab_membre(nb_membre);
}

void calcul_nb_membre(int *nb_membre) {
    FILE *fichier_membre = NULL;

    fichier_membre = fopen("sauvegardes/membres.txt", "r"); //"w" correspond a la ecriture seul (permet de limiter les erreurs) - fopen renvoie un pointeur sur le fichier

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

        *nb_membre = (*nb_membre) / 11; 

    } else { //le pointeur sur le fichier est toujours = NULL soit le fichier n'a pas était ouvert
        printf("Erreur au niveau de l'ouverture du fichier\n");
        printf("Le programme n'a pas les autorisations nécessaire pour acceder aux fichiers de votre ordinateur\n");
        printf("Gerer ceci dans les préférence de votre ordinateur\n");
        exit(0); //Fin du programme
    }
}

int *creer_tri_tab_membre(Membre **liste_membre, int *nb_membre) {

    /* le tableau tri_tab membre contient les identifiant des membres de manieres trier (nom)
    */
    int *tri_tab = NULL;

    tri_tab = (int *) malloc((*nb_membre) * sizeof(int));

    int i, j;
    int position_tab;
    for (i = 0; i < (*nb_membre); i++) {
        position_tab = 0;
        for (j = 0; j < (*nb_membre); i++) {
            if (compare_chaine_caractere(liste_membre[i]->nom, liste_membre[j]->nom) == 1) {
                position_tab++;
            }
        }
        tri_tab[position_tab] = liste_membre[i]->identifiant;
    }

    return (tri_tab);
}


Membre **creer_tab_membre(int *nb_membre) {
    Membre **liste_membres;
    FILE *fichier_membre = NULL;

    fichier_membre = fopen("sauvegardes/membres.txt", "r"); //"r" correspond a la lecture seul (permet de limiter les erreurs) - fopen renvoie un pointeur sur le fichier

    if (fichier_membre != NULL) {

        //allocation du tableau d'identifiant
        liste_membres = (Membre **) malloc((*nb_membre) * sizeof(Membre *));

        //recup des identifiants
        int i;

        for (i = 0; i < (*nb_membre); i++) {
            liste_membres[i] = creer_struct_membre();
            fscanf(fichier_membre, "id : %d\n", &(liste_membres[i]->identifiant));
            lecture_chaine_cara_fichier(fichier_membre, liste_membres[i]->prenom, 20);
            lecture_chaine_cara_fichier(fichier_membre, liste_membres[i]->nom, 20);
            lecture_chaine_cara_fichier(fichier_membre, liste_membres[i]->adresse.rue, 50);
            lecture_chaine_cara_fichier(fichier_membre, liste_membres[i]->adresse.code_postal, 10);
            lecture_chaine_cara_fichier(fichier_membre, liste_membres[i]->adresse.ville, 30);
            lecture_chaine_cara_fichier(fichier_membre, liste_membres[i]->adresse.pays, 20);
            lecture_chaine_cara_fichier(fichier_membre, liste_membres[i]->email, 40);
            lecture_chaine_cara_fichier(fichier_membre, liste_membres[i]->metier, 30);
            fscanf(fichier_membre, "pret : %d - %d - %d\n\n", &(liste_membres[i]->liste_emprunt[0]), &(liste_membres[i]->liste_emprunt[1]), &(liste_membres[i]->liste_emprunt[2]));
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


int saisie_champs_membre(Membre *membre, int *nb_membres_totale) {
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
    if (valide == TRUE) {
        if (position_cara_arobase == NULL) {
            valide = FALSE;
        }
    }
    valide_tot = valide_tot + valide;

    printf("     Metier : ");
    valide = saisie_chaine_caractere(membre->metier, 30);
    valide_tot = valide_tot + valide;

    membre->identifiant = *nb_membres_totale + 1;

    if (valide_tot == 5) {
        return (TRUE);
    } else {
        return (FALSE);
    }
}


void afficher_membre(Membre *membre) {

    printf("%s %s  id : %d     adresse : ", membre->prenom, membre->nom, membre->identifiant);
    afficher_adresse(&(membre->adresse));
    printf("     email : %s     metier : %s\n", membre->email, membre->metier);
}

void afficher_toute_info_membre(Membre *membre) {
    printf("\n                    %s %s (identifiant : %d)\n", membre->prenom, membre->nom, membre->identifiant);
    printf("                    Adresse : ");
    afficher_adresse(&(membre->adresse));
    printf("\n                    Email : %s\n", membre->email);
    printf("                    Metier : %s\n", membre->metier);

    if ((membre->liste_emprunt[0] == 0) && (membre->liste_emprunt[1] == 0) && (membre->liste_emprunt[2] == 0)) {
        printf("                    Pret : Aucun pret en cour\n\n");
    }
}

void lib_tab_membre(Membre **tab_membre, int *nb_membres) {
    int i;

    for (i = 0; i < *nb_membres; i++) {
        lib_struct_membre(tab_membre[i]);
    }

    free(tab_membre);
}

int saisie_id_membre_tab_membre(Membre **tab_membre, int *id_membre, int *nb_membre) {
    scanf(" %d", id_membre);

    int valide = FALSE;

    if ((*id_membre) == 0) { // retour au menu
        valide = TRUE;
    } else {
        int i;
        for (i = 0; i < *(nb_membre); i++) {
            if ((*id_membre) == tab_membre[i]->identifiant) {
                valide = TRUE;
            }
        }
    }

    return (valide);
}

int saisie_securise_membre_tab_membre(Membre *saisie, Membre **tab_membre, int *nb_membre, int *nb_membre_totale) {

    //retourne 1 (TRUE) si valeur saisie correspond a un membre deja existant et 0 sinon
    int valide = FALSE;
    int i;

    valide = saisie_champs_membre(saisie, nb_membre_totale);

    if (valide == TRUE) {
        valide = FALSE;

        //verif mail
        int indice_id_valide = 0;
        for (i = 0; i < (*nb_membre); i++) {
            if (compare_chaine_caractere(saisie->email, tab_membre[i]->email) == 0) {
                valide = TRUE;
                indice_id_valide = i;
            }
        }
    }

    return (valide);
}


void ajout_membre_fichier_membre(FILE *fichier_membre, Membre *saisie) {
    fichier_membre = fopen("sauvegardes/membres.txt", "a"); //"a" correspond a l'ajout - fopen renvoie un pointeur sur le fichier

    if (fichier_membre != NULL) {

        fprintf(fichier_membre, "id : %d\n", saisie->identifiant);
        fprintf(fichier_membre, "%s\n%s\n", saisie->prenom,saisie->nom);
        fprintf(fichier_membre, "%s\n%s\n%s\n%s\n", saisie->adresse.rue,saisie->adresse.code_postal, saisie->adresse.ville, saisie->adresse.pays);
        fprintf(fichier_membre, "%s\n%s\n", saisie->email,saisie->metier);
        fprintf(fichier_membre, "pret : 0 - 0 - 0\n\n");

        //Fermeture du fichier
        fclose(fichier_membre);

    } else { //le pointeur sur le fichier est toujours = NULL soit le fichier n'a pas était ouvert
        printf("Erreur au niveau de l'ouverture du fichier\n");
        printf("Le programme n'a pas les autorisations nécessaire pour acceder aux fichiers de votre ordinateur\n");
        printf("Gerer ceci dans les préférence de votre ordinateur\n");
        exit(0); //Fin du programme
    }
}


void supr_membre_fichier_membre(FILE *fichier_membre, int *id_membre, Membre **tab_membre, int *nb_membre) {
    fichier_membre = fopen("sauvegardes/membres.txt", "w"); //"w" correspond a l'ecriture - fopen renvoie un pointeur sur le fichier

    if (fichier_membre != NULL) {

        int i;

        for(i=0; i<*(nb_membre); i++)
        {
            if(*id_membre != tab_membre[i]->identifiant){
                fprintf(fichier_membre, "id : %d\n", tab_membre[i]->identifiant);
                fprintf(fichier_membre, "%s\n%s\n", tab_membre[i]->prenom ,tab_membre[i]->nom);
                fprintf(fichier_membre, "%s\n%s\n%s\n%s\n", tab_membre[i]->adresse.rue, tab_membre[i]->adresse.code_postal, tab_membre[i]->adresse.ville, tab_membre[i]->adresse.pays);
                fprintf(fichier_membre, "%s\n%s\n", tab_membre[i]->email,tab_membre[i]->metier);
                fprintf(fichier_membre, "pret : %d - %d - %d\n\n", tab_membre[i]->liste_emprunt[0],tab_membre[i]->liste_emprunt[1],tab_membre[i]->liste_emprunt[2]);
            }
        }

        //Fermeture du fichier
        fclose(fichier_membre);

    } else { //le pointeur sur le fichier est toujours = NULL soit le fichier n'a pas était ouvert
        printf("Erreur au niveau de l'ouverture du fichier\n");
        printf("Le programme n'a pas les autorisations nécessaire pour acceder aux fichiers de votre ordinateur\n");
        printf("Gerer ceci dans les préférence de votre ordinateur\n");
        exit(0); //Fin du programme
    }
}


