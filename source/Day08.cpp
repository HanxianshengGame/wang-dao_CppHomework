// Authors: Handling
// Created by 15870 on 2020/9/23.
// This is

#include <iostream>
using std::endl;
using std::cout;

class B {
  int y_;
 public:
  friend class A;
};
class A {
  int x_;
 public:
  A(int a, B &r, int b) {
    x_ = a;
    r.y_ = b;
  }
  void Display(B &);
};
void A::Display(B &r) {
 cout << x_ << " " << r.y_ << endl;
}
class Base {
  friend int operator+(const Base &lhs, const Base &rhs);
 public:
  explicit Base(int val):val_(val) {}
 private:
  int val_;
};

int operator+(const Base &lhs, const Base &rhs) {
  return rhs.val_ - lhs.val_;
}
int main() {
  B obj2;
  A obj1(33, obj2, 88);
  obj1.Display(obj2);
}

