#include<stdio.h>
#define MAX 20

typedef struct edge
{
    int u, v, w;
} edge;

typedef struct edgelist
{
    edge dados[MAX];
    int n;
} edgelist;

edgelist lista;
edgelist lista_auxiliar;

int busca(int b[],int v)
{
    return(b[v]);
}

void imprimir_grafo()
{
    int i, c = 0;
    printf("\nArvore geradora");
    for(i = 0; i < lista_auxiliar.n; i++)
    {
        printf("\n%d\t%d\t%d",lista_auxiliar.dados[i].u, lista_auxiliar.dados[i].v, lista_auxiliar.dados[i].w);
        c = c + lista_auxiliar.dados[i].w;
    }
    printf("\n\nCusto da arvore geradora = %d",c);
}

void ordenar(int n)
{
    int i, j;
    edge t;
    
    for(i = 1 ; i < lista.n; i++)
    {
        for(j = 0; j < lista.n-1; j++)
        {
            if(lista.dados[j].w > lista.dados[j+1].w)
            {
                t = lista.dados[j];
                lista.dados[j] = lista.dados[j+1];
                lista.dados[j+1] = t;
            }
        }
    }
}

void unir(int b[],int c1,int c2, int n)
{
    int i;
    
    for(i = 0; i < n; i++)
    {
        if(b[i] == c2)
        {
            b[i] = c1;
        }
    }
}

void kruskal(int graph[MAX][MAX], int n)
{
    int b[MAX], i, j, cnj1, cnj2;
    lista.n = 0;

    for(i = 1; i < n; i++){
        for(j = 0; j < i; j++)
        {
            if(graph[i][j] != 0)
            {
                lista.dados[lista.n].u = i;
                lista.dados[lista.n].v = j;
                lista.dados[lista.n].w = graph[i][j];
                lista.n++;
            }
        }
    }
    ordenar(n);
    for(i = 0; i < n; i++)
    {
        b[i] = i;
    }
    
    lista_auxiliar.n = 0;
    
    for(i = 0; i < lista.n; i++)
    {
        cnj1 = busca(b, lista.dados[i].u);
        cnj2 = busca(b, lista.dados[i].v);
        
        if(cnj1 != cnj2)
        {
            lista_auxiliar.dados[lista_auxiliar.n] = lista.dados[i];
            lista_auxiliar.n = lista_auxiliar.n+1;
            unir(b, cnj1, cnj2, n);
        }
    }
    imprimir_grafo();
}

void main()
{
    int i, j;
    int linha, coluna, peso, arestas, vertices;
    int grafo[MAX][MAX] = {{0}};
    char aux, nome[30];
    printf("Digite o nome do arquivo de entrada:\n");
    scanf("%s", nome);
    getchar();
    FILE *arquivo;
    arquivo = fopen(nome, "r");
    fscanf(arquivo, "%d", &vertices);
    fscanf(arquivo, "%d", &arestas);
    for(i=0;i<arestas;i++){
        fscanf(arquivo, "%d", &linha);
        fscanf(arquivo, "%d", &coluna);
        fscanf(arquivo, "%c", &aux);
        if (aux == ' ')
        {
            fscanf(arquivo, "%d", &peso);
        }else{
            peso = 1;
        }
        grafo[linha-1][coluna-1] = peso;
        grafo[coluna-1][linha-1] = peso;
    }
    kruskal(grafo, vertices);
}