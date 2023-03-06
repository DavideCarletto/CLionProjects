#include "Item.h"

struct item{
    int val, key;
};

Item ITEMsetvoid(){

    Item val = malloc(sizeof (Item*));
    val->val = -1;

    return val;
}

void ITEMset(Item item, int val){
    item->val = val;
}


void ITEMprint(FILE* fp, Item val){
    fprintf(fp,"%d ",val->val);
}

int ITEMgreater(Item item1, Item item2){
    return item1->val > item2->val ? 1:0;
}

int ITEMgetVal(Item item){
    return item->val;
}

int ITEMeq(Item item1, Item item2){
    return item1->val == item2->val ? 1:0;
}

int ITEMcmp(Item item1, Item item2){
    if(item1->val>item2->val)
        return 1;
    if(item1->val<item2->val)
        return -1;
    return 0;
}

