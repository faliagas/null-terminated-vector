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
  i1::null_terminated_int_vector<int> a(10);
  cout << "size of std::vector:            " << sizeof(std::vector<int>) << endl;
  cout << "size of null_terminated_vector:  " << sizeof(a) << endl;

  cout << "create vector a with 10 elements:" << endl;
  cout << "vector a:" << endl;
  cout << a << endl;

  cout << "assign value to each element:" << endl;
  for (size_t i = 0; i < 10; ++i)
    a[i] = (int)i;
  cout << a << endl;
  cout << "first 5 elements of vector a:" << endl;
  for (size_t i = 0; i < 5; ++i)
    cout << a[i] << " ";
  cout << endl;
  if (!(4 < a.size()))
  {
    cout << "assertion failed, " << "line " << __LINE__-2 << endl;
    return 3;
  };
  cout << "apply iterator to print vector a:" << endl;
  // for (auto it = a.begin(); it != a.end(); ++it) // OK
  // for (auto it = a.begin(); it != a.begin()+5; ++it) // OK
  // for (auto it = a.begin(); it != a.begin()+10; ++it) // OK
  for (auto it = a.begin(); it; ++it) // OK
    cout << *it << " ";
  cout << endl;

  return 0;
}
