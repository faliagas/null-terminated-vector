#include <iostream>
#include <list>
#include "nullTerminatedPtrVector.hpp"

using namespace std;

template<typename T>
ostream& operator<<(ostream& os, const i1::null_terminated_vector<T>& a) {
  for (const auto& x : a) os << x << " ";
  return os;
}

template<typename T>
ostream& operator<<(ostream& os, const i1::null_terminated_ptr_vector<T>& a) {
  for (const auto& x : a) os << *(const T*)x << " ";
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

int main()
{
  int x[]{ 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
          10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
          20, 21, 22, 23, 24, 25};
  i1::null_terminated_ptr_vector<int> v{x+1, x+2, x+3, x+4, x+5, x+6, x+7, x+8};
  i1::null_terminated_ptr_vector<int> a{x+12, x+21};
  cout << "vector v:" << endl;
  cout << v << endl;
  cout << "vector a:" << endl;
  cout << a << endl;

  cout << "apply move to a:" << endl;
  a = std::move(v);
  cout << "vector v:" << endl;
  cout << v << endl;
  cout << "vector a:" << endl;
  cout << a << endl;

  list<int*> l{x+11, x+12, x+13, x+14, x+15, x+16, x+17, x+18};
  cout << "list l:" << endl;
  for (const auto p : l) cout << *p << " ";
  cout << endl;
  cout << "assign list to a:" << endl;
  a.assign(l.begin(), l.end());
  cout << "list l:" << endl;
  for (const auto p : l) cout << *p << " ";
  cout << endl;
  cout << "vector a:" << endl;
  cout << a << endl;

  cout << "assign last 5 items of a to vector v:" << endl;
  v.assign(a.begin()+3, a.end());
  cout << "vector a:" << endl;
  cout << a << endl;
  cout << "vector v:" << endl;
  cout << v << endl;

  return 0;
}
