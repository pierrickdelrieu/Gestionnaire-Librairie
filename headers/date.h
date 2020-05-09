#ifndef date_h
#define date_h

typedef struct
{
    int jour;
    int mois;
    int annee;
} Date;

int recuperer_timestamp(Date *date);

Date *definir_date(int timestamp);

#endif /* date_h */