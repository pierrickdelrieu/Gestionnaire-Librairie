#include "../headers/livre.h"

//creer la structure livre de maniere dynamique
Livre *creer_struct_livre()
{
    return (Livre *) malloc(sizeof(Livre));
}

/*Libere la structure admin de maniere dynamique*/
void lib_struct_livre(Livre *livre)
{
    free(livre);
}

/*Recuperation des sauvegardes faites dans le fichier livres*/
Livre **creer_tab_livre(int *nb_livre)
{
    Livre **liste_livres;
    FILE *fichier_livre = NULL;

    fichier_livre = fopen("sauvegardes/livres.txt", "r"); //"r" correspond a la lecture seul (permet de limiter les erreurs) - fopen renvoie un pointeur sur le fichier

    if (fichier_livre != NULL)
    {

        //allocation du tableau d'identifiant
        liste_livres = (Livre **)malloc((*nb_livre) * sizeof(Livre *));

        //recup des identifiants
        int i;
        int j;

        for (i = 0; i < (*nb_livre); i++)
        {
            liste_livres[i] = creer_struct_livre();
            lecture_chaine_cara_fichier(fichier_livre, liste_livres[i]->titre, 40);
            lecture_chaine_cara_fichier(fichier_livre, liste_livres[i]->auteur, 40);
            lecture_chaine_cara_fichier(fichier_livre, liste_livres[i]->code, 9);
            fscanf(fichier_livre, "nb_exemplaires : %d - nb_exemplaires_dispos : %d\n\n", &(liste_livres[i]->nb_exemplaires), &(liste_livres[i]->nb_exemplaires_dispo));
        }

        //Fermeture du fichier
        fclose(fichier_livre);
    }
    else
    { //le pointeur sur le fichier est toujours = NULL soit le fichier n'a pas était ouvert
        erreur_ouverture_fichier();
    }

    return (liste_livres);
}

/*Permet de calculer le nombre de livre a partir du fichier livre.txt
Elle parcour le fichier et compte le nombre de livre qu'il contient (sachant que un livre = 11 ligne)*/
void calcul_nb_livre(int *nb_livre)
{
    FILE *fichier_livre = NULL;

    fichier_livre = fopen("sauvegardes/livres.txt", "r"); //"w" correspond a la ecriture seul (permet de limiter les erreurs) - fopen renvoie un pointeur sur le fichier

    if (fichier_livre != NULL)
    {

        //nombres d'identifiant
        int cara;
        *nb_livre = 0;
        do
        {
            cara = fgetc(fichier_livre);
            if (cara == '\n')
            {
                (*nb_livre)++;
            }
        } while (cara != EOF);

        //Fermeture du fichier
        fclose(fichier_livre);

        *nb_livre = (*nb_livre) / 5;
    }
    else
    { //le pointeur sur le fichier est toujours = NULL soit le fichier n'a pas était ouvert
        erreur_ouverture_fichier();
    }
}

/* Modifie le tableau de livre en fonction des modifications (ajout et supression) qui ont eu lieu sur le fichier
Cette fonction suprimme et recrer le tableau, la realocation est trop dangeureuse*/
void rafrachir_tab_livre(Livre ***tab_livre, int *nb_livre)
{
    lib_tab_livre(*tab_livre, nb_livre);

    calcul_nb_livre(nb_livre);

    *tab_livre = creer_tab_livre(nb_livre);
}

int saisie_code_livre(char code[8])
{
    int valide;
    valide = saisie_chaine_caractere(code,8);
    if (valide == TRUE){
        valide= verif_code_livre(code);
    }

    return (valide);
}

int verif_code_livre(char* code)
{
    int valide = TRUE;
    int i;
    
    //verification de la forme du code
    if(strlen(code) == 7){
        valide = TRUE;
    }
    else
    {
        valide = FALSE;
    }
    

    if(valide == TRUE){

        // if(compare_chaine_caractere(code,"0") == 0){ //verification retour au menu
        //     valide = TRUE;
        // }
        // else{
        //verification des trois premieres lettres
        for(i=0; i<3; i++){
            if((code[i]>'Z') || (code[i]<'A')){ //verif de lettre en majuscule
                valide = FALSE;
            }
        }

        //verification de la presence du tiret
        if(code[3] != '-'){
            valide = FALSE;
        }

        //verification des trois derniers chiffres
        for(i=4; i<7; i++){
            if((code[i]<'0') || (code[i]>'9')){ //verif du chiffre
                valide = FALSE;
            }
        }
    }

    return (valide);
}

