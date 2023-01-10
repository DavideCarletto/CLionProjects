#ifndef LAB_08_03_TITOLO_H
#define LAB_08_03_TITOLO_H

#include "Data.h"
#include "Ora.h"

typedef struct titolo *titolo_t;

titolo_t TITOLOInit();
char *GETCodiceTitolo(titolo_t titolo);

#endif //LAB_08_03_TITOLO_H
