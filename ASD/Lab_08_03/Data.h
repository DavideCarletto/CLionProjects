#ifndef LAB_08_03_DATA_H
#define LAB_08_03_DATA_H

typedef struct {
    int anno, mese, giorno;

}data_t;

data_t DATAInit();
char *DATAToString(data_t data);
#endif //LAB_08_03_DATA_H
