#ifndef LAB_08_03_QUOTAZIONE_H
#define LAB_08_03_QUOTAZIONE_H

#include "Data.h"

typedef struct{
    float val;
    int nTitoli;
    data_t data;
}quotazione_t;

quotazione_t QUOTAZIONEInit();
quotazione_t QUOTAZIONESetNull();
void QUOTAZIONEPrint(quotazione_t quotazione);
#endif //LAB_08_03_QUOTAZIONE_H
