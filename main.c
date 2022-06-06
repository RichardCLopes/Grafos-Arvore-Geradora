//Richard do Carmo Lopes,  RA: 1004683

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define V 9999
int pai[V];

//Encontra o conjunto do vertice i
int find(int i)
{
    while (pai[i] != i)
        i = pai[i];
    return i;
}

// Uni i e j, Return false se já estiverem no mesmo conjunto
void union1(int i, int j)
{
    int a = find(i);
    int b = find(j);
    pai[a] = b;
}

int main()
{
    //Leitra do arquivo
    FILE *arquivo;
    arquivo = fopen("dados5.txt", "r");
    char c;
    int cidades=0;

    //descobrindo quantas cidades sao
    while(!feof(arquivo)){
        c=fgetc(arquivo);
        if(c=='\n'){
            cidades++;
        }
    }
    cidades++;

    //Criando matriz de adjacencia
    int mat[cidades][cidades];
    rewind(arquivo);
    for(int i=0;i<cidades;i++){
        for(int j=0;j<cidades;j++){
            fscanf(arquivo,"%d ", &mat[i][j]);
        }
    }

    //Colocando o maior valor onde não há ligação
    for(int i=0;i<cidades;i++){
        for(int j=0;j<cidades;j++){
                if(mat[i][j]==0){
                    mat[i][j]=INT_MAX;
                }
        }
    }
    //fecha arquivo
    fclose(arquivo);


    int customin = 1;

    //Inicializa
    for (int i = 0; i < cidades; i++)
        pai[i] = i;

    //Inclusão de arestas de peso minimo
    int contcaminho = 0;
    while (contcaminho < cidades - 1) {
        int min = INT_MAX, a = -1, b = -1;
        for (int i = 0; i < cidades; i++) {
            for (int j = 0; j < cidades; j++) {
                if (find(i) != find(j) && mat[i][j] < min) {
                    min = mat[i][j];
                    a = i;
                    b = j;
                }
            }
        }

        union1(a, b);
        printf("Caminho %d => (V%d, V%d) Custo:%d \n", contcaminho++ +1, a+1, b+1, min);
        customin *= min;
    }
    printf("\n Custo Minimo= %d \n", customin);

    return 0;
}
