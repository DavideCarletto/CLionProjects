#include "equipArray.h"

struct equipArray_s{
    int *vettEq;
    int inUso;
};

equipArray_t equipArray_init(){
    equipArray_t arr = malloc(sizeof (equipArray_t));

    arr->vettEq = malloc(8*sizeof (inv_t));
    arr->inUso = 0;
}

void equipArray_free(equipArray_t equipArray){
    free(equipArray);
}

/* quanti equipaggiamenti sono in uso */
int equipArray_inUse(equipArray_t equipArray){
    return equipArray->inUso;
}

/* scrittura su file */
void equipArray_print(FILE *fp, equipArray_t equipArray, invArray_t invArray){
    int indexInv;
    inv_t  *inv;

    printf("\nEquipaggiamenti del personaggio:\n");
    for(int i=0; i<equipArray->inUso; i++){
        printf("%d_ ",i+1);
        indexInv = equipArray_getEquipByIndex(equipArray, i);
        inv = invArray_getByIndex(invArray,indexInv);
        inv_print(fp, inv);
    }
}
/* modifica equipaggiamento scegliendo un oggetto da inventario */
void equipArray_update(equipArray_t equipArray, invArray_t invArray){
    int scelta, equipAdd, equipRmv;
    equipArray_print(stdout, equipArray, invArray);

    printf("Si desidera rimuovere o aggiungere un equipaggiamento? (0) aggiungere  (1) rimuovere: ");
    scanf("%d", &scelta);

    switch (scelta) {
        case 0:
            printf("\nEquipaggiamenti disponibili:\n ");
            invArray_print(stdout,invArray);
            printf("\nSelezionare l'equipaggiamento che si vuole aggiungere: ");
            scanf("%d",&equipAdd);
            equipArray_add(equipArray,equipAdd-1);
            break;
        case 1:
            if(equipArray->inUso > 0) {
                printf("Selezionare l'equipaggiamento che si vuole rimuovere: ");
                scanf("%d", &equipRmv);
                if(equipRmv<=equipArray->inUso) {
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
    return equipArray->vettEq[index];
}

/* Si possono aggiungere altre funzioni se ritenute necessarie */
void equipArray_add(equipArray_t equipArray, int index){
    if(equipArray->inUso <= 8) {
        equipArray->vettEq[equipArray->inUso++] = index;
    }
    else
        printf("Superato il numero di equipaggiamenti utilizzabili da questo personaggio.");
}
void equipArray_remove(equipArray_t equipArray, int index){
    for(int i=index+1; i<equipArray->inUso; i++){
        equipArray[i-1] = equipArray[i];
    }
    equipArray->inUso--;
}

void equipArray_newEquipStats(equipArray_t equipArray, stat_t *eq_stat, invArray_t invArray){
    int indexInv;
    inv_t *inv;

    for(int i=0; i<equipArray->inUso; i++){
        indexInv = equipArray_getEquipByIndex(equipArray, i);
        inv = invArray_getByIndex(invArray,indexInv);
        eq_stat->hp+= inv->stat.hp;
        eq_stat->mp+= inv->stat.mp;
        eq_stat->atk+= inv->stat.atk;
        eq_stat->def+= inv->stat.def;
        eq_stat->mag+= inv->stat.mag;
        eq_stat->spr+= inv->stat.spr;
    }

    if(eq_stat->hp<0) eq_stat->hp = 0; if(eq_stat->mp<0) eq_stat->mp = 0; if(eq_stat->atk<0) eq_stat->atk = 0;
    if(eq_stat->def<0) eq_stat->def = 0; if(eq_stat->mag<0) eq_stat->mag = 0; if(eq_stat->spr<0) eq_stat->spr = 0;
}
