#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define V 9999
int lig[V];

//Encontra o conjunto do vertice i
int verifica(int i)
{
    while (lig[i] != i)
        i = lig[i];
    return i;
}

// Uni i e j, Return false se ja estiverem no mesmo conjunto
void uni(int i, int j)
{
    int a = verifica(i);
    int b = verifica(j);
    lig[a] = b;
}

int main()
{
    //Leitra do arquivo
    FILE *arquivo;
    arquivo = fopen("matrizes_adj/dados1.txt", "r");
    char c;
    int cidades=0;

    //Descobrindo quantas cidades sao
    while(!feof(arquivo)){
        c=fgetc(arquivo);
        if(c=='\n'){
            cidades++;
        }
    }
    cidades++;

    //Passando dados do arquivo para matriz de adjacencia
    int mat[cidades][cidades];
    rewind(arquivo);
    for(int i=0;i<cidades;i++){
        for(int j=0;j<cidades;j++){
            fscanf(arquivo,"%d ", &mat[i][j]);
        }
    }

    //Colocando o maior valor onde nao ha ligacao
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
        lig[i] = i;

    //Inclusao de arestas de peso minimo
    int contcaminho = 0;
    while (contcaminho < cidades - 1) {
        int min = INT_MAX, a = -1, b = -1;
        for (int i = 0; i < cidades; i++) {
            for (int j = 0; j < cidades; j++) {
                if (verifica(i) != verifica(j) && mat[i][j] < min) {
                    min = mat[i][j];
                    a = i;
                    b = j;
                }
            }
        }

        uni(a, b);
        printf("Caminho %d => (V%d, V%d) Custo:%d \n", contcaminho++ +1, a+1, b+1, min);
        customin *= min;
    }
    printf("\n Custo Minimo= %d \n", customin);

    return 0;
}
