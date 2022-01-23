#include <iostream>
#include "nullTerminatedVector.hpp"

using namespace std;

template<typename T>
ostream& operator<<(ostream& os, const i1::null_terminated_vector<T>& a) {
  for (const auto& x : a) os << x << " ";
  return os;
}

struct B {
  int i;
  B() : i() {}
  B(int n) : i(n) {}
  static B null_terminator() noexcept {return B{-1000000};}
  bool is_null() const noexcept {return i == null_terminator().i; }
  B& operator=(int n) noexcept { i = n; return *this; }
};

ostream& operator<<(ostream& os, const B& b) {
  os << b.i;
  return os;
}

int main()
{
  cout << "create a from std::initializer_list:" << endl;
  i1::null_terminated_vector<B> a{1, 2, 3, 4, 5, 6, 7, 8};
  cout << a << endl;
  a.erase(a.begin()+2);
  cout << "after erase at pos 2:" << endl;
  cout << a << endl;
  B e2;
  e2 = -12;
  a.emplace(a.begin()+5, e2);
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
