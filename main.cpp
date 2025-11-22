#include <iostream>

struct Ints
{
  ~Ints();
  Ints();
  Ints(const Ints & w);
  Ints(Ints && w);
  Ints & operator=(const Ints & w);
  Ints & operator=(Ints &&);

private:
  int* d;
  size_t k;
};

int main()
{

}

Ints::Ints():
  d(nullptr),
  k(0)
{}

Ints::Ints(const Ints & w):
  d(w.k ? new int[w.k] : nullptr),
  k(w.k)
{
  for (size_t i = 0; i < w.k; ++ i)
  {
    d[i] = w.d[i];
  }
}

Ints & Ints::operator=(const Ints & w)
{
  int * r = nullptr;
  if (w.k)
  {
    r = new int[w.k];
    for (size_t i = 0; i < w.k; ++ i)
    {
      d[i] = w.d[i];
    }
    delete[] d;
    d = r;
    k = w.k;
    return *this;
  }
}

Ints & Ints::operator=(Ints && w)
{
  if (this == &w)
  {
    return *this;
  }
  delete[] d;
  d = w.d;
  k = w.k;
  w.d = nullptr;
  return *this;
}