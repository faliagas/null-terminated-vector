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
  const vector<int> v{45, 32, 6, 9};
  cout << "std::vector v:" << endl;
  cout << v << endl;
  cout << "create o from std::vector v:" << endl;
  const i1::null_terminated_int_vector<int> o{v.begin(), v.end()};
  cout << "vector o:" << endl;
  cout << o << endl;
  auto it = o.begin();
  ++it; ++it;
  cout << "create a from first 2 elements of vector o:" << endl;
  i1::null_terminated_int_vector<int> a{o.begin(), it};
  // i1::null_terminated_vector<B> a{o.begin(), o.begin()+3};
  // i1::null_terminated_vector<B> a{o.begin(), o.end()};

  cout << "vector a:" << endl;
  cout << "size = " << a.size() << endl;
  cout << a << endl;

  return 0;
}
