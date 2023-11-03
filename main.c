#include "fileGenerator.h" // Inclui o cabeçalho do arquivo "fileGenerator.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Inclui a biblioteca "unistd.h" para uso da função access

int main()
{
    FILE *arq;
    int n, op;
    scanf("%d %d", &op, &n); // Lê a operação (op) e a quantidade de registros (n) a partir da entrada padrão

    Data *arryDatas = (Data *)malloc(n * sizeof(Data)); // Aloca espaço para armazenar os dados

    // Verifica a operação selecionada e a existência do arquivo binário correspondente
    if (op == 1)
    {
        if (access("crescente.bin", F_OK) == -1) // Verifica se o arquivo "crescente.bin" não existe
        {
            // Caso o arquivo não exista, gera os dados e o arquivo binário correspondente
            generatorBinFile(n, op);
        }
        arq = openFile("crescente.bin", "rb"); // Abre o arquivo "crescente.bin" para leitura
    }
    else if (op == 2)
    {
        if (access("decrescente.bin", F_OK) == -1) // Verifica se o arquivo "decrescente.bin" não existe
        {
            // Caso o arquivo não exista, gera os dados e o arquivo binário correspondente
            generatorBinFile(n, op);
        }
        arq = openFile("decrescente.bin", "rb"); // Abre o arquivo "decrescente.bin" para leitura
    }
    else if (op == 3)
    {
        if (access("aleatorio.bin", F_OK) == -1) // Verifica se o arquivo "aleatorio.bin" não existe
        {
            // Caso o arquivo não exista, gera os dados e o arquivo binário correspondente
            generatorBinFile(n, op);
        }
        arq = openFile("aleatorio.bin", "rb"); // Abre o arquivo "aleatorio.bin" para leitura
    }

    if (arq == NULL)
    {
        exit(1); // Sai do programa se houver erro na abertura do arquivo
    }

    // Ler os dados do arquivo
    printf("\n");

    // Determine o número de registros no arquivo
    fseek(arq, 0, SEEK_END);              // Move o indicador de posição para o final do arquivo
    long fileSize = ftell(arq);           // Obtém o tamanho do arquivo em bytes
    rewind(arq);                          // Retorna o indicador de posição para o início do arquivo
    int maxArq = fileSize / sizeof(Data); // Calcula o número máximo de registros no arquivo

    if (maxArq < n)
    {
        printf("Não existe essa quantidade de dados no arquivo");
        exit(1); // Sai do programa se não houver dados suficientes no arquivo
    }

    fread(arryDatas, sizeof(Data), n, arq); // Lê os dados do arquivo para o vetor de dados

    // Exibe os dados lidos
    for (int i = 0; i < n; i++)
    {
        printf("%d | %ld | %s \n", arryDatas[i].key, arryDatas[i].longNumber, arryDatas[i].randChars);
    }

    // Fechar o arquivo após a leitura
    fclose(arq);

    free(arryDatas); // Libera a memória alocada para o vetor de dados

    // Agora você pode usar os dados em 'datas'

    return 0;
}
