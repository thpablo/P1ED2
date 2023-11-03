#include <stdio.h>
#include <stdlib.h>
#include "reg.h"

#define ARQ_ORIGEM "./bin/decrescente.bin"
#define TIPO_ARQUIVO 2

void showOriginFile(){
    Reg tempreg;
    FILE* origin = fopen(ARQ_ORIGEM, "rb");
    printf("Arquivo origem: \n");
    while(fread(&tempreg, sizeof(tempreg), 1, origin)){
        printf("%d: %ld %s\n", tempreg.key, tempreg.data1, tempreg.data2);
    }
    printf("\n");
    fclose(origin);
}

void showBinThreeFile(FILE *arq) {
    Node tempnode;
    rewind(arq);

    printf("%-10s%-10s%-10s\n", "CHAVE", "ESQ.", "DIR.");
    while (fread(&tempnode, sizeof(tempnode), 1, arq) == 1) {
        printf("%-10d%-10d%-10d\n", tempnode.reg.key, tempnode.esq, tempnode.dir);
    }
}

/* key: chave buscada
** levelCurrentNode: nivel da arvore onde esta o No atual da pesquisa.
** levelLastNodeInsert: Ultimo nivel que esta sendo inserido na arvore a cada leitura do arquivo origem.
*/
void searchInBinThree(FILE *fileBinThree, int key, int levelCurrentNode, int levelLastNodeInserted){
    Node node;
    /* Atualiza ponteiro para o No onde sera comparado a chave */
    fseek(fileBinThree, levelCurrentNode * sizeof(node), SEEK_SET);
    
    /* Leitura do No naquele nivel */
    fread(&node, sizeof(node), 1, fileBinThree);

    /* Chave maior */
    if(key > node.reg.key){
        /* No filho para direita */
        if(node.dir == -1){
            node.dir = levelLastNodeInserted;
            fseek(fileBinThree, levelCurrentNode * sizeof(node), SEEK_SET);
            fwrite(&node, sizeof(node), 1, fileBinThree);
            
            return ;
        }
        searchInBinThree(fileBinThree, key, node.dir, levelLastNodeInserted);
    }
    /* Chave menor */
    if(key < node.reg.key){
        /* No filho para esquerda */
        if(node.esq == -1){
            node.esq = levelLastNodeInserted;
            fseek(fileBinThree, levelCurrentNode * sizeof(node), SEEK_SET);
            fwrite(&node, sizeof(node), 1, fileBinThree);
            
            return;
        }
        searchInBinThree(fileBinThree, key, node.esq, levelLastNodeInserted);
    }

}


int buildFileBinThree(FILE* origin, FILE* fileBinThree, int condition){
    Node nodes;
    // Ordem aleatoria = 0
    int countNodeLevel = (condition == 3) ? 0 : 1;
    
    // Construcao Arvore
    while(fread(&nodes.reg, sizeof(nodes.reg), 1, origin) == 1){
        nodes.dir = -1;
        nodes.esq = -1;

        switch (condition)
        {
        case 1: //Ascendente
            nodes.dir = countNodeLevel;
            fwrite(&nodes, sizeof(nodes), 1, fileBinThree);
            break;

        case 2: //Descendente
            nodes.esq = countNodeLevel;
            fwrite(&nodes, sizeof(nodes), 1, fileBinThree);
            break;

        case 3: //Aleatorio
            //Coloca valor
            fseek(fileBinThree, countNodeLevel * sizeof(nodes), SEEK_SET);
            fwrite(&nodes, sizeof(nodes), 1, fileBinThree);
            rewind(fileBinThree);
            searchInBinThree(fileBinThree, nodes.reg.key, 0, countNodeLevel);
            break;

        }
        countNodeLevel++;
    }
    /* Caso condicao seja 1 ou 2
    ** Ultimo registro pesquisado sera no folha
    */
    if(condition == 1 || condition == 2){
        nodes.dir = -1;
        nodes.esq = -1;

        fseek(fileBinThree, -1 * sizeof(nodes), 1);
        fwrite(&nodes, sizeof(nodes), 1, fileBinThree);
    }
    return 1;
}

int main(int argc, char const *argv[])
{
    FILE* fileOrigin = fopen(ARQ_ORIGEM, "rb");
    if(fileOrigin == NULL){
        perror("Erro ao abrir o arquivo de origem");
        exit(1);
    }

    FILE *fileBinThree = fopen("./bin/arvore_binaria.bin", "wb+");
    if(fileBinThree == NULL){
        perror("Erro ao criar arquivo da arvore binaria");
        exit(1);
    }

    showOriginFile();

    printf("Arvore binaria: \n");
    if(buildFileBinThree(fileOrigin, fileBinThree, TIPO_ARQUIVO))
        showBinThreeFile(fileBinThree);

    fclose(fileBinThree);
    fclose(fileOrigin);

    return 0;
}
