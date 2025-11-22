#include <iostream>

void sum(size_t n, size_t m, int * c, const int * a, const int * b);
int * sum(size_t n, size_t m, const int * a, const int * b);
void add(size_t n, size_t m, const int * a, const int * b);
void mul(int * c, const int * a, size_t n1, size_t m1, const int * b, size_t m2);

void sum_of_mul(size_t n, int * c, const int * a, const int * const * b, size_t s);
int * sum_of_mul(size_t n, const int * a, const int * const * b, size_t s);
void mul_of_mul(size_t n, int * c, const int * a, const int * const * b, size_t s);
int * mul_of_mul(size_t n, const int * a, const int * const * b, size_t s);

int main()
{

}

void sum(size_t n, size_t m, int * c, const int * a, const int * b)
{
  for (size_t i = 0; i < n; ++i)
  {
    for (size_t j = 0; j < m; ++j)
    {
      c[i * m + j] = a[i * m + j] + b[i * m + j];
    }
  }
}

int * sum(size_t n, size_t m, const int * a, const int * b)
{
  int * c = new int[n * m];
  sum(n, m, c, a, b);
}

void add(size_t n, size_t m, int * a, const int * b)
{
  sum(n, m, a, a, b);
}

void mul(int * c, const int * a, size_t n1, size_t m1, const int * b, size_t m2)
{
  for (size_t i = 0; i < n1; ++i)
  {
    for (size_t j = 0;  j < m2; ++j)
    {
      int res = 0;
      for (size_t k = 0; k < m1; ++k)
      {
        res += a[i * m1 + k] * b[k * m2 + j];
      }
      c[i*m2 + j] = res;
    }
  }
}

void sum_of_mul(size_t n, int * c, const int * a, const int * const * b, size_t s)
{
  for (size_t i = 0; i < s; ++i)
  {
    c = sum(n, n, c, b[i]);
  }
  mul(c, a, n, n, c, n);
}

int * sum_of_mul(size_t n, const int * a, const int * const * b, size_t s)
{
  int * c = new int[n];
  sum_of_mul(n, c, a, b, s);
  return c;
}

void mul_of_mul(size_t n, int * c, const int * a, const int * const * b, size_t s)
{
  for (size_t i = 0; i < n; ++i)
  {
    for (size_t j = 0; j < n; ++j)
    {
      if (i == j)
      {
        c[i*n + j] = 1;
      }
      else
      {
        c[i*n + j] = 0;
      }
    }
  }

  for (size_t i = 0; i < s; ++i)
  {
    int * t = new int[n];
    mul(t, a, n, n, b[i], n);
    mul(c, t, n, n, c, n);
    delete[] t;
  }

}

int * mul_of_mul(size_t n, const int * a, const int * const * b, size_t s)
{
  int * c = new int[n];
  mul_of_mul(n, c, a, b, s);
  return c;
}



void mul_of_sum(size_t n, int * c, const int * a, const int * const * b, size_t s)
{
  for (size_t i = 0; i < n; ++i)
  {
    for (size_t j = 0; j < n; ++j)
    {
      if (i == j)
      {
        c[i*n + j] = 1;
      }
      else
      {
        c[i*n + j] = 0;
      }
    }
  }

  for (size_t i = 0; i < s; ++i)
  {
    int * t = new int[n];
    sum(n, n, t, a, b[i]);
    mul(c, t, n, n, c, n);
    delete[] t;
  }

}

int * mul_of_sum(size_t n, const int * a, const int * const * b, size_t s)
{
  int * c = new int[n];
  mul_of_sum(n, c, a, b, s);
  return c;
}