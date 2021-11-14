/*
There are N countries {1,2,3,4....N} and N-1 roads
(i.e depicting a tree)
Bishu lives in the Country 1 so this can be considered 
as the root of the tree.
Now there are Q girls who lives in various countries (not equal to 1) .
All of them want to propose Bishu.But Bishu has some condition.
He will accept the proposal of the girl who lives at minimum distance from his country.
Now the distance between two countries is the number of roads between them.
If two or more girls are at the same minimum distance then he will accept the proposal of the girl who 
lives in a country with minimum id.
No two girls are at same country.
Input: First line consists of N,i.e number of countries Next N-1 lines follow the type u v 
which denotes there is a road between u and v. Next line consists of Q Next Q lines consists 
of x where the girls live.
Output: Print the id of the country of the girl who will be accepted.
Help Him!!!!!
contraints: 2<=N<=1000 1<=u,v<=N 1<=Q<=(N-1)
SAMPLE INPUT 
6
1 2
1 3
1 4
2 5
2 6
4
5
6
3
4
SAMPLE OUTPUT 
3
Time Limit:	1,0 sec(s) for each input file.
Memory Limit:	256 MB
Source Limit:	1024 KB
*/
#include<stdio.h>
#include<stdlib.h>

int arr[1000];

typedef struct node
{
    int visited;
    int distance;
    struct lista *lista_adj;
}node;

typedef struct lista
{
    int qtd;
    struct country *inicio;
}lista;

typedef struct country
{
    int value;
    struct country *prox;
}country;

void dfs(node *nodes,int x, int distance);
void push(node *n,int x);
lista *aloca_lista();
country *aloca_country();
int incluir_ordenado_lista(lista *l,int x);

int main()
{
    int girl_max = int_max;
    int min_distance = int_max;
    int N;
    cin>>N;

    int girls[];
    int u,v;

    for(int i=1;i<=N;i++)
    {
        push(&arr[u],v);
        push(&arr[v],u);
        dfs(1,0);
    }

    int Q;
    cin>>Q;

    int girl;
    node *nodes;
    nodes = (node*)calloc(1000, sizeof(node));

    for(int j=1;j<=Q;j++)
    {
        cin>>girl;

        if(nodes[girl].distance<=min_distance && girl<=girl_max)
        {
            min_distance = nodes[girl].distance;
            girl_max = girls;
        }
    }

    cout<<girl_max<<endl;      
}

void push(node *n,int x)
{
    if(n->lista_adj==NULL)
        n->lista_adj = aloca_lista();
    incluir_ordenado_lista(n->lista_adj,x);
}

lista *aloca_lista()
{
    lista *novo;
    novo = (lista*)calloc(1,sizeof(lista));
    return novo;
}

country *aloca_country()
{
    country *novo;
    novo = (country*)calloc(1,sizeof(country));
    return novo;
}

int incluir_ordenado_lista(lista *l,int x)
{
    if(l==NULL)
        return 0;
    
    country *novo,*aux=NULL,*ant=NULL;
    novo = aloca_country();
    novo->value = x;

    if(l->inicio==NULL)
    {
        l->inicio = novo;
    }
    else
    {
        int inserido = 0;
        aux = l->inicio;

        while(aux!=NULL && !inserido)
        {
            if(aux->value==novo->value)
            {
                return 0;
            }

            if(aux->value < novo->value)
            {
                ant = aux;
                aux = aux->prox;
            }
            else
            {
                if(ant==NULL)
                    l->inicio = novo;
                else
                    ant->prox = novo;
                
                novo->prox = aux;
                inserido = 1;
            }
        }

        if(!inserido)
        {
            ant->prox = novo;
            inserido = 1;
        }
    }
    l->qtd++;
    return 1;
}

void dfs(node *nodes,int x, int distance)
{
    country *aux;
    nodes[x].visited = 1;
    nodes[x].distance = distance;

    printf("\n %d",x);

    if(nodes[x].lista_adj==NULL)
        return;
    
    aux = nodes[x].lista_adj->inicio;

    while(aux!=NULL)
    {
        if(nodes[aux->valor].visitado==0)
        {
            dfs(nodes,aux->valor,distance+1);
        }

        aux = aux->prox;
    }
}