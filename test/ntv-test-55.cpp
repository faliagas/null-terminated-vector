#include <iostream>
// #include <list>
#include "nullTerminatedIntVector.hpp"

using namespace std;

template<typename T>
ostream& operator<<(ostream& os, const i1::null_terminated_int_vector<T>& a) {
  for (const auto& x : a) os << x << " ";
  return os;
}

int main()
{
  i1::null_terminated_int_vector<long> a{1, 2, 3, 4, 5};
  cout << "vector a:" << endl;
  cout << a << endl;

  cout << "using at() to access element 2:" << endl;
  cout << a.at(2) << endl;
  cout << "using at() to modify element 3:" << endl;
  a.at(3) = 111;
  cout << a << endl;
  cout << "using at() to access element 5:" << endl;
  try {
    cout << a.at(5) << endl;
  }
  catch (exception& e) {
    cout << "this throws the following exception:" << endl;
    cout << e.what() << endl;
  }

  return 0;
}
