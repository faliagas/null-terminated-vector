#include <iostream>
#include <list>
#include "nullTerminatedIntVector.hpp"

using namespace std;

template<typename T>
ostream& operator<<(ostream& os, const i1::null_terminated_int_vector<T>& a) {
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

int main()
{
  i1::null_terminated_int_vector<int> v{1, 2, 3, 4, 5, 6, 7, 8};
  i1::null_terminated_int_vector<int> a{12, 21};
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

  list<int> l{101, 102, 103, 104, 105, 106, 107, 108};
  cout << "list l:" << endl;
  cout << l << endl;
  cout << "assign list to a:" << endl;
  a.assign(l.begin(), l.end());
  cout << "list l:" << endl;
  cout << l << endl;
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
