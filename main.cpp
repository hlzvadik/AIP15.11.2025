#include <iostream>

struct Stud
{
  const char * fst;
  const char * snd;
  int year;
  int dep;
};

size_t count_year(const Stud * const * studs, size_t k, int y)
{
  size_t r = 0;
  for (size_t i = 0, i < k, ++i)
  {
    const Stud * stud_i = studs[i];
    int stud_y = stud_i->year;
    r += (stud_y == y) ? 1 : 0;
  }
  return r;
}

const Stud ** stud_dep(const Stud * const * studs, size_t k, int dep, size_t & found)
{
  size_t dep_count = 0;
  for (size_t i = 0; i < k; ++i)
  {
    const Stud * stud_i = studs[i];
    dep_count += (stud_i->dep == dep);
  }
  const Stud ** r = new const Stud*[dep_count];
  size_t id = 0;
  for (size_t i = 0; i < k; ++i)
  {
    const Stud * stud_i = studs[i];
    if (stud_i->dep == dep)
    {
      r[id] = stud_i;
      ++id;
    }
  }
  return r;
}

int main()
{

}