#include <iostream>
#include <list>
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

template<typename T>
ostream& operator<<(ostream& os, const std::list<T>& a) {
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
  i1::null_terminated_vector<B> a{1, 2, 3, 4, 5};
  cout << "vector a:" << endl;
  cout << a << endl;

  cout << "using data() to access element 2:" << endl;
  B* p = a.data();
  cout << p[2] << endl;
  cout << "using data() to modify element 3:" << endl;
  p[3] = 111;
  cout << a << endl;
  cout << "using data() to access elements 5, 6:" << endl;
  try {
    cout << p[5] << endl;
    cout << p[6] << endl;
  }
  catch (exception& e) {
    cout << "this throws the following exception:" << endl;
    cout << e.what() << endl;
  }

  cout << "using resize(8):" << endl;
  a.resize(8);
  cout << a << endl;

  cout << "using resize(5):" << endl;
  a.resize(5);
  cout << a << endl;

  cout << "resize(8) with value 44:" << endl;
  a.resize(8, B(44));
  cout << a << endl;

  // cout << "erase from 6 to end:" << endl;
  // a.erase(a.begin()+6, a.end());
  cout << "erase from 6 to 8:" << endl;
  a.erase(a.begin()+6, a.begin()+8);
  cout << a << endl;

  cout << "clear:" << endl;
  a.clear();
  cout << "size of a: " << a.size() << endl;

  return 0;
}
