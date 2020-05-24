#include "../headers/pret.h"


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
        long int date_pret, date_retour;

        for (i = 0; i < (*nb_pret); i++) {
            liste_prets[i] = creer_struct_pret();
            fscanf(fichier_pret, "id : %d | ", &liste_prets[i]->id_pret);
            fscanf(fichier_pret, "id_membre : %d | ", &liste_prets[i]->id_membre);
            fscanf(fichier_pret, "code_livre : %s | ", liste_prets[i]->code_livre);
            fscanf(fichier_pret, "date_pret : %ld | ", &(date_pret));
            fscanf(fichier_pret, "date_retour : %ld | ", &(date_retour));
            fscanf(fichier_pret, "etat_livre : %d | ", &(liste_prets[i]->etat_livre));

            // conversion du timestamp en date
            liste_prets[i]->date_pret = definir_date(date_pret);
            liste_prets[i]->date_retour = definir_date(date_retour);
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


int saisie_champs_pret(Pret *pret, int *donnee) {
    int valide;
    int valide_tot = 0; //2 si pas d'erreur
    long int timestamp = (int) time(NULL);

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

    printf("     Code livre : ");
    valide = saisie_code_livre(pret->code_livre);
    valide_tot = valide_tot + valide;

    pret->etat_livre = 1;
    pret->date_pret = definir_date(timestamp);
    pret->date_retour = definir_date(timestamp + 1 * 3600 * 24 * 7 * 3); // 3 semaines plus tard

    pret->id_pret = donnee[1] + 1;

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
        fprintf(fichier_pret, "id : %d | ", saisie->id_pret);
        fprintf(fichier_pret, "id_membre : %d | ", saisie->id_membre);
        fprintf(fichier_pret, "code_livre : %s | ", saisie->code_livre);
        fprintf(fichier_pret, "date_pret : %ld | ", recuperer_timestamp(&saisie->date_pret));
        fprintf(fichier_pret, "date_retour : %ld | ", recuperer_timestamp(&saisie->date_retour)); // 1 * 3600 * 24 * 7 * 3 -> 1sec * 3600 (donc heure) * 24 (donc jour) * 7 (donc semaine) * 3 (donc 3 semaines)
        fprintf(fichier_pret, "etat_livre : %d \n", saisie->etat_livre);


        //Fermeture du fichier
        fclose(fichier_pret);

    } else { //le pointeur sur le fichier est toujours = NULL soit le fichier n'a pas était ouvert
        erreur_ouverture_fichier();
    }
}

void afficher_pret(Pret *pret, Membre **tab_membre, Livre **tab_livre, int *nb_membre, int *nb_livre) 
{
    int i;

    //recuperation indice membre
    int indice_membre;
    for(i=0; i<*nb_membre; i++) 
    {
        if(tab_membre[i]->identifiant == pret->id_membre) {
            indice_membre = i;
        }
    }


    //recuperation indice livre
    int indice_livre;
    for(i=0; i<*nb_livre; i++) 
    {
        if(compare_chaine_caractere(tab_livre[i]->code, pret->code_livre) == 0) {
            indice_livre = i;
        }
    }


    printf("   id pret : %d   membre : %s %s (%d)   livre : %s de %s (%s)   date d'emprunt : ", pret->id_pret, tab_membre[indice_membre]->prenom, tab_membre[indice_membre]->nom, tab_membre[indice_membre]->identifiant, tab_livre[indice_livre]->titre, tab_livre[indice_livre]->auteur, pret->code_livre);
    afficher_date(&pret->date_pret);
    printf("   date de retour : ");
    afficher_date(&pret->date_retour);
    
    if(pret->etat_livre == 1) {
        printf("   A JOUR\n");
    }
    else if(pret->etat_livre == 0) {
        printf("   EN RETARD\n");
    }

}

