/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <bits/stdc++.h>
using namespace std;

class graph{
    public:
    int v;
    vector<vector<int>> adj;
    graph(int ver){
        v = ver;
        adj.resize(v);
    }
    
    void addedge(int u,int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
        
    }
    
    void bfs(int start){
        queue<int> q;
        q.push(start);
        vector<int> visited(v,0);
        visited[start] = 1;
        while(!q.empty()){
            int top = q.front();
            q.pop();
            cout<<top<<endl;
            for(auto it : adj[top]){
                if(!visited[it]){
                    q.push(it);
                    visited[it] = 1;
                }
            }
            
        }
    }
    void bfspara(int start){
        queue<int> q;
        q.push(start);
        vector<int> visited(v,0);
        visited[start] = 1;
        while(!q.empty()){
            int siz = q.size();
            vector<int> frontier;
            for(int i = 0;i<siz;i++){
                int top = q.front();
                q.pop();
                cout<<top<<endl;
                 #pragma omp parallel for
                    for(auto it : adj[top]){
                        #pragma omp critical{
                        if(!visited[it]){
                            frontier.push_back(it);
                            visited[it] = 1;
                        }
                    }
                    }
            for (int il = 0; il < frontier.size(); ++il)
                q.push(frontier[il]);
            }
        }
        
        void dfs(int start,vector<int> &visited){
            visited[start] = 1;
            cout<<start<<endl;
            for(auto it : adj[start]){
                if(!visited[it]){
                    dfs(it,visited);
                }
            }
        }
        
        void dfsseq(int start){
            vector<int> visited(v,0);
            dfs(start,visited);
            
        }
        
        void parallelDFS(int start) {
    vector<int> visited(v, 0);
    #pragma omp parallel
    {
        #pragma omp single
        dfs(start, visited); // Start the recursive DFS in parallel region
    }
    cout << endl;
}   
    };
int main()
{
    graph g(5);
    g.addedge(0,1);
    g.addedge(0,2);
    g.addedge(0,3);
    g.addedge(0,4);
    g.addedge(4,3);
    
    g.parallelDFS(0);
    

    return 0;
}