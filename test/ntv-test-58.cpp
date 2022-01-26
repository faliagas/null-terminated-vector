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
  for (const auto x : a) os << x << " ";
  return os;
}

int main()
{
  vector<int> v{1, 2, 3, 4, 5, 6, 7, 8};
  cout << "vector v:" << endl;
  cout << v << endl;

  vector<int> tmp = v;
  cout << "apply move from v:" << endl;
  i1::null_terminated_int_vector<int> a = std::move(v);
  cout << "vector a:" << endl;
  cout << a << endl;
  cout << "size of v: " << v.size() << endl;

  cout << "restored v" << endl;
  v = tmp;
  cout << "apply move constructor from v:" << endl;
  i1::null_terminated_int_vector<int> b(std::move(v));
  cout << "vector b:" << endl;
  cout << b << endl;
  cout << "size of v: " << v.size() << endl;

  #if 0
  #endif // 0

  return 0;
}
