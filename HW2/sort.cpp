#include <cstdio>
#include <cstdlib>

#include "sort.h"

/* 
 * HW 2 part
 */
int string_compare(char* s1, char *s2)
{ 
/*
 * We assume that s1 and s2 are non-null pointers
 */
  int i;

  i = 0;
  while ((s1[i] != 0) && (s2[i] != 0) && (s1[i] == s2[i]))
    i++;

  if (s1[i] == s2[i])
    return 0;
  else
    {
      if (s1[i] < s2[i])
	return -1;
      else
	return 1;
    }
} /*>>>*/

void insertion_sort(char** A, int l, int r)
{ 
  int i;
  char* key;

  for (int j = l+1; j <= r; j++)
    {
      key = A[j];
      i = j - 1;
      while ((i >= l) && (string_compare(A[i], key) > 0))
      {
        A[i+1] = A[i];
        i = i - 1;
      }
      A[i+1] = key;
    }
}

void insertion_sort_digit(char** A, int* A_len, int l, int r, int d)
{
	for(int i = 1; i <= r; i++)
	{
		char* key = A[i];
		int key_len = A_len[i];
		int j = i - 1;
    char temp_id = (A_len[j] < d) ? 0 : A[j][d];
    char key_id = (key_len < d) ? 0 : key[d];

		while(j >= 0 && (temp_id > key_id))
		{
			A_len[j+1] = A_len[j];
			A[j+1] = A[j];
			j = j - 1;
      temp_id = (j >= 0) ? (A_len[j] < d ? 0 : A[j][d]) : 0;
		}
		A_len[j+1] = key_len;	
		A[j+1] = key;
	}
}

void counting_sort_digit(char** A, int* A_len, char** B, int* B_len, int n, int d)
{
  int countArray[256] = {};

  for (int i = 0; i < n; i++) {
    char ch = (A_len[i] - 1 >= d) ? A[i][d] : 0;
    countArray[ch] = countArray[ch] + 1;
  }

  for(int i = 1; i <255;i++){
    countArray[i] += countArray[i-1];
  }

  for (int j = n - 1; j >= 0; j--) {
    char ch = (A_len[j] - 1 >= d) ? A[j][d] : 0;
    int index = countArray[ch] - 1;
    B[index] = A[j];
    B_len[index] = A_len[j];
    countArray[ch]--;
  }
  
  for(int i = 0; i < n;i++){
    A[i] = B[i];
    A_len[i] =B_len[i];
  }

}

void radix_sort_is(char** A, int* A_len, int n, int m)
{ 
	for(int i = m-1; i >= 0; i--)
	{
		insertion_sort_digit(A, A_len, 0, n-1, i);
	}
}

void radix_sort_cs(char** A, int* A_len, int n, int m)
{ 
	char** B = new char* [n];
	int* B_len = new int[n];
	char** A_temp = A;
	int* A_temp_length = A_len;
	char** B_temp = B;
	int* B_temp_length = B_len;
	
	for(int i = m-1; i >= 0; i--)
	{
		counting_sort_digit(A_temp, A_temp_length, B_temp, B_temp_length, n-1, i);
	}
}

/*
 * Simple function to check that our sorting algorithm did work
 * -> problem, if we find position, where the (i-1)-th element is 
 *    greater than the i-th element.
 */
bool check_sorted(char** A, int l, int r)
{
  for (int i = l+1; i < r; i++)
    if (string_compare(A[i-1],A[i]) > 0)
      return false;
  return true;
}
