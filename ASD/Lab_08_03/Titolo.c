#include "Titolo.h"
#include "stdio.h"
#include "stdlib.h"

#define MAX_C 100

struct titolo{
    char codiceTitolo[MAX_C];
    data_t data;
    ora_t ora;
    int valore, numero;
};

titolo_t TITOLOInit(){
    titolo_t  titolo = malloc(sizeof (*titolo));
    titolo->data = DATAInit();
    titolo->ora = ORAInit();
    titolo->valore = 0;
    titolo->numero = 0;

    return titolo;
}

void leggiTitoli(FILE *fp){
    int dim_titoli, dim_transaz;
    //TODO: mi son fermato qui perchè sto finendo la voglia di vivere contando il fatto che sto studiando 10/12 ore al giorno materie che non ha un minimo senso che siano nella stessa sessione
    fscanf(fp,"%d", &dim_titoli);

    for(int i=0; i< dim_titoli; i++){
        fscanf(fp, "%s %d",NULL, &dim_transaz);
        for(int j=0; j< dim_transaz;j++){

        }
    }
}

char *GETCodiceTitolo(titolo_t titolo){
    return titolo->codiceTitolo;
}