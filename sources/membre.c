#include "../headers/membre.h"


//creer la structure membre de maniere dynamique
Membre *creer_struct_membre() {
    Membre *x;

    x = (Membre *) malloc(sizeof(Membre));

    return (x);
}


/*Libere la structure admin de maniere dynamique*/
void lib_struct_membre(Membre *membre) {
    free(membre);
}


/*Recuperation des sauvegardes faites dans le fichier membres*/
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
            lecture_chaine_cara_fichier(fichier_membre, liste_membres[i]->prenom, 40);
            lecture_chaine_cara_fichier(fichier_membre, liste_membres[i]->nom, 40);
            lecture_chaine_cara_fichier(fichier_membre, liste_membres[i]->adresse.rue, 70);
            lecture_chaine_cara_fichier(fichier_membre, liste_membres[i]->adresse.code_postal, 20);
            lecture_chaine_cara_fichier(fichier_membre, liste_membres[i]->adresse.ville, 50);
            lecture_chaine_cara_fichier(fichier_membre, liste_membres[i]->adresse.pays, 50);
            lecture_chaine_cara_fichier(fichier_membre, liste_membres[i]->email, 40);
            lecture_chaine_cara_fichier(fichier_membre, liste_membres[i]->metier, 40);
            fscanf(fichier_membre, "pret : %d - %d - %d\n\n", &(liste_membres[i]->liste_emprunt[0]), &(liste_membres[i]->liste_emprunt[1]), &(liste_membres[i]->liste_emprunt[2]));
        }
        
        //Fermeture du fichier
        fclose(fichier_membre);

    } else { //le pointeur sur le fichier est toujours = NULL soit le fichier n'a pas était ouvert
        erreur_ouverture_fichier();
    }

    return (liste_membres);
}


/*Permet de calculer le nombre de membre a partir du fichier membre.txt
Elle parcour le fichier et compte le nombre de membre qu'il contient (sachant que un membre = 11 ligne)*/
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
        erreur_ouverture_fichier();
    }
}


/* Modifie le tableau de membre en fonction des modifications (ajout et supression) qui ont eu lieu sur le fichier
Cette fonction suprimme et recrer le tableau, la realocation est trop dangeureuse*/
void rafrachir_tab_membre(Membre ***tab_membre, int *nb_membre) {

    lib_tab_membre(*tab_membre, nb_membre);

    calcul_nb_membre(nb_membre);

    *tab_membre = creer_tab_membre(nb_membre);
}


/*Saisie des champs de la structure d'un nouveau membre*/
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


/*Affiche un membre en ligne sans toute les infos sur les prets*/
void afficher_membre(Membre *membre) {

    printf("%s %s  id : %d     adresse : ", membre->nom, membre->prenom, membre->identifiant);
    afficher_adresse(&(membre->adresse));
    printf("     email : %s     metier : %s\n", membre->email, membre->metier);
}


/*affiche la totalité du membre avec tous les détais sur les prets*/
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


/*libere de maniere dynamique le tableau de membre*/
void lib_tab_membre(Membre **tab_membre, int *nb_membres) {
    int i;

    for (i = 0; i < *nb_membres; i++) {
        lib_struct_membre(tab_membre[i]);
    }

    free(tab_membre);
}


/*saisie d'un identifiant valide (cad d'un membre existant)
permet la verification lors de la supression ou la consultation d'un membre*/
int saisie_id_membre_tab_membre(Membre **tab_membre, int *id_membre, int *nb_membre) {
    saisie_entier(id_membre);

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


/*saisie des champs d'un membre valide (cad d'un membre existant)
permet la verification lors de la creation d'un nouveau membre
on considere que un membre est different si il possede une adresse mail jamais enregistré*/
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


/*initialisation d'un tableau contenant les indices des membres dans le tab_admin
le tableau contient les indices des membres trier dans l'ordre alphabétique (tri au niveau des nom de famille)
Cette fonction permet l'affichage de tous les membres*/
void init_tab_tri_ordre_alpha(Membre **tab_membre, int *tab, int *nb_membre) {

    int i, j;
    int cpt;

    for(i=0; i<(*nb_membre); i++)
    {
        cpt = 0;
        for(j=0; j<(*nb_membre); j++)
        {
            if(compare_chaine_caractere(tab_membre[i]->nom, tab_membre[j]->nom) == 1){ //tab_membre[i]->nom > tab_membre[j]->nom
                cpt ++;
            }
        }
        if(tab[cpt] == 0){
            tab[cpt] = i;
        } 
        else{
            tab[cpt+1] = i;
        }
    }
}


/*Modification du fichier membres.txt lors de l'ajout d'un membre
apres la modification il faudra rafraichir les valeurs du tab membre et nb_membre
ouverture du fichier en mode ajout pour ne pas modifier le contenue qui est deja dans le fichier*/
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
        erreur_ouverture_fichier();
    }
}


/*Modification du fichier membre.txt lors de la supression d'un membre
ouverture du fichier en mode ecriture pour suprimmer tous les elements du fichier
les membres seront ensuite tous reinsérré sauf celui dont on demande la suppression
apres la modification il faudra rafraichir les valeurs du tab membre et nb_membre*/
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
        erreur_ouverture_fichier();
    }
}


