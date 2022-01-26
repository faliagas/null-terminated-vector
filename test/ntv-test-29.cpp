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
  int x[]{ 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
          10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
          20, 21, 22, 23, 24, 25};
  i1::null_terminated_vector<B> a(x+1, x+8);
  cout << "apply copy constructor for b:" << endl;
  i1::null_terminated_vector<B> b(a);
  cout << "vector a:" << endl;
  cout << a << endl;
  cout << "vector b:" << endl;
  cout << b << endl;

  cout << "apply move constructor for c:" << endl;
  i1::null_terminated_vector<B> c(std::move(a));
  cout << "vector a:" << endl;
  cout << "size of a: " << a.size() << endl;
  cout << a << endl;
  cout << "vector c:" << endl;
  cout << c << endl;

  return 0;
}
