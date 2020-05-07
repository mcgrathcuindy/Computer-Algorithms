/*
Name: Christopher McGrath
Date: 4/26/20
Desc: Ford-Fulkerson c++ implementation for max-flow and min-cut
*/
#include <bits/stdc++.h>
using namespace std;
#define INF 0xffff
bool bfs(int *graph, int src, int sink, int *parent,int nVertex)
{
    bool visited[nVertex];
    for(int i = 0; i < nVertex; i++)
        visited[i] = false;
    queue <int> q;
    q.push(src);
    visited[src] = true;
    parent[src] = -1;
    
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        for(int v = 0; v < nVertex; v++)
        {
            if(visited[v] == false && *((graph+u*nVertex) + v) > 0)
            {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    if(visited[sink] == true)
        return true;
    return false;
}

void dfs(int *graph, int src, bool visited[],int nVertex)
{
    visited[src] = true;
    for(int i = 0; i < nVertex; i++)
        if(*((graph+src*nVertex) + i) == true && visited[i] == false)
            dfs(graph, i, visited,nVertex);
}

void fordFulkerson(int *graph, int src, int sink,int nVertex)
{
    int i, j;
    int copyGraph[nVertex][nVertex];
    for(i = 0; i < nVertex; i++)
        for(j = 0; j < nVertex; j++)
            copyGraph[i][j] = *((graph+i*nVertex) + j);
    
    int parent[nVertex];
    int maxFlow = 0;
    while(bfs((int*)copyGraph, src, sink, parent,nVertex))
    {
        int path = INF;
        for(j = sink; j!=src; j=parent[j])
        {
            i = parent[j];
            if(copyGraph[i][j] < path)
                path = copyGraph[i][j];
        }
        for(j = sink; j != src; j=parent[j])
        {
            i = parent[j];
            copyGraph[i][j] = copyGraph[i][j] - path;
            copyGraph[j][i] = copyGraph[i][j] + path;
        }
        maxFlow = maxFlow + path;
    }
    cout << "\nMax flow: " <<  maxFlow << endl;
    
    bool visited[nVertex];
    for(i = 0; i < nVertex; i++)
        visited[i] = false;
    dfs((int *)copyGraph, src, visited,nVertex);
    cout << "Min cut edges:" << endl;
    for(i = 0; i < nVertex; i++)
    {
        for(j = 0; j < nVertex; j++)
        {
            if(visited[i] == true && visited[j] == false && *((graph+i*nVertex) + j) != 0)
                cout << i << " - " << j << endl;
        }
    }
    return;
}

int main(void)
{
    int nVertex, nEdge, i,j, u, v, c;
    ifstream file; 
 
    file.open("input.txt",ios::in); 
 
    if(!file) 
    { 
        cout<<"Error in creating file!!!"; 
        return 0; 
    }
    
    cout<<"Populating graph from \"input.txt\"..."<<endl;
    file>>nVertex;
    file>>nEdge;
    
    int graph[nVertex][nVertex];
    for(i = 0; i < nVertex;i++)
        for(j = 0; j < nVertex;j++)
            graph[i][j] = 0;
    for(i = 0; i < nEdge; i++)
    {
        file>>u;
        file>>v;
        file>>c;
        graph[u][v] = c;
        //g.addEdge(u, v, w);
    }

    for(i = 0; i < nVertex-1; i++)
    {    
        if(i == 0 )
        {    
            cout << "Printing graph..." << endl;
            cout << "   [";
        }
        cout << i << "][";
        if(i == nVertex - 2)
            cout << nVertex-1 << "]" << endl;
    }

    for (i = 0; i < nVertex; i++)
    {
        cout << "[" << i << "] ";
        for(j = 0; j < nVertex; j++)
        {
            cout << graph[i][j] << "  ";
        }
        cout << endl;
    }
    
    fordFulkerson((int *)graph, 0, nVertex-1, nVertex);
}