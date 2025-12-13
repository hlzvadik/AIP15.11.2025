#include <iostream>

struct Stud
{
  const char* fst;
  const char* snd;
  int year;
  int dep;
};

struct Subj
{
  const char* name;
  size_t people, classes;
  const Stud* const * studs;
  const size_t* visited;
};

const Stud** copy(const Stud* const* src, const Stud** dest, size_t k)
{
  for (size_t i = 0; i < k; ++i)
  {
    dest[i] = src[i];
  }
  return dest + k;
}

bool contains(const Stud* const* studs, size_t k, const Stud* s)
{
  for (size_t i = 0; i < k; ++i)
  {
    if (studs[i] == s)
    {
      return true;
    }
  }
  return false;
}

const Stud** stud_union(size_t& r, const Stud * const* st1, size_t k1, const Stud * const* st2, size_t k2)
{
  const Stud** uni = new const Stud*[k1+ k2];
  size_t count = 0;
  copy(st1, uni, k1);
  count += k1;
  for (size_t i = 0; i < k2; ++i)
  {
    if (!contains(uni, count, st2[i]))
    {
      uni[count++] = st2[i];
    }
  }

  try
  {
    const Stud** tmp = new const Stud*[count];
    copy(uni, tmp, count);
    delete[] uni;
    uni = tmp;
  }
  catch(const std::exception& e)
  {
    delete[] uni;
    throw;
  }
  
  r = count;
  return uni;
}

const Stud ** stud_union(size_t& r, const Subj& s1, const Subj& s2)
{
  return stud_union(r, s1.studs, s1.people, s2.studs, s2.people);
}

const Stud** stud_union(size_t& r, const Subj* ss, size_t k)
{
  if (!k)
  {
    r = 0;
    return nullptr;
  }
  else if (k == 1)
  {
    const Stud** uni = new const Stud* [ss[0].people];
    copy(ss[0].studs, uni, ss[0].people);
    return uni;
  }
  size_t count = 0;
  const Stud** uni = stud_union(count, ss[0], ss[1]);
  for (size_t i = 2; i < k; ++i)
  {
    try
    {
      size_t tmp_count = 0;
      const Stud** tmp = stud_union(tmp_count, uni, count, ss[i].studs, ss[i].people);
      delete[] uni;
      count = tmp_count;
      uni = tmp;
    }
    catch(const std::exception& e)
    {
      delete[] uni;
      throw;
    }
  }
}

int main()
{

}