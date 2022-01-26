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
  cout << "create a from std::initializer_list:" << endl;
  i1::null_terminated_int_vector<int> a{1, 2, 3, 4, 5, 6, 7, 8};

  cout << a << endl;
  const int e1{39};
  // a.insert(a.begin()+2, {e1});
  // a.insert(a.begin()+2, 39);
  a.insert(a.begin()+2, e1);
  cout << "after insert 39 at pos 2:" << endl;
  cout << a << endl;
  int e2;
  e2 = -12;
  a.emplace(a.begin()+5, e2);
  // a.emplace(a.begin()+5, B{-12});
  cout << "after emplace -12 at pos 5:" << endl;
  cout << a << endl;

  return 0;
}
