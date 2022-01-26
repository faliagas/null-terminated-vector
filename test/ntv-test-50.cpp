#include <iostream>
#include "nullTerminatedIntVector.hpp"

using namespace std;

template<typename T>
ostream& operator<<(ostream& os, const i1::null_terminated_int_vector<T>& a) {
  for (const auto& x : a) os << x << " ";
  return os;
}

int main()
{
  i1::null_terminated_int_vector<int> a{1, 2, 3, 4, 5, 6, 7, 8};
  i1::null_terminated_int_vector<int> b{101, 102, 103};

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
