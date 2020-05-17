#include "../headers/pret.h"

#include <time.h>


Pret *creer_struct_pret() {
    return (Pret *) malloc(sizeof(Pret));
}

void lib_struct_pret(Pret *pret) {
    free(pret);
}

void lib_tab_pret(Pret **tab_pret, int *nb_prets) {
    int i;

    for (i = 0; i < *nb_prets; i++) {
        lib_struct_pret(tab_pret[i]);
    }

    free(tab_pret);
}

Pret **creer_tab_pret(int *nb_pret) {
    Pret **liste_prets;
    FILE *fichier_pret = NULL;

    fichier_pret = fopen("sauvegardes/prets.txt", "r");

    if (fichier_pret != NULL) {
        liste_prets = (Pret **) malloc((*nb_pret) * sizeof(Pret *));
        int i;

        for (i = 0; i < (*nb_pret); i++) {
            liste_prets[i] = creer_struct_pret();
            fscanf(
                    fichier_pret,
                    "id : %d | ", &liste_prets[i]->id_pret
            );
            fscanf(
                    fichier_pret,
                    "id_membre : %d | ",
                    &liste_prets[i]->id_membre
            );
            fscanf(
                    fichier_pret,
                    "code_livre : %s | ",
                    liste_prets[i]->code_livre
            );
            fscanf(
                    fichier_pret,
                    "date_pret : %d | ",
                    &(liste_prets[i]->date_pret)
            );
            fscanf(
                    fichier_pret,
                    "date_retour : %d | ",
                    &(liste_prets[i]->date_retour)
            );
            fscanf(
                    fichier_pret,
                    "etat_livre : %d | ",
                    &(liste_prets[i]->etat_livre)
            );
        }

        fclose(fichier_pret);

    } else { //le pointeur sur le fichier est toujours = NULL soit le fichier n'a pas était ouvert
        erreur_ouverture_fichier();
    }

    return liste_prets;
}

void calcul_nb_pret(int *nb_pret) {
    FILE *fichier_pret = NULL;

    fichier_pret = fopen("sauvegardes/prets.txt", "r"); //"w" correspond a la ecriture seul (permet de limiter les erreurs) - fopen renvoie un pointeur sur le fichier

    if (fichier_pret != NULL) {
        int cara;
        *nb_pret = 0;

        do {
            cara = fgetc(fichier_pret);
            if (cara == '\n') {
                (*nb_pret)++;
            }
        } while (cara != EOF);

        //Fermeture du fichier
        fclose(fichier_pret);

    } else { //le pointeur sur le fichier est toujours = NULL soit le fichier n'a pas était ouvert
        erreur_ouverture_fichier();
    }
}

void rafrachir_tab_pret(Pret ***tab_pret, int *nb_pret) {
    lib_tab_pret(*tab_pret, nb_pret);
    calcul_nb_pret(nb_pret);
    *tab_pret = creer_tab_pret(nb_pret);
}

int saisie_securise_pret_tab_pret(Pret *saisie, Pret **tab_pret, int *nb_pret) {
    return saisie_champs_pret(saisie);
}

int saisie_champs_pret(Pret *pret) {
    int valide;
    int valide_tot = 0; //2 si pas d'erreur
    int timestamp = (int) time(NULL);

    printf("     Identifiant membre : ");
    saisie_entier(&(pret->id_membre));
    if(pret->id_membre == -1){
        valide = 0;
    }
    else
    {
        valide = 1;
    }
    valide_tot = valide_tot + valide;
    // scanf("%d", &(pret->id_membre));

    printf("     Code livre : ");
    valide = saisie_code_livre(pret->code_livre);
    valide_tot = valide_tot + valide;
    // scanf("%s", pret->code_livre);

    pret->etat_livre = 1;
    pret->date_pret = timestamp;
    pret->date_retour = timestamp + 1 * 3600 * 24 * 7 * 3;

    if (valide_tot == 2) {
        return (TRUE);
    } else {
        return (FALSE);
    }
}

