// Quick Sort
// Worst Case: O(n^2)
// Best Case: O(n*logn)
// Not good if the Pivot Index is at the Beggining or End of the List
// Method: Partitioning
int partition(int A[], int l, int h)
{
  int pivot = A[l];
  int i = l, j = h;

  do
  {
    do
      i++;
    while (A[i] <= pivot);

    do
      j--;
    while (A[j] > pivot);

    if (i < j)
      swap(A[i], A[j]);
  } while (i < j);

  swap(&A[l], &A[j]);
  return j;
}

void quickSort(int A[], int l, int h)
{
  int j;

  if (l < h)
  {
    j = partition(A, l, h);
    quickSort(A, l, j);
    quickSort(A, j + 1, h);
  }
}