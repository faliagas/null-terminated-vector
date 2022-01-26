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
ostream& operator<<(ostream& os, const std::list<T*>& a) {
  for (const auto x : a) os << *x << " ";
  return os;
}

template<typename T>
ostream& operator<<(ostream& os, const std::list<T>& a) {
  for (const auto& x : a) os << x << " ";
  return os;
}

int* _B(int value) {
  static std::list<int> v;
  v.push_back(value);
  return &v.back();
}

int main()
{
  int x[]{1, 2, 3, 4, 5};
  i1::null_terminated_ptr_vector<int> a{x, x+1, x+2, x+3, x+4};
  cout << "vector a:" << endl;
  cout << a << endl;

  list<int*> l{_B(802), _B(803), _B(804), };
  cout << "list l:" << endl;
  cout << l << endl;

  cout << "insert list at pos 2 of a:" << endl;
  a.insert(a.begin()+2, l.begin(), l.end());
  cout << "vector a:" << endl;
  cout << a << endl;

  cout << "remove penultimate element:" << endl;
  a.erase(a.end()-2);
  cout << "vector a:" << endl;
  cout << a << endl;
  cout << "back of a: " << *a.back() << endl;

  cout << "declare const vector b initialized from list l:" << endl;
  const i1::null_terminated_ptr_vector<int> b(l.begin(), l.end());
  cout << "vector b:" << endl;
  cout << b << endl;
  cout << "front of b: " << *b.front() << endl;
  cout << "back of b: " << *b.back() << endl;

  cout << "declare vector c initialized with 7 copies of 125:" << endl;
  i1::null_terminated_ptr_vector<int> c(7, _B(125));
  cout << "vector c:" << endl;
  cout << c << endl;

  cout << "append list l to vector c:" << endl;
  c.insert(c.end(), l.begin(), l.end());
  cout << "vector c:" << endl;
  cout << c << endl;

  cout << "append a to list l:" << endl;
  l.insert(l.end(), a.begin(), a.end());
  cout << "list l:" << endl;
  cout << l << endl;

  cout << "assign b to a:" << endl;
  a.assign(b.begin(), b.end());
  cout << "vector a:" << endl;
  cout << a << endl;

  cout << "move a to c:" << endl;
  c = std::move(a);
  cout << "vector a:" << endl;
  cout << "size of a:" << a.size() << endl;
  cout << a << endl;
  cout << "vector c:" << endl;
  cout << c << endl;

  cout << "create vector d on heap:" << endl;
  i1::null_terminated_ptr_vector<int> *d =
      new i1::null_terminated_ptr_vector<int>{_B(99), _B(-2), _B(101), _B(64)};
  cout << "vector d:" << endl;
  cout << *d << endl;

  cout << "delete d... ";
  delete d;
  cout << "OK!" << endl;

  return 0;
}
