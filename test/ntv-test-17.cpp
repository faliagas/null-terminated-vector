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

int* _B(int value) {
  static std::list<int> v;
  v.push_back(value);
  return &v.back();
}

int main()
{
  int x[]{ 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
          10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
          20, 21, 22, 23, 24, 25};
  cout << "create a from std::initializer_list:" << endl;
  i1::null_terminated_ptr_vector<int> a{x+1, x+2, x+3, x+4, x+5, x+6, x+7, x+8};

  cout << a << endl;
  const int e1{39};
  // a.insert(a.begin()+2, {e1});
  // a.insert(a.begin()+2, 39);
  a.insert(a.begin()+2, const_cast<int*>(&e1));
  cout << "after insert 39 at pos 2:" << endl;
  cout << a << endl;
  int e2 = -12;
  a.emplace(a.begin()+5, &e2);
  // a.emplace(a.begin()+5, _B(-12));
  cout << "after emplace -12 at pos 5:" << endl;
  cout << a << endl;

  return 0;
}
