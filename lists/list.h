//
// Created by fcarollo on 07/04/2022.
//

#ifndef LISTS_LIST_H
#define LISTS_LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct List list;

//#region proto
list* init();
list* add(list* head, int val);
list* delete(list* head, int pos);
list* searchLast(list* head);
list* getPtrFromList(list* head, int index, int pos);
int update(list* head, int index, int pos, int newVal);
int* getFromList(list* head, int pos);
int* getVal(list* head, int index, int pos);
int listLength(list* head, int length);
//#endregion;

struct List{
    int num;
    list* next;
};

list* init(){
    list* head = NULL;
    return head;
}

void printList(list *head);

/**
 * Nelle funzioni che modificano la lista va ritornato di nuovo il riferimento al primo elemento
 * per i meccanismi di C
 */
list* add(list* head, int val){
    list* new = (list*) calloc(1,sizeof(list)); //alloca nuova memoria per l'oggetto
    list* last;
    new->next = NULL;
    new->num = val;
    last = searchLast(head);
    if(last == NULL){
        head = new;
    } else {    //aggiunge in coda all'ultimo elemento il nuovo
        last->next = new;
    }
    return head;
}

/**
 *
 * @param head
 * @param pos
 * @param newVal
 * @return 0 if failure, 1 if success
 */
int update(list* head, int index, int pos, int newVal){
    if(head == NULL || index > pos)
        return 0;
    else {
        if(index == pos){
            head->num = newVal;
            return 1;
        }
        else{
            return update(head->next, ++index, pos, newVal);
        }

    }
}
/**
 * Funziona ma non riporta errori in caso di failure
 * COntorllare da codice che la posizione da eliminare sia <= lstLen
 * @param head
 * @param pos
 */
list* delete(list* head, int pos){
    list* toDelete = getPtrFromList(head,0, pos);
    if(toDelete == NULL)
        return head;
    int l = listLength(head, 0);
    if(l == 0)
        return head;
    if(pos == 0){
        return head->next;
    } else {
        list *beforeDelete = getPtrFromList(head, 0, pos-1);
        if(beforeDelete == NULL)    //non dovrebbe succedere
        {
            return head;
        }
        beforeDelete->next = toDelete->next;
        free(toDelete);
        return head;
    }

}

/**
 * Non distingue tra HEAD = NULL e HEAD->NEXT = NULL
 * controllo a mano dove richiamata!
 */
list* searchLast(list* head){
    if(head == NULL || head->next == NULL){
        return head;
    } else
        return searchLast(head->next);
}

/**
 * Stampa tutta la lista
 */
void printList(list *head){
    if(head!=NULL){
        list temp = *(head);    //uso una variabile appoggio perché sennò sclera male e head.next inizia a puntare
        list* tempPTR = &temp;  // a caso a 0x05 perché si
        printf("%d ", temp.num);
        printList(tempPTR->next);
    } else{
        putchar('\n');
    }
}

/**
 * Recupera il valore int alla posizione specificata
 * Uso puntatore in modo da poter ritornare NULL
 */
int* getFromList(list* head, int pos){
    list* ptr = getPtrFromList(head, 0, pos);
    return &(ptr->num);
}

int getListLength(list* head){
    return listLength(head, 0);
}

/**
 * Ritorna la lunghezza della lista
 */
int listLength(list* head, int length){
    if(head == NULL){
        return length;
    }
    return listLength(head->next, ++length);
}

/**
 * Ritorna il riferimento all'elemento list alla posizione specificata
 */
list* getPtrFromList(list* head, int index, int pos){
    if(head == NULL || index>pos){
        return NULL;
    }
    if(index == pos){
        return head;
    } else {
        return getPtrFromList(head->next, ++index, pos);
    }
}

#endif //LISTS_LIST_H
