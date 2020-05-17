#ifndef date_h
#define date_h

#include <stdio.h>

typedef struct
{
    int jour;
    int mois;
    int annee;
} Date;

void saisir_date(Date *d);

long int recuperer_timestamp(Date *date);

Date *definir_date(long int timestamp);

void afficher_date(Date *date);

int compare_date(Date *d1, Date *d2);

#endif /* date_h */