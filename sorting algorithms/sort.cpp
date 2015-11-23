#include <vector>
#include "sort.hpp"

//insertion sort to be switched when vector size less than or equal to 40
template <typename T>
void insertion_sort (std::vector<T> &a, unsigned long int low, unsigned long int high)
{
  for (unsigned long int i = low+1; i <= high; i++) {
    for (unsigned long int j = i; (j > low) && (a[j] < a[j-1]); j--) {
      std::swap(a[j], a[j-1]);
    }
  }
}


template <typename T>
void merge(std::vector<T> &a, std::vector<T> &tmp, unsigned long int low,
		unsigned long int mid, unsigned long int high) {
  unsigned long int i = low;
  unsigned long int Mid = mid - 1; //last index of first vector to merge
  unsigned long int size = high - low + 1;


  while (low <= Mid && mid <= high) {
    if (a[low] <= a[mid]) {
      tmp[i++] = std::move(a[low++]);//put vector less than mid before mid in the temp vector
    } else {
      tmp[i++] = std::move(a[mid++]); //put vector larger than mid after mid in the temp vector

    }
  }

  while (low <= Mid) {
    tmp[i++] = std::move(a[low++]); //put leftover index to temp array
  }

  while ( mid <= high) {
    tmp[i++] = std::move(a[mid++]); //put leftover index to temp array
  }

  for (unsigned long int j = 0; j < size; ++j, --high) {
    a[high] = std::move(tmp[high]); //copy temp array to the original array
  }
}

template <typename T>
void mergesort_recursive (std::vector<T> &a, std::vector<T> &tmp,
		unsigned long int low, unsigned long int high) {
  if (low + 40 > high) {
    insertion_sort(a, low, high); //insertion sort when subarray size <= 40
  } else {
    unsigned long int mid = (low + high)/2;
    mergesort_recursive(a, tmp, low, mid); //recursively split the subarray
    mergesort_recursive(a, tmp, mid + 1, high);
    merge(a, tmp, low, mid + 1, high); //merge the two subarrays
  }
}

template <typename T>
void mergesort_recursive(std::vector<T> &a) { //driver function
  try {std::vector<T> tmp( a.size( ) );}
  catch (...) {throw;} //see if the length of vector fits the memory
  std::vector<T> tmp( a.size( ) );
  mergesort_recursive(a, tmp, 0, a.size() - 1);
}


template <typename T>
void mergesort_iterative (std::vector<T> &a, std::vector<T> &tmp,
		unsigned long int low, unsigned long int high) {
     for (unsigned long int i = 1; i < a.size(); i = i*2) {
       for (unsigned long int j = 0; j < a.size() - i; j += 2*i) {
    	 unsigned long int templow = j;
    	 unsigned long int temphigh = std::min(j + 2*i - 1, a.size() -1) ;//pick the last index as the min number of end of the vector and the length of the subvector
    	 unsigned long int tempmid = j + i - 1; // pick the middle index of the leftover subvector
	 
         merge(a, tmp, templow, tempmid + 1, temphigh); //merge two subvectors 
       }
   }
}

template <typename T>
void mergesort_iterative(std::vector<T> &a) { //driver function
  try {std::vector<T> tmp( a.size( ) );}
  catch (...) {throw;}
  std::vector<T> tmp( a.size( ) );
  mergesort_iterative(a, tmp, 0, a.size() - 1);
}

template <typename T>
const T & median3(std::vector<T> & a,
		unsigned long int left, unsigned long int right )
{ //pick the medians of the subvector as pivots
	unsigned long int center = (left+right) / 2;
	if(a[center] < a[left] )
		std::swap( a[left], a[center] );
	if(a[right] < a[left])
		std::swap( a[left],a[right]);
	if(a[right]<a[center])
		std::swap(a[center], a[right]);
	std::swap( a[ center ], a[ right - 1 ] );
	//place the pivot position
	return a[right-1];
}

template <typename T>
void quicksort(std::vector<T> & a, unsigned long int left, unsigned long int right )
{
	if(left+40<=right)
	{
	  const T & pivot = median3(a,left, right); //get the pivot
	  unsigned long int i = left, j = right - 1;
	  for( ; ; ) //wait until the loop breaks
	  {
	    while( a[++i ] < pivot) { } //find the index from left that needs to swap
	    while( pivot < a[--j] ) { } //find the index from right that needs to swap
	    if( i < j ) std::swap( a[ i ], a[ j ] );
	    else break;
	  }	
	  std::swap(a[i], a[right-1]);
	  quicksort( a,left,i-1);
          quicksort( a,i+1,right);
		//recursive call on subarrays
	}
	else  // Do an insertion sort on the subarray when array size less than 40
		insertion_sort( a, left, right );
}

template <typename T>
void quicksort(std::vector<T> &a) { //driver function for quicksort
  try {std::vector<T> tmp( a.size( ) );}
  catch (...) {throw;}
  quicksort(a, 0, a.size() - 1); 
 
}
