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
  static constexpr B null_terminator() noexcept {return B{-1000000};}
  bool is_null() const noexcept {return i == null_terminator().i; }
  B& operator=(int n) noexcept { i = n; return *this; }
};

ostream& operator<<(ostream& os, const B& b) {
  os << b.i;
  return os;
}

int main()
{
  i1::null_terminated_vector<B> a(10);
  cout << "create vector a with 10 elements:" << endl;
  cout << "vector a:" << endl;
  cout << a << endl;

  cout << "assign value to each element:" << endl;
  for (size_t i = 0; i < 10; ++i)
    a[i] = B{(int)i};
  cout << a << endl;
  cout << "first 5 elements of vector a:" << endl;
  for (size_t i = 0; i < 5; ++i)
    cout << a[i] << " ";
  cout << endl;
  if (!(4 < a.size()))
  {
    cout << "assertion failed, " << "line " << __LINE__-2 << endl;
    return 3;
  };
  cout << "apply iterator to print vector a:" << endl;
  // for (auto it = a.begin(); it != a.end(); ++it) // OK
  // for (auto it = a.begin(); it != a.begin()+5; ++it) // OK
  // for (auto it = a.begin(); it != a.begin()+10; ++it) // OK
  for (auto it = a.begin(); it; ++it) // OK
    cout << *it << " ";
  cout << endl;

  return 0;
}
