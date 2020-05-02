
#include "../headers/admin.h"

#include <stdio.h>
#include <stdlib.h>


//création de l'identifaint du programmeur
void recup_admin(Admin** tab_identifiant, int* nb_identifiant){
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
        printf("- nb_id = %d\n",*nb_identifiant);
        *tab_identifiant = (Admin*) malloc((*nb_identifiant) * sizeof(Admin));

        //recup des identifiants
        fseek(fichier_admin, 0, SEEK_SET); //remise du curseur au début du fichier
        int i;
        for(i=0; i<(*nb_identifiant); i++)
        {
            printf("nb_id = %d\n",*nb_identifiant);
            fscanf(fichier_admin, "id : %d mp : %s\n", &(tab_identifiant[i]->identifiant), tab_identifiant[i]->mot_de_passe);
            printf("nb_id = %d\n",*nb_identifiant);
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

void affichage_tab_admin(Admin** tab_identifiant, int* nb_identifiant){
    int i;

    printf("Les identifiants et mot de passe des administrateurs sont : \n");
    for(i=0; i<(*nb_identifiant); i++)
    {
        printf("     id : %d mp : %s\n", tab_identifiant[i]->identifiant, tab_identifiant[i]->mot_de_passe);
    }

    printf("Seul ces personnes ont les autoirisations pour gérer la bibliothèque\n");
}



void saisie_identifiant(Admin* admin){
    printf("                    ..........CONNEXION..........\n\n\n\n");

    printf("               Identifiant : ");
    scanf(" %d",&(admin->identifiant));
    printf("               Mot de passe : ");
    saisie_chaine_caractere(admin->mot_de_passe,30);

    //ajouter l'insertion dans le fichier admin.txt
}