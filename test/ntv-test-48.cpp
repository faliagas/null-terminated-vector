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
  a.erase(a.begin()+2);
  cout << "after erase at pos 2:" << endl;
  cout << a << endl;
  a.emplace(a.begin()+5, -12);
  // a.emplace(a.begin()+5, B{-12});
  cout << "after emplace -12 at pos 5:" << endl;
  cout << a << endl;
  a.erase(a.begin()+3, a.begin()+6);
  cout << "after erase from pos 3 to 6:" << endl;
  cout << a << endl;
  a.erase(a.begin()+3, a.end());
  cout << "after erase from pos 3 to end:" << endl;
  cout << a << endl;
  a.erase(a.begin()+1, a.begin()+1);
  cout << "after erase from pos 1 to 1:" << endl;
  cout << a << endl;
  a.erase(a.begin()+1, a.begin()+2);
  cout << "after erase from pos 1 to 2:" << endl;
  cout << a << endl;
  cout << "last item: " << *(a.end()-1) << endl;
  a.erase(a.end()-1);
  // a.erase(a.begin()+1);
  cout << "after erase at last pos:" << endl;
  cout << a << endl;

  return 0;
}
