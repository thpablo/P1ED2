#include "./functions.h"

// Printar arquivo de origem
void showOriginFile(char nameFile[]){
    Reg tempreg;
    FILE* origin = fopen(nameFile, "rb");
    printf("Arquivo origem: \n");
    while(fread(&tempreg, sizeof(tempreg), 1, origin)){
        printf("%d: %ld %s\n", tempreg.key, tempreg.data1, tempreg.data2);
    }
    printf("\n");
    fclose(origin);
}
// Printar arquivo com arvore binaria
void showBinThreeFile(FILE *arq) {
    Node tempnode;
    rewind(arq);
    printf("\n%-10s%-10s%-10s", "CHAVE", "ESQ.", "DIR.");
    while (fread(&tempnode, sizeof(tempnode), 1, arq) == 1) {
        printf("\n%-10d%-10d%-10d", tempnode.reg.key, tempnode.esq, tempnode.dir);
    }
}

/* key: chave buscada
** levelCurrentNode: nivel da arvore onde esta o No atual da pesquisa.
** levelNodeInOriginFile: Ultimo nivel que esta sendo inserido na arvore a cada leitura do arquivo origem.
** isCreating: Indica se esta criando ou somente pesquisando
*/
int searchInBinThree(FILE *fileBinThree, int key, int levelCurrentNode, int levelNodeInOriginFile, bool isCreating){
    Node node;
    /* Atualiza ponteiro para o No onde sera comparado a chave */
    fseek(fileBinThree, levelCurrentNode * sizeof(node), SEEK_SET);
    /* Leitura do No naquele nivel */
    fread(&node, sizeof(node), 1, fileBinThree);

    /* Chave maior */
    if(key > node.reg.key){
        /* No filho para direita */
        if(node.dir == -1){
            if(isCreating){
                node.dir = levelNodeInOriginFile;
                fseek(fileBinThree, levelCurrentNode * sizeof(node), SEEK_SET);
                fwrite(&node, sizeof(node), 1, fileBinThree);
            }
            return -1;
        }
        return searchInBinThree(fileBinThree, key, node.dir, levelNodeInOriginFile, isCreating);
    }

    /* Chave menor */
    if(key < node.reg.key){
        /* No filho para esquerda */
        if(node.esq == -1){
            if(isCreating){
                node.esq = levelNodeInOriginFile;
                fseek(fileBinThree, levelCurrentNode * sizeof(node), SEEK_SET);
                fwrite(&node, sizeof(node), 1, fileBinThree);
            }
            return -1;
        }
        return searchInBinThree(fileBinThree, key, node.esq, levelNodeInOriginFile, isCreating);
    }
    
    return levelCurrentNode;
}
/* Cria arquivo com arvore binaria */
int buildFileBinThree(FILE* origin, FILE* fileBinThree, int condition){
    Node nodes;
    // Ordem aleatoria-> countNodeLevel = 0
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
            searchInBinThree(fileBinThree, nodes.reg.key, 0, countNodeLevel, true);
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
/* Seta nome do arquivo de origem com base no tipo de ordenacao */
void setNameOriginFile(int type, char* nameFile){
    switch(type){
        case 1:
            strcpy(nameFile, CRESCENTE);
        break;
        case 2:
            strcpy(nameFile, DECRESCENTE);
        break;
        case 3:
            strcpy(nameFile, ALEATORIO);
        break;
        default:
            printf("Tipo de ordenacao incorreto, tente valores validos (1, 2 ou 3 )\n");
            exit(1);
    }
}
/* Funcao decide se quer criar arquivo novo */
void wantToCreateThree(FILE* fileOrigin, FILE* fileBinThree, int type){
    clock_t start, end;
    start = clock();

    printf("Criando Arvore binaria... ");
    if(buildFileBinThree(fileOrigin, fileBinThree, type))
        showBinThreeFile(fileBinThree);
    end = clock();
    printf("\nFoi levado %lf para montar a árvore", (double)(end - start) / (double)(CLOCKS_PER_SEC));
}

/* Funcao chama pesquisa na arvore binaria */
void search(FILE *file, int key){
    Node node;
    printf("\n--------------------------------------------------------");
    /* Funcao retorna posicao onde esta registro na arvore */
    int pos = searchInBinThree(file, key, 0, 0, false);
    if(pos != -1){  
        fseek(file, pos * sizeof(node), SEEK_SET);
        printf("\nChave se encontra na linha: %d", pos);
        fread(&node, sizeof(node), 1, file);
        printf("\nKey: [%d] - %ld | %s\nFilho a Direita: %d\nFilho a Esquerda: %d\n", node.reg.key, node.reg.data1, node.reg.data2, node.esq, node.dir);
    }
    else
        printf("\nChave nao encontrada\n");
}