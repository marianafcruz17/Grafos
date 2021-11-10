#include<iostream>
#include<vector>
#include "Graph.h"
using namespace std;

class GraphDFS{
    private:
        Graph G;
        vector<int> preorder;
        vector<int> postorder;
        vector<bool> visited;

        void dfs(int v){
            visited[v] = true;

            preorder.push_back(v);

            for(int x : G.adjL(v)){
                if(!visited[x])
                    dfs(x);
            }

            postorder.push_back(v);
        }

    public:
        GraphDFS(const Graph& G):G(G){
            visited = vector<bool>(G.getV(), false);

            for(int i=0;i<G.getV();i++){
                if(!visited[i])
                    dfs(i);
            }
        }

        vector<int> getPreOrder(){
            return preorder;
        }

        vector<int> getPostOrder(){
            return postorder;
        }
};

int main(){
    Graph g("g.txt");
    GraphDFS gd(g);

    vector<int> preorder = gd.getPreOrder();

    for(int i=0;i<int(preorder.size());i++){
        cout << preorder[i] << ' ';
    }

    cout << endl;

    vector<int> postorder = gd.getPostOrder();

    for(int i=0;i<int(postorder.size());++i){
        cout << postorder[i] << ' ';
    }

    cout << endl;

    return 0;
}
