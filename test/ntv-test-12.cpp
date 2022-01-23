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
  std::vector<B> v{1, 2, 3, 4, 5, 6, 7, 8};
  cout << "std::vector v:" << endl;
  cout << v << endl;

  i1::null_terminated_vector<B> a;
  cout << "apply copy from std::vector:" << endl;
  a = std::move(v);

  cout << "size of std::vector v: " << v.size() << endl;
  cout << "vector a:" << endl;
  cout << a << endl;

  v.push_back(123);
  v.push_back(-74);
  v.push_back(512);
  cout << "std::vector v:" << endl;
  cout << v << endl;

  i1::null_terminated_vector<B> b;
  b.push_back(32);
  b.push_back(244);
  cout << "vector b:" << endl;
  cout << b << endl;

  cout << "apply copy to b from std::vector v:" << endl;
  b = std::move(v);

  cout << "size of std::vector v: " << v.size() << endl;
  cout << "vector b:" << endl;
  cout << b << endl;

  cout << "convert to std::vector:" << endl;
  b.convert_to(v);
  cout << "size of vector b: " << b.size() << endl;
  cout << "vector v:" << endl;
  cout << v << endl;
  cout << "pushing elements -6 and 992 to std::vector:" << endl;
  v.push_back(-6);
  v.push_back(992);
  cout << "vector v:" << endl;
  cout << v << endl;

  cout << "apply copy to b from std::vector v:" << endl;
  b = std::move(v);
  cout << "size of std::vector v: " << v.size() << endl;
  cout << "vector b:" << endl;
  cout << b << endl;

  return 0;
}
