#include <iostream>

void sum(size_t n, size_t m, int * c, const int * a, const int * b);
int * sum(size_t n, size_t m, const int * a, const int * b);
void add(size_t n, size_t m, const int * a, const int * b);
void mul(int * c, const int * a, size_t n1, size_t m1, const int * b, size_t m2);

int main()
{

}

void sum(size_t n, size_t m, int * c, const int * a, const int * b)
{
  for (size_t i = 0; i < n; ++i)
  {
    for (size_t j = 0; j < m; ++j)
    {
      c[i*m + j] = a[i*m + j] + b[i*m + j];
    }
  }
}

int * sum(size_t n, size_t m, const int * a, const int * b)
{
  int * c = new int[n*m];
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
    for (size_t j = 0;  j<m2; ++j)
    {
      int res = 0;
      for (size_t k = 0; k < m1; ++k)
      {
        res += a[i*m1 + k]*b[k*m2 + j];
      }
      c[i*m2 + j] = res;
    }
  }
}