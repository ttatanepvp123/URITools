#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

char *URIEncode(char *text){
    if (text == NULL)
        return NULL;
    char whiteList[] = "()*-.0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz~";
    char *secureOuput = NULL;
    char *output = NULL;
    _Bool tmp = false;
    size_t textSize = strlen(text);
    size_t outputSize = 0;
    for (size_t i = 0; i < textSize; i++){
        tmp = false;
        for (size_t j = 0; j < sizeof(whiteList)-1; j++){
            if (whiteList[j] == text[i]){
                tmp = true;
                if (output == NULL) {
                    secureOuput = calloc(1, 2);
                    outputSize = 1;
                    if(secureOuput == NULL)
                        return NULL;
                    output = secureOuput;
                } else {
                    secureOuput = realloc(output, strlen(output)+2);
                    outputSize++;
                    if(secureOuput == NULL){
                        free(output);
                        return NULL;
                    }
                    output = secureOuput;
                }
                output[outputSize-1] = text[i];
                break;
            }
        }
        if (tmp == false){
            if (output == NULL) {
                secureOuput = calloc(1, 4);
                outputSize = 3;
                if(secureOuput == NULL){
                    fprintf(stderr, "calloc() failed !\n");
                    exit(EXIT_FAILURE);
                }
                output = secureOuput;
            } else {
                secureOuput = realloc(output, strlen(output)+4);
                outputSize+=3;
                if(secureOuput == NULL){
                    fprintf(stderr, "calloc() failed !\n");
                    exit(EXIT_FAILURE);
                }
                output = secureOuput;
            }
            sprintf(output, "%s%%%hhX", output, text[i]);
        }
    }
    return output;
}

char *URIDecode(char *text){
    if (text == NULL)
        return NULL;
    char tmp = '\0';
    char hex[3] = {};
    char *secureOuput = NULL;
    char *output = NULL;
    size_t textSize = strlen(text);
    size_t outputSize = 0;
    for (size_t i = 0; i < textSize; i++){
        if (text[i] == '%'){
            i++;
            hex[0] = text[i];
            i++;
            hex[1] = text[i];
            sscanf(hex, "%hhx", &tmp);
        } else {
            tmp = text[i];
        }
        if (output == NULL) {
            secureOuput = calloc(1, 2);
            outputSize = 1;
            if(secureOuput == NULL){
                fprintf(stderr, "calloc() failed !\n");
                exit(EXIT_FAILURE);
            }
            output = secureOuput;
        } else {
            secureOuput = realloc(output, strlen(output)+2);
            outputSize++;
            if(secureOuput == NULL){
                fprintf(stderr, "calloc() failed !\n");
                exit(EXIT_FAILURE);
            }
            output = secureOuput;
        }
        output[outputSize-1] = tmp;
    }
    return output;
}