#include <iostream>
#include "nullTerminatedVector.hpp"

using namespace std;

template<typename T>
ostream& operator<<(ostream& os, const i1::null_terminated_vector<T>& a) {
  for (const auto& x : a) os << x << " ";
  return os;
}

template<typename T>
ostream& operator<<(ostream& os, const std::vector<T>& a) {
  for (const auto x : a) os << x << " ";
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
  vector<B> v{1, 2, 3, 4, 5, 6, 7, 8};
  cout << "vector v:" << endl;
  cout << v << endl;

  vector<B> tmp = v;
  cout << "apply move from v:" << endl;
  i1::null_terminated_vector<B> a = std::move(v);
  cout << a << endl;
  cout << "size of v: " << v.size() << endl;

  cout << "restored v" << endl;
  v = tmp;
  cout << "apply move constructor from v:" << endl;
  i1::null_terminated_vector<B> b(std::move(v));
  cout << b << endl;
  cout << "size of v: " << v.size() << endl;

  #if 0
  #endif // 0

  return 0;
}
