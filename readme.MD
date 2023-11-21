# Pesquisa em árvore binária
## Sobre
Trabalho realizado para a materia de Estrutura de Dados 2, para Universidade Federal de Ouro Preto. O algoritmo utiliza arquivos binários com uma estrutura padrão (Localizada no arquivo `reg.h`) para construção e pesquisa de uma árvore binária em memória secundária.

## Compilação

```make```

## Execução

Necessita de três argumentos para execução do arquivo:

```./exe MetodoPesquisa QuantidadeLer TipoDeArquivo Chave```

em que:
- MetodoPesquisa: Metodo que sera pesquisado a chave, neste caso insira qualquer valor, pois ira sempre pesquisar com Arvore binaria.
- QuantidadeLer: Quantidade de dados que lerá do arquivo de origem (certifique que a quantidade é menor que do tamanho de arquivo de origem).
- TipoDeArquivo: Tipo de Ordenacao desejada:
    1. Arquivo ordenado Crescente
    2. Arquivo ordenado Decrescente
    3. Arquivo ordenado Aleatorio 
- Chave: Chave que será pesquisada.
- QuerConstruirArvore: [!!Não funcionando!!] Decide se é necessario criar outro arquivo com a estrutura da árvore binária (Sendo 1 verdadeiro e 0 falso).