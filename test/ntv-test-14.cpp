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
  i1::null_terminated_vector<B> v;
  cout << "assign 3 items 25 to v:" << endl;
  v.assign(3, 25);
  cout << "vector v:" << endl;
  cout << v << endl;

  i1::null_terminated_vector<B> a{12, 21};
  cout << "vector a:" << endl;
  cout << a << endl;
  cout << "assign initializer list to a:" << endl;
  a.assign({1, 2, 3, 4, 5, 6, 7, 8});
  cout << "vector a:" << endl;
  cout << a << endl;

  cout << "assign a to list:" << endl;
  list<B> l{101, 102};
  l.assign(a.begin(), a.end());
  cout << "vector a:" << endl;
  cout << a << endl;
  cout << "list l:" << endl;
  cout << l << endl;

  return 0;
}
