#include "../headers/librairie.h"

/*Reinitialisation de toute les valeurs dans librairie
- le nombre de pret (donnee[1]) et de le nombre de membre (donnee[0]) depuis l'ouverture de la librairie
- tous les administrateurs sauf celui du programmeur
- tous les membres
- tous les prets
- tous les livres*/
void reinitialise_librairie(int tab_donnee[2], Donnee_livre *donnee_livre, Liste_admin *gestion_admin, Liste_membre *gestion_membre, Liste_livre *gestion_livre, Liste_pret *gestion_pret)
{
    int choix;

    do
    {
        supr_console();
        affichage_sous_titre("REINITIALISATION DONNEE LIBRAIRIE");
        printf("     Cette opération est irréversible\n\n\n");
        printf("Saisir 1 pour valider et 0 pour quitter : ");
        saisie_entier(&choix);
    } while ((choix != 0) && (choix != 1));

    if (choix == 1)
    {
        tab_donnee[0] = 0; //reinitialisation des membres
        tab_donnee[1] = 0; //reinitialisation des prets

        //reinitialisation des donnees livres
        int i;
        for(i=0; i<NB_GENRE_LIVRE; i++)
        {
            donnee_livre->nb_livre[i]=0;
        }

        FILE *fichier_membre = NULL;
        fichier_membre = fopen("sauvegardes/membres.txt", "w"); //ouvre le fichier en mode ecriture et supprime tous sont contenue au préalable
        fclose(fichier_membre);

        FILE *fichier_prets = NULL;
        fichier_membre = fopen("sauvegardes/prets.txt", "w"); //ouvre le fichier en mode ecriture et supprime tous sont contenue au préalable
        fclose(fichier_prets);

        FILE *fichier_livres = NULL;
        fichier_membre = fopen("sauvegardes/livres.txt", "w"); //ouvre le fichier en mode ecriture et supprime tous sont contenue au préalable
        fclose(fichier_livres);

        FILE *fichier_admin = NULL;
        fichier_admin = fopen("sauvegardes/admin.txt", "w"); //ouvre le fichier en mode ecriture et supprime tous sont contenue au préalable
        fprintf(fichier_admin, "id : %d mp : %s\n", ID_PROGRAMMEUR, MP_PROGRAMMEUR);
        fclose(fichier_admin);

        rafrachir_fichier_donnee(tab_donnee, donnee_livre);
        rafrachir_tab_membre(&(gestion_membre->liste_membre), &(gestion_membre->nb_membre));
        rafrachir_tab_admin(&(gestion_admin->liste_admin), &(gestion_admin->nb_admin));
        rafrachir_tab_livre(&(gestion_livre->liste_livre), &(gestion_livre->nb_livre));
        rafrachir_tab_pret(&(gestion_pret->liste_pret),&(gestion_pret->nb_pret));
        
        supr_console();
        printf("Toutes les données (membres, admin, livres, prets) de la librairies ont été supprimés\n");

        sleep(2);
        supr_console();
    }
}

/*recuperation des donnes se situant dans le fichier donnee.txt et modification du tableau en memoire
cad la recuperation du nombre de pret et de membre depuis l'ouverture de la librairie*/
void creer_tab_donnee(int tab[2], Donnee_livre *donne_livre)
{
    FILE *fichier_donnee = NULL;
    fichier_donnee = fopen("sauvegardes/donnee.txt", "r"); //"r" correspond a la lecture seul - fopen renvoie un pointeur sur le fichier

    if (fichier_donnee != NULL)
    {
        int i;

        fscanf(fichier_donnee, "nombre de membres total : %d\n", &(tab[0]));
        fscanf(fichier_donnee, "nombre de prets total : %d\n", &(tab[1]));
        fscanf(fichier_donnee, "livre :");

        for(i=0; i<NB_GENRE_LIVRE; i++)
        {
            fscanf(fichier_donnee, " %s %d -",donne_livre->liste_code[i], &donne_livre->nb_livre[i]);
        }


        //Fermeture du fichier
        fclose(fichier_donnee);
    }
    else
    { //le pointeur sur le fichier est toujours = NULL soit le fichier n'a pas était ouvert
        erreur_ouverture_fichier();
    }
}

