#ifndef LAB_08_03_TITOLILIST_H
#define LAB_08_03_TITOLILIST_H

#include "Titolo.h"

typedef struct list *LIST;

LIST LISTInit();
void LISTInsert(LIST list, titolo_t titolo);
void LISTLeggiTitoli(LIST list, FILE *fp);
int TitoloInList(LIST list, char *titolo);
titolo_t LISTGetTitoloByCodice(LIST list, char *codice);
void LISTPrint(LIST list);
void LISTInsert(LIST list, titolo_t titolo);

#endif //LAB_08_03_TITOLILIST_H
