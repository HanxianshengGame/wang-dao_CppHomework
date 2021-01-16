// Authors: Handling
// Created by 15870 on 2020/10/17.
// This is 

#ifndef CPPHOMEWORK_THREADPOOL_TASKQUEUE_H_
#define CPPHOMEWORK_THREADPOOL_TASKQUEUE_H_
#include "MutexLock.h"
#include "Condition.h"
#include <queue>

using std::queue;
namespace threadpool {

class Task;
using ElemType = Task*;
class TaskQueue {
 public:
  explicit TaskQueue(size_t que_size);
  bool empty() const;
  bool full() const;
  void push(const ElemType &elem);
  ElemType pop();
  void exit();

 private:
  size_t que_sz_;
  queue<ElemType> que_;
  MutexLock mutex_;
  Condition not_empty_;
  Condition not_full_;
  bool is_exit_;
};

}
#endif //CPPHOMEWORK_THREADPOOL_TASKQUEUE_H_