/*modification du tableau de donnée en fonction du fichier donne.txt*/
void rafrachir_fichier_donnee(int *tab, Donnee_livre *donne_livre)
{
    FILE *fichier_donnee = NULL;
    fichier_donnee = fopen("sauvegardes/donnee.txt", "w"); //"w" correspond a l'ecriture seul - fopen renvoie un pointeur sur le fichier

    if (fichier_donnee != NULL)
    {
        int i;

        fprintf(fichier_donnee, "nombre de membres total : %d\n", tab[0]);
        fprintf(fichier_donnee, "nombre de prets total : %d\n", tab[1]);
        fprintf(fichier_donnee, "livre :");

        for(i=0; i<NB_GENRE_LIVRE; i++)
        {
            fprintf(fichier_donnee, " %s %d -",donne_livre->liste_code[i], donne_livre->nb_livre[i]);
        }

        //Fermeture du fichier
        fclose(fichier_donnee);
    }
    else
    { //le pointeur sur le fichier est toujours = NULL soit le fichier n'a pas était ouvert
        erreur_ouverture_fichier();
    }
}

/*ecran de connexion*/
void connexion(Admin **tab_admin, int *nb_identifiant)
{
    Admin saisie;
    int valide = TRUE;

    do
    {
        supr_console();
        affichage_titre_app();
        affichage_sous_titre("CONNEXION");
        if (valide == FALSE)
        {
            printf("          Identifiant ou mot de passe incorrect\n");
        }
        valide = saisie_securise_id_tab_admin(&saisie, tab_admin, nb_identifiant);
    } while (valide == FALSE);
}

/***********************************************FONCTION ADMIN***********************************************/

/*affichage de la liste des admins*/
void affichage_liste_admin(Admin ***tab_identifiant, int *nb_identifiant)
{
    int choix;

    do
    {
        supr_console();
        affichage_sous_titre("AFFICHAGE DES ADMINISTRATEURS");
        affichage_tab_admin(*tab_identifiant, nb_identifiant);
        printf("     Saisir 1 pour revenir au menu : ");
        saisie_entier(&choix);
    } while (choix != 1);
}

/*saisie d'un nouveau admin dans le tableau en memoire et dans le fichier*/
void saisie_nx_admin(Admin ***tab_admin, int *nb_identifiant)
{

    //Saise de l'administrateur a supprimer
    int valide;
    Admin saisie;

    //saisie de l'administrateur a ajouter
    do
    {
        supr_console();
        affichage_sous_titre("AJOUT NOUVEAU ADMINISTRATEUR");
        printf("L'identifiant doit comporter 8 chiffres\n\n");
        valide = saisie_identifiant(&saisie);
    } while (valide == FALSE);

    //modification du contenu du fichier admin.txt
    FILE *fichier_admin = NULL;
    ajout_admin_fichier_admin(fichier_admin, &(saisie));

    rafrachir_tab_admin(tab_admin, nb_identifiant); //modif du nombre d'identifiant

    supr_console();
    printf("L'administrateur %d a bien était ajouté\n", saisie.identifiant);

    sleep(2);
    supr_console();
}

