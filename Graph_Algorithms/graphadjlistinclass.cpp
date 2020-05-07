#include <bits/stdc++.h> 
using namespace std;

class Graph
{
    int numVertices, numEdges;
    list <int> *adjLists;
    int * distance; //keep the distance of all vertices from a source vertex
    int * parent; //keep the parent of all vertices during a traversal
    bool directed;
    bool* visited; //keep track of the vertices that are visited
    int * color;
public:
    Graph(int vertices);
    ~Graph();
    void addEdge(int src, int dest); 
    void BFS(int startVertex);
    bool isBipartite(int startVertex);
    void DFSUtil(int startVertex);
    void DFS(int startVertex);
    void removeEdge(int src, int dest);
	bool isEdge(int src, int dest);
    int getInDegree(int src);
    void printAdjVertices(int src);
    bool hasCommonAdjacent(int src, int dest);
    void getDist(int startVertex);
    void printGraph();
};
 
Graph::Graph(int vertices)
{
    numVertices = vertices;
    numEdges = 0;
    directed = false;
    adjLists = new list <int>[vertices];
}

void Graph::addEdge(int src, int dest)
{
    //In class
    if(src < 0 || src >= numVertices || dest < 0 || dest >= numVertices)
    {
        return;
    }
    adjLists[src].push_front(dest);
    numEdges++;
    if(!directed)
    {
        adjLists[dest].push_back(src);
    }
    return;
}

void Graph::removeEdge(int src, int dest)
{
    //write this function
    numEdges--;
    return;
}

bool Graph::isEdge(int src, int dest)
{
    //returns true if (src,dest) is an edge, otherwise should return false
}

int Graph::getInDegree(int src)
{
    //returns the degree of vertex src
    int inDegree = 0;
    list <int>::iterator it;
    for (int i=0; i<numVertices; i++) 
    { 
        for (it = adjLists[i].begin(); it != adjLists[i].end(); ++it)
        {
             if(*it == src)
             {
                inDegree++; 
                //If you want to create an array of the indegree of all vertices
                //inDegree[*it]++;
             }
        }
    } 
    return inDegree;
}

void Graph::printAdjVertices(int usrc)
{
    //prints all adjacent vertices of a vertex src
}

bool Graph::hasCommonAdjacent(int src, int dest)
{
    //returns true if vertices src and dest have common adjacent vertices

}

void Graph::BFS(int startVertex)
{
    int i;
    visited = new bool[numVertices];
    //this will be needed for to implement the getDistance function
    distance = new int[numVertices];
    
    //initialize visited and distance array
    
    //declare a queue 
    //make the visited array index for startVertex true and push it in queue 

 
    list <int>::iterator it;
      
    while()
    {

 
    }
    return;
}

//check bipartiteness of a graph
bool Graph::isBipartite(int startVertex)
{

}

void Graph::DFSUtil(int startVertex) 
{ 

} 
  
// DFS traversal of the vertices reachable from startVertex 
// It uses recursive DFSUtil() 
void Graph::DFS(int startVertex) 
{ 
    // Mark all the vertices as not visited 
    
    // Call the recursive helper function to print DFS traversal 
    DFSUtil(startVertex); 
    return;
}

//Find the distance of all vertices from start vertex
//assume all the edges have weight 1
void Graph::getDist(int startVertex)
{

}


void Graph::printGraph()
{
    list <int>::iterator j;
    printf("\nNumber of vertices: %d, Number of edges: %d\n", numVertices, numEdges);
    for(int i = 0; i < numVertices; i++)
    {
        cout << i << ": ";
        for(j = adjLists[i].begin(); j != adjLists[i].end(); ++j)
        {
            cout << "==>"<<*j; 
        }
        cout << endl;
    }
}

Graph::~Graph()
{
    //write your destructor here
}

int main()
{
    int nVertex, nEdge, choice, i, u, v;
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
        g.addEdge(u, v);
    }

    while (1)
    {
        cout<<"\n----------------------"<<endl;
        cout<<"Operations on Graph"<<endl;
        cout<<"\n----------------------"<<endl;
        cout<<"1.Add Edge"<<endl;
        cout<<"2.Remove Edge"<<endl;
        cout<<"3.Find Edge"<<endl;
        cout<<"4.Get Degree of a vertex"<<endl;
        cout<<"5.Find Adjacent Vertices"<<endl;
        cout<<"6.Find Common Adjacent Vertices"<<endl;
        cout<<"7.Find Distance"<<endl;
        cout<<"8.BFS"<<endl;
        cout<<"9.DFS"<<endl;
        cout<<"10.Check Bipartiteness"<<endl;
        cout<<"11.Topological Sorting"<<endl;
        cout<<"12.Print Graph"<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;
        switch(choice)
        {
            case 1:
                //int u, v;
                cout<<"Please enter the source and destination vertes of the edge"<<endl;
                cin>>u >>v;
                g.addEdge(u, v);
                break;
            
            case 2:
                //remove edge
                break;
            
            case 3:
                //Find Edge
                break;
            
            case 4:
                //Get Degree of a vertex
                cout<<"Please enter the source vertex"<<endl;
                cin>>u;
                cout<<"Indegree of "<<u<<": "<<g.getInDegree(u);
                break;
            
            case 5:
                //Find Adjacent Vertices
                break;
            
            case 6:
                //Get Degree of a vertex
                break;
            
            case 7:
                //Find Distance
                cout<<"Please enter the source vertex"<<endl;
                cin>>u;
                g.getDist(u);
                break;
            
            case 8:
                //BFS
                cout<<"Please enter the source vertex"<<endl;
                cin>>u;
                g.BFS(u);
                break;
            
            case 9:
                //DFS

                break;
            
            case 10:
                //check bipartiteness

                break;
            
            case 11:
                //Topological sorting
                break;   
                
            case 12:
                //Print Graph
                g.printGraph();
                break;    
                
            default:
               cout<<"\nEnter correct option\n";
        }
    }

    return 0;
}