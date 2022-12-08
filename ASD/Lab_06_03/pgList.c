#include "pgList.h"

typedef struct node *link;

struct node{
    pg_t val;
    link next;
};

struct pgList_s{
    link head;
    int N;
};

link newNode(pg_t val, link next);
link listInsHEad(link h, pg_t val);

pgList_t pgList_init(){

    pgList_t lista = malloc(sizeof (pgList_t));
    lista->head= NULL;
    lista->N = 0;

    return lista;
}

void pgList_free(pgList_t pgList){
}

/* lettura e scrittura su file */
void pgList_read(FILE *fp, pgList_t pgList){

    pg_t personaggio;

   while(!feof(fp)){
       pg_read(fp, &personaggio);
       fscanf(fp,"\n");
       personaggio.equip = equipArray_init();
       personaggio.eq_stat = personaggio.b_stat;
       pgList_insert(pgList, personaggio);

   }
}

void pgList_print(FILE *fp, pgList_t pgList, invArray_t invArray){
    link x;

    for(x = pgList->head; x!= NULL; x = x->next){
        pg_print(fp, &x->val, NULL);
    }
}

/* inserimento di un nuovo personaggio */
void pgList_insert(pgList_t pgList, pg_t pg){
    pgList->head = listInsHEad(pgList->head, pg);
    pgList->N++;
}
/* cancellazione con rimozione */
void pgList_remove(pgList_t pgList, char* cod){
    link x, p;
    pg_t *val;

    val = pgList_searchByCode(pgList, cod);

    if(pgList->head == NULL) return;

    for (x = pgList->head, p = NULL; x!= NULL && &(x->val) != val; p = x, x = x->next);


    if(x == pgList->head){
        pgList->head = x->next;
        return;
    }
    p->next = x->next;
}
/* ricerca per codice, ritornando il puntatore */
pg_t *pgList_searchByCode(pgList_t pgList, char* cod){
    link x;

    for(x = pgList->head; x!= NULL; x = x->next){
        if(strcmp(x->val.cod, cod)==0){
            return &x->val;
        }
    }

    return NULL;
}

/* Si possono aggiungere altre funzioni se ritenute necessarie */
link newNode(pg_t val, link next){
    link x = malloc(sizeof *x);

    if(x == NULL)
        return NULL;

    else{
        x->val = val;
        x->next = next;
    }
    return x;
}

link listInsHEad(link h, pg_t val){
    h = newNode(val, h);
    return h;
}