/*supression d'un admin dans le tableau en memoire et dans le fichier*/
void supr_admin(Admin ***tab_admin, int *nb_identifiant)
{

    //Saisie de l'administrateur a supprimer
    int valide = TRUE;
    Admin saisie;

    if (*nb_identifiant == 1)
    {
        supr_console();
        affichage_sous_titre("SUPRESSION ADMINISTRATEUR");
        affichage_tab_admin(*tab_admin, nb_identifiant);
        printf("     !!!Vous ne pouvez pas supprimer d'administarteur!!!\n");
        printf(" L'administrateur de référence (programmeur) ne peut pas etre supprimer\n");
        sleep(3);
        supr_console();
    }
    else
    {
        do
        {
            supr_console();
            affichage_sous_titre("SUPRESSION ADMINISTRATEUR");
            affichage_tab_admin(*tab_admin, nb_identifiant);

            printf("Il n'est pas possible de supprimer les identifiants du programmeur :\n");
            printf("          id : %d mp : %s\n\n", ID_PROGRAMMEUR, MP_PROGRAMMEUR);

            if (valide == FALSE)
            {
                printf("     ERREUR\n");
            }
            valide = saisie_securise_id_tab_admin(&saisie, *tab_admin, nb_identifiant);

            //pas possible de supprimer l'administrateur de référence
            if ((saisie.identifiant == ID_PROGRAMMEUR) && (compare_chaine_caractere(saisie.mot_de_passe, MP_PROGRAMMEUR) == 0))
            {
                valide = FALSE;
            }
        } while (valide == FALSE);

        //supression et recréation du contenu du fichier admin.txt
        FILE *fichier_admin = NULL;
        supr_admin_fichier_admin(fichier_admin, *(tab_admin), &saisie, nb_identifiant);
        rafrachir_tab_admin(tab_admin, nb_identifiant); //modif de la valeur de nb_id

        supr_console();
        printf("L'administrateur %d a bien était suprimer\n", saisie.identifiant);

        sleep(2);
        supr_console();
    }
}

/**********************************************FONCTION MEMBRE**********************************************/

/*ajout d'un membre dans le tableau en memoire et dans le fichier*/
void saisie_nx_membre(Membre ***tab_membre, int *nb_membre, int tab_donnee[2], Donnee_livre *donnee_livre)
{

    int valide = FALSE;
    Membre saisie;

    //saisie du membre a ajouter
    do
    {
        supr_console();
        affichage_sous_titre("AJOUT NOUVEAU MEMBRE");

        if (valide == TRUE)
        {
            printf("ERREUR (adresse mail deja existante)\nReesayer\n\n");
        }

        printf("Saisir 0 a un élément pour retourner au menu\n\n");

        valide = saisie_securise_membre_tab_membre(&saisie, *tab_membre, nb_membre, &(tab_donnee[0]));

        //Possibilité de retour au menu
        if((compare_chaine_caractere(saisie.prenom, "0") == 0) || (compare_chaine_caractere(saisie.nom, "0") == 0) || (compare_chaine_caractere(saisie.adresse.ville, "0") == 0) || (compare_chaine_caractere(saisie.adresse.rue, "0") == 0) || (compare_chaine_caractere(saisie.adresse.code_postal, "0") == 0) || (compare_chaine_caractere(saisie.adresse.pays, "0") == 0) || (compare_chaine_caractere(saisie.metier, "0") == 0) || (compare_chaine_caractere(saisie.email, "0") == 0)) {
            valide = FALSE;
        }

    } while (valide == TRUE);

    if((compare_chaine_caractere(saisie.prenom, "0") == 0) || (compare_chaine_caractere(saisie.nom, "0") == 0) || (compare_chaine_caractere(saisie.adresse.ville, "0") == 0) || (compare_chaine_caractere(saisie.adresse.rue, "0") == 0) || (compare_chaine_caractere(saisie.adresse.code_postal, "0") == 0) || (compare_chaine_caractere(saisie.adresse.pays, "0") == 0) || (compare_chaine_caractere(saisie.metier, "0") == 0) || (compare_chaine_caractere(saisie.email, "0") == 0)) {
        valide = TRUE;
    }

    if(valide == FALSE) {
        //modification du contenu du fichier membre.txt
        FILE *fichier_membre = NULL;
        ajout_membre_fichier_membre(fichier_membre, &(saisie));

        rafrachir_tab_membre(tab_membre, nb_membre); //modif du nombre de membre

        tab_donnee[0]++;

        rafrachir_fichier_donnee(tab_donnee, donnee_livre);

        supr_console();
        printf("%s %s a bien était ajouté comme nouveau membre\n", saisie.prenom, saisie.nom);

        sleep(2);
        supr_console();
    }
}

