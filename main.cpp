#include <iostream>

struct Ints
{
  ~Ints();
  Ints();
  Ints append(int i) const;
  Ints append(const Ints &) const;
  Ints(const Ints & w);
  Ints(Ints && w);
  Ints & operator=(const Ints & w);
  Ints & operator=(Ints &&);
  Ints(size_t k, int i);
  void set(size_t id, int i);
  size_t size();
  int get(size_t id) const;

private:
  int* d;
  size_t k;
};

struct p_t
{
  int x,y;
};

struct Points
{
  Points()=default;
  ~Points();
  Points(size_t k, p_t a);
  void set(size_t id, p_t a);
  p_t get(size_t id) const;
  size_t size() const;
  Points append(p_t a) const;
  Points append(const Points & w) const;

private:
  Ints data;
  Points(Ints && d);


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

Ints Ints::append(int i) const
{
  Ints r;
  r.d = new int[k+1];
  for (size_t j = 0; j < k; ++j)
  {
    r.d[j] = d[j];
  }
  r.d[k] = i;
  r.k = k + 1;
  return r;
}


Ints Ints::append(const Ints & ap) const
{
  Ints r;
  r.d = new int[k + ap.k];
  for (size_t j = 0; j < k; ++j)
  {
    r.d[j] = d[j];
  }
  for (size_t j = 0; j < ap.k; ++j)
  {
    r.d[k + j] = ap.d[j];
  }
  r.k = k + ap.k;
  return r;
}

void Ints::set(size_t id, int i)
{
  d[id] = i;
}

size_t Ints::size()
{
  return k;
}

int Ints::get(size_t id) const
{
  if (id >= k)
  {
    throw std::range_error("...");
  }
  return d[id];
}






Points::Points(size_t k, p_t a):
  data(k*2, a.x)
{
  for (size_t i = 0; i < k; ++i)
  {
    data.set(i*2 + 1, a.y);
  }
}


size_t Points::size() const
{
  return data.size()/2;
}

void Points::set(size_t id, p_t a)
{
  data.set(id*2, a.x);
  data.set(id*2, a.y);
}

p_t Points::get(size_t id) const
{
  p_t r{data.get(id*2), data.get(id*2 + 1)};
  return r;
}

Points Points::append(p_t a) const
{
  Ints delta(2,a.x);
  delta.set(1,a.y);
  delta=data.append(delta);

  return Points(std::move(delta));
}

Points::Points(Ints && d):
  data(std::move(d))
{}