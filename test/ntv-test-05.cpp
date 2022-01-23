#include <iostream>
#include <iterator>
#include "nullTerminatedVector.hpp"

using namespace std;

template<typename T>
ostream& operator<<(ostream& os, const i1::null_terminated_vector<T>& a) {
  for (const auto& x : a) os << x << " ";
  return os;
}

struct B {
  int i;
  // B(int n) : i(n) {}
  static B null_terminator() noexcept {return B{-1000000};}
  bool is_null() const noexcept {return i == null_terminator().i; }
  B& operator=(int n) noexcept { i = n; return *this; }
  // B& operator=(B&& r) noexcept { std::swap(i, r.i); return *this; }
};

ostream& operator<<(ostream& os, const B& b) {
  os << b.i;
  return os;
}

int main()
{
  cout << "default constructor for vector a:" << endl;
  i1::null_terminated_vector<B> a;
  cout << "vector a:" << endl;
  cout << "size = " << a.size() << endl;
  for (const auto& i : a) {
    cout << i << endl;
  }

  cout << "pushing 5 elements onto a:" << endl;
  for (int i = 0; i < 5; ++i) {
    // const B b{i + 10};
    // a.push_back(b);
    a.push_back(B{i + 10});
  }

  cout << "vector a:" << endl;
  cout << "size = " << a.size() << endl;
  cout << a << endl;
  cout << "front = " << a.front() << endl;
  cout << "back = " << a.back() << endl;

  return 0;
}
