// Bubble Sort
// O(n^2)
// Stable
// Method: Exchanging
// Good for Already Sorted Arrays
void bubbleSort(int A[], int n)
{

  int i, j, flag;

  for (i = 0; i < n - 1; i++)
  {
    flag = 0;

    for (j = 0; j < n - 1 - i; j++)
    {
      if (A[j] > A[j + 1])
      {
        swap(&A[j], &A[j + 1]);
        flag = 1;
      }
    }
    if (flag == 0)
    {
      break;
    }
  }
}