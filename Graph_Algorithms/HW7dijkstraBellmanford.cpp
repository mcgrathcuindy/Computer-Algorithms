/*
NAME: Christopher McGrath
DATE: 4/9/2020
DESC: HW7 Dijkstra's algorithm / Bellman Ford (STL)
*/
#include <bits/stdc++.h> 
using namespace std;
# define INF 0xffff


typedef pair<int, int> iPair; 
class Graph
{
    int numVertices, numEdges;
    list <pair <int, int> > *adjLists;
    int * distance; //keep the distance of all vertices from a source vertex
    int * parent; //keep the parent of all vertices during a traversal
    bool* visited;
    bool directed;

public:
    Graph(int vertices);
    ~Graph();
    void addEdge(int src, int dest, int weight); 
    void removeEdge(int src, int dest);
    int getInDegree(int src);
    void getDistDijkstra(int src);
    void getDistBellmanFord(int src);
    void printPath(int v);
    void printGraph();
};
 
Graph::Graph(int vertices)
{
    numVertices = vertices;
    numEdges = 0;
    directed = true;
    distance = new int[numVertices];
    visited = new bool[numVertices];
    parent = new int[numVertices];
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
}

void Graph::removeEdge(int src, int dest)
{
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

int Graph::getInDegree(int src)
{
    //returns the degree of vertex src
    
    int inDegree = 0;
    
    list <iPair>::iterator it;
    for (int i=0; i<numVertices; i++) 
    { 
        for (it = adjLists[i].begin(); it != adjLists[i].end(); ++it)
        {
            if((*it).second == src)
            {
                inDegree++; 
            }
        }
    } 
    
    return inDegree;
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



// Prints shortest paths from src to all other vertices 
// You can insert the same node with multiple different 
// weights but that is not a problem. Since they will be ultimately popped
// from the priority queue but their adjacent nodes would not be inserted 
// since distance to those nodes through this node will not satisfy the 
// condition distance[v] > distance[u] + weight
void Graph::getDistDijkstra(int src) 
{ 
    // Create a priority queue to store vertices that 
    // are being preprocessed. Priority Queue is a max heap (by default)
    //in C++ STL (that means it uses the default Less than operator)
    // Since we need min heap, we need to call the greater comparator
    priority_queue< iPair, vector <iPair> , greater<iPair> > pq; 
    // initialize all distances as infinite (INF) 

    vector<int> dist(numVertices, INF); 
    // Insert source itself in priority queue 
    // Initialize its distance as 0. 
    pq.push(make_pair(0,src));
    dist[src] = 0;
    // Looping till priority queue becomes empty 
    while(!pq.empty())
    {
        int popped = pq.top().first;
        pq.pop();
        list< pair<int,int> >::iterator it;
        for(it = adjLists[popped].begin(); it != adjLists[popped].end(); ++it)
        {
            int v = (*it).second;
            int weight = (*it).first;
            if(dist[v] > dist[popped] + weight)
            {
                dist[v] = dist[popped] + weight;
                pq.push(make_pair(v,dist[v]));
            }
        }
    }
    // Print shortest distances stored in distance[] 
    cout << "Vertex  Distance from Source" << endl;
    for(int i = 0; i < numVertices; ++i)
        printf("%d \t\t %d\n",i,dist[i]);
    
    return;
} 

void Graph::getDistBellmanFord(int src) 
{   
    for(int i = 0; i < numVertices; i++)
    {
        distance[i] = INF;
        parent[i] = -1;
    }
    list <iPair>::iterator it;
    distance[src] = 0;
    for(int i = 0; i <= numVertices-1; i++)
    {
        int u = i;
        for(it = adjLists[i].begin(); it != adjLists[i].end(); ++it)
        {
            int v = (*it).second;
            int weight = (*it).first;
            if(distance[u] != INF && distance[u] + weight < distance[v])
            {
                distance[v] = distance[u] + weight;
                parent[v] = u;
            }
        }
    }
    //code to detect negative cycle
    for(it = adjLists[src].begin(); it != adjLists[src].end(); ++it)
    {
        if(distance[src] + (*it).first < distance[(*it).second])
        {
            cout << "Negative cycle exists!" << endl;
            return;
        }
    }
    //code to call printPath for each vertex
    cout << "Vertex  Distance from Source\n";
    for(int i = 0; i < numVertices; i++)
    {
        cout << i << "\t" << distance[i];
        cout << "[";
        printPath(i);
        cout << "]" << endl;
    }
    
} 

// Recurive Function to print path of given vertex v from source vertex
void Graph::printPath(int v)
{
    //if we reach source vertex
    if(v == 0 )//since zero is source vertex
    {
        cout << v << " ";
        return;
    }
    printPath(parent[v]);
    cout << v << " ";
}


Graph::~Graph()
{
    //write your destructor here
    delete[] distance;
    delete[] parent;
    delete[] adjLists;
    delete[] visited;
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
        cout<<"3.Get Degree of a vertex"<<endl;
        cout<<"4.Find Distance: Dijkstra"<<endl;
        cout<<"5.Find Distance: Bellman Ford"<<endl;
        cout<<"6.Print Graph"<<endl;
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
                //Get Degree of a vertex
                cout<<"Please enter the source vertex"<<endl;
                cin>>u;
                cout<<"Indegree of "<<u<<": "<<g.getInDegree(u);
                break;
            
            case 4:
                //Get Distance of other nodes uisng Dijkstra
                cout<<"Please enter the source vertex"<<endl;
                cin>>u;
                g.getDistDijkstra(u);
                break;
            
            case 5:
                //Get Distance of other nodes uisng Bellman Ford
                cout<<"Please enter the source vertex"<<endl;
                cin>>u;
                g.getDistBellmanFord(u);
                break;
            
            case 6:
                //Print Graph
                g.printGraph();
                break;
            
            default:
               cout<<"\nEnter correct option\n";
        }
    }
    
    return 0;
}