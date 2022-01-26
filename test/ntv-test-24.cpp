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
  i1::null_terminated_ptr_vector<int> v;
  cout << "assign 3 items 5 to v:" << endl;
  v.assign(3, x+5);
  cout << "vector v:" << endl;
  cout << v << endl;

  i1::null_terminated_ptr_vector<int> a{x+12, x+21};
  cout << "vector a:" << endl;
  cout << a << endl;
  cout << "assign initializer list to a:" << endl;
  a.assign({x+1, x+2, x+3, x+4, x+5, x+6, x+7, x+8});
  cout << "vector a:" << endl;
  cout << a << endl;

  cout << "assign a to list:" << endl;
  list<int*> l{x+11, x+12};
  l.assign(a.begin(), a.end());
  cout << "vector a:" << endl;
  cout << a << endl;
  cout << static_cast<i1::null_terminated_ptr_vector<int>::_Base>(a) << endl;
  cout << "list l:" << endl;
  cout << l << endl;

  return 0;
}
