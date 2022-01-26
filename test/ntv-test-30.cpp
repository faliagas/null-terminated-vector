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
  int* px[]{x+ 0, x+ 1, x+ 2, x+ 3, x+ 4, x+ 5, x+ 6, x+ 7, x+ 8, x+ 9,
            x+10, x+11, x+12, x+13, x+14, x+15, x+16, x+17, x+18, x+19,
            x+20, x+21, x+22, x+23, x+24, x+25};
  i1::null_terminated_ptr_vector<int> a(px+1, px+8);
  cout << "apply copy constructor for b:" << endl;
  i1::null_terminated_ptr_vector<int> b(a);
  cout << "vector a:" << endl;
  cout << a << endl;
  cout << "vector b:" << endl;
  cout << b << endl;

  cout << "apply move constructor for c:" << endl;
  i1::null_terminated_ptr_vector<int> c(std::move(a));
  cout << "vector a:" << endl;
  cout << "size of a:" << a.size() << endl;
  cout << a << endl;
  cout << "vector c:" << endl;
  cout << c << endl;

  return 0;
}
