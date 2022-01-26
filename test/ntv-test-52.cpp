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
  std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8};
  cout << "std::vector v:" << endl;
  cout << v << endl;

  i1::null_terminated_int_vector<int> a;
  cout << "apply copy from std::vector:" << endl;
  a = std::move(v);

  cout << "size of std::vector v: " << v.size() << endl;
  cout << "vector a:" << endl;
  cout << a << endl;

  v.push_back(123);
  v.push_back(-74);
  v.push_back(512);
  cout << "std::vector v:" << endl;
  cout << v << endl;

  i1::null_terminated_int_vector<int> b;
  b.push_back(32);
  b.push_back(244);
  cout << "vector b:" << endl;
  cout << b << endl;

  cout << "apply copy to b from std::vector v:" << endl;
  b = std::move(v);

  cout << "size of std::vector v: " << v.size() << endl;
  cout << "vector b:" << endl;
  cout << b << endl;

  cout << "convert to std::vector:" << endl;
  b.convert_to(v);
  cout << "size of vector b: " << b.size() << endl;
  cout << "vector v:" << endl;
  cout << v << endl;
  cout << "pushing elements -6 and 992 to std::vector:" << endl;
  v.push_back(-6);
  v.push_back(992);
  cout << "vector v:" << endl;
  cout << v << endl;

  cout << "apply copy to b from std::vector v:" << endl;
  b = std::move(v);
  cout << "size of std::vector v: " << v.size() << endl;
  cout << "vector b:" << endl;
  cout << b << endl;

  return 0;
}
