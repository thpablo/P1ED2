#ifndef REG_H
#define REG_H

#define DATA_2_MAX 80 // Tamanho maximo de caracteres char no Dado2

typedef struct reg{
    int key;
    long int data1;
    char data2[DATA_2_MAX];
}Reg;

typedef struct node{
    Reg reg;
    int esq;
    int dir;
}Node;

#endif // REG_H
