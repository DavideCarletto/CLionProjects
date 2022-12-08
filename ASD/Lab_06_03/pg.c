#include "pg.h"

/* lettura e scrittura su file */
int pg_read(FILE *fp, pg_t *pgp){
        fscanf(fp,"%s %s %s %d %d %d %d %d %d",pgp->cod, pgp->nome, pgp->classe, &pgp->b_stat.hp, &pgp->b_stat.mp, &pgp->b_stat.atk, &pgp->b_stat.def,&pgp->b_stat.mag,&pgp->b_stat.spr);
}
/* non essendo struct dinamica, pulisce chiamando il distruttire di equipArray */
void pg_clean(pg_t *pgp){

}

void pg_print(FILE *fp, pg_t *pgp, invArray_t invArray){
    fprintf(fp,"%s %s %s %d %d %d %d %d %d\n",pgp->cod, pgp->nome, pgp->classe, pgp->b_stat.hp, pgp->b_stat.mp, pgp->b_stat.atk, pgp->b_stat.def,pgp->b_stat.mag,pgp->b_stat.spr);

    if(equipArray_getSize(pgp->equip)>0){
        equipArray_print(stdout, pgp->equip, NULL);
        fprintf(fp,"\nPersonaggio con statistiche equipaggiate:\n ");
        fprintf(fp,"%s %s %s %d %d %d %d %d %d\n",pgp->cod, pgp->nome, pgp->classe, pgp->eq_stat.hp, pgp->eq_stat.mp, pgp->eq_stat.atk, pgp->eq_stat.def,pgp->eq_stat.mag,pgp->eq_stat.spr);
        fprintf(fp, "\n");
    }
}

/* modifica personaggio aggiungendo/togliendo un equipaggiamento selezionato da inventario:
di fatto e' sufficiente chiamare l'opportuna funzione dal modulo equipArray */
void pg_updateEquip(pg_t *pgp, invArray_t invArray){
    equipArray_update(pgp->equip,invArray);
    pgp->eq_stat = pgp->b_stat;
    equipArray_newEquipStats(pgp->equip, &pgp->eq_stat);

}

/* Si possono aggiungere altre funzioni se ritenute necessarie */

