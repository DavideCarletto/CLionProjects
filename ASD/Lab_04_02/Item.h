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
link deleteNode(link *head, link val);
link getEndNode(link head);
void formatDate(Item *val);
void printList(link h);
void printItem(link x);
link listSearchC(link head, char *key);
link listSearchD(link head, char *key);
int KEYcmp(char *a, char *b);
void dealloca(link *head);

#endif //LAB_04_02_ITEM_H
