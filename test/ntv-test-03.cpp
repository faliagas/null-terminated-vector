#include <iostream>
#include <algorithm>
#include "nullTerminatedVector.hpp"

using namespace std;

template<typename T>
ostream& operator<<(ostream& os, const i1::null_terminated_vector<T>& a) {
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
  i1::null_terminated_vector<B> a{45, 32, 6, 9};
  cout << "create a from std::initializer_list:" << endl;
  cout << "size = " << a.size() << endl;
  cout << "vector a:" << endl;
  cout << a << endl;
  cout << "using std::for_each to add 100 to each element of a:" << endl;
 // for (auto it = a.begin(); it; ++it) // OK
  for_each(a.begin(), a.end(), [](B& item){
    item.i += 100;
  });
  cout << "using for (:) to print vector a:" << endl;
  for (const auto& item : a)
    cout << item << " ";
  cout << endl;
  cout << "vector a:" << endl;
  cout << a << endl;

  return 0;
}
