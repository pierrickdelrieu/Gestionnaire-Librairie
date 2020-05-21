#include "../headers/date.h"
#include <time.h>

void saisir_date(Date *d) {
    do {
        printf("     jour : ");
        scanf(" %d", &(d->jour));  //(*d).jour <=> &(d->jour)
    } while ((d->jour <= 0) || (d->jour > 31));

    do {
        printf("     mois : ");
        scanf(" %d", &(d->mois));
    } while ((d->mois <= 0) || (d->mois > 12));

    printf("     annee : ");
    scanf(" %d", &(d->annee));
}

long int recuperer_timestamp(Date *date) {
    struct tm t;

    t.tm_year = date->annee;
    t.tm_mon = date->mois;
    t.tm_mday = date->jour;
    t.tm_hour = 0;
    t.tm_min = 0;
    t.tm_sec = 0;

    return mktime(&t);
}

Date definir_date(long int timestamp) {
    struct tm *dts = localtime(&timestamp);
    Date date;

    date.jour = dts->tm_mday;
    date.mois = dts->tm_mon + 1;
    date.annee = 1900 + dts->tm_year;

    return date;
}

void afficher_date(Date *date) {
    if (date->jour < 10)
        printf("0%d", date->jour);
    else
        printf("%d", date->jour);

    printf("/");

    if (date->mois < 10)
        printf("0%d", date->mois);
    else
        printf("%d", date->mois);

    printf("/");

    printf("%d", date->annee);
}

int compare_date(Date *d1, Date *d2) {
    /*retourne 0 si d1 = d2
      retourne 1 si d1 > d2
      retourne −1 si d1 < d2*/

    int retour = -1; //valeur de retour

    if ((d2->annee == d1->annee) && (d2->mois == d1->mois) && (d2->jour == d1->jour)) {
        retour = 0;
    } else {
        if (d2->annee < d1->annee) {
            retour = 1;
        } else {
            if (d2->mois < d1->mois) {
                retour = 1;
            } else {
                if (d2->jour < d1->jour) {
                    retour = 1;
                }
            }
        }
    }

    return (retour);
}