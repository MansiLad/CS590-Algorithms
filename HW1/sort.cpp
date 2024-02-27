#include <cstdio>
#include <cstdlib>
#include <math.h>

#include "sort.h"


int ivector_length(int* v, int n)
{
  int sum;

  sum = 0;
  for (int i = 0; i < n; i++)
    sum += (v[i] < 0) ? -v[i] : v[i];

  return sum;
}

/*
 * insertion sort
 */
void insertion_sort(int** A, int n, int l, int r)
{ 
  int i;
  int* key;

  for (int j = l+1; j <= r; j++)
    {
      key = A[j];
      i = j - 1;

      while ((i >= l) && (ivector_length(A[i], n) > ivector_length(key, n)))
        {
	  A[i+1] = A[i];
	  i = i - 1;
	}

      A[i+1] = key;
    }
}

/*
*   TO IMPLEMENT: Improved Insertion Sort for problem 1.
*/
void insertion_sort_im(int** A, int n, int l, int r)
{ 
   int* key;
   int kvalue;
   int* new_array = new int[r+1];

   for(int j = 0; j <= r; j++) {
      new_array[j] = ivector_length(A[j], n);
   }
   
   for(int j = 1; j <= r; j++) {
      key = A[j];
      kvalue = new_array[j];
      int i = j - 1;
	  
      while(i >= l && (new_array[i] > kvalue)) {
         A[i+1] = A[i];
         new_array[i+1] = new_array[i];
         i = i - 1;
      }

      A[i+1] = key;
      new_array[i+1] = kvalue;
   }    
}

/*
*   TO IMPLEMENT: Improved Merge Sort for problem 2.
*/
void merge(int** A, int* lengths, int n, int p, int midpoint, int r) {

    int** left = new int*[midpoint-p+1];
    int* left_len = new int[midpoint-p+1];

    int** right = new int*[r-midpoint];
    int* right_len = new int[r-midpoint+1];

    for (int i =0; i<midpoint-p+1; i++) {
      left[i] = new int[n];
      left_len[i] = lengths[p+i];
      left[i] = A[p+i];
    }

    for (int j =0; j<r-midpoint; j++) {
      right[j] = new int[n];
      right_len[j] = lengths[midpoint + 1 +j];
      right[j] = A[midpoint + j + 1];
    }

    left_len[midpoint - p + 1] = numeric_limits<int>::max();
    right_len[r-midpoint] = numeric_limits<int>::max();

    int i = 0; 
    int j = 0;

    for (int k=p; k<=r; k++) {
      if(left_len[i] <= right_len[j]) {
        lengths[k] = left_len[i];
        A[k] = left[i];
        i += 1;
      } else {
        lengths[k] = right_len[j];
        A[k] = right[j];
        j += 1;
      }
    }
}

void merge_divide(int** A, int* lengths, int n, int p, int r) {
  if (p < r) {
    int midpoint = floor((p + r) / 2);
    merge_divide(A, lengths, n, p, midpoint);
    merge_divide(A, lengths, n, midpoint + 1, r);
    merge(A, lengths, n, p, midpoint, r);
  }
}


void merge_sort(int** A, int n, int p, int r)
{
    int* len = new int[r+1];
    for (int i = 0; i <= r; i++) {
      len[i] = ivector_length(A[i], n);
    }

    merge_divide(A, len, n, p, r);

}


/*
 * Simple function to check that our sorting algorithm did work
 * -> problem, if we find position, where the (i-1)-th element is 
 *    greater than the i-th element.
 */
bool check_sorted(int** A, int n, int l, int r)
{
  for (int i = l+1; i <= r; i++)
    if (ivector_length(A[i-1], n) > ivector_length(A[i], n))
      return false;
  return true;
}


/*
 * generate sorted/reverse/random arrays of type hw1type
 */
int** create_ivector(int n, int m)
{
  int** iv_array;

  iv_array = new int*[m];
  for (int i = 0; i < m; i++)
    iv_array[i] = new int[n];

  return iv_array;
}

void remove_ivector(int** iv_array, int m)
{
  for (int i = 0; i < m; i++)
    delete[] iv_array[i];
  delete[] iv_array;
}

int** create_sorted_ivector(int n, int m)
{
  int** iv_array;

  iv_array = create_ivector(n, m);
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      iv_array[i][j] = (i+j)/n;

  return iv_array;
}

int** create_reverse_sorted_ivector(int n, int m)
{
  int** iv_array;

  iv_array = create_ivector(n, m);
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      iv_array[i][j] = ((m-i)+j)/n;

  return iv_array;
}

int** create_random_ivector(int n, int m, bool small)
{
  random_generator rg;
  int** iv_array;

  iv_array = create_ivector(n, m);
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      {
	rg >> iv_array[i][j];
	if (small)
	  iv_array[i][j] %= 100;
	else
	  iv_array[i][j] %= 65536;
      }

  return iv_array;
}

