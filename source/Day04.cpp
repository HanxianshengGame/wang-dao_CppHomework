// Authors: Handling
// Created by 15870 on 2020/9/18.
// This is Day04
#include <bits/stdc++.h>
using namespace std;
namespace bindirectlist {
struct Node {
  int data_;
  Node *pre;
  Node *next;
  Node(): data_(0), pre(nullptr), next(nullptr){}
};

class BinaryList {
 private:
  Node *head_;
  Node *tail_;
  int   size_;

 public:

  BinaryList() {
    head_ = tail_ = nullptr;
    size_ = 0;
  }
  ~BinaryList();

  int size() const { return size_; }
  bool empty() const { return size() == 0; }
  void push_front(int data) {

    auto new_node = new Node();
    new_node->data_ = data;
    new_node->next = head_;
    new_node->pre = tail_;

    if(empty()) {
      head_ = tail_ = new_node;
    } else {
      head_->pre = new_node;
      tail_->next = new_node;
      head_ = new_node;
    }
    ++size_;
  }

  void push_back(int data) {
    push_front(data); //双向链表的头插尾插相同。
  	tail_ = head_;
  	if(!empty())
      head_ = head_->next;
  }

  void pop_front() {
    if(empty())
	  return;
    if(size() == 1) {
	  delete tail_;
	  head_ = tail_ = nullptr;
	  --size_;
	  return;
    }
    tail_->next = head_->next;
    head_->next->pre = tail_;
	delete head_;
	head_ = tail_->next;
	--size_;
  }

  void pop_back() {
    tail_->pre->next = head_;
    head_->pre = tail_->pre;
	delete tail_;
	tail_ = head_->pre;
	--size_;
  }
  bool find(int data) {
    if(empty())
	  return false;
    auto beg = head_;
	if(head_->data_ == data)
	  return true;
	beg = beg->next;
	while(beg != head_) {
	  if(beg->data_ == data)
		return true;
	}
    return false;
  }

  void insert(int pos, int data) {
    if(pos == 0 || empty()) {
	  push_front(data);
	}
    bool forward_insert = pos > 0; //pos 大于0 向前查找， 小于 0 向后查找
    auto beg = head_;
	auto new_node = new Node();
	new_node->data_ = data;
	if(forward_insert) {
		while(--pos)
		  beg = beg->next;
		new_node->next = beg->next;
		new_node->pre = beg;
		beg->next = new_node;
		new_node->next->pre = new_node;
    } else {
      while(++pos)
       	beg = beg->pre;
	  new_node->next = beg->next;
	  new_node->pre = beg;
	  beg->next = new_node;
	  new_node->next->pre = new_node;
    }
	++size_;
  }

  void display() const {
    if(empty())
	  return;
	auto beg = head_;
	while(beg != tail_) {
	  cout << beg->data_ << endl;
	  beg = beg->next;
	}
	cout << tail_->data_ << endl;
  }
  void erase(int data) {
    if(!find(data))
	  return;
    auto beg = head_;
    while(beg != tail_) {
	  if(beg->data_ == data) {
		beg->pre->next = beg->next;
		beg->next->pre = beg->pre;
		delete beg;
		--size_;
		return;
	  }
	  beg = beg->next;
	}
	if(size() != 1) {
	  tail_->pre->next = tail_->next;
	  tail_->next->pre = tail_->pre;
	}
	delete tail_;
	if(size() == 1) {
	  tail_ = head_ = nullptr;
	}
	--size_;
  }
};
}
int main() {

}


