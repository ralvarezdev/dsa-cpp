// Binary Search
int binarySearch(int A[], int num)
{
  int startA = 0, endA = sizeof(A) / sizeof(A[0]) - 1;

  while (startA <= endA)
  {
    int mid = startA + (endA - startA) / 2;

    if (A[mid] == num)
      return mid;
    else if (A[mid] < num)
      startA = mid + 1;
    else
      endA = mid - 1;
  }
  return -1;
}