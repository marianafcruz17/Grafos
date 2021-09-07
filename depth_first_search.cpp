#include<iostream>
#include<list>

using namespace std;

class Grafo{
    int V;
    list<int> *adj;
    bool *visitado;
public:
    Grafo(int V);
    //grafo dirigido v->w
    void adicionar_aresta(int v,int w);
    void dfs(int v);
};

Grafo::Grafo(int V)
{
    this->V = V;
    adj = new list<int>[V];
    this->visitado = new bool[this->V];

    for(int i=0;i<this->V;i++)
        this->visitado[i] = false;
}

void Grafo::adicionar_aresta(int v,int w)
{
    //coloca w na posicao de v
    adj[v].push_back(w);
}

void Grafo::dfs(int v)
{
    //marca como visitado e imprime
    this->visitado[v] = true;
    cout << v << " ";

    list<int>::iterator it;

    for(it=adj[v].begin().it!=adj[v].end();it++)
    {
        if(!this->visitado[*it])
        {
            dfs(*it);
        }
    }
}

int main()
{
    int V = 4;
    Grafo grafo(V);
    grafo.adicionar_aresta(0,1);
    grafo.adicionar_aresta(0,2);
    grafo.adicionar_aresta(1,2);
    grafo.adicionar_aresta(2,0);
    grafo.adicionar_aresta(2,3);
    grafo.adicionar_aresta(3,3);

    int src = 2;
    cout << "O dfs do grafo e: " << endl << endl;
    grafo.dfs(src);

    return 0;
}