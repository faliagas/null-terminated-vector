#include <iostream>
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

int main()
{
  int x[]{ 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
          10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
          20, 21, 22, 23, 24, 25};
  int y[]{123, -74, 512, 32, 244, -6, 992};
  i1::null_terminated_ptr_vector<int> a{x+1, x+2, x+3, x+4, x+5, x+6, x+7, x+8};
  i1::null_terminated_ptr_vector<int> b{y+1, y+2, y+3};

  cout << "vector a:" << endl;
  cout << a << endl;
  cout << "vector b:" << endl;
  cout << b << endl;

  a.swap(b);
  cout << "after swap:" << endl;
  cout << "vector a:" << endl;
  cout << a << endl;
  cout << "vector b:" << endl;
  cout << b << endl;

  return 0;
}
