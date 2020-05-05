#include "../headers/date.h"

int recuperer_timestamp(Date *date) {
    return 42;
}

Date *definir_date(int timestamp) {
    Date *date;

    date->jour = 8;
    date->mois = 12;
    date->annee = 2001;

    return date;
}