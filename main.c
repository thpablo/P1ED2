#include <stdio.h>
#include <stdlib.h>
#include "./reg.h"
#include "./functions.h"

int main(int argc, char const *argv[])
{
    /* Seleciona qual tipo de arquivo esta pesquisando */
    char nameFile[TAM_MAX_NAME_FILE];
    setNameOriginFile(atoi(argv[1]), nameFile);

    /* Cria arquivo de Origem */
    FILE* fileOrigin = fopen(nameFile, "rb");
    if(fileOrigin == NULL){
        perror("Erro ao abrir o arquivo de origem");
        exit(1);
    }

    /* Cria arquivo com arvore binaria */
    FILE *fileBinThree = fopen("./bin/arvore_binaria.bin", "wb+");
    if(fileBinThree == NULL){
        perror("Erro ao criar arquivo da arvore binaria");
        exit(1);
    }

    /* Cria arvore Binaria, caso queira */
    /* !!MUDAR 1 para argv[3] -  Nao esta funcionando */  
    if(1){ wantToCreateThree(fileOrigin, fileBinThree, atoi(argv[1])); }

    /* Pesquisa da chave */
    search(fileBinThree, atoi(argv[2]));

    /* Fecha arquivos */
    fclose(fileBinThree);
    fclose(fileOrigin);

    return 0;
}