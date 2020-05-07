/* QuickSort*/
#include <bits/stdc++.h> 
using namespace std;

// This function swap two given items. As it takes pointer, it is call by reference
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
    return;
}

/* This function takes last element as pivot and find the partition point */
int partition(int arr[], int low, int high)
{
  int pi = low;
  int pivot = arr[low];  
  do
  {
     while ( low <= high && arr[low] <= pivot )
        low++;
     while ( arr[high] > pivot )
        high--;
     if ( low < high )
        swap(&arr[low], &arr[high]);
  }
  while ( low < high );
  swap(&arr[pi], &arr[high]);
  pi = high;
  return(pi); 
}

void quickSelect(int arr[], int low, int high,int k)
{
        int p = partition(arr, low, high);
        if(k-1 == p)
        {
            cout << k<<"th smallest element = " << arr[p]<< endl;
            return;
        }
        if(k-1 < p)
            quickSelect(arr, low, p - 1,k); //before p
        if(k-1 >= p)
            quickSelect(arr, p + 1, high,k); //after p
}

void printArray(int arr[], int size)
{
    int i;
    for (i=0; i < size; i++)
        cout<<arr[i]<< "  ";
    cout<<endl;
}

int main()
{
    int arr[] = {2, 4, 9, 10, 6, 7, 1, 23, 0, 100};
    int n = sizeof(arr)/sizeof(arr[0]);
    int k = 0;
    cout << "Unordered array: \n";
    printArray(arr, n);
    cout << "Enter a number k to find the Kth smallest element\n";
    cin >> k;
    quickSelect(arr, 0, n-1,k);
    
    return 0;
}
