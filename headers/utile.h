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

int saisie_chaine_caractere(char *chaine, int nb_cara_max);

int compare_chaine_caractere(char *chaine1, char *chaine2);


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

void supr_console(void);

void system_pause();

void affichage_date_du_jour();

#endif /* utile_h */