/*supression d'un membre dans le tableau en memoire et dans le fichier*/
void supr_membre(Membre ***tab_membre, int *nb_membre)
{

    if (*nb_membre == 0)
    {
        supr_console();
        affichage_sous_titre("SUPRESSION D'UN MEMBRE");
        printf("                        !!!Il y a aucun membre!!!\n");
        sleep(2);
        supr_console();
    }
    else
    {
        int i;
        int id_membre;
        // int nb_pret_membre;
        int valide = TRUE;

        do
        {
            supr_console();
            affichage_sous_titre("SUPRESSION D'UN MEMBRE");

            if(valide == FALSE) {
                printf("ERREUR Il n'est pas possible de supprimer le membre\n\n");
            }

            printf("     Saisir l'identifiant du membre a supprimer ou 0 pour retourner au menu : ");
            valide = saisie_id_membre_tab_membre(*tab_membre, &id_membre, nb_membre);

            // verif si le membre peut etre supprimé (pas de pret en cours)
            if((valide == TRUE) &&  (id_membre != 0)){
                i=0;
                while((*tab_membre)[i]->identifiant != id_membre) {
                    i++;
                }
                
                if(calcul_nb_pret_membre((*tab_membre)[i]) != 0) {
                    valide = FALSE;
                }
            }

        } while (valide != TRUE);


        if(id_membre != 0) {
            int choix;
            do
            {
                supr_console();
                affichage_sous_titre("SUPRESSION D'UN MEMBRE");
                if (id_membre != 0)
                {
                    for (i = 0; i < (*nb_membre); i++)
                    {
                        if ((*tab_membre)[i]->identifiant == id_membre)
                        {
                            afficher_toute_info_membre((*tab_membre)[i]);
                        }
                    }
                }

                printf("Voulez vous supprimer ce membre (1 : OUI - 0 : NON (retour au menu)): ");
                saisie_entier(&choix);
            } while ((choix != 1) && (choix != 0));

            if (choix == 1)
            {
                //supression et recréation du contenu du fichier membre.txt
                FILE *fichier_membre = NULL;
                supr_membre_fichier_membre(fichier_membre, &id_membre, *tab_membre, nb_membre);
                rafrachir_tab_membre(tab_membre, nb_membre); //modif de la valeur de nb_membre

                supr_console();
                printf("Le membre %d a bien était suprimer\n", id_membre);

                sleep(2);
                supr_console();
            }
        }
    }

}

/*afichage de la liste des membre en ligne par ordre alphabétique*/
void affichage_liste_membre(Membre **tab_membre, int *nb_membre)
{

    if (*nb_membre == 0)
    {
        supr_console();
        affichage_sous_titre("AFFICHAGE DES MEMBRES");
        printf("                        !!!Il y a aucun membre!!!\n");
        sleep(2);
        supr_console();
    }
    else
    {
        int i;
        int choix;
        int *tab_tri;
        tab_tri = (int *)calloc(1, sizeof(int)); //les valeurs du tableau sont initialisé a 0

        do
        {
            supr_console();
            affichage_sous_titre("AFFICHAGE DES MEMBRES");
            printf("     La librairie contient %d membres\n\n", *nb_membre);

            //affichage dans l'ordre alphabétique
            init_tab_tri_ordre_alpha(tab_membre, tab_tri, nb_membre);
            for (i = 0; i < (*nb_membre); i++)
            {
                afficher_membre(tab_membre[tab_tri[i]]);
            }

            printf("     Saisir 1 pour revenir au menu : ");
            saisie_entier(&choix);
        } while (choix != 1);

        free(tab_tri);
    }
}

/*affichage de toute les informations sur un membre en particulier*/
void affichage_info_membre(Liste_membre *gestion_membre, Liste_pret *gestion_pret, Liste_livre *gestion_livre)
{

    if (gestion_membre->nb_membre == 0)
    {
        supr_console();
        affichage_sous_titre("INFORMATION SUR UN MEMBRE");
        printf("                        !!!Il y a aucun membre!!!\n");
        sleep(2);
        supr_console();
    }
    else
    {
        int i;
        int choix;
        int id_membre;
        int valide = FALSE;

        do
        {
            supr_console();
            affichage_sous_titre("INFORMATION SUR UN MEMBRE");
            printf("     Saisir l'identifiant du membre ou 0 pour revenir au menu : ");

            valide = saisie_id_membre_tab_membre(gestion_membre->liste_membre, &id_membre, &gestion_membre->nb_membre);

            if ((valide == TRUE) && (id_membre != 0))
            {
                for (i = 0; i < gestion_membre->nb_membre; i++)
                {
                    if (gestion_membre->liste_membre[i]->identifiant == id_membre)
                    {
                        afficher_toute_info_membre(gestion_membre->liste_membre[i]);
                        affichage_info_pret_membre(gestion_membre->liste_membre[i],gestion_pret->liste_pret, &gestion_pret->nb_pret, gestion_livre->liste_livre, &gestion_livre->nb_livre);
                    }
                }

                printf("     Saisir 1 pour revenir au menu : ");
                saisie_entier(&choix);
            }

        } while ((choix != 1) && (valide == FALSE));
    }
}

