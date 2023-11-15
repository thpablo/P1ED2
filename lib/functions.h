#ifndef FUNCTIONS
#define FUNCTIONS

#include <stdio.h>
#include <stdlib.h>
#include "./reg.h"
#include <time.h>
#include <stdbool.h>
#include <string.h>
#define ALEATORIO "./bin/aleatorio.bin"
#define CRESCENTE "./bin/crescente.bin"
#define DECRESCENTE "./bin/crescente.bin"
#define TAM_MAX_NAME_FILE 21

void showOriginFile(char nameFile[]);
void showBinThreeFile(FILE *arq);
int searchInBinThree(FILE *fileBinThree, int key, int levelCurrentNode, int levelNodeInOriginFile, bool isCreating);
int buildFileBinThree(FILE* origin, FILE* fileBinThree, int condition);
void setNameOriginFile(int type, char* nameFile);
void wantToCreateThree(FILE* fileOrigin, FILE* fileBinThree, int type);
void search(FILE *file, int key);

#endif // FUNCTIONS
