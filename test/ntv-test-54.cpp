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
  i1::null_terminated_int_vector<int> v;
  cout << "assign 3 items 25 to v:" << endl;
  v.assign(3, 25);
  cout << "vector v:" << endl;
  cout << v << endl;

  i1::null_terminated_int_vector<int> a{12, 21};
  cout << "vector a:" << endl;
  cout << a << endl;
  cout << "assign initializer list to a:" << endl;
  a.assign({1, 2, 3, 4, 5, 6, 7, 8});
  cout << "vector a:" << endl;
  cout << a << endl;

  cout << "assign a to list:" << endl;
  list<int> l{101, 102};
  l.assign(a.begin(), a.end());
  cout << "vector a:" << endl;
  cout << a << endl;
  cout << "list l:" << endl;
  cout << l << endl;

  return 0;
}