/*Saisie des champs de la structure d'un nouveau livre*/
int saisie_champs_livre(Livre *livre, Donnee_livre *donne_livre)
{
    int valide;
    int valide_tot = 0; //5 si pas d'erreur

    printf("     Titre : ");
    valide = saisie_chaine_caractere(livre->titre, 40);
    valide_tot = valide_tot + valide;

    printf("     Auteur : ");
    valide = saisie_chaine_caractere(livre->auteur, 40);
    valide_tot = valide_tot + valide;

    printf("     Genre (3 lettres) : ");
    // valide = saisie_code_livre(livre->code);
    valide = saisie_genre_livre_securise(livre->code, donne_livre);
    valide_tot = valide_tot + valide;

    printf("     Saisie nombre d'exemplaires : ");
    saisie_entier(&(livre->nb_exemplaires));


    if (valide_tot == 3) {
        livre->nb_exemplaires_dispo = livre->nb_exemplaires;
        return (TRUE);
    }
    else {
        return (FALSE);
    }
}


/*Affiche un livre en ligne sans toute les infos sur les prets*/
void afficher_livre(Livre *livre)
{
    printf("Titre : %s     Auteur : %s     Code : %s     Nombre exemplaires totals : %d     Nombre exemplaires dispo : %d\n", livre->titre, livre->auteur, livre->code,livre->nb_exemplaires, livre->nb_exemplaires_dispo);
}

/*affiche la totalité du livre avec tous les détais sur les prets*/
void afficher_toute_info_livre(Livre *livre)
{
    printf("\n                    Titre : %s\n", livre->titre);
    printf("                    Auteur : %s\n", livre->auteur);
    printf("                    Code : %s\n", livre->code);
    printf("                    Nombre d'exemplaires totals : %d\n", livre->nb_exemplaires);
    printf("                    Nombre d'exemplaires disponibles : %d\n", livre->nb_exemplaires_dispo);
}


/*libere de maniere dynamique le tableau de livre*/
void lib_tab_livre(Livre **tab_livre, int *nb_livres)
{
    int i;

    for (i = 0; i < *nb_livres; i++)
    {
        lib_struct_livre(tab_livre[i]);
    }

    free(tab_livre);
}

/*saisie d'un code valide (cad d'un livre existant)
permet la verification lors de la supression ou la consultation d'un livre
renvoie 1 si le code est dans le tableau et 0 sinon*/
int verif_code_livre_in_tab_libre(Livre **tab_livre, char* code_livre, int *nb_livre)
{
    int valide = FALSE;

    int i;
    
    for (i = 0; i < *(nb_livre); i++)
    {
        if (compare_chaine_caractere(code_livre, tab_livre[i]->code) == 0) //si les chaines sont egales
        {
            valide = TRUE;
        }
    }

    return (valide);
}

/*saisie des champs d'un livre valide (cad d'un livre existant)
permet la verification lors de la creation d'un nouveau livre
Un livre est considéré comme existant si le titre et l'auteur existe deja dans le genre*/
int saisie_securise_livre_not_in_tab_livre(Livre *saisie, Livre **tab_livre, int *nb_livre, Donnee_livre *donnee_livre)
{
    //retourne 1 (TRUE) si valeur saisie correspond a un livre non existant et 0 (FALSE) sinon
    int valide;

    valide = saisie_champs_livre(saisie,donnee_livre);

    if(valide == TRUE){
        valide = FALSE;
       int i;

       //verif titre livre
       int indice_livre = -1;
       for(i=0; i<*nb_livre; i++)
       {
            if(compare_chaine_caractere(saisie->titre, tab_livre[i]->titre) == 0) { //si le titre existe
                valide = TRUE;
                indice_livre = i;
            }
       }

        //verification auteur
        if(valide == TRUE) {
            if(compare_chaine_caractere(saisie->auteur, tab_livre[indice_livre]->auteur) == 0) { //si l'auteur coorespond au titre
                valide = TRUE;
            }
            else {
                valide = FALSE;
            }
        }

        ////verification genre
        if(valide == TRUE) {
            if((saisie->code[0] == tab_livre[indice_livre]->code[0]) && (saisie->code[1] == tab_livre[indice_livre]->code[1]) && (saisie->code[2] == tab_livre[indice_livre]->code[2])) { //si le livre existe deja dans ce genre
                valide = TRUE;
            }
            else {
                valide = FALSE;
            }
        }

        //inversion de la sortie
        if (valide == TRUE) {
            valide = FALSE;
        }
        else {
            valide = TRUE;
        }
    }

    return(valide);
}


