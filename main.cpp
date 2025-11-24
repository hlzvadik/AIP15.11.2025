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

int main()
{

}