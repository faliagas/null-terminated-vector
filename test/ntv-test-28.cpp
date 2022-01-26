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

int* _B(int value) {
  static std::list<int> v;
  v.push_back(value);
  return &v.back();
}

int main()
{
  i1::null_terminated_ptr_vector<int> a{_B(1), _B(2), _B(3), _B(4), _B(5)};
  cout << "vector a:" << endl;
  cout << a << endl;

  cout << "size of _NTPV_element<int>: "
       << sizeof(i1::_NTPV_element<int>) << endl;
  cout << "size of int*: " << sizeof(int*) << endl;

  cout << "using data() to access element 2:" << endl;
  auto p = a.data();
  cout << *(int*)(p[2]) << endl;
  cout << "using data() to modify element 3:" << endl;
  *p[3] = 111;
  cout << a << endl;
  cout << "using data() to access element 4:" << endl;
  cout << *p[4] << endl;
  try {
    // cout << *p[5] << endl;
    // cout << *p[6] << endl;
  }
  catch (exception& e) {
    cout << "this throws the following exception:" << endl;
    cout << e.what() << endl;
  }

  cout << "using resize(8):" << endl;
  a.resize(8);
  cout << static_cast<i1::null_terminated_ptr_vector<int>::_Base>(a) << endl;

  cout << "using resize(5):" << endl;
  a.resize(5);
  cout << static_cast<i1::null_terminated_ptr_vector<int>::_Base>(a) << endl;
  cout << a << endl;

  cout << "resize(8) with value 44:" << endl;
  a.resize(8, _B(44));
  cout << a << endl;

  cout << "create b with copy constructor:" << endl;
  i1::null_terminated_ptr_vector<int> b(a);
  cout << "vector b:" << endl;
  cout << b << endl;

  // cout << "erase from 6 to end:" << endl;
  // a.erase(a.begin()+6, a.end());
  cout << "erase from 5 to 7:" << endl;
  a.erase(a.begin()+5, a.begin()+7);
  cout << a << endl;

  cout << "erase at 1:" << endl;
  a.erase(a.begin()+1);
  cout << a << endl;

  cout << "swap a, b:" << endl;
  a.swap(b);
  cout << "vector a:" << endl;
  cout << a << endl;
  cout << "vector b:" << endl;
  cout << b << endl;

  cout << "clear a:" << endl;
  a.clear();
  cout << "size of a: " << a.size() << endl;

  return 0;
}
