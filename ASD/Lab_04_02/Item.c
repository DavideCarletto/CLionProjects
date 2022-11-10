//
// Created by Davide on 09/11/2022.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Item.h"

link listSearch(link h, char *key){
    link x;
   for(x = h; x!= NULL; x = x->next){
       if(KEYeq(x->val.codice, key)==0)
           return x;
   }
    return NULL;
}

link SortListIns(link h, Item val) {
    link x, p;
    if (h==NULL || KEYgreater(h->val,val)>0) {
        return newNode(val, h);
    }
    for (x=h->next, p=h;x!=NULL && KEYgreater(val,x->val)>0;p=x, x=x->next);
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

int KEYeq(char *a, char *b){
    return strcmp(a, b);
}
void printList(link h){
    link x;

    printf("\n");
    for(x  = h; x!= NULL; x = x->next){
        printf("%s %s %s %s %s %s %d\n", x->val.codice, x->val.nome, x->val.cognome, x->val.dataNascita, x->val.via, x->val.citta, x->val.cap);
    }
    printf("\n");

}
void printItem(link x){
    printf("%s %s %s %s %s %s %d\n\n", x->val.codice, x->val.nome, x->val.cognome, x->val.dataNascita, x->val.via, x->val.citta, x->val.cap);
}
void formatDate(Item *val){
    char r[MAX_S],temp[MAX_S];
    int i,j,k,z,n;
    j = 0;
    for(n=strlen(val->dataNascita)-1; n>=0; n=i)
    {
        i=n;
        k=0;
        while(val->dataNascita[i]!='/' && i >= 0)
        {
            temp[k++]=val->dataNascita[i];
            i--;
        }
        i--;
        temp[k] = '\0';
        for(z=strlen(temp)-1; z>=0; z--,j++)
        {
            r[j]=temp[z];
        }
        if(i >= 1)
        {
            r[j++] = val->dataNascita[i + 1];
        }
        temp[0]='\0';
    }
    r[strlen(val->dataNascita)]='\0';
    strcpy(val->dataNascita, r);

}



