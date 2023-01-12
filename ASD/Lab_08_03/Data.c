#include "Data.h"
#include "stdio.h"
#define MAX_C 50

data_t DATAInit(){
    data_t data;

    data.anno=0;
    data.mese=0;
    data.giorno=0;

    return data;
}

char *DATAToString(data_t data){
    char dataS[MAX_C];

    sprintf(dataS,"%d/%2d/%d", data.anno,data.mese,data.giorno);

    printf("%s",dataS);
}