#include<iostream>
#include<list>
]
using namespace std;

class Grafo
{
    int V;
    list<int> *adh;

    void dfs_rec(int v,bool visitado[]);
public:
    Grafo(int V);
    void adicionar_aresta(int v,int w);
    void dfs(int v);
};

Grafo::Graafo(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

void Grafo::adicionar_Aresta(int v,int w)
{
    adj[v].push_back(w);
}

void Grafo::dfs_rec(int v,bool visiteado[])
{
    visitado[v] = true;
    cout << v << " ";

    list<int>::interator i;

    for(i=adj[v].begin();i!=adj[v].end();i++)
        if(!visitado[*i])
            dfs_rec(*i,visitado);
}
void Grafo::dfs(int v)
{
    bool *visitado = new bool[V];

    for(int i=0;i<V;i++)
        visitado[i] = false;
    
    dfs_rec(v,visitado);
}

int main()
{
    Grafo grafo(4);
    grafo.adicionar_aresta(0,1);
    grafo.adicionar_aresta(0,2);
    grafo.adicionar_aresta(1,2);
    grafo.adicionar_aresta(2,0);
    grafo.adicionar_aresta(2,3);
    grafo.adicionar_aresta(3,3);

    dout << "\n O caminho do DFS, a partir do vertice 2, e: ";
    grafo.dfs(2);
    cout << endl;

    return 0;
}