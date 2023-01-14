#ifndef LAB_08_03_DATA_H
#define LAB_08_03_DATA_H

typedef struct {
    int anno, mese, giorno;

}data_t;

data_t DATAInit();
char *DATAToString(data_t data);
int DATAcmp(data_t data1, data_t data2);
#endif //LAB_08_03_DATA_H
