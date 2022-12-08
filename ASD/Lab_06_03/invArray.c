#include "invArray.h"

struct invArray_s{
    inv_t *items;
    int size;
};

invArray_t invArray_init(){
    invArray_t arr = malloc(sizeof (invArray_t*));

    arr->items = NULL;
    arr->size = 0;

    return arr;
}
void invArray_free(invArray_t invArray){

}

/* lettura e scrittura su file */
void invArray_read(FILE *fp, invArray_t invArray){
    inv_t inventario;

    if(!feof(fp)){
        fscanf(fp, "%d", &invArray->size);
    }
    invArray->items = malloc(invArray->size* sizeof (inv_t));

    for(int i=0; i< invArray->size; i++) {
        inv_read(fp, &inventario);
        invArray->items[i] = inventario;
    }
}

void invArray_print(FILE *fp, invArray_t invArray){
    fprintf(fp, "\n");
    for(int i=0; i< invArray->size; i++){
        fprintf(fp,"%d_ ",i+1);
        inv_print(fp, &invArray->items[i]);
    }
}
/* stampa un unico oggetto selezionato da indice (nel vettore) */
void invArray_printByIndex(FILE *fp, invArray_t invArray, int index){

}
/* ritorna puntatore a oggetto selezionato da indice (nel vettore) */
inv_t *invArray_getByIndex(invArray_t invArray, int index){
    return &(invArray->items)[index];
}
/* ritorna indice (nel vettore) a oggetto selezionato da nome */
int invArray_searchByName(invArray_t invArray, char *name){

}