/*Modification du fichier livres.txt lors de l'ajout d'un livre
apres la modification il faudra rafraichir les valeurs du tab livre et nb_livre
ouverture du fichier en mode ajout pour ne pas modifier le contenue qui est deja dans le fichier*/
void ajout_livre_fichier_livre(FILE *fichier_livre, Livre *saisie)
{
    fichier_livre = fopen("sauvegardes/livres.txt", "a"); //"a" correspond a l'ajout - fopen renvoie un pointeur sur le fichier

    int j;

    if (fichier_livre != NULL)
    {

        fprintf(fichier_livre, "%s\n", saisie->titre);
        fprintf(fichier_livre, "%s\n", saisie->auteur);
        fprintf(fichier_livre, "%s\n", saisie->code);
        fprintf(fichier_livre, "nb_exemplaires : %d - nb_exemplaires_dispos : %d\n\n", saisie->nb_exemplaires, saisie->nb_exemplaires_dispo);

        //Fermeture du fichier
        fclose(fichier_livre);
    }
    else
    { //le pointeur sur le fichier est toujours = NULL soit le fichier n'a pas était ouvert
        erreur_ouverture_fichier();
    }
}

/*Modification du fichier livre.txt lors de la supression d'un livre
ouverture du fichier en mode ecriture pour suprimmer tous les elements du fichier
les livres seront ensuite tous reinsérré sauf celui dont on demande la suppression
apres la modification il faudra rafraichir les valeurs du tab livre et nb_livre*/
void supr_livre_fichier_livre(FILE *fichier_livre, char *code, Livre **tab_livre, int *nb_livre)
{
    fichier_livre = fopen("sauvegardes/livres.txt", "w"); //"w" correspond a l'ecriture - fopen renvoie un pointeur sur le fichier

    if (fichier_livre != NULL)
    {
        int i;
        int j;

        for (i = 0; i < *(nb_livre); i++)
        {
            if (compare_chaine_caractere(code, tab_livre[i]->code) != 0) //si ce n'est pas le livre a supprimer
            {
                fprintf(fichier_livre, "%s\n", tab_livre[i]->titre);
                fprintf(fichier_livre, "%s\n", tab_livre[i]->auteur);
                fprintf(fichier_livre, "%s\n", tab_livre[i]->code);
                fprintf(fichier_livre, "nb_exemplaires : %d - nb_exemplaires_dispos : %d\n\n", tab_livre[i]->nb_exemplaires, tab_livre[i]->nb_exemplaires_dispo);
            }
        }

        //Fermeture du fichier
        fclose(fichier_livre);
    }
    else
    { //le pointeur sur le fichier est toujours = NULL soit le fichier n'a pas était ouvert
        erreur_ouverture_fichier();
    }
}


