#include<stdio.h>
#include<stdlib.h>
#define M 20

int parente[M],posicao[M];

typedef struct vertice{
    int pai;
    int filho;
    int distancia;
    struct lista *lista_adj;
}vertice;

typedef struct lista{
    int qtd;
    struct registro *inicio;
}lista;

typedef struct registro{
    int valor;
    struct registro *prox;
}registro;

void mostrar_MST(vertice *v,int x){
    int i;
    int count=0;

    printf("\n Informe o valor dos vertices: ");

    for(i=0;i<x;i++){
        printf("%d %d %d\n",v[i].pai,v[i].filho,v[i].distancia);
        count += v[i].distancia;
    }

    printf("\n Peso = %d",count);
}

void troca(vertice *x,vertice *y){
	vertice aux;
	aux = *x;
	*x = *y;
	*y = aux;
}

int partition(vertice *vertices,int inicio,int fim){
    int i, aux=inicio, prox=vertices[fim].distancia;

    for(i=inicio;i<fim;i++){
        if(vertices[i].distancia<=prox){
            troca(&vertices[i],&vertices[aux]);
            aux++;
        }
    }

    troca(&vertices[fim],&vertices[aux]);
    return aux;
}

void quick_sort(vertice *vertices,int inicio,int fim){
    int x;

    if(inicio>=fim){
        return;
    }

    x = partition(vertices,inicio,fim);
    quick_sort(vertices,inicio,x-1);
    quick_sort(vertices,x+1,fim);
}

int encontrar(int x){
    int i=0,vertices[M];

    while(x!=parente[x]){
        vertices[i] = x;
        x = parente[x];
        i++;
    }

    i--;

    while(i>=0){
        parente[vertices[i]] = x;
        i--;
    }

    return x;
}

int unir(int pai,int filho){
    int x,y;

    x = encontrar(pai);
    y = encontrar(filho);

    if(posicao[x]<posicao[y]){
        parente[x] = y;
    }else if(posicao[y]<posicao[x]){
        parente[y] = x;
    }else{
        parente[x] = y;
        posicao[y]++;
    }
}

void kruskal(vertice *vertices,int n, int e){
    int i,j,x,y,u,v;
    vertice *aux;

    aux = (vertice*)malloc((n-1)*sizeof(vertice));
    quick_sort(vertices,0,e-1);

    j = 0;

    for(i=0;i<e;i++){
        if(j==n-1){
            break;
        }

        u = vertices[i].pai;
        v = vertices[i].filho;

        x = encontrar(u);
        y = encontrar(v);

        if(x!=y){
            aux[j] = vertices[i];
            unir(x,y);
            j++;
        }
    }

    mostrar_MST(aux,n-1);
}

int main(){
    int i,j,k,n,e,w;
    vertice *vertices;

    printf("\nInforme a quantidade de vertices: ");
    scanf("%d",&n);
    printf("\nInforme a quantidade de arestas: ");
    scanf("%d",&e);

    vertices = (vertice*)malloc(e*sizeof(vertice));

    for(i=1;i<n+1;i++){
        parente[i] = i;
        posicao[i] = 0;
    }

    for(k=0;k<e;k++){
        printf("\nInforme os vertices e o peso: ");
        scanf("%d %d %d",&i,&j,&w);

        vertices[k].pai = i;
        vertices[k].filho = j;
        vertices[k].distancia = w;
    }

    kruskal(vertices,n,e);
}