#include<stdio.h>
#include<stdlib.h>
#include "Grafo.h"

int main()
{
    /*Busca em profundidade
        - Partindo de um vértice inicial, ela explora o máximo possível cada um dos seus ramos antes de retroceder("backtracking")
        - Pode ser usado para:
            - Encontrar componentes conectados e fortemente conectados
            - Ordenação topológica de um grafo
            - Resolver quebra-cabeças
    */

   int eh_digrafo = 1;
   Grafo *gr = cria_grafo(5,5,0);
   insere_aresta(gr,0,1,eh_digrafo,0);
   insere_aresta(gr,1,3,eh_digrafo,0);
   insere_aresta(gr,1,2,eh_digrafo,0);
   insere_aresta(gr,2,4,eh_digrafo,0);
   insere_aresta(gr,3,0,eh_digrafo,0);
   insere_aresta(gr,3,4,eh_digrafo,0);
   insere_aresta(gr,4,1,eh_digrafo,0);
   
   //mesmo numero de vertices
   int vis[5];
   
   busca_profundidade_grafo(gr,0,vis);

   libera_grafo(gr);

   system("pause");
   return 0;
}

//Função auxiliar: realiza o calculo
void busca_profundidade(Grafo *gr, int ini, int *visitado, int cont)
{
    int i;

    //marca o vertice como visitado e visita os vizinhos ainda não visitados
    visitado[ini] = cont;
    for(i=0;i<gr->grau[ini];i++)
    {
        if(!=visitado[gr->arestas[ini][i]])
            busca_profundidade(gr,gr->arestas[ini][i],visitado,cont+1);
    }
}

//Função principal: faz a interface com o usuário
void busca_profundidade_grafo(Grafo *gr, int ini, int *visitado)
{
    int i, cont=1;

    //marca vertices como não visitado
    for(i-0;i<gr->qtd_vertices;i++)
        visitado[i] = 0;
    busca_profundidade(gr,ini,visitado,cont);
}