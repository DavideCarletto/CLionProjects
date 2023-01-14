#include "Titolo.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"


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
    titolo->BST = BSTInit();
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

void TITOLOBSTLoad(quotazioneBST bst, titolo_t titolo){
    quotazione_t quotazioneSearch, quotazioneTitolo;

    for(int i=0; i<titolo->nTransizioni; i++){
        quotazioneTitolo = TITOLOGeneraQuotazione(titolo,titolo->elencoTransizioni[i].data);
        quotazioneSearch = BSTSearch(bst, titolo->elencoTransizioni[i].data);
        if(quotazioneSearch.nTitoli== -1){
            BSTInsert(bst, quotazioneTitolo);
        }
    }
}

quotazione_t TITOLOGeneraQuotazione(titolo_t titolo, data_t data){
    quotazione_t quotazione = QUOTAZIONEInit();
    float num=0, den=0;

    for(int i=0; i<titolo->nTransizioni; i++){
        if(DATAcmp(titolo->elencoTransizioni[i].data, data)==0) {
            num+= titolo->elencoTransizioni[i].valore* (float)titolo->elencoTransizioni[i].numero;
            den+= (float) titolo->elencoTransizioni[i].numero;
        }
    }
    quotazione.nTitoli++;
    quotazione.val = num/den;
    quotazione.data = data;

    return quotazione;
}

quotazioneBST TITOLOGetBST(titolo_t titolo){
    return titolo->BST;
}

quotazione_t TITOLOCercaQuotazioneMin(titolo_t titolo, data_t data1, data_t data2){
    data_t dataCurr;
    dataCurr.anno =-1;
    quotazione_t quotazioneMin = QUOTAZIONESetNull(), quotazione;
    quotazioneMin.val = (float)INT_MAX;

    for (int i = 0; i < titolo->nTransizioni; i++) {
        if(DATAcmp(dataCurr, titolo->elencoTransizioni[i].data)!=0 && DATAcmp(titolo->elencoTransizioni[i].data,data1)>=0 && DATAcmp(titolo->elencoTransizioni[i].data,data2)<=0) {
            quotazione = BSTSearch(titolo->BST, titolo->elencoTransizioni[i].data);
            if (quotazione.nTitoli != -1) {
                dataCurr = titolo->elencoTransizioni[i].data;
                if (quotazione.val < quotazioneMin.val)
                    quotazioneMin = quotazione;
            }
        }
    }
    return quotazioneMin;
}
quotazione_t TITOLOCercaQuotazioneMax(titolo_t titolo, data_t data1, data_t data2){
    data_t dataCurr;
    dataCurr.anno =-1;
    quotazione_t quotazioneMax = QUOTAZIONESetNull(), quotazione;
    quotazioneMax.val = (float)INT_MIN;

    for (int i = 0; i < titolo->nTransizioni; i++) {
        if(DATAcmp(dataCurr, titolo->elencoTransizioni[i].data)!=0 && DATAcmp(titolo->elencoTransizioni[i].data,data1)>=0 && DATAcmp(titolo->elencoTransizioni[i].data,data2)<=0) {
            quotazione = BSTSearch(titolo->BST, titolo->elencoTransizioni[i].data);
            dataCurr = titolo->elencoTransizioni[i].data;
            if (quotazione.nTitoli != -1) {
                if (quotazione.val > quotazioneMax.val)
                    quotazioneMax = quotazione;
            }
        }
    }
    return quotazioneMax;
}

data_t TITOLOGetDataMax(titolo_t titolo){
    data_t dataMax =DATAInit();

    for(int i=0; i< titolo->nTransizioni; i++){
        if(DATAcmp(titolo->elencoTransizioni[i].data,dataMax)>0)
            dataMax = titolo->elencoTransizioni[i].data;
    }
    return dataMax;
}

data_t TITOLOGetDataMin(titolo_t titolo){
    data_t dataMin =DATAInit();
    dataMin.anno = INT_MAX;

    for(int i=0; i< titolo->nTransizioni; i++){
        if(DATAcmp(titolo->elencoTransizioni[i].data,dataMin)<0)
            dataMin = titolo->elencoTransizioni[i].data;
    }
    return dataMin;
}