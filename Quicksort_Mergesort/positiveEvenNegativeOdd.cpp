// C++ program to rearrange positive 
// and negative numbers 
#include<iostream> 
using namespace std; 
  
// Swap function 
void swap(int* a, int i , int j) 
{ 
    int temp = a[i]; 
    a[i] = a[j]; 
    a[j] = temp; 
    return ; 
} 
  
// Print array function 
void printArray(int* a, int n) 
{ 
    for(int i = 0; i < n; i++) 
        cout << a[i] << " "; 
    cout << endl; 
    return ; 
} 
  
// Driver code 
int main() 
{ 
    int arr[] = { 1, -3, 5, 6, -3, 6, 7, -4, 9, 10 }; 
    int n = sizeof(arr)/sizeof(arr[0]); 
      
    //before modification 
    printArray(arr, n); 
  
    for(int i = 0; i < n; i++) 
    { 
        if(arr[i] >= 0 && i % 2 == 1) 
        {  
            // out of order positive element 
            for(int j = i + 1; j < n; j++) 
            { 
                if(arr[j] < 0 && j % 2 == 0) 
                {  
                    // find out of order negative  
                    // element in remaining array 
                    swap(arr, i, j); 
                    break ; 
                } 
            } 
        } 
        else if(arr[i] < 0 && i % 2 == 0) 
        { 
            // out of order negative element 
            for(int j = i + 1; j < n; j++) 
            { 
                if(arr[j] >= 0 && j % 2 == 1) 
                { 
                    // find out of order positive  
                    // element in remaining array 
                    swap(arr, i, j); 
                    break; 
                } 
            }  
        } 
    } 
      
    //after modification 
    printArray(arr, n);  
    return 0; 
} 