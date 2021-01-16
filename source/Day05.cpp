// Authors: Handling
// Created by 15870 on 2020/9/18.
// This is
#include <bits/stdc++.h>

namespace onlycreatedbystackorheap {
//将类的 new 表达式设置为私有，就可以规定该类的对象生成禁止使用动态内存
class ClassCreateByStack {
 private:
  void *operator new(size_t) {}
};
//将类的析构函数设置为私有，就不能使用栈去构造，只能用堆构造，析构时外部不能析构，只能通过
//类内部定义的函数去delete
class ClassCreateByHeap {
 private:
  ~ClassCreateByHeap() = default;
 public:
  void destory() {
	delete this;
  }
};
}

int main() {
  using onlycreatedbystackorheap::ClassCreateByStack;
  using onlycreatedbystackorheap::ClassCreateByHeap;
  ClassCreateByHeap *my_class = new ClassCreateByHeap();

}