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
  cout << "default constructor for vector a:" << endl;
  i1::null_terminated_int_vector<int> a;

  cout << "push 5 elements:" << endl;
  for (int i = 0; i < 5; ++i)
    a.push_back(i + 10);

  cout << "vector a:" << endl;
  cout << "size = " << a.size() << endl;
  cout << a << endl;
  cout << "front = " << a.front() << endl;
  cout << "back = " << a.back() << endl;
  cout << "pop 1 element:" << endl;
  a.pop_back();
  cout << "vector a:" << endl;
  cout << "size = " << a.size() << endl;
  cout << a << endl;
  cout << "push move 887:" << endl;
  a.push_back(887);
  cout << "vector a:" << endl;
  cout << "size = " << a.size() << endl;
  cout << a << endl;

  return 0;
}
