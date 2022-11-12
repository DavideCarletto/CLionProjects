//
// Created by Federico Carollo on 28/10/2022.
//
#include <stdlib.h>

#ifndef MODELLI_COMBINATORI_UTIL_H
#define MODELLI_COMBINATORI_UTIL_H
int cmp_int(const void* a, const void* b){
    return *((int*)a) - *((int*) b);
}

int filterArray(int *val,int len, int** occ, int** new_v){
    int allocated_size = 1;
    int current_pos = 0;
    int last_found;
    *occ = (int*) calloc(allocated_size, sizeof(int));
    *new_v = (int*) calloc(allocated_size, sizeof(int));
    if(len == 0)
        return 0;

    last_found = val[0];
    (*occ)[0]++;
    (*new_v)[0] = last_found;
    for (int i = 1; i < len; ++i) {
        if(val[i] == last_found){
            (*occ)[current_pos]++;
        } else{
            if((current_pos+1) == allocated_size){
                allocated_size = 2*allocated_size + 1;
                (*occ) = (int*) realloc(*occ, allocated_size*sizeof(int));
                (*new_v) = (int*) realloc(*new_v, allocated_size*sizeof(int));
            }
            (*occ)[++current_pos] = 1;
            last_found = val[i];
            (*new_v)[current_pos] = last_found;
        }
    }
    if((current_pos+1) < allocated_size){
        *occ = (int*) realloc(*occ, sizeof(int)*(current_pos+1));
        *new_v = (int*) realloc(*new_v, sizeof(int)*(current_pos+1));
    }
    return current_pos+1;
}


#endif //MODELLI_COMBINATORI_UTIL_H
