#include "Quotazione.h"
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