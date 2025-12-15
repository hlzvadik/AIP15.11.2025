#include <iostream>
using s_t = size_t;
struct Stud
{
  const char* fst;
  const char* snd;
  int year;
  int dep;
};

struct Subj
{
  const char* name;       // name of class
  size_t people, classes; // count of people and classes
  const Stud* const* studs;
  const size_t* visited;
};
struct r_t
{
  s_t n, q;
};

const Subj** copy(const Subj* const* src, const Subj** dest, s_t k)
{
  for (s_t i = 0; i < k; ++i) {
    dest[i] = src[i];
  }
  return dest + k;
}
void cut(const Subj*** s, s_t k)
{
  const Subj** tmp = new const Subj*[k];
  copy(*s, tmp, k);
  delete[] *s;
  (*s) = tmp;
  throw;
}
bool is_mag(const Stud* s)
{
  return s->year > 4 && s->year < 7;
}
const Subj** popular_mag(s_t& r, const Subj* const* ss, s_t k, r_t rv)
{
  s_t count = 0;
  const Subj** res = new const Subj*[k];
  for (s_t i = 0; i < k; ++i) {
    bool ok = true;
    const Subj* tmp = ss[i];
    for (s_t j = 0; j < tmp->people; ++j) {
      if (tmp->visited[j] * rv.q <= rv.n * tmp->classes && is_mag(tmp->studs[j])) {
        ok = false;
        break;
      }
    }
    if (ok) {
      res[count++] = tmp;
    }
  }
  try {
    cut(&res, count);
  } catch (...) {
    throw;
  }
  return res;
}
const Stud** copy(const Stud* const* src, const Stud** dest, s_t k)
{
  for (s_t i = 0; i < k; ++i) {
    dest[i] = src[i];
  }
  return dest + k;
}
void cut(const Stud*** s, s_t k)
{
  const Stud** tmp = new const Stud*[k];
  copy(*s, tmp, k);
  delete[] *s;
  (*s) = tmp;
  throw;
}
bool contain(const Stud* const* studs, const Stud* s, s_t k)
{
  bool result = false;
  for (s_t i = 0; (i < k) && !result; ++i) {
    result = result || studs[i] == s;
  }
  return result;
}
const Stud** stud_union(s_t& r, const Stud* const* st1, s_t k1, const Stud* const* st2, s_t k2)
{
  const Stud** uni = new const Stud*[k1 + k2];
  s_t count = 0;
  copy(st1, uni, k1);
  count += k1;

  for (s_t i = 0; i < k2; ++i) {
    if (!(contain(uni, st2[i], count))) {
      uni[count++] = st2[i];
    }
    uni[count++] = st2[i];
  }

  // try {
  //   const Stud** tmp=new const Stud*[count];
  //   copy(tmp,uni,count);
  //   delete [] uni;
  //   uni=tmp;
  // } catch (...) {
  //   delete [] uni;
  //   throw;
  // }
  try {
    cut(&uni, count);
  } catch (...) {
    delete[] uni;
    throw;
  }
  r = count;
  return uni;
}

const Stud** stud_union(s_t& r, const Subj& s1, const Subj& s2)
{
  return stud_union(r, s1.studs, s1.people, s2.studs, s2.people);
}

const Stud** stud_union(s_t& r, const Subj* ss, s_t k)
{
  if (!k) {
    r = 0;
    return nullptr;
  } else if (k == 1) {
    const Stud** u = new const Stud*[ss[0].people];
    copy(ss[0].studs, u, ss[0].people);
  }
  s_t count = 0;
  const Stud** uni = stud_union(count, ss[0], ss[1]);
  for (s_t i = 2; i < k; ++i) {
    try {
      s_t tmp_count = 0;
      const Stud** tmp = stud_union(tmp_count, uni, count, ss[i].studs, ss[i].people);
      delete[] uni;
      count = tmp_count;
      uni = tmp;
    } catch (...) {
      delete[] uni;
      throw;
    }
  }
  r = count;
  return uni;
}
const Stud** filter(size_t& r, const Stud* const* studs, s_t k, bool (*cond)(const Stud*))
{
  const Stud** f = new const Stud*[k];
  s_t count = 0;
  for (s_t i = 0; i < k; ++i) {
    if (cond(studs[i])) {
      f[count++] = studs[i];
    }
  }
  try {
    cut(&f, count);
  } catch (...) {
    delete[] f;
    throw;
  }
  return f;
}
bool is_bachalor(const Stud* s)
{
  return s->year < 5;
}
const Stud** stud_union_bach(size_t& r, const Subj* ss, size_t k)
{
  size_t count = 0;
  const Stud** uni = stud_union(count, ss, k);
  try {
    s_t tmp_count = 0;
    const Stud** tmp = filter(tmp_count, uni, count, is_bachalor);
    delete[] uni;
    uni = tmp;
    count = tmp_count;
  } catch (...) {
    delete[] uni;
    throw;
  }
  r = count;
  return uni;
}
bool is_year_y(const Stud* stud, int y)
{
  return stud->year == y;
}
template <s_t Y> bool is_year_Y(const Stud* stud)
{
  return stud->year == Y;
}
bool (*is_year_y(int y))(const Stud* stud)
{
  switch (y) {
  case 1:
    return is_year_Y<1>;
  case 2:
    return is_year_Y<2>;
  case 3:
    return is_year_Y<3>;
  case 4:
    return is_year_Y<4>;
  case 5:
    return is_year_Y<5>;
  case 6:
    return is_year_Y<6>;
  default:
    throw std::logic_error("bad year");
  }
}
const Stud** stud_union_y(size_t& r, const Subj* ss, size_t k, int y)
{
  size_t count = 0;
  const Stud** uni = stud_union(count, ss, k);
  try {
    s_t tmp_count = 0;
    const Stud** tmp = filter(tmp_count, uni, count, is_bachalor);
    delete[] uni;
    uni = tmp;
    count = tmp_count;
  } catch (...) {
    delete[] uni;
    throw;
  }
  r = count;
  return uni;
}
int main()
{}