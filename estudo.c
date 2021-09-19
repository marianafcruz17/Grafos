//Definindo o TAD "Grafo" usando "Lista de Adjacência"

//Arquivo Grafo.h
typedef struct grafo Grafo;

//Arquivo Grafo.c
#include<stdio.h>
#include<stdlib.h>
#include "Grafo.h" //inclui os protótipos

//Definição do tipo grafo
struct grafo{
    int ponderado;
    int num_vertices;
    int grau_max;
    //** = matrix
    int** arestas;
    float** pesos;
    //grau = define quantas arestas o grafo já possui
    int* grau;
};

//Programa princial
Grafo *gr;

int main(){
    printf("Criando um grafo\n");

    //Arquivo Grafo.h
    Grafo *cria_grafo(int num_vertices,int grau_max,int ponderado);

    int insere_aresta(Grafo *gr,int orig,int dest,int digrafo,float peso);
    int remove_aresta(Grafo *gr,int orig,int dest,int digrafo);
    void dfs(Grafo *gr,int ini,int *visitado);
    void menor_caminho(Grafo *gr,int ini,int *ant,float *dist);
    int digrafo=1;
    int vis[5];
    int ant[5];
    float dist[5];

    //Programa principal
    Gr *gr = cria_grafo(5,5,0);
    insere_aresta(gr,0,1,digrafo,0);
    insere_aresta(gr,1,2,digrafo,0);
    insere_aresta(gr,1,4,digrafo,0);
    insere_aresta(gr,2,3,digrafo,0);
    insere_aresta(gr,3,4,digrafo,0);
    insere_aresta(gr,3,6,digrafo,0);
    insere_aresta(gr,4,5,digrafo,0);
    insere_aresta(gr,4,1,digrafo,0);
    insere_aresta(gr,5,6,digrafo,0);
    insere_aresta(gr,6,3,digrafo,0);
    remove_aresta(gr,4,1,digrafo);
    remove_aresta(gr,6,3,digrafo);

    dfs(gr,0,vis);
    menor_caminho(gr,0,ant,dist);
    libera_grafo(gr);

    system("pause");
    return 0;
}

Grafo* cria_grafo(int num_vertices,int grau_max,int ponderado){
    //aloca o grafo
    Grafo *gr = (Grafo*)malloc(sizeof(struct grafo));

    if(gr!=NULL){
        int i;
        gr->num_vertices = num_vertices;
        gr->grau_max = grau_max;
        gr->ponderado = (ponderado!=0)?1:0;

        gr->grau = (int*)calloc(num_vertices,sizeof(int*));

        //matriz arestas
        gr->arestas = (int*)malloc(num_vertices * sizeof(int*));

        for(i=0;i<num_vertices;i++)
            //para cada aresta, cria o grau max dela
            gr->aresta[i] = (int*)malloc(grau_max * sizeof(int));

            //matriz peso
            if(gr->ponderado){
                gr->pesos = (float**)malloc(num_vertices * sizeof(float*));

                for(i=0;i<num_vertices;i++)
                    gr->pesos[i] = (float*)malloc(grau_max * sizeof(float));
            }
    }

    return gr;
}

void libera_grafo(Grafo *gr){
    ig(gr!=NULL){
        int i;

        //libera matriz aresta
        for(i=0;i<gr->num_vertices;i++)
            free(gr->arestas[i]);
        free(gr->arestas);

        //libera matriz peso
        if(gr->ponderado){
            for(i=0;i<gr->num_vertices;i++)
                free(gr->pesos[i]);
            free(gr->pesos);
        }

        //libera vetor de grau
        free(gr->grau);
        //libera grafo
        free(gr);
    }
}

int insere_aresta(Grafo *gr,int orig,int dest,int digrafo,float peso){
    if(gr==NULL)
        return 0;

    //verifica a existencia de vertices
    if(orig<0 || orig>=gr->num_vertices)
        return 0;
    if(dest<0 || dest>=gr->num_vertices)
        return 0;

    //insere no final da fila
    gr->arestas[orig][gr->grau[orig]] = dest;

    if(gr->ponderado)
        gr->pesos[orig][gr->grau[orig]] = peso;
    gr->grau[orig]++;

    //insere outra aresta se não for digrafo
    if(digrafo==0)
        insere_aresta(gr,dest,orig,1,peso);
    return 1;
}

int remove_aresta(Grafo *gr,int orig,int dest,int digrafo){
    if(gr==NULL)
        return 0;

    if(orig<0 || orig>=gr->num_vertices)
        return 0;
    if(dest<0 || dest>=gr->num_vertices)
        return 0;
    
    //procura aresta
    int i=0;

    while(i<gr->grau[orig] && gr->arestas[orig][i]!=dest)
        i++;
    
    //elemento nao encontrado
    if(i==gr->grau[orig])
        return 0;

    //copia o ultimo para a posição do removido
    gr->grua[orig]--;
    gr->arestas[orig][i] = gr->arestas[orig][gr->grau[orig]];

    if(gr->ponderado)
        gr->pesos[orig][i] = gr->pesos[orig][gr->grau[orig]];

    //remove outra aresta se não for digrafo
    if(digrafo==0)
        remove_aresta(gr,dest,orig,1);
    return 1;
}

//função auxiliar: realiza o calculo
void busca_profundidade(Grafo *gr,int ini,int *visitado,int cont){
    int i;

    //marca o vertice vistido e visita os vizinhos que não foram visitados
    visitado[ini] = cont;

    for(i=0;i<gr->grau[ini];i++){
        if(!visitado[gr->arestas[ini][i]])
            busca_profundidade(gr,gr->arestas[ini][i],visitado,cont+1);
    }
}

//função principal: faz a interface com o usuário
void dfs(Grafo *gr,int ini,int *visitado){
    int i,cont=1;

    //marca o vertice como nao visitado
    for(i=0;i<gr->num_vertices;i++)
        visitado[i] = 0;
    busca_profundidade(gr,ini,visitado,cont);
}

int procura_menor_distancia(float *dist,int *visitado,int num_vertice){
    int i,menor=-1,primeiro=1;

    for(i=0;i<num_vertice;i++){
        //procura o vertice com menor distancia e que ainda nao foi visitado
        if(dist[i]>=0 && visitado[i]==0){
            if(primeiro){
                menor = 1;
                primeiro = 0;
            }else{
                if(dist[menor]>dist[i]){
                    menor = i;
                }
            }
        }
    }
    return menor;
}

void menor_caminho(Grafo *gr,int ini,int *ant,flaot *dist){
    int i,cont,num_vertice,ind,*visitado,u;
    cont = num_vertice = gr->num_vertices;

    //cria o vetor auxiliar, iniciando distancias anteriores
    visitado = (int*)malloc(num_vertice * sizeof(int));

    for(i=0;i<num_vertice;i++){
        ant[i] = -1;
        dist[i] = -1;
        visitado[i] = 0;
    }

    dist[ini] = 0;

    while(cont>0){
        //procura o vertice com menor distancia e marca como visitado
        u = procura_menor_distancia(dist,visitado,num_vertice);

        if(u==-1)
            break;
        visitado[u] = 1;
        cont--;
    }
    free(visitado);

    for(i=0;i<gr->grau[u];i++){
        ind = gr->arestas[u][i];

        //atualiza distancias dos vizinhos
        if(dist[ind]<0){
            dist[ind] = dist[u] + 1;
            ant[ind] = u;
        }else{
            if(dist[ind]>dist[u]+){
                dist[ind] = dist[u] + ;
                ant{ind} = u;
            }
        }
    }
}