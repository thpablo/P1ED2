#ifndef FILE_GENERATOR
#define FILE_GENERATOR

#include <stdlib.h>
#include <stdio.h>

#define LEN 80

typedef struct
{
    int key;
    long int longNumber;
    char randChars[LEN];
} Data;

void randomString(char *s, const int len, int timex);
void generatorBinFile(int n, int op);
FILE *openFile(const char *nomeArquivo, const char *modo);
void shuffle(Data arr[], int n);
#endif