#include "equipArray.h"

struct equipArray_s{
    inv_t *items;
    int size, max;
};
equipArray_t equipArray_init(){
    equipArray_t arr = malloc(sizeof (equipArray_t));

    arr->items = malloc(8*sizeof (inv_t));
    arr->size = 0;
    arr->max = 8;
}

void equipArray_free(equipArray_t equipArray){

}

/* quanti equipaggiamenti sono in uso */
int equipArray_inUse(equipArray_t equipArray){
    return equipArray->size;
}

/* scrittura su file */
void equipArray_print(FILE *fp, equipArray_t equipArray, invArray_t invArray){
    printf("\nEquipaggiamenti del personaggio:\n");
    for(int i=0; i<equipArray->size;i++){
        printf("%d_ ",i+1);
        inv_print(fp, &equipArray->items[i]);
    }
}
/* modifica equipaggiamento scegliendo un oggetto da inventario */
void equipArray_update(equipArray_t equipArray, invArray_t invArray){
    int scelta, equipAdd, equipRmv;
    inv_t *inv;
    equipArray_print(stdout, equipArray, invArray);

    printf("Si desidera rimuovere o aggiungere un equipaggiamento? (0) aggiungere  (1) rimuovere: ");
    scanf("%d", &scelta);

    switch (scelta) {
        case 0:
            printf("\nEquipaggiamenti disponibili:\n ");
            invArray_print(stdout,invArray);
            printf("\nSelezionare l'equipaggiamento che si vuole aggiungere: ");
            scanf("%d",&equipAdd);
            inv = invArray_getByIndex(invArray,equipAdd-1);
            equipArray_add(equipArray,inv);
            break;
        case 1:
            if(equipArray->size>0) {
                printf("Selezionare l'equipaggiamento che si vuole rimuovere: ");
                scanf("%d", &equipRmv);
                if(equipRmv<=equipArray->size) {
                    equipArray_remove(equipArray, equipRmv - 1);
                } else{
                    printf("Scelta non valida.");
                }
            }else
                printf("Non ci sono equipaggiamenti da rimuovere");
            break;
        default:
            printf("Scelta non valida.");
    }
}
/* torna indice (nel vettore inventario) dell'oggetto in posizione index (0..EQUIP_SLOT-1) di equipArray */
int equipArray_getEquipByIndex(equipArray_t equipArray, int index){
}

/* Si possono aggiungere altre funzioni se ritenute necessarie */
void equipArray_add(equipArray_t equipArray, inv_t *inv){
    if(equipArray->size <= equipArray->max) {
        equipArray->items[equipArray->size++] = *inv;
    }
    else
        printf("Superato il numero di equipaggiamenti utilizzabili da questo personaggio.");
}
void equipArray_remove(equipArray_t equipArray, int index){
    for(int i=index+1; i<equipArray->size;i++){
        equipArray[i-1] = equipArray[i];
    }
    equipArray->size--;
}

void equipArray_newEquipStats(equipArray_t equipArray, stat_t *eq_stat){

    for(int i=0; i<equipArray->size;i++){
        eq_stat->hp+= equipArray->items[i].stat.hp;
        printf("%d %d \n",  eq_stat->hp, equipArray->items[i].stat.hp);
        eq_stat->mp+= equipArray->items[i].stat.mp;
        eq_stat->atk+= equipArray->items[i].stat.atk;
        eq_stat->def+= equipArray->items[i].stat.def;
        eq_stat->mag+= equipArray->items[i].stat.mag;
        eq_stat->spr+= equipArray->items[i].stat.spr;
    }
}

int equipArray_getSize(equipArray_t equipArray){
    return equipArray->size;
}