void ajout_pret_fichier_pret(FILE *fichier_pret, Pret *saisie) {
    /*
     * id : int
     * id_membre : int
     * code_livre : int
     * date_pret int (timestamp)
     * date_retour int (timestamp + 3semaines)
     * etat_livre : int
     */
    fichier_pret = fopen("sauvegardes/prets.txt", "a"); //"a" correspond a l'ajout - fopen renvoie un pointeur sur le fichier

    if (fichier_pret != NULL) {
        fprintf(
                fichier_pret,
                "id : %d | ",
                saisie->id_pret
        );
        fprintf(
                fichier_pret,
                "id_membre : %d | ",
                saisie->id_membre
        );
        fprintf(
                fichier_pret,
                "code_livre : %s | ",
                saisie->code_livre
        );
        fprintf(
                fichier_pret,
                "date_pret : %d | ",
                saisie->date_pret
        );
        fprintf(
                fichier_pret,
                "date_retour : %d | ",
                saisie->date_retour
                // 1 * 3600 * 24 * 7 * 3 -> 1sec * 3600 (donc heure) * 24 (donc jour) * 7 (donc semaine) * 3 (donc 3 semaines)
        );
        fprintf(
                fichier_pret,
                "etat_livre : %d \n",
                saisie->etat_livre
        );

        //Fermeture du fichier
        fclose(fichier_pret);

    } else { //le pointeur sur le fichier est toujours = NULL soit le fichier n'a pas était ouvert
        erreur_ouverture_fichier();
    }
}

void afficher_pret(Pret *pret) {
    printf("     %d: %d -> %s \n", pret->id_pret, pret->id_membre, pret->code_livre);
}

void afficher_toute_info_pret(Pret *pret) {
    printf("     id : %d     id membre : %d     code livre : %s \n", pret->id_pret, pret->id_membre, pret->code_livre);
    printf("     Date d'emprunt : ");
    afficher_date(definir_date(pret->date_pret));
    printf("\n     Date de retour : ");
    afficher_date(definir_date(pret->date_pret));
}


/*fonction utilisé pour l'ajout d'un pret
verification si le mebre existe et verification si le livre existe*/
int saisie_champ_pret_securise(Pret *saisie, Membre **tab_membre, Livre **tab_livre, int *nb_membre, int *nb_livre)
{
    //la fonction retourne 1 (TRUE) si la saisie du pret est valide (livre et membre existant) et 0 (FALSE) sinon
    int valide;

    valide = saisie_champs_pret(saisie);

    if(valide == TRUE){
        int i;
        
        //verification du membre
        int indice_membre = -1;
        valide = FALSE;
        for(i=0; i<(*nb_membre); i++)
        {
            if(saisie->id_membre == tab_membre[i]->identifiant) {
                valide = TRUE;
                indice_membre = i;
            }
        }

        //verifier si le membre peut encore emprunté un livre (pret en retard ou pret max atteint)
        if(valide == TRUE){
            if(calcul_nb_pret_membre(tab_membre[indice_membre]) == 0) //si il y a aucun pret
                valide = TRUE;
            else 
                valide = FALSE;
        }

        //verification du livre
        int indice_livre = -1;
        if(valide == TRUE) {
            valide = FALSE;
            for(i=0; i<(*nb_livre); i++)
            {
                if(saisie->code_livre == tab_livre[i]->code) {
                    valide = TRUE;
                    indice_livre = i;
                }
            }
        }

        //verification si le livre est disponible
        if(valide == TRUE){
            if(tab_livre[i]->nb_exemplaires_dispo != 0)
                valide = TRUE;
            else
                valide = FALSE;
        }
    }

    return (valide);
}

/*verification si un membre a des prets en retard
La fonction retourne un tableau avec les indices des prets étant en retard dans le tableau de pret*/
// int* membre_nb_pret_retard(Pret **tab_pret, int *id_membre)
// {
//     int* tab_indice = NULL;
    

// }


/*cette fonction est a appellé seulement si la fonction saisie champs pret securise est verifié*/
void ajout_pret_struct_membre(Pret *pret, Membre **tab_membre)
{

    //recuperation de l'indice du membre dans le tableau de membre
    int i;
    do{
        i++;
    } while(tab_membre[i]->identifiant != pret->id_membre);


    //modification du membre
    int valide = 0;
    do{
        if(tab_membre[i]->liste_emprunt[valide] != 0){
            tab_membre[i]->liste_emprunt[valide] = pret->id_pret;
            valide = -1;
        }   
        else
            valide ++;
    }while(valide == 0);
}


/*cette fonction est a appellé seulement si la fonction saisie champs pret securise est verifié*/
void ajout_pret_struct_livre(Pret *pret, Livre **tab_livre)
{
    //recuperation de l'indice du livre dans le tableau de livre
    int i;
    do{
        i++;
    } while(tab_livre[i]->code != pret->code_livre);


    //modification du livre (supression d'un exemplaire disponible)
    tab_livre[i]->nb_exemplaires_dispo --; 
 
}