/* Counting inverse*/
#include <bits/stdc++.h> 
using namespace std;

int mergeSortAndCountInv(int arr[], int l, int r); 
int merge(int arr[], int l, int m, int r); 

int merge(int arr[], int l, int m, int r) 
{ 
	int i, j, k, inv_count = 0; 
	int n1 = m - l + 1; 
	int n2 = r - m; 

	/* create temp arrays */
	int * L = new int[n1];
	int * R = new int[n2];
 

	/* Copy data to temp arrays L[] and R[] */
	for(i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for(j = 0; j < n2; j++)
		R[j] = arr[m + j +1];

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0; // Initial index of first subarray 
	j = 0; // Initial index of second subarray 
	k = l; // Initial index of merged subarray 
	while (i < n1 && j < n2) 
	{ 
		if(L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{ 
			arr[k] = R[j];
			j++;
			inv_count += m - i + 1;//num of elements left in left sub array 
		}
		k++;
	}

	/* Copy the remaining elements of L[], if there are any */
	while (i < n1) 
	{ 
		arr[k] = L[i];
		i++;
		k++;
	} 

	/* Copy the remaining elements of R[], if there are any */
	while (j < n2) 
	{ 
		arr[k] = R[j];
		j++;
		k++;
	} 
	delete [] L;
	delete [] R;
    return inv_count;
} 

int mergeSortAndCountInv(int arr[], int l, int r) 
{ 
	int inv_count = 0;
	if(l < r)
	{
		int m = (l+r)/2;
		inv_count = mergeSortAndCountInv(arr,l,m);
		inv_count += mergeSortAndCountInv(arr,m+1,r);
		inv_count += merge(arr,l,m,r);
	}
	return inv_count; 
} 

/* Function to print an array */
void printArray(int A[], int size) 
{ 
	int i; 
	for (i=0; i < size; i++) 
        cout<<A[i]<< "  ";
    cout<<endl;
} 

/* Driver program to test above functions */
int main() 
{ 
	//int arr[] = { 1, 20, 6, 4, 5 };
	//int arr[] = { 3, 1, 2, 4, 5};
	int arr[] = { 3, 7, 10, 14, 18, 19, 2, 11, 16, 17, 23, 25};
	int arr_size = sizeof(arr)/sizeof(arr[0]);

	cout<<"Given array is \n";
	printArray(arr, arr_size);

	cout<<"Number of inversions are \n"<< mergeSortAndCountInv(arr, 0, arr_size - 1) << endl;

	return 0; 
} 
