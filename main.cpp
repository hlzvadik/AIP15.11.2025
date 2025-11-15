#include <iostream>

void sum(size_t n, size_t m, int * c, const int * a, const int * b);
int * sum(size_t n, size_t m, const int * a, const int * b);
void add(size_t n, size_t m, const int * a, const int * b);

int main()
{

}

void sum(size_t n, size_t m, int * c, const int * a, const int * b)
{
  for (size_t i = 0; i < n; ++i)
  {
    for (size_t j = 0; j < m; ++j)
    {
      c[i][j] = a[i][j] + b[i][j];
    }
  }
}

int * sum(size_t n, size_t m, const int * a, const int * b)
{
  int * c = new int[n*m];
  sum(n, m, c, a, b);
}

void add(size_t n, size_t m, const int * a, const int * b)
{
  sum(n, m, a, a, b);
}