#include <iostream>
#include "nullTerminatedIntVector.hpp"

using namespace std;

template<typename T>
ostream& operator<<(ostream& os, const i1::null_terminated_int_vector<T>& a) {
  for (const auto& x : a) os << x << " ";
  return os;
}

template<typename T>
ostream& operator<<(ostream& os, const std::vector<T>& a) {
  for (const auto& x : a) os << x << " ";
  return os;
}

int main()
{
  vector<int> v{45, 32, 6, 9};
  cout << "std::vector v:" << endl;
  cout << v << endl;
  cout << "create a from std::vector v:" << endl;
  i1::null_terminated_int_vector<int> a(v.begin(), v.end());
  cout << "vector a:" << endl;
  cout << a << endl;

  cout << "size of a = " << a.size() << endl;
 // for (auto it = a.begin(); it; ++it) // OK
   // cout << *it << " ";
  cout << "using for (:) to print vector a:" << endl;
  for (const auto& item : a)
    cout << item << " ";
  cout << endl;

  return 0;
}
