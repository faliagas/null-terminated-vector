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
  // for (const auto& x : a) os << *x.__ptr << " ";
  return os;
}

int* _B(int value) {
  static std::list<int> v;
  v.push_back(value);
  return &v.back();
}

int main()
{
  cout << "default constructor for vector a:" << endl;
  i1::null_terminated_ptr_vector<int> a;

  cout << "push 5 elements:" << endl;
  for (int i = 0; i < 5; ++i) {
    int* const p = _B(i + 10);
    a.push_back(p);
  }

  cout << "vector a:" << endl;
  cout << "size = " << a.size() << endl;
  cout << a << endl;
  cout << "front = " << *a.front() << " (" << a.front() << ")" << endl;
  cout << "back = " << *a.back() << " (" << a.back() << ")" << endl;
  cout << "pop 1 element:" << endl;
  a.pop_back();
  cout << "vector a:" << endl;
  cout << "size = " << a.size() << endl;
  cout << a << endl;
  cout << "push move 887:" << endl;
  a.push_back(_B(887));
  cout << "vector a:" << endl;
  cout << "size = " << a.size() << endl;
  cout << a << endl;

  return 0;
}