void afficher_toute_info_pret(int *id_pret, Pret **tab_pret, int *nb_pret, Livre **tab_livre, int *nb_livre, Membre **tab_membre, int *nb_membre) {
    int i;

    //recuperation indice pret
    int indice_pret;
    for(i=0; i<*nb_pret; i++) 
    {
        if(tab_pret[i]->id_pret == *id_pret) {
            indice_pret = i;
        }
    }

    //recuperation indice membre
    int indice_membre;
    for(i=0; i<*nb_membre; i++) 
    {
        if(tab_membre[i]->identifiant == tab_pret[indice_pret]->id_membre) {
            indice_membre = i;
        }
    }

    //recuperation indice livre
    int indice_livre;
    for(i=0; i<*nb_livre; i++) 
    {
        if(compare_chaine_caractere(tab_livre[i]->code, tab_pret[indice_pret]->code_livre) == 0) {
            indice_livre = i;
        }
    }

    printf("     Numéro du pret : %d\n", tab_pret[indice_pret]->id_pret);
    printf("     Membre : %s %s (id : %d)   email : %s\n", tab_membre[indice_membre]->prenom, tab_membre[indice_membre]->nom, tab_membre[indice_membre]->identifiant, tab_membre[indice_membre]->email);
    printf("     Livre : %s de %s (id : %s)\n", tab_livre[indice_livre]->titre, tab_livre[indice_livre]->auteur, tab_livre[indice_livre]->code);
    printf("     Date d'emprunt : ");
    afficher_date(&tab_pret[indice_pret]->date_pret);
    printf("     Date de retour : ");
    afficher_date(&tab_pret[indice_pret]->date_retour);

    if(tab_pret[indice_pret]->etat_livre == 1) {
        printf("   Le pret est a jour\n");
    }
    else if(tab_pret[indice_pret]->etat_livre == 0) {
        printf("   !!! Le pret est en retard !!!\n");
    }
}


/*fonction utilisé pour l'ajout d'un pret
verification si le mebre existe et verification si le livre existe*/
int saisie_champ_pret_securise_ajout(Pret *saisie, Membre **tab_membre, Livre **tab_livre, Pret **tab_pret, int *nb_membre, int *nb_livre, int *nb_pret, int *donnee)
{
    //la fonction retourne 1 (TRUE) si la saisie du pret est valide (livre et membre existant) et 0 (FALSE) sinon
    int valide;

    valide = saisie_champs_pret(saisie, donnee);

    if ((saisie->id_membre == 0) || (compare_chaine_caractere(saisie->code_livre,"0") == 0)) { //si l'utilisateur veut revenir au menu
        valide = TRUE;
    }
    else if (valide == TRUE) {
        int i;
        
        // verification si l'identifiant du membre existe
        int indice_membre = -1;
        valide = FALSE;
        for(i=0; i<(*nb_membre); i++)
        {
            if(saisie->id_membre == tab_membre[i]->identifiant) {
                valide = TRUE;
                indice_membre = i;
            }
        }

        // verification si le membre a atteint le nombre de pret maximum
        if(valide == TRUE) {
            valide = FALSE;

            if(calcul_nb_pret_membre(tab_membre[indice_membre]) < NB_EMPRUNT_MAX) { //si il y a aucun pret
                valide = TRUE;
            }   
            else {
                valide = FALSE;
            }
        }

        // verification si le membre a des prets en retard
        if(valide == TRUE){
            if(membre_nb_pret_retard(tab_pret, nb_pret, tab_membre, &(saisie->id_membre)) > 0) { //si au moins un pret en retard
                valide = FALSE;
            } else {
                valide = TRUE;
            }
        }


        //verification du livre
        int indice_livre = -1;
        if(valide == TRUE) {
            valide = FALSE;
            for(i=0; i<(*nb_livre); i++)
            {
                if(compare_chaine_caractere(saisie->code_livre, tab_livre[i]->code) == 0) {
                    valide = TRUE;
                    indice_livre = i;
                }
            }
        }


        //verification si le livre est disponible
        if(valide == TRUE){
            if(tab_livre[indice_livre]->nb_exemplaires_dispo != 0) {
                valide = TRUE;
            }
            else {
                valide = FALSE;
            }
        }
    }

    return (valide);
}


