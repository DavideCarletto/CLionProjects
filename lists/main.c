#include <stdio.h>
#include "list.h"

int main() {
    list* lstNum = init();
    printf("Lunghezza lista %d\n", getListLength(lstNum));
    lstNum = add(lstNum, 1);
    lstNum = add(lstNum, 2);
    lstNum = add(lstNum, 3);
    lstNum = add(lstNum, 4);
    lstNum = add(lstNum, 5);
    lstNum = add(lstNum, 6);
    printList(lstNum);
    int *el = getFromList(lstNum, 1);
    if(el == NULL){
        fputs("Indice non valido!", stderr);
    } else {
        printf("%d\n", *(el));
    }
    printf("Lunghezza lista %d\n", getListLength(lstNum));

    if(!update(lstNum, 0, 1, 8)){
        printf("indice pos non valido");
    }
    printList(lstNum);
    lstNum = delete(lstNum,1);
    lstNum = delete(lstNum, 0);
    printList(lstNum);

    return 0;
}
