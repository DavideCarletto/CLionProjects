#include "Quotazione.h"
#include "stdio.h"

quotazione_t QUOTAZIONEInit(){
    quotazione_t quotazione;

    quotazione.nTitoli=0;
    quotazione.val=0;
    quotazione.data = DATAInit();

    return quotazione;
}

quotazione_t QUOTAZIONESetNull(){
    quotazione_t   quotazione;

    quotazione.nTitoli = -1;

    return quotazione;
}

void QUOTAZIONEPrint(quotazione_t quotazione){
    printf("Valore della quotazione in data %d/%d/%d: %f \n",quotazione.data.anno, quotazione.data.mese, quotazione.data.giorno,quotazione.val);
}