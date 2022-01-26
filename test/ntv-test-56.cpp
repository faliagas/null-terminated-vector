#include <iostream>
#include "nullTerminatedIntVector.hpp"

using namespace std;

template<typename T>
ostream& operator<<(ostream& os, const i1::null_terminated_int_vector<T>& a) {
  for (const auto& x : a) os << x << " ";
  return os;
}

using element_type = i1::null_terminated_int_vector<short>::element_type;
using element_u8_t = i1::null_terminated_int_vector<uint8_t>::element_type;

int main()
{
  cout << "size of element_type( short ) = " << sizeof(element_type) << endl;
  cout << "size of element_type(uint8_t) = " << sizeof(element_u8_t) << endl;

  i1::null_terminated_int_vector<short> a{1, 2, 3, 4, 5};
  cout << "vector a:" << endl;
  cout << a << endl;

  cout << "using data() to access element 2:" << endl;
  short* p = a.data();
  cout << p[2] << endl;
  cout << "using data() to modify element 3:" << endl;
  p[3] = 111;
  cout << a << endl;
  cout << "using data() to access elements 5, 6:" << endl;
  try {
    cout << p[5] << " (wrong)" << endl;
    cout << p[6] << " (wrong)" << endl;
  }
  catch (exception& e) {
    cout << "this throws the following exception:" << endl;
    cout << e.what() << endl;
  }

  cout << "using resize(8):" << endl;
  a.resize(8);
  cout << a << endl;

  cout << "using resize(5):" << endl;
  a.resize(5);
  cout << a << endl;

  cout << "resize(8) with value 44:" << endl;
  a.resize(8, 44);
  cout << a << endl;

  // cout << "erase from 6 to end:" << endl;
  // a.erase(a.begin()+6, a.end());
  cout << "erase from 6 to 8:" << endl;
  a.erase(a.begin()+6, a.begin()+8);
  cout << a << endl;

  cout << "clear:" << endl;
  a.clear();
  cout << "size of a: " << a.size() << endl;

  return 0;
}
