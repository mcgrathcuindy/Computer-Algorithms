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
    int* discoveryTime; //keep track of the vertices as they are discovered
    int* finishTime; //keep track of the vertices as they are finished processing
    int * color;
    stack <int> Stack;
    list <int> finish;
public:
    Graph(int vertices);
    ~Graph();
    void addEdge(int src, int dest); 
    void BFS(int startVertex);
    bool isBipartite(int startVertex);
    void DFSUtil(int startVertex);
    void DFS(int startVertex);
    void topologicalSortingUtil(int startVertex);
    void topologicalSorting(int startVertex);
    void removeEdge(int src, int dest);
	bool isEdge(int src, int dest);
    int getInDegree(int src);
    void printAdjVertices(int src);
    bool hasCommonAdjacent(int src, int dest);
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
    if(src<0 || src>=numVertices || dest<0 || dest >=numVertices)
        return;
    adjLists[src].push_back(dest); 
    if(!directed)
    {
        adjLists[dest].push_back(src);    
    }
    return;
}

void Graph::removeEdge(int src, int dest)
{
    list <int>::iterator it;
    for(it=adjLists[src].begin(); it != adjLists[src].end(); it++)
    {
        if(*it == dest)
        {
            adjLists[src].erase(it);
            break;
        }
    }
    for(it = adjLists[dest].begin(); it != adjLists[dest].end(); it++){
        if(*it == src)
        {
            adjLists[dest].erase(it);
            break;
        }
    }
    numEdges--;
    return;
}

bool Graph::isEdge(int src, int dest)
{
    //returns true if (src,dest) is an edge, otherwise should return false
    list<int>::iterator it;
    bool flag1 = false,flag2 = false;
    for(it = adjLists[src].begin(); it != adjLists[src].end();it++)
    {
        if(*it == dest)
        {
            flag1 = 1;
            break;
        }
    }
    for(it = adjLists[dest].begin(); it != adjLists[dest].end(); ++it)
    {
        if(*it == src)
        {
            flag2 = 1;
            break;
        }
    }
    if(flag1 == true || flag2 == true) return true;
    else return false;
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
    list <int>::iterator it;
    for(it = adjLists[usrc].begin(); it != adjLists[usrc].end(); ++it)
        cout << *it << " ";
}

bool Graph::hasCommonAdjacent(int src, int dest)
{
    //returns true if vertices src and dest have common adjacent vertices
    list <int>::iterator it1;
    list <int>::iterator it2;
    for(it1 = adjLists[src].begin(); it1 != adjLists[src].end(); ++it1)
        for(it2 = adjLists[dest].begin(); it2 != adjLists[dest].end(); ++it2)
            if(*it1 == *it2 && *it1 != src && *it1 != dest)
                return true;
    return false;
}

void Graph::BFS(int startVertex)
{
    int i;
    visited = new bool[numVertices];
    //this will be needed for to implement the getDistance function
    distance = new int[numVertices];
    
    //initialize visited and distance array
    for(i = 0; i < numVertices; i++)
    {
        visited[i] = false;
        distance[i] = 0;
    }
    //declare a queue 
    list<int> queue;
    //make the visited array index for startVertex true and push it in queue 
    visited[startVertex] = true;
    queue.push_back(startVertex);
    list <int>::iterator it;
      
    while(!queue.empty())
    {
        //pop the top of the queue
        //note that the built in pop function doesn't return any value
        //so, call the built in front function of queue and then call the pop function
        startVertex = queue.front();
        cout << startVertex << " ";
        queue.pop_front();
        for(it = adjLists[startVertex].begin(); it != adjLists[startVertex].end(); ++it)
        {
            if(!visited[*it])
            {
                visited[*it] = true;
                queue.push_back(*it);
            }
        }
    }
    return;
}

//check bipartiteness of a graph
bool Graph::isBipartite(int startVertex)
{
    int i;
    bool flag1 = false, flag2 = false;
    int keepTrack[numVertices];
    visited = new bool[numVertices];
    for(i = 0; i < numVertices; i++)
        visited[i] = false;
    list<int> queue;
    visited[startVertex] = true;
    queue.push_back(startVertex);
    
    list <int>::iterator it1;
    list <int>::iterator it2;
    
    while(!queue.empty())//queuue is not empty
    {
        //pop the top of the queue
        startVertex = queue.front();
        queue.pop_front();
        for(it1 = adjLists[startVertex].begin(); it1 != adjLists[startVertex].end(); ++it1)//all adjacent edges
        {
            //case 1: self loop  or odd edge cycle of length 1
            // that means currVertex == adjVertex then return false
            if(!visited[*it1])
            {
                visited[*it1] = true;
                for(it2 = adjLists[*it1].begin(); it2 != adjLists[*it1].end(); ++it2)
                {
                    if(keepTrack[*it2] == 1)
                        flag1 = true;
                    else if(keepTrack[*it2] == 2)
                        flag2 = true;
                }
                if(flag1 == true && flag2 == true)
                    return false;
                else if(flag1 == true && flag2 != true )
                    keepTrack[*it1] = 2;
                else if(flag1 != true && flag2 == true )
                    keepTrack[*it1] = 1;
                else keepTrack[*it1] = 1;
                flag1 = false;
                flag2 = false;
                queue.push_back(*it1);
            }
        }
    }
    return true;
}