/***********************************************FONCTION LIVRE***********************************************/

/*ajout d'un livre dans le tableau en memoire et dans le fichier*/
void saisie_nx_livre(Livre ***tab_livre, int *nb_livre, Donnee_livre *donnee_livre, int *donnee)
{

    int valide = TRUE;
    Livre* saisie;
    saisie = creer_struct_livre();

    //saisie du livre a ajouter
    do
    {
        supr_console();
        affichage_sous_titre("AJOUT NOUVEAU LIVRE");
        

        if (valide == FALSE)
        {
            printf(" code : %s\n", saisie->code);
            printf("ERREUR livre deja existant ou code non valide\nReesayer\n\n");
        }

        printf("Saisir 0 a un élément pour retourner au menu\n\n");

        valide = saisie_securise_livre_not_in_tab_livre(saisie, *tab_livre, nb_livre, donnee_livre);

        //retour au menu
        if((compare_chaine_caractere(saisie->titre,"0") == 0) || (compare_chaine_caractere(saisie->auteur,"0") == 0) || (compare_chaine_caractere(saisie->code,"0") == 0)) {
            valide = TRUE;
        }
    } while (valide == FALSE);

     if((compare_chaine_caractere(saisie->titre,"0") == 0) || (compare_chaine_caractere(saisie->auteur,"0") == 0) || (compare_chaine_caractere(saisie->code,"0") == 0)) {
         valide = FALSE;
    }

    if(valide == TRUE) {
    //modification du contenu du fichier livre.txt
        FILE *fichier_livre = NULL;
        ajout_livre_fichier_livre(fichier_livre, saisie);

        rafrachir_tab_livre(tab_livre, nb_livre); //modif du nombre de membre

        rafrachir_fichier_donnee(donnee, donnee_livre);

        supr_console();
        printf("%s - %s a bien était ajouté comme nouveau livre\n", saisie->titre, saisie->auteur);

        sleep(2);
        lib_struct_livre(saisie);
        supr_console();
    }
}

