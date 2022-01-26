#include <iostream>
#include "nullTerminatedIntVector.hpp"

using namespace std;

template<typename T>
ostream& operator<<(ostream& os, const i1::null_terminated_int_vector<T>& a) {
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
  i1::null_terminated_int_vector<int> a{1, 2, 3, 4, 5, 6, 7, 8};

  cout << "original vector:" << endl;
  cout << a << endl;
  a.clear();
  cout << "after clear:" << endl;
  cout << a << endl;
  cout << "size = " << a.size() << endl;
  a.push_back(83);
  cout << "after push_back 83:" << endl;
  cout << a << endl;
  cout << "an exception will be thrown:" << endl;
  a.clear();
  a[0] = 1001;

  return 0;
}
