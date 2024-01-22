// f(n) = 3*n^0
// O(n^0) = O(1)
void swap(int x, int y)
{
  int t;

  t = x; // 1
  x = y; // 1
  y = t; // 1
}

// f(n) = 2*n + 3
// O(n)
int sum(int A[], int n)
{
  int s, i;

  s = 0;                  // 1
  for (i = 0; i < n; i++) // n + 1
    s += A[i];            // n

  return s; // 1
}

// f(n) = 2*n^2 + 2*n + 1
// O(n^2)
void add(int **A, int **B, int **C, int n)
{
  int i, j;

  for (i = 0; i < n; i++)          // n + 1
    for (j = 0; j < n; j++)        // n*(n+1)
      C[i][j] = A[i][j] + B[i][j]; // n*n
}