#ifndef utile_h
#define utile_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <unistd.h>

#include "date.h"

#define TRUE 1
#define FALSE 0

void saisie_entier(int *entier);

int saisie_chaine_caractere(char *chaine, int nb_cara_max);

int compare_chaine_caractere(char *chaine1, char *chaine2);

int lecture_chaine_cara_fichier(FILE *fichier, char *chaine, int taille_max);


//...................SYSTEME D'EXLOITATION....................
#ifdef _WIN32
#define SYSTEME_EXPLOITATION "win" //windows
#elif __linux__
#define SYSTEME_EXPLOITATION "linux"
#elif __APPLE__
#define SYSTEME_EXPLOITATION "mac"
#else
#define SYSTEME_EXPLOITATION "unk" //systéme inconnu
#endif

void supr_console();


#endif /* utile_h */

