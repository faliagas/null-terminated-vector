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
  for (const auto& x : a) os << x << " ";
  return os;
}

struct B {
  int i;
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
  const vector<int> v{45, 32, 6, 9};
  cout << "std::vector v:" << endl;
  cout << v << endl;
  cout << "create o from std::vector v:" << endl;
  const i1::null_terminated_vector<B> o{v.begin(), v.end()};
  cout << "vector o:" << endl;
  cout << o << endl;
  auto it = o.begin();
  ++it; ++it;
  cout << "create a from first 2 elements of vector o:" << endl;
  i1::null_terminated_vector<B> a{o.begin(), it};
  // i1::null_terminated_vector<B> a{o.begin(), o.begin()+3};
  // i1::null_terminated_vector<B> a{o.begin(), o.end()};

  cout << "vector a:" << endl;
  cout << "size = " << a.size() << endl;
  cout << a << endl;

  return 0;
}
