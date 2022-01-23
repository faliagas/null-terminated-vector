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
  // vector<B> v{B{45}, B{32}, B{6}, B{9}};
  vector<B> v{45, 32, 6, 9};
  cout << "std::vector v:" << endl;
  cout << v << endl;
  cout << "create a from std::vector v:" << endl;
  i1::null_terminated_vector<B> a(v.begin(), v.end());
  cout << "vector a:" << endl;
  cout << a << endl;

  cout << "size of a = " << a.size() << endl;
 // for (auto it = a.begin(); it; ++it) // OK
   // cout << *it << " ";
  cout << "using for (:) to print vector a:" << endl;
  for (const auto& item : a)
    cout << item << " ";
  cout << endl;

  return 0;
}
