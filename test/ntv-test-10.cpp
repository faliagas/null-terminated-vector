#include <iostream>
#include "nullTerminatedVector.hpp"

using namespace std;

template<typename T>
ostream& operator<<(ostream& os, const i1::null_terminated_vector<T>& a) {
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
  i1::null_terminated_vector<B> a{1, 2, 3, 4, 5, 6, 7, 8};
  i1::null_terminated_vector<B> b{101, 102, 103};

  cout << "vector a:" << endl;
  cout << a << endl;
  cout << "vector b:" << endl;
  cout << b << endl;

  a.swap(b);
  cout << "after swap:" << endl;
  cout << "vector a:" << endl;
  cout << a << endl;
  cout << "vector b:" << endl;
  cout << b << endl;

  return 0;
}
