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

template<typename T>
ostream& operator<<(ostream& os, const std::vector<T>& a) {
  for (const auto& x : a) os << x << " ";
  return os;
}

int main()
{
  int x[]{ 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
          10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
          20, 21, 22, 23, 24, 25};
  int y[]{123, -74, 512, 32, 244, -6, 992};
  std::vector<int*> v{x+1, x+2, x+3, x+4, x+5, x+6, x+7, x+8};
  cout << "std::vector v:" << endl;
  for (const auto p : v) cout << *p << " ";
  cout << endl;
  cout << v << endl;

  i1::null_terminated_ptr_vector<int> a;
  cout << "apply move from std::vector:" << endl;
  a = std::move(v);
  cout << "size of std::vector v: " << v.size() << endl;
  cout << "vector a:" << endl;
  cout << a << endl;

  v.push_back(y+0);
  v.push_back(y+1);
  v.push_back(y+2);
  cout << "push 3 items to std::vector v:" << endl;
  for (const auto p : v) cout << *p << " ";
  cout << endl;

  i1::null_terminated_ptr_vector<int> b;
  b.push_back(y+3);
  b.push_back(y+4);
  cout << "vector b:" << endl;
  cout << b << endl;

  cout << "apply move to b from std::vector v:" << endl;
  b = std::move(v);
  cout << "size of std::vector v: " << v.size() << endl;
  cout << "vector b:" << endl;
  cout << b << endl;

  cout << "convert to std::vector:" << endl;
  b.convert_to(v);
  cout << "size of vector b: " << b.size() << endl;
  cout << "vector v:" << endl;
  for (const auto p : v) cout << *p << " ";
  cout << endl;
  cout << "pushing elements -6 and 992 to std::vector:" << endl;
  v.push_back(y+5);
  v.push_back(y+6);
  cout << "vector v:" << endl;
  for (const auto p : v) cout << *p << " ";
  cout << endl;

  cout << "apply move to b from std::vector v:" << endl;
  b = std::move(v);
  cout << "size of std::vector v: " << v.size() << endl;
  cout << "vector b:" << endl;
  cout << b << endl;

  return 0;
}
