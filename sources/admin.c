
#include "../headers/admin.h"


Admin* creer_struct_admin(){
    Admin* x;

    x = (Admin*) malloc(sizeof(Admin));

    return (x);
}


void lib_struct_admin(Admin* admin){
    free(admin);
}

void calcul_nb_admin(int* nb_identifiant){
    FILE* fichier_admin = NULL;

    fichier_admin = fopen("sauvegardes/admin.txt", "r"); //"w" correspond a la ecriture seul (permet de limiter les erreurs) - fopen renvoie un pointeur sur le fichier

    if (fichier_admin != NULL) {

        //nombres d'identifiant
        int cara;
        *nb_identifiant = 0;
        do{
            cara = fgetc(fichier_admin);
	        if(cara == '\n'){
		        (*nb_identifiant)++;
            } 
        }while(cara != EOF);

        //Fermeture du fichier
        fclose(fichier_admin);

    } else{ //le pointeur sur le fichier est toujours = NULL soit le fichier n'a pas était ouvert
        printf("Erreur au niveau de l'ouverture du fichier\n");
        printf("Le programme n'a pas les autorisations nécessaire pour acceder aux fichiers de votre ordinateur\n");
        printf("Gerer ceci dans les préférence de votre ordinateur\n");
        exit(0); //Fin du programme
    }
}


Admin** creer_tab_admin(int* nb_identifiant){
    Admin** tab_identifiant;
    FILE* fichier_admin = NULL;

    fichier_admin = fopen("sauvegardes/admin.txt", "r"); //"w" correspond a la ecriture seul (permet de limiter les erreurs) - fopen renvoie un pointeur sur le fichier

    if (fichier_admin != NULL) {

        //nombres d'identifiant
        int cara;
        *nb_identifiant = 0;
        do{
            cara = fgetc(fichier_admin);
	        if(cara == '\n'){
		        (*nb_identifiant)++;
            } 
        }while(cara != EOF);

        //allocation du tableau d'identifiant
        tab_identifiant = (Admin**) malloc((*nb_identifiant) * sizeof(Admin*));

        //recup des identifiants
        fseek(fichier_admin, 0, SEEK_SET); //remise du curseur au début du fichier
        int i;

        for(i=0; i<(*nb_identifiant); i++)
        {
            tab_identifiant[i] = creer_struct_admin();
            fscanf(fichier_admin, "id : %ld mp : %s\n", &(tab_identifiant[i]->identifiant), tab_identifiant[i]->mot_de_passe);
        }

        //Fermeture du fichier
        fclose(fichier_admin);

    } else{ //le pointeur sur le fichier est toujours = NULL soit le fichier n'a pas était ouvert
        printf("Erreur au niveau de l'ouverture du fichier\n");
        printf("Le programme n'a pas les autorisations nécessaire pour acceder aux fichiers de votre ordinateur\n");
        printf("Gerer ceci dans les préférence de votre ordinateur\n");
        exit(0); //Fin du programme
    }

    return (tab_identifiant);
}


void lib_tab_admin(Admin** tab_admin, int* nb_identifiant){
    int i;

    for(i=0; i<*nb_identifiant; i++){
        free(tab_admin[i]);
    }

    free(tab_admin);
}


void affichage_tab_admin(Admin** tab_identifiant, int* nb_identifiant){
    int choix;

    do{
        supr_console();
        int i;
        affichage_sous_titre("AFFICHAGE DES ADMINISTRATEURS");

        printf("Les identifiants et mot de passe des administrateurs sont : \n");

        for(i=0; i<(*nb_identifiant); i++)
        {
            printf("     id : %ld mp : %s\n", tab_identifiant[i]->identifiant, tab_identifiant[i]->mot_de_passe);
        }

        printf("\nSeul ces personnes ont les autoirisations pour gérer la bibliothèque\n\n");
        printf("     Saisir 1 pour revenir au menu : ");
        scanf(" %d", &choix);
    }while(choix != 1);
}

void saisie_identifiant(Admin* admin){
    printf("          Identifiant : ");
    scanf(" %ld",&(admin->identifiant));
    printf("          Mot de passe : ");
    saisie_chaine_caractere(admin->mot_de_passe,30);
}


Admin** saisie_nx_admin(Admin** tab_admin, int* nb_identifiant){

    supr_console();
    //Saise de l'administrateur a supprimer
    int valide = TRUE;
    Admin saisie;

    //saisie de l'administrateur a ajouter
    affichage_sous_titre("AJOUT NOUVEAU ADMINISTRATEUR");
    saisie_identifiant(&saisie);


    //creation du nouveau tableau admin
    Admin** nx_tab_admin;
    (*nb_identifiant)++;
    nx_tab_admin = (Admin**) malloc((*nb_identifiant) * sizeof(Admin*));

    int i;
    for(i=0; i<(*nb_identifiant)-1; i++)
    {
        nx_tab_admin[i] = creer_struct_admin();
        nx_tab_admin[i]->identifiant = tab_admin[i]->identifiant;
        strcpy(nx_tab_admin[i]->mot_de_passe, tab_admin[i]->mot_de_passe);
    }

    nx_tab_admin[(*nb_identifiant)-1] = creer_struct_admin();
    nx_tab_admin[(*nb_identifiant)-1]->identifiant = saisie.identifiant;
    strcpy(nx_tab_admin[(*nb_identifiant)-1]->mot_de_passe, saisie.mot_de_passe);

    //desalocation de l'ancien tableau d'admin
    lib_tab_admin(tab_admin,nb_identifiant-1);


    //recréation du contenu du fichier admin.txt
    FILE* fichier_admin = NULL;
    modif_fichier_admin(fichier_admin, nx_tab_admin, nb_identifiant);

    supr_console();
    printf("L'administrateur %ld a bien était ajouté\n", saisie.identifiant);

    pause_3sec();
    supr_console();

    return (nx_tab_admin);
}


