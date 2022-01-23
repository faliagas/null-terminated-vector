#include <iostream>
#include <list>
#include "nullTerminatedVector.hpp"

using namespace std;

template<typename T>
ostream& operator<<(ostream& os, const i1::null_terminated_vector<T>& a) {
  for (const auto& x : a) os << x << " ";
  return os;
}

template<typename T>
ostream& operator<<(ostream& os, const std::vector<T>& a) {
  for (const auto& x : a) os << x << " ";
  return os;
}

template<typename T>
ostream& operator<<(ostream& os, const std::list<T>& a) {
  for (const auto& x : a) os << x << " ";
  return os;
}

struct B {
  int i;
  B() : i() {}
  B(int n) : i(n) {}
  static B null_terminator() noexcept {return B{-1000000};}
  bool is_null() const noexcept {return i == null_terminator().i; }
  B& operator=(int n) noexcept { i = n; return *this; }
};

ostream& operator<<(ostream& os, const B& b) {
  os << b.i;
  return os;
}

int main()
{
  i1::null_terminated_vector<B> v{1, 2, 3, 4, 5, 6, 7, 8};
  i1::null_terminated_vector<B> a{12, 21};
  cout << "vector v:" << endl;
  cout << v << endl;
  cout << "vector a:" << endl;
  cout << a << endl;

  cout << "apply move to a:" << endl;
  a = std::move(v);
  cout << "vector v:" << endl;
  cout << v << endl;
  cout << "vector a:" << endl;
  cout << a << endl;

  list<B> l{101, 102, 103, 104, 105, 106, 107, 108};
  cout << "list l:" << endl;
  cout << l << endl;
  cout << "assign list to a:" << endl;
  a.assign(l.begin(), l.end());
  cout << "list l:" << endl;
  cout << l << endl;
  cout << "vector a:" << endl;
  cout << a << endl;

  cout << "assign last 5 items of a to vector v:" << endl;
  v.assign(a.begin()+3, a.end());
  cout << "vector a:" << endl;
  cout << a << endl;
  cout << "vector v:" << endl;
  cout << v << endl;

  return 0;
}
