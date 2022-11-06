#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_S 50

typedef struct{
    char codice[MAX_S];
    char nome[MAX_S];
    char cognome[MAX_S];
    char dataNascita[MAX_S];
    char via[MAX_S];
    char citta[MAX_S];
    int cap;
}Item;

typedef struct node *link;

struct node {
    Item val;
    link next;
};


void leggiFile(FILE *fp, link *head);
link SortListIns(link h, Item val);
link newNode(Item val, link next) ;
int KEYgreater(Item a, Item b);

int main() {
    FILE *fp = NULL;
    link head = NULL;


    if((fp = fopen("../E2/anag1.txt","r"))==NULL){
        printf("Error opening file...");
        return 1;
    }

    leggiFile(fp, &head);

    link x,p = NULL;
    for (x=head; x!=NULL; p = x, x=x->next) {
        printf("%s %s\n", x->val.nome,x->val.cognome);
    }
    return 0;
}

void leggiFile(FILE *fp, link* head){
    Item val;

    while(!feof(fp)){
            fscanf(fp, "%s %s %s %s %s %s %d", &val.codice[0], &val.nome[0], &val.cognome[0], &val.dataNascita[0],
                   &val.via[0], &val.citta[0], &val.cap);
            (*head) = SortListIns(*head, val);
    }

}

link SortListIns(link h, Item val) {
    link x, p;
    if (h==NULL || KEYgreater(h->val,val))
        return newNode(val, h);
    for (x=h->next, p=h;x!=NULL && KEYgreater(val,x->val);p=x, x=x->next); //aggiungo controllo Keygrater
    p->next = newNode(val, x);
    return h;
}

link newNode(Item val, link next) {
    link x = malloc(sizeof *x);
    if (x==NULL)
        return NULL;
    else {
        x->val = val;
        x->next = next;
    }
    return x;
}

int KEYgreater(Item a, Item b){
    return strcmp(a.dataNascita, b.dataNascita);
}