#ifndef date_h
#define date_h

#include <stdio.h>
#include <time.h>


//Structure date
typedef struct {
    int jour;
    int mois;
    int annee;
} Date;


void saisir_date(Date *d);
void afficher_date(Date *date);
int compare_date(Date *d1, Date *d2);


//fonction recuperation et ransformation date/timestamp
long int recuperer_timestamp(Date *date);
Date definir_date(long int timestamp);

#endif /* date_h */