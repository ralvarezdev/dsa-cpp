#include <stdio.h>

// Prints: 5 10 15 20 25
int func(int n)
{
  static int x = 0;
  int t;

  if (n > 0)
  {
    x++;

    t = func(n - 1) + x;
    printf("%d ", t);

    return t;
  }
  return 0;
}

int main()
{
  int a = 5;
  printf("%d", func(a));
}