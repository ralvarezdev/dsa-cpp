#include <limits.h>

// Count Sort
// O(n)
// Memory Intensive
int findMax(int A[], int n)
{
  int max = INT_MIN;
  int i;

  for (i = 0; i < n; i++)
    if (A[i] > max)
      max = A[i];

  return max;
}

void countSort(int A[], int n)
{
  int max, i, j, *c;

  max = findMax(A, n);
  c = (int *)mallox(sizeof(int) * (max + 1));

  for (i = 0; i < max; i++)
    c[i] = 0;

  for (i = 0; i < n; i++)
    c[A[i]]++;

  i = 0;
  j = 0;
  while (j < max + 1)
    if (c[j] > 0)
    {
      A[i++] = j;
      c[j]--;
    }
    else
      j++;
}