/*verification si un membre a des prets en retard
La fonction retourne le nombre de pret en retard d'un membre*/
int membre_nb_pret_retard(Pret **tab_pret, int *nb_pret, Membre **tab_membre, int *id_membre)
{
    // recuperation de l'indice du membre dans le tableau de membre
    int i = 0;
    while(tab_membre[i]->identifiant != *id_membre) {
        i++;
    }

    int nb_pret_membre;
    nb_pret_membre = calcul_nb_pret_membre(tab_membre[i]);

    // calul du nombre de pret en retard
    int nb_pret_retard = 0;
    int j; //parcours le tableau de pret
    int k; //parcours les id prets de la structure membre
    for(j=0; j<(*nb_pret); j++)
    {
        for(k=0; k<nb_pret_membre; k++) //on parcours tout les prets du membre
        {
            if(tab_pret[j]->id_pret == tab_membre[i]->liste_emprunt[k]) { //on regarde si le pret correspond au membre
                if(tab_pret[j]->etat_livre == 0){ //le pret est en retard
                    nb_pret_retard ++;
                }
            }
        }
    }
    
    return (nb_pret_retard);
}


/*cette fonction est a appellé seulement si la fonction saisie champs pret securise est verifié*/
void ajout_pret_struct_membre(Pret *pret, Membre **tab_membre)
{
    // recuperation de l'indice du membre dans le tableau de membre
    int i = 0;
    while(tab_membre[i]->identifiant != pret->id_membre) {
        i++;
    }

    //modification du membre
    int valide = 0;
    do {
        if(tab_membre[i]->liste_emprunt[valide] == 0) { //si c'est la case a modifier (entrer l'id du pret)
            tab_membre[i]->liste_emprunt[valide] = pret->id_pret; //enregistrement de l'identifiant du pret
            valide = 0;
        }   
        else {
            valide ++;
        }
    } while(valide != 0);
}


/*cette fonction est a appellé seulement si la fonction saisie champs pret securise est verifié*/
void ajout_pret_struct_livre(Pret *pret, Livre **tab_livre)
{
    //recuperation de l'indice du livre dans le tableau de livre
    int i = 0;
    while(compare_chaine_caractere(tab_livre[i]->code, pret->code_livre) != 0) {
        i++;
    }

    //modification du livre (supression d'un exemplaire disponible)
    tab_livre[i]->nb_exemplaires_dispo --; 
}


/*cette fonction est a appellé seulement si la fonction saisie champs pret securise est verifié*/
void supr_pret_struct_livre(Pret *pret, Livre **tab_livre)
{
    //recuperation de l'indice du livre dans le tableau de livre
    int i = 0;
    while(compare_chaine_caractere(tab_livre[i]->code, pret->code_livre) != 0) {
        i++;
    }

    //modification du livre (ajout d'un exemplaire disponible)
    tab_livre[i]->nb_exemplaires_dispo ++; 
}


void supr_pret_struct_membre(Pret *pret, Membre **tab_membre)
{
    //recuperation de l'indice du membre dans le tableau de membre
    int i = 0;
    while(tab_membre[i]->identifiant != pret->id_membre){
        i++;
    }

    //modification du membre
    int valide = 0;
    do {
        if(tab_membre[i]->liste_emprunt[valide] == pret->id_pret) { //si c'est le membre a mdifier
            tab_membre[i]->liste_emprunt[valide] = 0; //supression de l'enregistrement de l'identifiant du pret
            valide = -1;
        }   
        else {
            valide ++;
        }
    } while(valide != -1);
}


