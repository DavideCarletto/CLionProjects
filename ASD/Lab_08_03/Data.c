#include "Data.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#define MAX_C 50

data_t DATAInit(){
    data_t data;

    data.anno=0;
    data.mese=0;
    data.giorno=0;

    return data;
}

char *DATAToString(data_t data){
    char *dataS = malloc(MAX_C*sizeof (char));

    sprintf(dataS,"%d/%d/%d", data.anno,data.mese,data.giorno);

    return dataS;
}

int DATAcmp(data_t data1, data_t data2){
    return strcmp(DATAToString(data1), DATAToString(data2));
}

