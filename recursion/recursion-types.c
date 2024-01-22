#include <stdio.h>

// Tail Recursion
// NOTE: Regular Loops are more Efficient in Space Complexity
// Prints: n n-1 n-2 ... 1
void decrease(int n)
{
  if (n > 0)
  {
    printf("%d ", n);
    decrease(n - 1); // Must be at the End
  }
}

void decreaseLoop(int n)
{
  while (n > 0)
  {
    printf("%d ", n);
    n--;
  }
}
// Head Recursion
// NOTE: Cannot be Easily Converted to Regular Loops
// Prints: 1 2 ... n
void increase(int n)
{
  if (n > 0)
  {
    increase(n - 1); // Must be at the Beginning
    printf("%d ", n);
  }
}

void increaseLoop(int n)
{
  int i = 1;

  while (i <= n)
  {
    printf("%d ", n);
    i++;
  }
}

// NOTE: If the Recursion is being Called at Neither the Beginning nor the End of the Function, It's Called Linear Recursion

// Tree Recursion
// NOTE: If the Function Calls itself more than one Time, It's Called Tree Recursion.
// Prints: 3 2 1 1 2 1 1
// Time Complexity is a GP Serie, O(2^n)
// Space Complexity is Equal to Tree Height, O(n)
void treeDecrease(int n)
{
  if (n > 0)
  {
    printf("%d ", n);
    treeDecrease(n - 1);
    treeDecrease(n - 1);
  }
}

int main()
{
  int x = 3;

  decrease(x);
  printf("%c", '\n');
  increase(x);
  printf("%c", '\n');
  treeDecrease(x);

  return 0;
}