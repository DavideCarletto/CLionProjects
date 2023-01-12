#ifndef LAB_08_03_TITOLO_H
#define LAB_08_03_TITOLO_H

#include "Data.h"
#include "Ora.h"
#include "stdio.h"

typedef struct titolo *titolo_t;

titolo_t TITOLOInit(char *codice);
char *GETCodiceTitolo(titolo_t titolo);
void TITOLOload(FILE *fp, titolo_t titolo, int dim_transiz);
void TITOLOPrint(titolo_t titolo);

#endif //LAB_08_03_TITOLO_H