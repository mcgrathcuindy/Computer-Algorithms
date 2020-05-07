/*
 * C++ Program to Implement Hash Tables chaining 
 * with Singly Linked Lists
 */
#include<iostream>
#include<cstdlib>
#include<string>
#include<cstdio>
using namespace std;
const int TABLE_SIZE = 7;
 
/*
 * HashNode Class Declaration
 */
class HashNode
{
    public:
    int key;
	HashNode* next;
    HashNode(int key)
    {
        this->key = key;
        this->next = NULL;
    }
};
 
/*
 * HashMap Class Declaration
 */
class HashMap
{
    private:
        HashNode** htable;
    public:
        HashMap()
        {
            htable = new HashNode*[TABLE_SIZE];
            for (int i = 0; i < TABLE_SIZE; i++)
                htable[i] = NULL;
        }
        ~HashMap()
        {
            for (int i = 0; i < TABLE_SIZE; ++i)
	        {
                HashNode* entry = htable[i];
                while (entry != NULL)
	            {
                    HashNode* prev = entry;
                    entry = entry->next;
                    delete prev;
                }
            }
            delete[] htable;
        }
        /*
         * Hash Function
         */
        int HashFunc(int key)
        {
            return key % TABLE_SIZE;
        }
 
        /*
         * Insert Element at a key
         */
        void Insert(int key)
        {
            int hash_val = HashFunc(key);
            HashNode* temp = NULL;
            HashNode* entry = htable[hash_val];
            if(entry == NULL)
            {
                entry = new HashNode(key);
                htable[hash_val] = entry;
            }
            else {
                while(entry -> next != NULL)
                    entry = entry -> next;
                temp = new HashNode(key);
                entry -> next = temp;
            }
            return;
        }
        /*
         * Remove Element at a key
         */
        void Remove(int key)
        {
            int hash_val = HashFunc(key);
            HashNode* entry = htable[hash_val];
            HashNode* prev = entry;

            if(entry == NULL) //list empty
            {
                
            }
            else if () //only one element
            {

            } 
            else if () // multiple elements but match with the first element
            {

            } 
            else // multiple elements but match with any element other than the first element
            {

            }
            return;
        }
        /*
         * Search Element at a key
         */
        int Search(int key)
        {
 
        }
        
        void Display() 
        { 
            for (int i = 0; i < TABLE_SIZE; ++i)
	        {
                HashNode* entry = htable[i];
                cout << i << ": ";
                while (entry != NULL)
	            {
                    cout << entry->key << " --> "; 
                    entry = entry->next;
                }
                cout << endl;
            }
        } 
};
/*
 * Main Contains Menu
 */
int main()
{
    HashMap hash;
    int key;
    int choice;
    while (1)
    {
        cout<<"\n----------------------"<<endl;
        cout<<"Operations on Hash Table"<<endl;
        cout<<"\n----------------------"<<endl;
        cout<<"1.Insert element into the table"<<endl;
        cout<<"2.Search element from the key"<<endl;
        cout<<"3.Delete element at a key"<<endl;
        cout<<"4.Display all elements"<<endl;
        cout<<"5.Exit"<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;
        switch(choice)
        {
            case 1:
                cout<<"Enter element to be inserted: ";
                cin>>key;
                hash.Insert(key);
                hash.Display();
                break;
            
            case 2:
                cout<<"Enter element to be searched: ";
                cin>>key;
                if (hash.Search(key) == -1)
                {
    	            cout<<"No element found at key "<<key<<endl;
    	            continue;
    	        }
                break;
            
            case 3:
                cout<<"Enter key of the element to be deleted: ";
                cin>>key;
                hash.Remove(key);
                hash.Display();
                break;
            
            case 4:
                cout<<"Displaying all the entries: "<< endl;
                hash.Display();
                break;
            
            case 5:
                exit(1);
            
            default:
               cout<<"\nEnter correct option\n";
        }
    }
    return 0;
}