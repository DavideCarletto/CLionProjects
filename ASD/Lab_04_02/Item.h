//
// Created by Davide on 09/11/2022.
//

#ifndef LAB_04_02_ITEM_H
#define LAB_04_02_ITEM_H

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

link SortListIns(link h, Item val);
link newNode(Item val, link next) ;
int KEYgreater(Item a, Item b);
void formatDate(Item *val);
void printList(link h);
void printItem(link x);
link listSearch(link head, char *key);
int KEYeq(char *a, char *b);

#endif //LAB_04_02_ITEM_H
