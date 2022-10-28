#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100
char *cercaRegexp(char *src, char *regexp);
int isInString(char c, char *str);
char *findSub(int init, char fin, char *str, int len);
int isUpper(char c);

int main() {
    char *src = "Ai5t2", *regexp = "\\A[aeiou]5t[123]", *founded=NULL;

    founded = cercaRegexp(src,regexp);

    if(founded!= NULL)
        printf("Regex trovata: %s", founded);
    else
        printf("Regex non trovata.");

    return 0;
}

char *cercaRegexp(char *src, char *regexp){
    char corrCharRegexp, corrCharSrc, *finalString = (char*)malloc(sizeof(char) * (MAX   + 1)),nextCharRegexp;
    int  indexRegexp = 0, countFinalString=0, countRegexp =0;


    for (int i=0; i< strlen(src);i++){
        char *sub;

        corrCharSrc = src[i];
        corrCharRegexp = regexp[indexRegexp];
        nextCharRegexp = regexp[indexRegexp+1];

        switch (corrCharRegexp) {
            case '.':
                finalString[countFinalString++] = corrCharSrc;
                countRegexp++;
                break;

            case '[':
                sub = findSub(indexRegexp+1,']',regexp, strlen(regexp)-indexRegexp);

                if(sub[0]!='^'){
                    if(isInString(corrCharSrc,sub)){
                        finalString[countFinalString++] = corrCharSrc;
                        countRegexp++;
                    }
                }else{
                    if(!isInString(corrCharSrc,sub)){
                        finalString[countFinalString++] = corrCharSrc;
                        countRegexp++;
                    }
                }
                indexRegexp+= (strlen(sub)+1);
                break;

            case '\\':
                if(nextCharRegexp == 'a'){
                    if(!isUpper(corrCharSrc)) {
                        finalString[countFinalString++] = corrCharSrc;
                        countRegexp++;
                    }
                }else if (nextCharRegexp == 'A'){
                    if(isUpper(corrCharSrc)) {
                        finalString[countFinalString++] = corrCharSrc;
                        countRegexp++;
                    }
                }
                indexRegexp++;

                break;

            default:
                if (corrCharRegexp == corrCharSrc) {
                    finalString[countFinalString++] = corrCharSrc;
                    countRegexp++;
                }
                break;
        }
        indexRegexp++;
    }
    finalString[countFinalString] = '\0';

    if(regexp[indexRegexp]== '\0' && countRegexp == strlen(src))
        return &finalString[0];
    return NULL;
}

int isInString(char c, char *str){
    for (int i=0; i< strlen(str);i++){
        if(c == str[i])
            return 1;
    }
    return 0;
}

char *findSub(int init, char fin,char *str, int len){
    char *finString = (char*)malloc(sizeof(char) * (len   + 1)); //alloca una parte di memoria per ospitare gli elementi del vettore
    int count = 0;

    for(int i = init; str[i]!= fin; i++){
        finString[count++] = str[i];
    }
    finString[count] = '\0';

    return finString;
}

int isUpper(char c){
    if(c>='A' && c<='Z')
        return 1;
    return 0;
}