/*supression d'un livre dans le tableau en memoire et dans le fichier*/
void supr_livre(Livre ***tab_livre, int *nb_livre, int *donnee, Donnee_livre *donnee_livre)
{

    if (*nb_livre == 0)
    {
        supr_console();
        affichage_sous_titre("SUPRESSION D'UN LIVRE");
        printf("                        !!!Il y a aucun livre!!!\n");
        sleep(2);
        supr_console();
    }
    else
    {
        int i;
        char code_livre[8];
        int valide = TRUE;

        do
        {
            supr_console();
            affichage_sous_titre("SUPRESSION D'UN LIVRE");

            if(valide == FALSE){
                printf("     ERREUR\n");
            }

            printf("     Saisir le code du livre a supprimer (XXX-YYY) ou 0 pour revenir au menu : ");

            valide = saisie_code_livre(code_livre);

            if(valide == TRUE){
                valide = verif_code_livre_in_tab_libre(*tab_livre,code_livre,nb_livre);
            }
            else if(compare_chaine_caractere(code_livre, "0") == 0){ //chaine egale (l'user veut revenir au menu)
                valide = TRUE;
            }
        } while (valide == FALSE);

        if (compare_chaine_caractere(code_livre, "0") != 0) //si on l'user ne veut pas retourner au menu
        {
            //affichage du livre
            int i;
            int indice_livre;
            for (i=0; i<*nb_livre; i++)
            {
                if(compare_chaine_caractere(code_livre, (*tab_livre)[i]->code) == 0)
                {
                    indice_livre = i;
                }
            }

            afficher_toute_info_livre((*tab_livre)[indice_livre]);

            if((*tab_livre)[indice_livre]->nb_exemplaires_dispo != (*tab_livre)[indice_livre]->nb_exemplaires){ //si il y a des prets en cours
                printf("\n     Le livre ne peut pas etre suprimer, il y a des prets en cour\n");
                printf("     Supprimer d'abord les prets pour pouvoir supprimer le livre\n");
                sleep(4);
                supr_console();
            }
            else{

                int choix;
                printf("\nVoulez vous supprimer ce livre (1 : OUI - autres choses : NON (retour au menu)): ");
                saisie_entier(&choix);

                if(choix == 1)
                {
                    //supression et recréation du contenu du fichier livre.txt
                    FILE *fichier_membre = NULL;
                    supr_livre_fichier_livre(fichier_membre, code_livre, *tab_livre, nb_livre);
                    rafrachir_tab_livre(tab_livre, nb_livre); //modif de la valeur de nb_livre

                    // supression d'un livre du genre
                    for(i=0; i<NB_GENRE_LIVRE; i++)
                    {
                        if((donnee_livre->liste_code[i][0] == (*tab_livre)[indice_livre]->code[0]) && (donnee_livre->liste_code[i][1] == (*tab_livre)[indice_livre]->code[1]) && (donnee_livre->liste_code[i][2] == (*tab_livre)[indice_livre]->code[2])) {
                            donnee_livre->nb_livre[i] --;
                        }
                    }
                    printf("ok");
                    rafrachir_fichier_donnee(donnee, donnee_livre);

                    supr_console();
                    printf("Le livre %s a bien était suprimer\n", code_livre);

                    sleep(2);
                    supr_console();
                }
            }
        }
    }
}

// /*affichage de la liste des membre en ligne par ordre alphabétique*/
// void affichage_liste_membre(Membre **tab_membre, int *nb_membre)
// {

//     if (*nb_membre == 0)
//     {
//         supr_console();
//         affichage_sous_titre("AFFICHAGE DES MEMBRES");
//         printf("                        !!!Il y a aucun membre!!!\n");
//         sleep(2);
//         supr_console();
//     }
//     else
//     {
//         int i;
//         int choix;
//         int *tab_tri;
//         tab_tri = (int *)calloc(1, sizeof(int)); //les valeurs du tableau sont initialisé a 0

//         do
//         {
//             supr_console();
//             affichage_sous_titre("AFFICHAGE DES MEMBRES");
//             printf("     La librairie contient %d membres\n\n", *nb_membre);

//             //affichage dans l'ordre alphabétique
//             init_tab_tri_ordre_alpha(tab_membre, tab_tri, nb_membre);
//             for (i = 0; i < (*nb_membre); i++)
//             {
//                 afficher_membre(tab_membre[tab_tri[i]]);
//             }

//             printf("     Saisir 1 pour revenir au menu : ");
//             saisie_entier(&choix);
//         } while (choix != 1);

//         free(tab_tri);
//     }
// }

/*affichage de toute les informations sur un livre en particulier*/
void affichage_info_livre(Liste_livre *gestion_livre, Liste_membre *gestion_membre, Liste_pret *gestion_pret)
{

    if (gestion_livre->nb_livre == 0)
    {
        supr_console();
        affichage_sous_titre("INFORMATION SUR UN LIVRE");
        printf("                        !!!Il y a aucun livre!!!\n");
        sleep(2);
        supr_console();
    }
    else
    {
        int i;
        int choix;
        char code_livre[8];
        int valide = TRUE;

        do{
            choix = 0;

            supr_console();
            affichage_sous_titre("INFORMATION SUR UN LIVRE");

            if(valide == FALSE){
                printf("     ERREUR\n");
            }

            printf("     Saisir le code du livre a consulter (XXX-YYY) ou 0 pour revenir au menu : ");
            valide = saisie_code_livre(code_livre);
            if(valide == TRUE){
                valide = verif_code_livre_in_tab_libre(gestion_livre->liste_livre, code_livre, &gestion_livre->nb_livre);
            }
            else if(compare_chaine_caractere(code_livre, "0") == 0){ //chaine egale (l'user veut revenir au menu)
                valide = TRUE;
            }


            if ((valide == TRUE) && (compare_chaine_caractere(code_livre, "0") != 0))
            {
                for (i = 0; i < gestion_livre->nb_livre; i++)
                {
                    if (compare_chaine_caractere(gestion_livre->liste_livre[i]->code, code_livre) == 0) //chaine identique
                    {
                        afficher_toute_info_livre(gestion_livre->liste_livre[i]);
                        affichage_info_pret_livre(gestion_livre->liste_livre[i], gestion_pret->liste_pret, &gestion_pret->nb_pret, gestion_membre->liste_membre, &gestion_membre->nb_membre);
                    }
                }

                printf("     Saisir 1 pour revenir au menu : ");
                saisie_entier(&choix);
            }

        } while ((choix != 1) && (valide == FALSE));
    }

    supr_console();
}


