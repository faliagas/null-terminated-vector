#include <iostream>
#include <list>
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

template<typename T>
ostream& operator<<(ostream& os, const std::list<T>& a) {
  for (const auto& x : a) os << x << " ";
  return os;
}

// ostream& operator<<(ostream& os, const B& b) {
  // os << b.i;
  // return os;
// }

int main()
{
  int x[]{1, 2, 3, 4, 5};
  i1::null_terminated_ptr_vector<int> a{x, x+1, x+2, x+3, x+4};
  cout << "vector a:" << endl;
  cout << a << endl;
  cout << static_cast<i1::null_terminated_ptr_vector<int>::_Base>(a) << endl;
  cout << "should be:" << endl;
  for (auto p = x; p != x+5; ++p)
    cout << p << " ";
  cout << endl;
  const int n1 = 85;
  int n2 = 92;
  cout << "push 85 and 92:" << endl;
  a.push_back(const_cast<int*>(&n1));
  a.push_back(&n2);
  cout << "vector a:" << endl;
  cout << a << endl;

  cout << "pop:" << endl;
  a.pop_back();
  cout << "vector a:" << endl;
  cout << a << endl;

  cout << "assign from initializer list:" << endl;
  int n3 = 506;
  a.assign({x+2, &n3, &n2});
  cout << "vector a:" << endl;
  cout << a << endl;

  cout << "copy from initializer list:" << endl;
  a = {x+3, &n2};
  cout << "vector a:" << endl;
  cout << a << endl;

  i1::null_terminated_ptr_vector<int> b{x, x+1, x+2, x+3, x+4};
  cout << "vector b:" << endl;
  cout << b << endl;
  cout << "insert from b:" << endl;
  a.insert(a.begin(), b.begin()+1, b.end()-1);
  cout << "vector a:" << endl;
  cout << a << endl;

  cout << "using at() to access element 2:" << endl;
  cout << a.at(2) << " (" << *a.at(2) << ")" << endl;
  cout << "using at() to modify element 3:" << endl;
  int n4 = 111;
  a.at(3) = &n4;
  cout << a << endl;

  cout << "using [] to access element 1:" << endl;
  cout << a[1] << " (" << *a[1] << ")" << endl;
  cout << "using [] to modify element 1:" << endl;
  a[1] = &n3;
  cout << a << endl;

  cout << "emplace_back 506:" << endl;
  a.emplace_back(&n3);
  cout << a << endl;

  cout << "emplace 3 at pos 1:" << endl;
  a.emplace(a.begin()+1, x+2);
  cout << a << endl;

  return 0;
}
