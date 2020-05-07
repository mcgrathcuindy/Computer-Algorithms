/*
Name: Christopher McGrath
Date: 4/19/2020
Desc: HW8 & LAB2 Prim's Algorithm & Kruskal's algorithm implementation using STL
*/
#include <bits/stdc++.h> 
using namespace std;
# define INF 0xffff

typedef pair<int, int> iPair; 
class Graph
{
    int numVertices, numEdges;
    list <pair <int, int> > *adjLists;
    vector< pair<int, iPair> > edges;
    bool directed;

public:
    Graph(int vertices);
    ~Graph();
    void addEdge(int src, int dest, int weight); 
    void removeEdge(int src, int dest);
    void getPrimMST(int src);
    int getKruskalMST();
    void printGraph();
};

Graph::Graph(int vertices)
{
    numVertices = vertices;
    numEdges = 0;
    directed = true;
    adjLists = new list <iPair> [vertices];
}

void Graph::addEdge(int src, int dest, int weight)
{
    if(src<0 || src>=numVertices || dest<0 || dest>=numVertices) 
        return;
    //Weight (or distance) is used used as first item  of pair
    //as first item is by default used to compare two pairs
    adjLists[src].push_back(make_pair(weight, dest));
    numEdges++;
    if(!directed)
    {
        adjLists[dest].push_back(make_pair(weight, src));
    }
    //adding an edge to the vector adjList for Kruskal Algorithm
    edges.push_back({weight, {src, dest}});
}

void Graph::removeEdge(int src, int dest)
{
    edges.pop_back();
    list <iPair>::iterator it;
    for (it = adjLists[src].begin(); it != adjLists[src].end(); ++it)
    {
         if((*it).second == dest)
         {
            adjLists[src].erase(it); 
            cout << "Removed"<< endl;
            break;
         }
    }
    
    if(!directed)
    {
        for (it = adjLists[dest].begin(); it != adjLists[dest].end(); ++it)
        {
            if((*it).second == src)
            {
                adjLists[dest].erase(it); 
                cout << "Removed"<< endl;
                return;
            }
        }
    }
    cout << "Element not found\n";
    return;
}
    
void Graph::printGraph()
{
    list <iPair>::iterator j;
    printf("\nNumber of vertices: %d, Number of edges: %d\n", numVertices, numEdges);
    for(int i=0;i<numVertices;i++)
    {
        cout<<i<<": ";
        for(j = adjLists[i].begin(); j != adjLists[i].end(); ++j)
        {
            cout<<"-->"<< (*j).second<<"("<< (*j).first<<")";
        }
        cout<<endl;
    }
}

void Graph::getPrimMST(int src)
{
    priority_queue< iPair, vector <iPair> , greater<iPair> > pq;
    vector<int> key(numVertices, INF);
    
    vector<int> predecessor(numVertices, -1);
    vector<bool> inMST(numVertices, false);
    pq.push(make_pair(0,src));
    key[src] = 0;
    while(!pq.empty())
    {
        int u = pq.top().first;
        pq.pop();
        inMST[u] = true;
        list< pair<int, int> >::iterator it;
        for(it = adjLists[u].begin(); it != adjLists[u].end(); ++it)
        {
            int v = (*it).second;
            int weight = (*it).first;
            if(inMST[v] == false && key[v] > weight)
            {
                key[v] = weight;
                pq.push(make_pair(v,key[v]));
                predecessor[v] = u;
            }
        }
    }
    for(int i = 1; i < numVertices; i++)
        cout << predecessor[i] << " - " << i << endl;
}

struct DisjointSets 
{ 
    int numVertices; 
    int *predecessor, *rank; 
    
    // Initialize the disjoint set
    DisjointSets(int numVertices) 
    {
        this->numVertices = numVertices; 
        predecessor = new int[numVertices+1];
        rank = new int[numVertices+1]; 
        //initialize all elements to have rank 0 and to be the predecessor if itself
        for (int i = 0; i <= numVertices; i++) 
        { 
            rank[i] = 0; 
            predecessor[i] = i; 
        } 
    }
    
    //Recursive function to find the predecessor of a given node
    int findPredecessor(int u) 
    {
        if (u != predecessor[u]) 
            predecessor[u] = findPredecessor(predecessor[u]); 
        return predecessor[u]; 
    }
  
    void Union(int x, int y) 
    { 
        x = findPredecessor(x), y = findPredecessor(y); 
        if (rank[x] > rank[y]) 
            predecessor[y] = x; 
        else predecessor[x] = y; 
        if (rank[x] == rank[y]) 
            rank[y]++; 
    }
};

int Graph::getKruskalMST()
{   
    int weightOfMST = 0;
    sort(edges.begin(), edges.end());
    DisjointSets disjointSet(numVertices);
    vector< pair<int, iPair> >::iterator it;
    for(it = edges.begin(); it != edges.end(); it++)
    {
        if(disjointSet.findPredecessor(it->second.first) != disjointSet.findPredecessor(it->second.second))
        {
            cout << it->second.first << " - " << it->second.second << endl;
            weightOfMST += it->first;
            disjointSet.Union(disjointSet.findPredecessor(it->second.first), disjointSet.findPredecessor(it->second.second));
        }
    }
    return weightOfMST;
}

Graph::~Graph()
{
    //write your destructor here
    delete[] adjLists;
}

int main()
{
    int nVertex, nEdge, choice, i, u, v, w;
    ifstream file; 
 
    file.open("input.txt",ios::in); 
 
    if(!file) 
    { 
        cout<<"Error in creating file!!!"; 
        return 0; 
    } 
    cout<<"File opened successfully: "; 
    
    cout<<"Enter number of vertices: "<<endl;
    file>>nVertex;
    Graph g(nVertex);
    file>>nEdge;
    
    for(i = 0; i < nEdge; i++)
    {
        file>>u;
        file>>v;
        file>>w;
        g.addEdge(u, v, w);
    }
    
    g.printGraph();
    
    while (1)
    {
        cout<<"\n----------------------"<<endl;
        cout<<"Operations on Graph"<<endl;
        cout<<"\n----------------------"<<endl;
        cout<<"1.Add Edge"<<endl;
        cout<<"2.Remove Edge"<<endl;
        cout<<"3.Find MST: Prim"<<endl;
        cout<<"4.Find MST: Kruskal"<<endl;
        cout<<"5.Print Graph"<<endl;
        cout<<"6.Quit"<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;
        switch(choice)
        {
            case 1:
                //add edge
                cout<<"Please enter the source,destination and weight for the edge"<<endl;
                cin>>u >>v >>w;
                g.addEdge(u, v, w);
                break;
            
            case 2:
                //remove edge
                cout<<"Please enter the source and destination of the edge"<<endl;
                cin>>u >>v;
                g.removeEdge(u, v);
                break;
            
            case 3:
                //Get Distance of other nodes uisng Dijkstra
                cout<<"Please enter the source vertex"<<endl;
                cin>>u;
                g.getPrimMST(u);
                break;
            
            case 4:
                //Get Distance of other nodes uisng Bellman Ford
                cout << "Weight of minimum spanning tree is " << g.getKruskalMST();
                break;
            
            case 5:
                //Print Graph
                g.printGraph();
                break;
            
            case 6:
                exit(1);
            
            default:
               cout<<"\nEnter correct option\n";
        }
    }
    
    return 0;
}