void Graph::DFSUtil(int startVertex) 
{ 
    visited[startVertex] = true;
    cout << startVertex << " ";
    list <int>::iterator it;
    for( it = adjLists[startVertex].begin(); it != adjLists[startVertex].end(); ++it){
        if(!visited[*it])
            DFSUtil(*it);
    }
}
  
// DFS traversal of the vertices reachable from startVertex 
// It uses recursive DFSUtil() 
void Graph::DFS(int startVertex) 
{ 
    // Mark all the vertices as not visited 
    visited = new bool[numVertices];
    for(int i = 0; i < numVertices; i ++)
        visited[i] = false;
    // Call the recursive helper function to print DFS traversal 
    DFSUtil(startVertex); 
    return;
}

void Graph::printGraph()
{
    list <int>::iterator j;
    printf("\nNumber of vertices: %d, Number of edges: %d\n", numVertices, numEdges);
    //complete in class
    for(int i = 0; i<numVertices; i++)
    {
        cout<<i<<": ";
        for(j=adjLists[i].begin(); j!=adjLists[i].end(); j++)
        {
            cout<<"-->"<<*j;    
        }
        cout<<endl;
    }
}

void Graph::topologicalSortingUtil(int startVertex)
{
    visited[startVertex] = true;
    list <int>::iterator it;
    for(it = adjLists[startVertex].begin(); it != adjLists[startVertex].end(); ++it)
        if(!visited[*it])
            topologicalSortingUtil(*it);
    Stack.push(startVertex);
}

void Graph::topologicalSorting(int startVertex)
{
    int i = 0;
    visited = new bool[numVertices];
    for(i = 0; i < numVertices; i++)
        visited[i] = false;
    for(i = startVertex; i < numVertices; i++)
        if(visited[i] == false)
            topologicalSortingUtil(i);
    for(i = 0; i < startVertex; i++)
        if(visited[i] == false)
            topologicalSortingUtil(i);
    while(Stack.empty() == false)
    {
        cout << Stack.top() << "--->";
        Stack.pop();
    }
}

Graph::~Graph()
{
    //write your destructor here
    adjLists = NULL;
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
        cout<<"7.Print Graph"<<endl;
        cout<<"8.BFS"<<endl;
        cout<<"9.DFS"<<endl;
        cout<<"10.Check Bipartiteness"<<endl;
        cout<<"11.Topological Sorting"<<endl;
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
                cout << "Please enter src and dest vertices of edge" << endl;
                cin>>u>>v;
                g.removeEdge(u,v);
                break;
            
            case 3:
                //Find Edge
                cout << "Please enter src and dest vertices of edge" << endl;
                cin >> u >> v;
                u = g.isEdge(u,v);
                if(u == 1)
                    cout << "Edge exists"<< endl;
                else cout << "Edge does not exist" << endl;
                break;
            
            case 4:
                //Get Degree of a vertex
                cout<<"Please enter the source vertex"<<endl;
                cin>>u;
                cout<<"Indegree of "<<u<<": "<<g.getInDegree(u);
                break;
            
            case 5:
                //Find Adjacent Vertices
                cout << "Please enter the source vertex" << endl;
                cin >> u;
                g.printAdjVertices(u);
                break;
            
            case 6:
                //Find Common Adjacent Vertices
                cout << "Please enter your two vertices"<< endl;
                cin >> u >> v;
                u = g.hasCommonAdjacent(u, v);
	            if(u == 1)
	                cout<<"They DO share common vertices!"<<endl;
	            else cout<<"They DO NOT share common vertices!"<<endl;
                break;
            
            case 7:
                g.printGraph();
                break;
            
            case 8:
                //BFS
                cout<<"Please enter the source vertex"<<endl;
                cin>>u;
                g.BFS(u);
                break;
            
            case 9:
                //DFS
                cout << "Please enter the source vertex"<<endl;
                cin >> u;
                g.DFS(u);
                break;
            
            case 10:
                //check bipartiteness
                cout << "Please enter the source vertex!" << endl;
                cin >> u;
                cout << "Start Vertex: " << u << endl;
                u = g.isBipartite(u);
                if(u == 1)
                    cout << "Yes" << endl;
                else cout << "No" << endl;
                break;
            
            case 11:
                //Topological sorting
                cout << "Please enter the source vertex!" << endl;
                cin >> u;
                g.topologicalSorting(u);
                break;   

            default:
               cout<<"\nEnter correct option\n";
        }
    }

    return 0;
}