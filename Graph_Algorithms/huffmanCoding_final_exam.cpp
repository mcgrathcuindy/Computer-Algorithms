/*
Name: Christopher McGrath
Date: 4/22/2020
Desc:Huffman Coding implemented with STL priority queue, Final Exam for CSCI 340
*/
#include <bits/stdc++.h>
using namespace std;
class Node
{
    public:
    char data;
    int freq;
    Node *leftChild;
    Node *rightChild;
    Node(char nodeData, int nodeFreq)
    {
        data = nodeData;
        freq = nodeFreq;
        leftChild = NULL;
        rightChild = NULL;
    }
};
class comparatorFunction
{
    public:
    bool operator() (Node* a, Node* b)
    {
        return a->freq > b->freq;
    }
};
void PrintHuffmanTree(Node* rootNode,int* array,int recent)
{
    //if there is a node to the left, add 0 to the array at index [recent]
    //call PrintHuffmanTree with the leftChild node
    //increase recent, which will move to the next empty spot of array
    if(rootNode-> leftChild != NULL)
    {
        array[recent] = 0;
        PrintHuffmanTree(rootNode->leftChild, array, recent+1);
    }
    //if there is a node to the right, add 1 to the array at index [recent]
    //call PrintHuffmanTree with the leftChild node
    //increase recent, which will move to the next empty spot of array
    if(rootNode -> rightChild != NULL)
    {
        array[recent] = 1;
        PrintHuffmanTree(rootNode->rightChild, array, recent+1);
    }
    //if there is no node to the left or right aka "leaf node"
    //print the Node's data, and print the contents of array
    if(rootNode -> leftChild == NULL && rootNode -> rightChild == NULL)
    {
        cout << rootNode -> data << " ";
        for(int i = 0; i < recent; i++)
        {
            cout << array[i];
        }
        cout << endl;
    }
}
void buildHuffmanTree(char data[], int freq[],int size)
{
    //declare a priority queue of Nodes, with a vector of Nodes as the
    //underlying structure, pass the comparatorFunction
    priority_queue< Node*, vector <Node*> , comparatorFunction > pq;
    //create nodes with data[i], freq[i] and insert them into the pq
    for(int i = 0; i < size; i++)
    {
        Node* aNode = new Node(data[i], freq[i]);
        pq.push(aNode);
    }
    
    //While there is more than one node in the priority queue
    while(pq.size() != 1)
    {
        //remove the two nodes of highest priority(lowest frequency)
        Node *smallest = pq.top();
        pq.pop();
        Node *nextSmallest = pq.top();
        pq.pop();
        //Create a newNode with the other two nodes as children.
        //freq of newNode = smallest->freq + nextSmallest->freq
        Node *newNode = new Node('x',smallest->freq + nextSmallest->freq);
        newNode -> leftChild = smallest;
        newNode -> rightChild = nextSmallest;
        //add the new node into the priority queue
        pq.push(newNode);
    }
    Node *remainingNode = pq.top();
    int array[100];
    int recent = 0;
    PrintHuffmanTree(remainingNode,array,recent);
    return;
}

int main(void)
{
    char data[] = {'a','b','c','d','e','f'};
    int freq[] = {5,9,12,13,16,45};
    int size = sizeof(freq) / sizeof(freq[0]);
    buildHuffmanTree(data,freq,size);
    return 0;
}