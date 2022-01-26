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
  int z[]{ 83,  1001};
  i1::null_terminated_ptr_vector<int> a{x+1, x+2, x+3, x+4, x+5, x+6, x+7, x+8};

  cout << "original vector:" << endl;
  cout << a << endl;
  a.clear();
  cout << "after clear:" << endl;
  cout << a << endl;
  cout << "size = " << a.size() << endl;
  a.push_back(z);
  cout << "after push_back 83:" << endl;
  cout << a << endl;
  cout << "an exception will be thrown:" << endl;
  a.clear();
  a[0] = z+1;

  return 0;
}