void rafraichir_fichier_livre(FILE *fichier_livre, Livre **tab_livre, int *nb_livre)
{
    fichier_livre = fopen("sauvegardes/livres.txt", "w"); //"w" correspond a l'ecriture - fopen renvoie un pointeur sur le fichier

    if (fichier_livre != NULL)
    {
        int i;
        int j;

        for (i = 0; i < *(nb_livre); i++)
        {
            fprintf(fichier_livre, "%s\n", tab_livre[i]->titre);
            fprintf(fichier_livre, "%s\n", tab_livre[i]->auteur);
            fprintf(fichier_livre, "%s\n", tab_livre[i]->code);
            fprintf(fichier_livre, "nb_exemplaires : %d - nb_exemplaires_dispos : %d\n\n", tab_livre[i]->nb_exemplaires, tab_livre[i]->nb_exemplaires_dispo);
        }

        //Fermeture du fichier
        fclose(fichier_livre);
    }
    else
    { //le pointeur sur le fichier est toujours = NULL soit le fichier n'a pas était ouvert
        erreur_ouverture_fichier();
    }
}



void affichage_titre_auteur_code_livre(char *code_livre, Livre **tab_livre)
{
    //recuperation de l'indice du livre dans le tableau de livre
    int i = 0;
    while(compare_chaine_caractere(tab_livre[i]->code, code_livre) != 0) {
        i++;
    }

    printf("%s de %s (code : %s) ",tab_livre[i]->titre, tab_livre[i]->auteur, tab_livre[i]->code);
}


/*saisie du genre en 3 lettres lors de l'ajout d'un livre et calcul automatique du code du livre
l'appel de cette fonction doit engendré l'appelle de la fonction rafraichir tab donnee*/
int saisie_genre_livre_securise(char *code_livre, Donnee_livre *donnee_livre)
{
    int valide;

    valide = saisie_chaine_caractere(code_livre, 9);

    //verification du genre
    int indice_genre = -1;
    if(valide == TRUE) {
        int i;
        valide = FALSE;

        for(i=0; i<NB_GENRE_LIVRE; i++)
        {
            if(compare_chaine_caractere(code_livre, donnee_livre->liste_code[i]) == 0) {
                valide = TRUE;
                indice_genre = i;
            }
        }
    }


    //modification de la chaine
    if(valide == TRUE) {
        int dizaine;
        valide = FALSE;

        //verification que le numero du livre et inférieur a 999
        if(donnee_livre->nb_livre[indice_genre] < 999) {
            donnee_livre->nb_livre[indice_genre] ++;
            valide = TRUE;
        }

        if(valide == TRUE) {
            code_livre[3] = '-';

            if(donnee_livre->nb_livre[indice_genre] < 10) { // nombre a 1 chiffres
                code_livre[4] = '0';
                code_livre[5] = '0';
                code_livre[6] = donnee_livre->nb_livre[indice_genre] + 48; //transformation en cara

            } else if (donnee_livre->nb_livre[indice_genre] < 100) { // nombre a 2 chiffres
                code_livre[4] = '0';

                //obtention du chiffre des dizaines
                int copie_nb_livre = donnee_livre->nb_livre[indice_genre];
                dizaine = 0;
                while(copie_nb_livre >=10)
                {
                    dizaine ++;
                    copie_nb_livre = copie_nb_livre - 10;
                }

                code_livre[5] = dizaine + 48;

                //obtention du chiffre des unité
                code_livre[6] = donnee_livre->nb_livre[indice_genre] - (10*dizaine) + 48;
            
            } else { // nombre a 3 chiffres
                int centaine = 0;

                //obtention du chiffre des centaines
                int copie_nb_livre = donnee_livre->nb_livre[indice_genre];
                while(copie_nb_livre >=100)
                {
                    centaine ++;
                    copie_nb_livre = copie_nb_livre - 100;
                }

                code_livre[4] = centaine + 48;

                //obtention du chiffre des dizaines
                dizaine = 0;
                while(copie_nb_livre >=10)
                {
                    dizaine ++;
                    copie_nb_livre = copie_nb_livre  - 10;
                }

                code_livre[5] = dizaine + 48;

                //obtention du chiffre des unité
                code_livre[6] = donnee_livre->nb_livre[indice_genre] - (centaine * 100) - (dizaine * 10) + 48;
            }
            
            code_livre[7] = '\0';
        }
    }


    return(valide);
}



