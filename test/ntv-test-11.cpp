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
  cout << "apply copy constructor:" << endl;
  i1::null_terminated_vector<B> b(a);

  cout << "vector a:" << endl;
  cout << a << endl;
  cout << "vector b:" << endl;
  cout << b << endl;

  cout << "apply copy initializer list:" << endl;
  i1::null_terminated_vector<B> c{33, 44, 55};
  cout << "vector c:" << endl;
  cout << c << endl;

  cout << "apply copy b = c:" << endl;
  b = c;
  cout << "vector b:" << endl;
  cout << b << endl;
  cout << "vector c:" << endl;
  cout << c << endl;

  i1::null_terminated_vector<B> d{333};
  cout << "vector d:" << endl;
  cout << d << endl;
  cout << "apply move a = d:" << endl;
  a = std::move(d);
  cout << "vector a:" << endl;
  cout << a << endl;
  cout << "vector d:" << endl;
  cout << "size of d: " << d.size() << endl;
  cout << d << endl;

  return 0;
}
