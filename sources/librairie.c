
#include "../headers/librairie.h"


void connexion(Admin** tab_admin, int* nb_identifiant){
    Admin saisie;
    int valide = TRUE;
    

    do{
        supr_console();
        affichage_titre_app();
        affichage_sous_titre("CONNEXION");
        if(valide == FALSE){
            printf("          Identifiant ou mot de passe incorrect\n");
        }
        valide = saisie_securise_id(&saisie, tab_admin, nb_identifiant);
    }while(valide == FALSE);
}

void affichage_liste_admin(Admin** tab_identifiant, int* nb_identifiant){
    int choix;

    do{
        supr_console();
        affichage_sous_titre("AFFICHAGE DES ADMINISTRATEURS");
        affichage_tab_admin(tab_identifiant,nb_identifiant);
        printf("     Saisir 1 pour revenir au menu : ");
        scanf(" %d", &choix);
    }while(choix != 1);
}

void saisie_nx_admin(Admin*** tab_admin, int* nb_identifiant){

    supr_console();
    //Saise de l'administrateur a supprimer
    int valide = TRUE;
    Admin saisie;

    //saisie de l'administrateur a ajouter
    affichage_sous_titre("AJOUT NOUVEAU ADMINISTRATEUR");
    saisie_identifiant(&saisie);

    //recréation du contenu du fichier admin.txt
    FILE* fichier_admin = NULL;
    ajout_admin_fichier_admin(fichier_admin, &(saisie));

    *tab_admin = rafrachir_tab_admin(*tab_admin,nb_identifiant); //modif du nombre d'identifiant

    supr_console();
    printf("L'administrateur %ld a bien était ajouté\n", saisie.identifiant);

    pause_3sec();
    supr_console();
}

void supr_admin(Admin*** tab_admin, int* nb_identifiant){

    supr_console();

    //Saisie de l'administrateur a supprimer
    int valide = TRUE;
    Admin saisie;

    affichage_sous_titre("SUPRESSION ADMINISTRATEUR");
    affichage_tab_admin(*tab_admin,nb_identifiant);
    do{
        if(valide == FALSE){
        printf("     ERREUR\n");
        }
        valide = saisie_securise_id(&saisie, *tab_admin, nb_identifiant);

        //pas possible de supprimer l'administrateur de référence
        if((saisie.identifiant == ID_PROGRAMMEUR) && (compare_chaine_caractere(saisie.mot_de_passe, MP_PROGRAMMEUR) == TRUE)){
            valide = FALSE;
        }
        supr_console();
    }while(valide == FALSE);


    //supression et recréation du contenu du fichier admin.txt
    FILE* fichier_admin = NULL;
    supr_admin_fichier_admin(fichier_admin,*(tab_admin), &saisie , nb_identifiant);
    *tab_admin = rafrachir_tab_admin(*tab_admin,nb_identifiant);

    supr_console();
    printf("L'administrateur %ld a bien était suprimer\n", saisie.identifiant);

    pause_3sec();
    supr_console();
}