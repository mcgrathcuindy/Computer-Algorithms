/*
NAME: Christopher McGrath
DATE: 3/3/20
DESC: Double hashtable HW 5 C++ Program to Implement Hash Tables
*/
#include<iostream>
#include<cstdlib>
#include<string>
#include<cstdio>
#include<bits/stdc++.h>
using namespace std;
// Hash table size 
const int TABLE_SIZE = 13;
const int PRIME = 11;
enum EntryType {Legitimate, Empty, Deleted};

/*
 * HashEntry Class Declaration
 */
class HashEntry
{
    public:
        int key;
        enum EntryType info;
};
 
/*
 * HashMap Class Declaration
 */
class HashMap
{
    private:
        int current_size;
        HashEntry *htable;
    public:   
        HashMap()
	    {
            htable = new HashEntry[TABLE_SIZE];
            current_size = 0;
            for(int i = 0; i < TABLE_SIZE; i++)
            {
                htable[i].info = Empty; // initialize each element with false
                //htable[i].key = NULL;
            }
        }
    	// function to calculate first hash 
    	int hash1(int key){ return key % TABLE_SIZE; } 
    
    	// function to calculate second hash 
    	int hash2(int key) { return 1 + (key % PRIME); } 
        
        // Insert the key in hashtable
        void Insert(int key2)
	    {
            if(current_size == TABLE_SIZE)
            {
                cout << "Full! Value not added to table.\n";
                return;
            }
            int position = hash1(key2);
            if(htable[position].info == Empty || htable[position].info == Deleted)
            {
                htable[position].key = key2;
                htable[position].info = Legitimate;
            }
            else
            {
                int i = 1;
                int nextIndex = (position + (i*hash2(key2))) % TABLE_SIZE;
                while(htable[nextIndex].info == Legitimate)
                {
                    i++;
                    nextIndex = (position + (i*hash2(key2))) % TABLE_SIZE;
                }
                htable[nextIndex].key = key2;
                htable[nextIndex].info = Legitimate;
            }
            current_size++;
	    }
        
        //Search the key
        int Search(int key2)
	    {
            if(current_size == 0)
            {
                cout << "Empty! Value not searched!\n";
                return -1;
            }
            int position = hash1(key2);
            if(htable[position].key == key2 && htable[position].info == Legitimate)
                return position;
            else
            {
                int i = 1;
                int nextIndex = (position + (i*hash2(key2))) % TABLE_SIZE;
                while(htable[nextIndex].key != key2)
                {
                    i++;
                    nextIndex = (position + (i*hash2(key2))) % TABLE_SIZE;
                    if(i == 10)
                    {
                        return -1;
                    }
                }
                return nextIndex;
            }
    	}
        
        //Delete the given key from hashtable
        void Remove(int key2)
	    {
            if(current_size == 0)
            {
                cout << "Empty! No values to delete.\n";
                return;
            }
            int position = hash1(key2);
            if(htable[position].info == Legitimate && htable[position].key == key2)
            {
                htable[position].info = Deleted;
                htable[position].key = 0;
            }
            else
            {
                int i = 1;
                int nextIndex = (position + (i*hash2(key2))) % TABLE_SIZE;
                while(htable[nextIndex].key != key2)
                {
                    i++;
                    if(i == 10)
                    {
                        cout << "Element not in array!\n";
                        return;
                    }
                    nextIndex = (position + (i*hash2(key2))) % TABLE_SIZE;
                }
                htable[nextIndex].info = Deleted;
                htable[nextIndex].key = 0;
            }
            current_size--;
    	}
        
        //Print all the elements in the hashtable
        void Display() 
        { 
            for(int i = 0; i < TABLE_SIZE; i++)
            {
                cout << i << ": ";
                if(htable[i].info == Legitimate)
                {
                    cout << htable[i].key;
                }
                cout << endl;
            }
        } 
        
        //Delete the hashtable
        ~HashMap()
	    {
            delete[] htable;
        }
};
/*
 * Main Contains Menu
 */
int main()
{
    HashMap hash;
    int key, flag;
    int n, d, s,i;
    int choice;
    // write code for taking input from file
    ifstream file; 
    file.open("input.txt",ios::in); 
    if(!file) 
    { 
        cout<<"File not opened\n"; 
        return 0; 
    } 
    file>>n;
    file>>d;
    file>>s;
    for(i = 0; i < n; i++)
    {
        file>>key;
        hash.Insert(key);
    }
    cout << endl << "After Insertion:"<< endl;
    hash.Display();
    //exit(1);
    for(i = 0; i < d; i++)
    {
        file>>key;
        hash.Remove(key);
    }
    cout << endl << "After Deletion:" << endl;
    hash.Display();
    //exit(1);
    cout << endl << "After Search:" << endl;
    for(i = 0; i < s; i++)
    {
        file>>key;
        if(hash.Search(key) != -1)
            cout << endl << key << " found at index " << hash.Search(key) << endl;
        else
            cout << endl << key << " not found" << endl;
    }
    
    while (1)
    {
        cout<<"\n----------------------"<<endl;
        cout<<"Operations on Hash Table"<<endl;
        cout<<"\n----------------------"<<endl;
        cout<<"1.Insert element into the table"<<endl;
        cout<<"2.Search element from the table"<<endl;
        cout<<"3.Delete element from the table"<<endl;
        cout<<"4.Display all the elements"<<endl;
        cout<<"5.Exit"<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;
        switch(choice)
        {
            case 1:
                cout<<"Enter element to be inserted: ";
                cin>>key;
                hash.Insert(key);
                cout << endl;
                hash.Display();
                break;
            case 2:
                cout<<"Enter element to be searched: ";
                cin>>key;
                if(hash.Search(key) == -1)
                    cout << key << " not found";
                else 
                    cout << key << " found at " << hash.Search(key) << endl;
                break;
            case 3:
                cout<<"Enter element to be removed: ";
                cin>>key;
                hash.Remove(key);
                cout << endl;
                hash.Display();
                break;
            case 4:
                cout << "\nDisplay:\n";
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