int saisie_securise_id(Admin* saisie, Admin** tab_admin, int* nb_identifiant){

    //retourne 1 (TRUE) si valeur saisie corresponde a une valeur du fichier admin.txt et retourne 0 (FALSE) sinon
    int valide = FALSE;
    int i;
    
    saisie_identifiant(saisie);

    //verif identifiant
    int indice_id_valide = 0;
    for(i=0; i<(*nb_identifiant); i++)
    {
        if(saisie->identifiant == tab_admin[i]->identifiant){
            valide = TRUE;
            indice_id_valide = i;
        }
    }

    //verif mot de passe correspondant a l'identifiant
    if(valide == TRUE){
        if(compare_chaine_caractere(saisie->mot_de_passe, tab_admin[indice_id_valide]->mot_de_passe) == FALSE){
            valide = FALSE;
        }
    }

    return (valide);
}


void connexion(Admin** tab_admin, int* nb_identifiant){
    Admin saisie;
    int valide = TRUE;
    

    do{
        supr_console();
        affichage_titre_app();
        affichage_sous_titre("CONNEXION");
        if(valide == FALSE){
            printf("          ERREUR\n");
        }
        valide = saisie_securise_id(&saisie, tab_admin, nb_identifiant);
    }while(valide == FALSE);
}


Admin** supr_admin(Admin** tab_admin, int* nb_identifiant){

    supr_console();

    //Saise de l'administrateur a supprimer
    int valide = TRUE;
    Admin saisie;

    affichage_sous_titre("SUPRESSION ADMINISTRATEUR");
    do{
        if(valide == FALSE){
        printf("     ERREUR\n");
        }
        valide = saisie_securise_id(&saisie, tab_admin, nb_identifiant);

        //pas possible de supprimer l'administrateur de référence
        if((saisie.identifiant == ID_PROGRAMMEUR) && (compare_chaine_caractere(saisie.mot_de_passe, MP_PROGRAMMEUR) == TRUE)){
            valide = FALSE;
        }
        supr_console();
    }while(valide == FALSE);


    //supression de l'admin dans le tableau admin
    Admin** nx_tab_admin;
    int i;
    for(i=0; i<(*nb_identifiant); i++)
    {
        if(tab_admin[i]->identifiant == saisie.identifiant){
            tab_admin[i]->identifiant = 0;
        }
    }

    //creation du nouveau tableau admin
    *nb_identifiant = *nb_identifiant - 1;
    nx_tab_admin = (Admin**) malloc((*nb_identifiant) * sizeof(Admin*));

    int j=0;
    for(i=0; i<(*nb_identifiant)+1; i++)
    {
        if(tab_admin[i]->identifiant != 0){
            nx_tab_admin[i] = creer_struct_admin();
            nx_tab_admin[i]->identifiant = tab_admin[i]->identifiant;
            strcpy(nx_tab_admin[i]->mot_de_passe, tab_admin[i]->mot_de_passe);
            j++;
        }
    }

    //desalocation de l'ancien tableau d'admin
    lib_tab_admin(tab_admin,nb_identifiant);


    //supression et recréation du contenu du fichier admin.txt
    FILE* fichier_admin = NULL;
    modif_fichier_admin(fichier_admin, nx_tab_admin, nb_identifiant);

    supr_console();
    printf("L'administrateur %ld a bien était suprimer\n", saisie.identifiant);

    pause_3sec();
    supr_console();
    return (nx_tab_admin);
}


void modif_fichier_admin(FILE* fichier_admin, Admin** tab_admin, int* nb_identifiant){
    fichier_admin = fopen("sauvegardes/admin.txt", "w"); //"w" correspond a la ecriture seul (permet de limiter les erreurs) - fopen renvoie un pointeur sur le fichier

    if (fichier_admin != NULL) {
        int i;

        for(i=0; i<(*nb_identifiant); i++)
        {
            fprintf(fichier_admin, "id : %ld mp : %s\n",tab_admin[i]->identifiant, tab_admin[i]->mot_de_passe);
        }

        //Fermeture du fichier
        fclose(fichier_admin);

    } else{ //le pointeur sur le fichier est toujours = NULL soit le fichier n'a pas était ouvert
        printf("Erreur au niveau de l'ouverture du fichier\n");
        printf("Le programme n'a pas les autorisations nécessaire pour acceder aux fichiers de votre ordinateur\n");
        printf("Gerer ceci dans les préférence de votre ordinateur\n");
        exit(0); //Fin du programme
    }
}