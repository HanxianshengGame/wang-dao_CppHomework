// Authors: Handling
// Created by 15870 on 2020/9/16.
// This is Day03 homework
#include <vector>
#include <exception>
using namespace std;
namespace stackquestion {
class Rect {
 private:
  double width_;
  double length_;

 public:
  Rect() = default;
  Rect(double width, double length) : width_(width), length_(length) {}

  double area() const { return width_ * length_; }
  double perimeter() const { return 2 * (width_ + length_); }

};
}
namespace stackquestion {
class MyStack {
 private:
  int full_size_;
  vector<int> data_;
 public:
  MyStack() : data_(0), full_size_(10) { data_.reserve(10); }

  void push(int val);
  void pop();
  int top() const { return data_.back(); }
  bool empty() const { return data_.empty(); }
  bool full() const { return size() == full_size_; }
  bool size() const { return data_.size(); }
};

inline void MyStack::push(int val) {
  if (full()) {
#ifdef DEBUG
	printf("stack is full!\n");
#endif
	return;
  }
  data_.push_back(val);
}
inline void MyStack::pop() {
  if (!empty()) {
#ifdef DEBUG
	printf("stack is empty!\n");
#endif
	return;
  }
  data_.pop_back();
}
}

namespace queuequestion {
class MyQueue {
 private:
  vector<int> data_;
  int full_size_;
 public:
  MyQueue() : data_(0), full_size_(10) {}
  void push_back(int val);
  void pop_front();
  int front() const { return data_.front(); }
  bool empty() const { return data_.empty(); }
  bool full() const { return size() == full_size_; }
  int size() const { return data_.size(); }
};
void MyQueue::push_back(int val) {
  if (full()) {
#ifdef DEBUG
	printf("queue is full\n");
#endif
	return;
  }
  data_.push_back(val);
}
void MyQueue::pop_front() {
  if (empty()) {
#ifdef DEBUG
	printf("queue is empty!\n");
#endif
	return;
  }
  data_.erase(data_.begin());
}

}

