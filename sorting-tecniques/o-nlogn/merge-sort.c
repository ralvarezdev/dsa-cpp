// Merge Sort
// O(n*logn)
// Stable
// Method: Merging
void merge(int A[], int l, int mid, int h)
{
  int i = l, j = mid + 1, k = l;
  int B[100];

  while (i <= mid && j <= h)
  {
    if (A[i] < A[j])
      B[k++] = A[i++];
    else
      B[k++] = A[j++];
  }
  for (; i <= mid; i++)
    B[k++] = A[i];
  for (; j <= h; j++)
    B[k++] = A[j];

  for (int i = l; i <= h; i++)
    A[i] = B[i];
}

void iterMergeSort(int A[], int n)
{
  int p, l, h, mid, i;

  for (p = 2; p <= n; p *= 2)
  {
    for (i = 0; i + p - 1 < n; i += p)
    {
      l = i;
      h = i + p - 1;
      mid = (l + h) / 2;
      merge(A, l, mid, h);
    }
    if (n - i > p / 2)
    {
      l = i;
      h = i + p - 1;
      mid = (l + h) / 2;
      merge(A, l, mid, n - 1);
    }
  }

  if (p / 2 < n)
    merge(A, 0, p / 2 - 1, n - 1);
}