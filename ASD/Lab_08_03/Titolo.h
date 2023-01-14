#ifndef LAB_08_03_TITOLO_H
#define LAB_08_03_TITOLO_H

#include "Data.h"
#include "Ora.h"
#include "stdio.h"
#include "QuotazioneBST.h"

typedef struct titolo *titolo_t;

titolo_t TITOLOInit(char *codice);
char *GETCodiceTitolo(titolo_t titolo);
void TITOLOload(FILE *fp, titolo_t titolo, int dim_transiz);
void TITOLOPrint(titolo_t titolo);
void TITOLOBSTLoad(quotazioneBST bst, titolo_t titolo);
quotazioneBST TITOLOGetBST(titolo_t titolo);
quotazione_t TITOLOGeneraQuotazione(titolo_t titolo, data_t data);
quotazione_t TITOLOCercaQuotazioneMin(titolo_t titolo, data_t data1, data_t data2);
quotazione_t TITOLOCercaQuotazioneMax(titolo_t titolo, data_t data1, data_t data2);
data_t TITOLOGetDataMax(titolo_t titolo);
data_t TITOLOGetDataMin(titolo_t titolo);
#endif //LAB_08_03_TITOLO_H