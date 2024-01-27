#include <stdio.h>

// --- SUM

// 1 + 2 + 3 + 4 + 5 + 6 + 7
// 1 + 2 + 3 + 4 + ... + n

// sum(n) = 1 + 2 + 3 + 4 + ... + (n-1) + n
// sum(n) = sum(n-1) + n

// sum (n) = {
// 0, n=0
// sum(n-1) + n, n>0
// }

// Time Complexity: O(n)
// Space Complexity: O(n)
int sum(int n)
{
  if (n == 0)
    return 0;

  return sum(n - 1) + n;
}

// Iterative Version
// Time Complexity: O(n)
// Space Complexity: O(1)
int sumLoop(int n)
{
  int i, s = 0;

  for (i = 1; i <= n; i++)
    s += i;

  return s;
}

// Time Complexity: O(1)
// Space Complexity: O(1)
int gaussSum(int n)
{
  return n * (n + 1) / 2;
}

// --- FACTORIAL

// n! = 1 * 2 * 3 * 4 * ... * n
// 5! = 1 * 2 * 3 * 4 * 5 = 120

// fact(n) = 1 * 2 * 3 * ... * (n-1) * n
// fac(n) = fact(n-1) * n

// fact(n) = {
// 1, n=0
// fact(n-1) * n, n>0
// }

int fact(int n)
{
  if (n < 0) // Prevent Stack Overflow Error
    return 0;
  else if (n == 0)
    return 1;

  return fact(n - 1) * n;
}

// Iterative Version
int factLoop(int n)
{
  int i, s = 1;

  for (i = 1; i < n; i++)
    s *= i;

  return s;
}

// --- EXPONENTATION

// 2^5 = 2 * 2 * 2 * 2 * 2
// m^n = m * m * m * ... for n times

// power(m, n) = (m * m * m * ... * for n-1 times) * m
// power(m, n) = power(m, n-1) * m

// power(m, n) = {
// 1, n=0
// power(m, n-1), n>0
// }

int power(int m, int n)
{
  if (n == 0)
    return 1;

  return power(m, n - 1) * m;
}

int powerByHalf(int m, int n)
{
  if (n == 0)
    return 1;

  if (n % 2 == 0)
    return power(m * m, n / 2); // Even

  return power(m * m, (n - 1) / 2) * m; // Odd
}

// --- TAYLOR SERIES

// e^x = 1 + x/1 +x^2/2! + x^3/3! + ... n terms

// sum(n) = 1 + 2 + 3 + ... + n
// fact(n) = 1 * 2 * 3 * ... * n
// power(x, n) = x * x * x * ... n times

// sum(n-1) + n
// fact(n-1) * n
// power(x, n-1) * x

// Iterative Version
double eR(int x, int n)
{
  double s, num, den;
  int i;

  s = num = den = 1;

  for (i = 1; i <= n; i++)
  {
    num *= x;
    den *= i;
    s += num / den;
  }

  return s;
}

// Recursive Version
double e(int x, int n)
{
  static double p, f; // Power and Factorial Temp VARIABLES
  double result;

  if (n == 0)
  {
    p = f = 1;
    return 1;
  }

  result = e(x, n - 1);
  p *= x;
  f *= n;
  return result + p / f;
}
// x=1, n=3
// Iterations:
// 1.) n=0: 1
// 2.) n=1: 1 + x/1
// 3.) n=2: 1 + x/1 + x^2/2
// 4.) n=3: 1 + x/1 + x^2/2 + x^3/6
// Result: 2.666667

// --- TAYLOR SERIES USING HORNER'S RULE

// Taylor Series Number of Multiplications

// e^x = 1 + x/1 +x^2/2! + x^3/3! + ... n terms
// 0 0 2 4 6 ... n terms
// 2(1 + 2 + 3 + ... n terms)
// 2*n*(n+1)/2 = n*(n+1)
// O(n^2) Multiplications

// Taylor Series Number of Multiplications Using Horner's Rule

// e^x = 1 + x/1 +x^2/2! + x^3/3! + ... n terms
// e^x = 1 + x/1 * (1 + x/2 * (1 + x/3 * (...)))
// O(n) Multiplications

// Iterative Version
double eHorner(int x, int n)
{
  double s = 1;

  for (; n > 0; n--)
    s = 1 + x * s / n;

  return s;
}

// Recursive Version
double eHornerR(int x, int n)
{
  static double s = 1;

  if (n == 0)
    return s;

  s = 1 + x * s / n;
  return eHornerR(x, n - 1);
}

int main()
{
  int x, m, n;

  // --- SUM
  x = 1000;
  int resultSum, resultSumLoop, resultGaussSum;

  resultSum = sum(x);
  resultSumLoop = sumLoop(x);
  resultGaussSum = gaussSum(x);

  printf("Sum of %d Natural Numbers by:\nRecursion: %d\nLoop: %d\nGauss Sum: %d\n\n",
         x, resultSum, resultSumLoop, resultGaussSum);

  // --- FACTORIAL
  x = 10;
  int resultFact, resultFactLoop;

  resultFact = fact(x);
  resultFactLoop = factLoop(x);

  printf("Factorial of %d by:\nRecursion: %d\nLoop: %d\n\n",
         x, resultFact, resultFactLoop);

  // --- EXPONENTATION
  m = 2, n = 19;
  int resultPower;

  resultPower = powerByHalf(m, n);

  printf("%d to the %d:\nResult: %d\n\n",
         m, n, resultPower);

  // TAYLOR SERIES (e^x)
  x = 1, n = 3;
  double resultTaylor;

  resultTaylor = e(x, n);

  printf("e^%d Taylor Serie of %d Terms\nResult: %lf\n\n", x, n + 1, resultTaylor);

  x = 5, n = 25;

  resultTaylor = e(x, n);

  printf("e^%d Taylor Serie of %d Terms\nResult: %lf\n\n", x, n + 1, resultTaylor);

  // With Horner's Rule
  x = 1, n = 3;

  resultTaylor = eHornerR(x, n);

  printf("e^%d Taylor Serie of %d Terms Using Horner\'s Rule\nResult: %lf", x, n + 1, resultTaylor);

  return 0;
}