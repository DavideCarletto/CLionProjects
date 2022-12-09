#include "invArray.h"

struct invArray_s{
    inv_t *vettInv;
    int nInv, maxInv;
};

invArray_t invArray_init(){
    invArray_t arr = malloc(sizeof (invArray_t*));

    arr->vettInv = NULL;
    arr->nInv = 0;
    arr->maxInv = 8;
    return arr;
}
void invArray_free(invArray_t invArray){
    free(invArray);
}

/* lettura e scrittura su file */
void invArray_read(FILE *fp, invArray_t invArray){
    inv_t inventario;

    if(!feof(fp)){
        fscanf(fp, "%d", &invArray->nInv);
    }
    invArray->vettInv = malloc(invArray->nInv * sizeof (inv_t));

    for(int i=0; i< invArray->nInv; i++) {
        inv_read(fp, &inventario);
        invArray->vettInv[i] = inventario;
    }
}

void invArray_print(FILE *fp, invArray_t invArray){
    fprintf(fp, "\n");
    for(int i=0; i< invArray->nInv; i++){
        fprintf(fp,"%d_ ",i+1);
        inv_print(fp, &invArray->vettInv[i]);
    }
}
/* stampa un unico oggetto selezionato da indice (nel vettore) */
void invArray_printByIndex(FILE *fp, invArray_t invArray, int index){
    inv_print(fp, &invArray->vettInv[index]);
}
/* ritorna puntatore a oggetto selezionato da indice (nel vettore) */
inv_t *invArray_getByIndex(invArray_t invArray, int index){
    return &(invArray->vettInv)[index];
}
/* ritorna indice (nel vettore) a oggetto selezionato da nome */
int invArray_searchByName(invArray_t invArray, char *name){
    for(int i=0; i<invArray->nInv; i++){
        if (strcmp(invArray->vettInv[i].nome, name) == 0 )
            return i;
    }
    return -1;
}
