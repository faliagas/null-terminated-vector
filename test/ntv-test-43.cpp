#include <iostream>
#include <algorithm>
#include "nullTerminatedIntVector.hpp"

using namespace std;

template<typename T>
ostream& operator<<(ostream& os, const i1::null_terminated_int_vector<T>& a) {
  for (const auto& x : a) os << x << " ";
  return os;
}

using element_type = typename i1::null_terminated_int_vector<int>::element_type;

struct U {};

int main()
{
  i1::null_terminated_int_vector<int> a{45, 32, 6, 9};
  cout << "create a from std::initializer_list:" << endl;
  cout << "size = " << a.size() << endl;
  cout << "vector a:" << endl;
  cout << a << endl;
  #if 0
  #endif // 0
  cout << "using std::for_each to add 100 to each element of a:" << endl;
 // for (auto it = a.begin(); it; ++it) // OK
  for_each(a.begin(), a.end(), [](element_type& item){
    item = item + 100;
  });
  cout << "using for (:) to print vector a:" << endl;
  for (const auto& item : a)
    cout << item << " ";
  cout << endl;
  cout << "vector a:" << endl;
  cout << a << endl;

  return 0;
}