/*actualisation des prets en retard ou non en debut de programme
entraine la modification des structures prets (rafrachir en meme temps le fichier pret*/
void actualisation_pret_en_retard(Pret **tab_pret, int *nb_pret)
{
    Date d1, d2;
    Date date_du_jour;

    //recuperation de la date du jour
    long int timestamp = (int) time(NULL);

    date_du_jour = definir_date(timestamp);

    //modification des valeurs en retard 
    int i;
    for(i=0; i<*(nb_pret); i++)
    {
        if(tab_pret[i]->etat_livre == 1) { // si le livre enregistré comme pas en retard
            if(compare_date(&date_du_jour, &tab_pret[i]->date_retour) == 1) { //si le livre doit changer de statut (il est aujourd'hui en retard)
                tab_pret[i]->etat_livre = 0; //on change le statut du livre qui devient en retard
            }
        }
    }

    //modification du fichier membre
    rafraichir_fichier_pret(tab_pret, nb_pret);
}


void rafraichir_fichier_pret(Pret **tab_pret, int *nb_pret) 
{
    FILE* fichier_pret = NULL;

    fichier_pret = fopen("sauvegardes/prets.txt", "w"); //"w" correspond a l'ecriture (supression du contenu au préalable) - fopen renvoie un pointeur sur le fichier

    if (fichier_pret != NULL) {

        int i;

        for(i=0; i<*(nb_pret); i++)
        {
            fprintf(fichier_pret, "id : %d | ", tab_pret[i]->id_pret);
            fprintf(fichier_pret, "id_membre : %d | ", tab_pret[i]->id_membre);
            fprintf(fichier_pret, "code_livre : %s | ", tab_pret[i]->code_livre);
            fprintf(fichier_pret, "date_pret : %ld | ", recuperer_timestamp(&tab_pret[i]->date_pret));
            fprintf(fichier_pret, "date_retour : %ld | ", recuperer_timestamp(&tab_pret[i]->date_retour)); // 1 * 3600 * 24 * 7 * 3 -> 1sec * 3600 (donc heure) * 24 (donc jour) * 7 (donc semaine) * 3 (donc 3 semaines)
            fprintf(fichier_pret, "etat_livre : %d \n", tab_pret[i]->etat_livre);
        }

        //Fermeture du fichier
        fclose(fichier_pret);

    } else { //le pointeur sur le fichier est toujours = NULL soit le fichier n'a pas était ouvert
        erreur_ouverture_fichier();
    }
}


void affichage_info_pret_membre(Membre *membre, Pret **tab_pret, int *nb_pret, Livre **tab_livre, int *nb_livre)
{
    int nb_pret_membre;
    nb_pret_membre = calcul_nb_pret_membre(membre);

    if (nb_pret_membre == 0){
        printf("                    Pret : Aucun pret en cour\n\n");
    }
    else{
        int i;

        for(i=0; i<NB_EMPRUNT_MAX; i++)
        {
            if(membre->liste_emprunt[i] !=0){
                //recuperation de l'indice du pret dans le tableau de pret
                int indice_pret = 0;
                while(tab_pret[indice_pret]->id_pret != membre->liste_emprunt[i]) {
                    indice_pret++;
                }

                //recuperation de l'indice du livre dans le tableau de livre
                int indice_livre = 0;
                while(compare_chaine_caractere(tab_livre[indice_livre]->code, tab_pret[indice_pret]->code_livre) != 0) {
                    indice_livre++;
                }
            
                printf("                    Pret -     id_pret : %d   ", tab_pret[indice_pret]->id_pret);
                affichage_titre_auteur_code_livre(tab_livre[i]->code, tab_livre);

                if(tab_pret[indice_pret]->etat_livre == 1) { //pret a jour
                    printf("     A JOUR (date de retour : ");
                    afficher_date(&tab_pret[indice_pret]->date_retour);
                } else {
                    printf("     EN RETARD (date de retour : ");
                    afficher_date(&tab_pret[indice_pret]->date_retour);
                }
                printf(")\n\n");
            }
        }
    }
}



