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
ostream& operator<<(ostream& os, const std::vector<T*>& a) {
  for (const auto x : a) os << *x << " ";
  return os;
}

int* _B(int value) {
  static std::list<int> v;
  v.push_back(value);
  return &v.back();
}

int main()
{
  vector<int*> v{_B(1),  _B(2),  _B(3),  _B(4),  _B(5),  _B(6),  _B(7),  _B(8)};
  cout << "vector v:" << endl;
  cout << v << endl;

  vector<int*> tmp = v;
  cout << "apply move from v:" << endl;
  i1::null_terminated_ptr_vector<int> a = std::move(v);
  cout << a << endl;
  cout << "size of v: " << v.size() << endl;

  cout << "restored v" << endl;
  v = tmp;
  cout << "apply move constructor from v:" << endl;
  i1::null_terminated_ptr_vector<int> b(std::move(v));
  cout << b << endl;
  cout << "size of v: " << v.size() << endl;

  return 0;
}
