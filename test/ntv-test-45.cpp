#include <iostream>
#include <iterator>
#include "nullTerminatedIntVector.hpp"

using namespace std;

template<typename T>
ostream& operator<<(ostream& os, const i1::null_terminated_int_vector<T>& a) {
  for (const auto& x : a) os << x << " ";
  return os;
}

int main()
{
  cout << "default constructor for vector a:" << endl;
  i1::null_terminated_int_vector<int> a;
  cout << "vector a:" << endl;
  cout << "size = " << a.size() << endl;
  for (const auto& i : a) {
    cout << i << endl;
  }

  cout << "pushing 5 elements onto a:" << endl;
  for (int i = 0; i < 5; ++i) {
    a.push_back(i + 10);
  }

  cout << "vector a:" << endl;
  cout << "size = " << a.size() << endl;
  cout << a << endl;
  cout << "front = " << a.front() << endl;
  cout << "back = " << a.back() << endl;

  return 0;
}
