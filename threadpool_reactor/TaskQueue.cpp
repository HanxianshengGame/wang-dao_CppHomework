// Authors: Handling
// Created by 15870 on 2020/10/26.
// This is 

#include "TaskQueue.h"
#ifdef TEST
#include <iostream>
using std::cout;
using std::endl;
using std::flush;
#endif
namespace concurrentserver {

TaskQueue::TaskQueue(size_t que_sz)
: que_sz_(que_sz)
, que_()
, mutex_()
, not_empty_(mutex_)
, not_full_(mutex_)
, flag_(true) {

#ifdef TEST
  cout << "TaskQueue::TaskQueue(size_t que_sz)" << endl;
#endif
}
bool TaskQueue::Empty() const {
#ifdef TEST
  cout << "bool TaskQueue::Empty() const" << endl;
#endif
  return que_.empty();
}
bool TaskQueue::Full() const {
#ifdef TEST
  cout << "bool TaskQueue::Full() const" << endl;
#endif
  return que_.size() == que_sz_;
}
void TaskQueue::Push(const Task &elem) {
#ifdef TEST
  cout << "void TaskQueue::Push(const Task &elem) " << endl;
#endif
  MutexLockGuard auto_lock(mutex_);
  while(Full()) {
    not_full_.Wait();  //等待不满的出现
  }

  que_.push(elem);
  not_empty_.Notify();  //使得不为空的条件变量激活
}
Task TaskQueue::Pop() {
#ifdef TEST
  cout << "Task TaskQueue::Pop()" << endl;
#endif
  MutexLockGuard auto_lock(mutex_);
  while(flag_ && Empty()) {
    not_empty_.Wait();
  }

  if(flag_) {
    auto task = que_.front();
    que_.pop();
    not_full_.Notify();
    return task;
  }
  return nullptr;

}
void TaskQueue::WakeUp() {
#ifdef TEST
  cout << "void TaskQueue::WakeUp()" << endl;
#endif
  flag_ = false;
  not_empty_.NotifyAll();
}
}