/***********************************************FONCTION PRET***********************************************/

void saisie_nx_pret(Liste_membre *gestion_membre, Liste_livre *gestion_livre, Liste_pret *gestion_pret, int tab_donnee[2], Donnee_livre *donnee_livre) 
{
    if ((gestion_livre->nb_livre == 0) || (gestion_membre->nb_membre == 0))
    {
        supr_console();
        affichage_sous_titre("AJOUT NOUVEAU PRET");
        printf("                !!!Il y a aucun livre ou aucun membre!!!\n");
        sleep(2);
        supr_console();
    }
    else{

    
        int valide = TRUE;
        Pret* saisie;
        saisie = creer_struct_pret();

        //saisie du pret a ajouter
        do {
            supr_console();
            affichage_sous_titre("AJOUT NOUVEAU PRET");

            if (valide == FALSE) {
                printf("ERREUR\nPret deja existant ou livre et membre inexistant ou il n'est pas possible d'emprunté le livre)\nReesayer\n\n");
            }

            printf("Saisir le pret ou saisir 0 pour revenir au menu : \n");
            valide = saisie_champ_pret_securise_ajout(saisie, gestion_membre->liste_membre, gestion_livre->liste_livre, gestion_pret->liste_pret, &(gestion_membre->nb_membre), &(gestion_livre->nb_livre), &(gestion_pret->nb_pret), tab_donnee);
        } while (valide == FALSE);


        if((saisie->id_membre != 0) && (compare_chaine_caractere(saisie->code_livre,"0") != 0)) { //si l'utilisateur ne veut pas revenir au menu
            int choix = 0;
            do {
                supr_console();
                affichage_sous_titre("AJOUT NOUVEAU PRET");

                printf("Le membre ");
                affichage_prenom_nom_id_membre(&saisie->id_membre, gestion_membre->liste_membre);
                printf("empreunte le livre ");
                affichage_titre_auteur_code_livre(saisie->code_livre, gestion_livre->liste_livre);
                
                printf("\n\nDate de retour maximum : ");
                afficher_date(&saisie->date_retour);

                printf("\n\n");

                if((choix != 0) && (choix != 1)) {
                    printf("ERREUR\n");
                }
                printf("Pour valider le pret ci-dessus taper 1 ou 0 pour revenir au menu : ");
                saisie_entier(&choix);
            } while((choix != 0) && (choix != 1));


            if(choix == 1) { 
                //modification du contenu du fichier prets.txt
                FILE *fichier_pret = NULL;
                ajout_pret_fichier_pret(fichier_pret, saisie);
                rafrachir_tab_pret(&(gestion_pret->liste_pret), &(gestion_pret->nb_pret)); //modif du nombre de pret

                //Ajout du pret dans le mebre correspondant
                FILE *fichier_membre = NULL;
                ajout_pret_struct_membre(saisie, gestion_membre->liste_membre);
                rafraichir_fichier_membre(fichier_membre, gestion_membre->liste_membre, &(gestion_membre->nb_membre));

                //Modification du nombre de pret depuis l'ouverture de la librairie (id pret tot)
                tab_donnee[1] ++;
                rafrachir_fichier_donnee(tab_donnee, donnee_livre);

                //Ajout du pret dans le livre correspondant
                FILE *fichier_livre = NULL;
                ajout_pret_struct_livre(saisie,gestion_livre->liste_livre);
                rafraichir_fichier_livre(fichier_livre, gestion_livre->liste_livre, &(gestion_livre->nb_livre));

                supr_console();
                printf("Le pret pour le livre %s à bien été enregistré\n", saisie->code_livre);
                lib_struct_pret(saisie);
                sleep(2);
                supr_console();
            }
        }
    }
}

