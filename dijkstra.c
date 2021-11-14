#include <limits.h>
#include <stdio.h>
#include <stdbool.h>
 

int vertices;

int distanciamin(int dist[], bool sptSet[])
{
    int min = INT_MAX, indexmin;
 
    for (int v = 0; v < vertices; v++)
    {
        if (sptSet[v] == false && dist[v] <= min)
        {
            min = dist[v], indexmin = v;
        }
    }
    return indexmin;
}
 
void printar(int dist[])
{
    printf("Vertice \t\t Distancia do vertice origem\n");
    for (int i = 0; i < vertices; i++)
    {
        printf("%d \t\t %d\n", i+1, dist[i]);
    }
}
 
void dijkstra(int grafo[vertices][vertices], int src)
{
    int dist[vertices]; 
 
    bool sptSet[vertices];

    for (int i = 0; i < vertices; i++)
    {
            dist[i] = INT_MAX, sptSet[i] = false;
    }
 
    dist[src] = 0;
 
    for (int aux = 0; aux < vertices - 1; aux++) 
    {

        int u = distanciamin(dist, sptSet);
 
        sptSet[u] = true;
 
        for (int v = 0; v < vertices; v++)
        {
            if (!sptSet[v] && grafo[u][v] && dist[u] != INT_MAX && dist[u] + grafo[u][v] < dist[v])
            {
                dist[v] = dist[u] + grafo[u][v];
            }
        }
    }
 
    printar(dist);
}
 
int main()
{
    int linha, coluna, peso, arestas, i,j,ori;
    char nome[30];
    char aux;
    printf("Digite o nome do arquivo de entrada:\n");
    scanf("%s", nome);
    getchar();
    FILE *arquivo;
    arquivo = fopen(nome, "r");
    fscanf(arquivo, "%d", &vertices);
    int grafo[vertices][vertices];
    for(i =0; i<vertices; i++)
    {
      for(j=0; j<vertices ; j++)
        {
          grafo[i][j] = 0;
        }
    }
    fscanf(arquivo, "%d", &arestas);
    for(i=0;i<arestas;i++)
    {
        fscanf(arquivo, "%d", &linha);
        fscanf(arquivo, "%d", &coluna);
        fscanf(arquivo, "%c", &aux);
        if (aux == ' ')
        {
            fscanf(arquivo, "%d", &peso);
        }
        else
        {
            peso = 1;
        }
        grafo[linha-1][coluna-1] = peso;
        grafo[coluna-1][linha-1] = peso;
    }
    printf("Digite o vertice que sera a origem:\n");
    scanf("%d", &ori);
    dijkstra(grafo, ori-1);
    
    return 0;
}