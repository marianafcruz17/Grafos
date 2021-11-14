#include <stdio.h>
#include <stdlib.h>

int qtd_global[10001];


typedef struct vertice
{
    int visitado;
    struct arvore *arvore_adj;
} vertice;

typedef struct arvore
{
    int qtd;
    struct no *raiz;
}arvore;

typedef struct no
{
    int valor;
    struct no *esq;
    struct no*dir;
}no;

int incluir_arvore(arvore *l, int x);
no *aloca_no();
arvore *aloca_arvore();
int carrega_arvore(vertice *vertices, char *nome_do_arquivo);
void push(vertice *v, int x);
void dfs(vertice * vertices , int x);
int iguais(arvore *n1, arvore *n2);
int subarvore(arvore *n1, arvore *n2);

int main(int *argc, char *argv[])
{
    int qtd_vertices, qtd_arestas,i,a,b,cont=0;

    vertice * vertices;

    scanf("%d %d",&qtd_vertices,&qtd_arestas);

    vertices = (vertice*)calloc(qtd_vertices+1,sizeof(vertice));

    i = 0;

    while(i<qtd_arestas)
    {
        scanf("%d %d",&a,&b);
        push(&vertices[a],b);
        push(&vertices[b],a);
        i++;
    }

    for(i=1;i<=qtd_vertices;i++)
    {
        if (vertices[i].visitado==0)
        {
            dfs(vertices,i);
            cont++;
        }
    }

    printf("\n Digite o primeiro vertice: ");
    scanf("%d",&a);
    printf("\n Digite o segundo vertice: ");
    scanf("%d",&b);
    int subarvore(arvore *a, arvore *b);

    printf("%d\n",cont);
    return 0;
}

int carrega_arvore(vertice *vertices, char *nome_do_arquivo)
{
    FILE *arq;
    arq = fopen(nome_do_arquivo, "r");
    int a, b;
    int qtd_vertices=0;

    int i;

    for(i=0;i<10001;i++)
    {
        qtd_global[i] =0;
    }

    if (arq == NULL)
    {
        printf("\n Arquivo nao localizado");
        return 0;
    }

    while (fscanf(arq, "%d;%d\n", &a, &b) != EOF)
    {
        printf("\n A: %d B: %d", a, b);

        if (qtd_global[a]==0)
            qtd_vertices++;
            qtd_global[a] = 1;

        if (qtd_global[b]==0)
            qtd_vertices++;
            qtd_global[b] = 1;

        push(&vertices[a], b);
        push(&vertices[b], a);
    }

    return qtd_vertices;
}

void push(vertice *v, int x)
{
    if (v->arvore_adj == NULL)
        v->arvore_adj = aloca_arvore();
    incluir_arvore(v->arvore_adj, x);
}

arvore *aloca_arvore()
{
    arvore *novo;
    novo = (arvore *)calloc(1, sizeof(arvore));
    return novo;
}

no *aloca_no()
{
    no *novo;
    novo = (no *)calloc(1, sizeof(no));
    return novo;
}

int incluir_arvore(arvore *l, int x)
{
    struct no *novo;
    novo = (no*)calloc(1,sizeof(no));

    if(l==NULL){
        if(novo==NULL)
            return 0;
        novo->valor = x;
        novo->dir = NULL;
        novo->esq = NULL;

        l = novo;
    }
    else
    {
        if(x==(*l)->valor)
            return 0;
        else if(x>(*l)->valor)
            return incluir_arvore(&(novo->dir),x);
        else
            return incluir_arvore(&(novo->esq),x);
    }

    return 1;
}

void dfs(vertice * vertices , int x)
{
    no * aux;
    vertices[x].visitado=1;

    if (vertices[x].arvore_adj==NULL)
        return;
        
    aux = vertices[x].arvore_adj->raiz;

    while(aux!=NULL)
    {
        if (vertices[aux->valor].visitado==0)
        {
            dfs(vertices,aux->valor); 
        }
        aux = aux->dir;
    }

}

int subarvore(arvore *n1, arvore *n2)
{
    if(n2==NULL){
        return 1;
    }

    if(n1==NULL){
        return 1;
    }

    return iguais(&n1, &n2) || subarvore(&(*n1)->esq, *n2) || subarvore(&(*n1)->dir, *n2);
}

int iguais(arvore *n1, arvore *n2)
{
    if (n1 == n2)
    {
        return 1;
    }
    if (n1 == NULL || n2 == NULL)
    {
        return 0;
    }

    if ((*n1)->valor!=(*n2)->valor)
    {
        return 0;
    }

    return iguais((*n1)->esq, (*n2)->esq) && iguais((*n1)->dir, (*n2)->dir);
}