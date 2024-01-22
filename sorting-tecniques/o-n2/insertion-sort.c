// Insertion Sort
// O(n^2)
// Adaptive and Stable
// Method: Insertion
void insertionSort(int A[], int n)
{
  int j, x;

  for (int i = 1; i < n; i++)
  {
    j = i - 1;
    x = A[i];

    while (j > -1 && A[j] > x)
      A[j + 1] = A[j--];

    A[j + 1] = x;
  }
}