void affichage_info_pret_livre(Livre *livre, Pret **tab_pret, int *nb_pret, Membre **tab_membre, int *nb_membre)
{
    int nb_pret_livre;
    nb_pret_livre = livre->nb_exemplaires - livre->nb_exemplaires_dispo;

    if (nb_pret_livre == 0){
        printf("                    Pret : Aucun pret en cour\n\n");
    }
    else{
        int i;

        for(i=0; i<nb_pret_livre; i++)
        {
            //recuperation de l'indice du pret dans le tableau de pret
            int indice_pret = 0;
            while(compare_chaine_caractere(tab_pret[indice_pret]->code_livre, livre->code) != 0) {
                indice_pret++;
            }

            //recuperation de l'indice du membre dans le tableau de membre
            int indice_membre = 0;
            while(tab_membre[indice_membre]->identifiant != tab_pret[indice_pret]->id_membre) {
                indice_membre++;
            }
        
            printf("                    Pret -     id_pret : %d   ", tab_pret[indice_pret]->id_pret);
            affichage_prenom_nom_id_membre(&tab_membre[indice_membre]->identifiant, tab_membre);

            if(tab_pret[indice_pret]->etat_livre == 1) { //pret a jour
                printf("     A JOUR (date de retour : ");
                afficher_date(&tab_pret[indice_pret]->date_retour);
            } else {
                printf("     EN RETARD (date de retour : ");
                afficher_date(&tab_pret[indice_pret]->date_retour);
            }
            printf(")\n\n");

        }
    }
}


/*fonction retourne le nombre de pret totale en retard dans la librairie*/
int calcul_nb_pret_total_retard(Pret **tab_pret, int *nb_pret)
{
    int nb_pret_retard = 0;

    int i;

    for(i=0; i<*nb_pret; i++)
    {
        if(tab_pret[i]->etat_livre == 0) {
            nb_pret_retard ++;
        }
    }

    return (nb_pret_retard);
}






int saisie_id_pret_securise(int *id_pret, Pret **tab_pret, int *nb_pret)
{
    int i;
    int valide = FALSE;

    saisie_entier(id_pret);

    for(i=0; i<*nb_pret; i++)
    {
        if(*id_pret == tab_pret[i]->id_pret) {
            valide = TRUE;
        }
    }

    return (valide);
}


/*Modification du fichier prets.txt lors de la supression d'un livre
ouverture du fichier en mode ecriture pour suprimmer tous les elements du fichier
les prets seront ensuite tous reinsérré sauf celui dont on demande la suppression
apres la modification il faudra rafraichir les valeurs du tab livre et nb_livre*/
void supr_pret_fichier_pret(FILE *fichier_pret, int *id_pret, Pret **tab_pret, int *nb_pret)
{
    fichier_pret = fopen("sauvegardes/prets.txt", "w"); //"w" correspond a l'ecriture - fopen renvoie un pointeur sur le fichier

    if (fichier_pret != NULL)
    {
        int i;
        int j;

        for (i = 0; i < *(nb_pret); i++)
        {
            if (*id_pret != tab_pret[i]->id_pret) //si ce n'est pas le livre a supprimer
            {
                fprintf(fichier_pret, "id : %d | ", tab_pret[i]->id_pret);
                fprintf(fichier_pret, "id_membre : %d | ", tab_pret[i]->id_membre);
                fprintf(fichier_pret, "code_livre : %s | ", tab_pret[i]->code_livre);
                fprintf(fichier_pret, "date_pret : %ld | ", recuperer_timestamp(&tab_pret[i]->date_pret));
                fprintf(fichier_pret, "date_retour : %ld | ", recuperer_timestamp(&tab_pret[i]->date_retour)); // 1 * 3600 * 24 * 7 * 3 -> 1sec * 3600 (donc heure) * 24 (donc jour) * 7 (donc semaine) * 3 (donc 3 semaines)
                fprintf(fichier_pret, "etat_livre : %d \n", tab_pret[i]->etat_livre);
            }
        }

        //Fermeture du fichier
        fclose(fichier_pret);
    }
    else
    { //le pointeur sur le fichier est toujours = NULL soit le fichier n'a pas était ouvert
        erreur_ouverture_fichier();
    }
}