/*fonction de tri par selection
1->code
2->titre
3->auteur

La fonction retourne un tableau contenant les indices des livres dans le tableau livre trier*/
//cette fonction appelle les fonction suivantes
void creation_tab_tri_livre(int type_tri, int* tab_tri, Livre **tab_livre, int *nb_livre)
{
    if (type_tri == 1) { // tri par code
        init_tab_tri_livre_code(tab_tri, tab_livre, nb_livre);
    } else if (type_tri == 2) { // tri par titre
        init_tab_tri_livre_titre(tab_tri, tab_livre, nb_livre);
    } else if (type_tri == 3) { // tri par auteur
        init_tab_tri_livre_auteur(tab_tri, tab_livre, nb_livre);
    }
}


void init_tab_tri_livre_code(int* tab_tri, Livre **tab_livre, int *nb_livre)
{
    int i, j;
    int rang_livre;

    for(i=0; i<*nb_livre; i++)
    {
        rang_livre = 0;

        for(j=-1; j<*nb_livre-1; j++)
        {
            if(compare_chaine_caractere(tab_livre[i]->code, tab_livre[j+1]->code) == 1) { // tab_livre[i]->code > tab_livre[j]->code
                rang_livre ++;
            }
        }
        tab_tri[rang_livre] = i;
    }
}

void init_tab_tri_livre_titre(int* tab_tri, Livre **tab_livre, int *nb_livre)
{
    int i, j;
    int rang_livre;

    for(i=0; i<*nb_livre; i++)
    {
        rang_livre = 0;

        for(j=-1; j<*nb_livre-1; j++)
        {
            if(compare_chaine_caractere(tab_livre[i]->titre, tab_livre[j+1]->titre) == 1) { // tab_livre[i]->titre > tab_livre[j]->titre
                rang_livre ++;
            }
        }
        tab_tri[rang_livre] = i;
    }
}

void init_tab_tri_livre_auteur(int* tab_tri, Livre **tab_livre, int *nb_livre)
{
    int i, j;
    int rang_livre;

    for(i=0; i<*nb_livre; i++)
    {
        rang_livre = 0;

        for(j=-1; j<*nb_livre-1; j++)
        {
            if(compare_chaine_caractere(tab_livre[i]->auteur, tab_livre[j+1]->auteur) == 1) { // tab_livre[i]->auteur > tab_livre[j]->auteur
                rang_livre ++;
            }
        }
        tab_tri[rang_livre] = i;
    }
}




/*fonction permettant la recherche d'un livre en fonction du critere
(1->code 2->titre)
fonction retourne -1 si le livre n'est pas dans le tableau et sinon retourne l'indice du livre dans le tableau
*/
int saisie_info_livre_critere(int type_tri, char *recherche, Livre **tab_livre, int *nb_livre)
{
    int valide;

    if (type_tri == 1) { // tri par code
        valide = saisie_securise_code(recherche, tab_livre, nb_livre);
    } else if (type_tri == 2) { // tri par titre
        valide = saisie_securise_titre(recherche, tab_livre, nb_livre);
    }

    return (valide);
}


int saisie_securise_code(char *recherche, Livre **tab_livre, int *nb_livre)
{
    int i;
    int valide;

    //saisie de la recherche
    printf("     Saisir le code du livre a consulter (XXX-YYY) ou 0 pour revenir au menu : ");
    valide = saisie_chaine_caractere(recherche, 40);

    // verif code
    int indice_livre = -1;
    if(valide == TRUE) {
        for(i=0; i<*nb_livre; i++)
        {
            if(compare_chaine_caractere(recherche, tab_livre[i]->code) == 0) { //si le code existe
                indice_livre = i;
            }
        }
    }

    return (indice_livre);
}


int saisie_securise_titre(char *recherche, Livre **tab_livre, int *nb_livre)
{
    int i;
    int valide;

    // saisie de la recherche
    printf("     Saisir le titre du livre a consulter ou 0 pour revenir au menu : ");
    valide = saisie_chaine_caractere(recherche, 40);

    //verif titre 
    int indice_livre = -1;
    if(valide == TRUE) {
        for(i=0; i<*nb_livre; i++)
        {
            if(compare_chaine_caractere(recherche, tab_livre[i]->titre) == 0) { //si le titre existe
                indice_livre = i;
            }
        }
    }

    return (indice_livre);
}
