#include "Titolo.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "QuotazioneBST.h"

#define MAX_C 100

typedef struct {
    data_t data;
    ora_t ora;
    float valore;
    int numero;
}transizione_t;

struct titolo{
    char codiceTitolo[MAX_C];
    transizione_t *elencoTransizioni;
    int nTransizioni;
    quotazioneBST BST;
};


titolo_t TITOLOInit(char *codice){
    titolo_t  titolo = malloc(sizeof (*titolo));
    titolo->elencoTransizioni  = malloc(100* sizeof (transizione_t));
    strcpy(titolo->codiceTitolo, codice);
    titolo->nTransizioni=0;
    return titolo;
}

void TITOLOload(FILE *fp, titolo_t titolo, int dim_transiz){
        for(int j=titolo->nTransizioni; j< dim_transiz+titolo->nTransizioni;j++){
            fscanf(fp,"%d/%d/%d %d:%d %f %d\n", &titolo->elencoTransizioni[j].data.anno,&titolo->elencoTransizioni[j].data.mese,&titolo->elencoTransizioni[j].data.giorno,&titolo->elencoTransizioni[j].ora.ore,&titolo->elencoTransizioni[j].ora.minuti, &titolo->elencoTransizioni[j].valore, &titolo->elencoTransizioni[j].numero);
//            fprintf(stdout,"%d/%d/%d %d:%d %f %d\nTitoli", titolo->elencoTransizioni[j].data.anno,titolo->elencoTransizioni[j].data.mese,titolo->elencoTransizioni[j].data.giorno,titolo->elencoTransizioni[j].ora.ore,titolo->elencoTransizioni[j].ora.minuti, titolo->elencoTransizioni[j].valore, titolo->elencoTransizioni[j].numero);
        }
        titolo->nTransizioni+=dim_transiz;
}

char *GETCodiceTitolo(titolo_t titolo){
    return titolo->codiceTitolo;
}

void TITOLOPrint(titolo_t titolo){

    printf("%s\n", titolo->codiceTitolo);
    for(int j=0; j<titolo->nTransizioni; j++) {
        printf("%d/%d/%d %d:%d %f %d\n", titolo->elencoTransizioni[j].data.anno, titolo->elencoTransizioni[j].data.mese,
               titolo->elencoTransizioni[j].data.giorno, titolo->elencoTransizioni[j].ora.ore,
               titolo->elencoTransizioni[j].ora.minuti, titolo->elencoTransizioni[j].valore,
               titolo->elencoTransizioni[j].numero);
    }
    printf("\n");
}
