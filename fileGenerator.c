#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fileGenerator.h"
#include <stdbool.h>

void shuffle(Data arr[], int n)
{
    // Inicialize o gerador de números aleatórios com a hora atual
    srand(time(NULL));

    // Comece do último elemento e vá até o primeiro
    for (int i = n - 1; i > 0; i--)
    {
        // Gere um índice aleatório entre 0 e i (inclusive)
        int j = rand() % (i + 1);

        // Troque arr[i] com arr[j]
        Data temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

void randomString(char *s, const int len, int timex)
{
    srand(timex);

    static const char alphanum[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len - 1; i++)
    {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    s[len - 1] = '\0';
}

FILE *openFile(const char *nomeArquivo, const char *modo)
{
    FILE *arq = fopen(nomeArquivo, modo);
    if (!arq)
    {
        perror("Erro na abertura do arquivo");
        exit(1);
    }
    return arq;
}

void generatorBinFile(int n, int op)
{
    FILE *arq;
    Data *arryDatas = (Data *)malloc(n * sizeof(Data));
    int timex = time(NULL);

    if (op == 1)
    {
        arq = openFile("crescente.bin", "wb+");

        if (arq == NULL)
            exit(1);

        for (int i = 0; i < n; i++)
        {
            arryDatas[i].key = i + 1;
            arryDatas[i].longNumber = rand() % LONG_MAX;
            randomString(arryDatas[i].randChars, LEN, timex);
            timex++;
        }

        fwrite(arryDatas, sizeof(Data), n, arq);
    }
    else if (op == 2)
    {
        arq = openFile("decrescente.bin", "wb+");

        if (arq == NULL)
            exit(1);

        printf("ss");

        for (int i = n - 1; i >= 0; i--)
        {
            arryDatas[(n - 1) - i].key = i + 1;
            arryDatas[(n - 1) - i].longNumber = rand() % LONG_MAX;
            randomString(arryDatas[i].randChars, LEN, timex);
            timex++;
        }

        fwrite(arryDatas, sizeof(Data), n, arq);
    }
    else if (op == 3)
    {

        arq = openFile("aleatorio.bin", "wb+");

        if (arq == NULL)
            exit(1);

        for (int i = 0; i < n; i++)
        {
            arryDatas[i].key = i + 1;
            arryDatas[i].longNumber = rand() % LONG_MAX;
            randomString(arryDatas[i].randChars, LEN, timex);
            timex++;
        }
        shuffle(arryDatas, n);
        fwrite(arryDatas, sizeof(Data), n, arq);
    }

    fclose(arq);
    free(arryDatas);
}
