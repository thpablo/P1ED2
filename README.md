# Geracao dos arquivos binários
## Compilação
```make```
ou
```gcc main.c filegenerator.c -c```
```gcc main.o filegenerator.o -o exe```
## Execução
Você irá rodar o executável:
```./exe```
Após executar passe o tipo de ordenação que terá o arquivo binário:
+ 1: Ordenação crescente
+ 2: Ordenação decrescente
+ 3: Ordenação aleatória
e a quantidade de registros que terá:
**Arquivo ordenado crescente com 100 registros**
```
./exe
1
100
```
**Arquivo ordenado aleatorio com 2050 registros**
```
./exe
3
2050
```