void supr_pret(Pret ***tab_pret, int *nb_pret) {

    if (*nb_pret == 0) {
        supr_console();
        affichage_sous_titre("SUPRESSION D'UN PRET");
        printf("                        !!!Il y a aucun pret!!!\n");
        sleep(2);
        supr_console();
    }
    else {
        int i;
        int id_pret;
        int valide = TRUE;

        do {
            supr_console();
            affichage_sous_titre("SUPRESSION D'UN PRET");
            printf("     Saisir l'identifiant du pret a supprimer ou 0 pour retourner au menu : ");

//            valide = saisie_id_membre_tab_membre(*tab_membre, &id_membre, nb_membre);
        } while (valide == FALSE);

        int choix;
        do{
            supr_console();
            affichage_sous_titre("SUPRESSION D'UN MEMBRE");
            if(id_pret != 0){
                for(i=0; i<(*nb_pret); i++)
                {
                    if((*tab_pret)[i]->id_pret == id_pret){
                        afficher_toute_info_pret((*tab_pret)[i]);
                    }
                }
            }

            printf("Voulez vous supprimer ce pret (1 : OUI - 0 : NON (retour au menu)): ");
            saisie_entier(&choix);
        }while((choix != 1) && (choix != 0));

        if(choix == 1){
            // todo: suppression du pret
        }
    }
}

void affichage_liste_pret(Pret **tab_pret, int *nb_pret) {
    int i;
    int choix;

    if (*nb_pret == 0) {
        supr_console();
        affichage_sous_titre("AFFICHAGE DES PRETS");
        printf("                        !!!Il y a aucun pret!!!\n");
        sleep(2);
        supr_console();
    } else {
        do {
            supr_console();
            affichage_sous_titre("AFFICHAGE DES PRETS");
            printf("     Il y a actuellement %d prets\n\n", *nb_pret);
            printf("     Saisir 1 pour consulter les prets en retard ou 0 pour consulter tous les prets : ");
            saisie_entier(&choix);
        } while((choix != 0) && (choix != 1));


        if(choix == 1) { //affichage des prets en retard
            do {
                supr_console();
                affichage_sous_titre("AFFICHAGE DES PRETS");
                //afficher les prets en retard
                printf("     Saisir 1 pour revenir au menu : ");
                saisie_entier(&choix);
            } while (choix != 1);
        }
        else{ //choix = 0
            do {
                supr_console();
                affichage_sous_titre("AFFICHAGE DES PRETS");
                //affichage de tous les prets
                printf("     Saisir 1 pour revenir au menu : ");
                saisie_entier(&choix);
            } while (choix != 1);
        }
    }
}

void affichage_info_pret(Pret **tab_pret, int *nb_pret) {

    if (*nb_pret == 0) {
        supr_console();
        affichage_sous_titre("INFORMATION SUR UN PRET");
        printf("                        !!!Il y a aucun pret!!!\n");
        sleep(2);
        supr_console();
    } else {
        int i;
        int choix;
        int id_pret;
        int valide = FALSE;

        do {
            supr_console();
            affichage_sous_titre("INFORMATION SUR UN PRET");
            printf("     Saisir l'identifiant du pret ou 0 pour revenir au menu : ");


//            valide = saisie_id_membre_tab_membre(tab_membre, &id_membre, nb_membre);
//
//
//            if ((valide == TRUE) && (id_membre != 0)) {
//                for (i = 0; i < (*nb_membre); i++) {
//                    if (tab_membre[i]->identifiant == id_membre) {
//                        afficher_toute_info_membre(tab_membre[i]);
//                    }
//                }
//
//                printf("     Saisir 1 pour revenir au menu : ");
//                saisie_entier(&choix);
//            }

        } while ((choix != 1) && (valide == FALSE));
    }
}
