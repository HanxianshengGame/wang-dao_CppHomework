// Authors: Handling
// Created by 15870 on 2020/10/17.
// This is 

#include "TaskQueue.h"

namespace threadpool {

TaskQueue::TaskQueue(size_t que_size)
: que_sz_(que_size),
  que_(),
  mutex_(),
  not_empty_(mutex_),
  not_full_(mutex_),
  is_exit_(false) {

}
bool TaskQueue::empty() const {
  return que_.empty();
}
bool TaskQueue::full() const {
  return que_.size() == que_sz_;
}
void TaskQueue::push(ElemType elem) {
  MutexLockGuard auto_lock(mutex_);

  while(full()) {
    not_full_.wait();
  }

  que_.push(elem);
  not_empty_.notify();
}
ElemType TaskQueue::pop() {
  MutexLockGuard auto_lock(mutex_);

  while(empty()) {
    not_empty_.wait();
    if(is_exit_)
      return nullptr;
  }

  ElemType  elem = que_.front();
  que_.pop();
  not_full_.notify();
  return elem;
}
void TaskQueue::exit() {
  is_exit_ = true;
  not_empty_.notify_all();
}
}