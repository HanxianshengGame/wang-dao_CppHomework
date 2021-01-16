// Authors: Handling
// Created by 15870 on 2020/10/26.
// This is 

#ifndef CPPHOMEWORK_THREADPOOL_REACTOR_TASKQUEUE_H_
#define CPPHOMEWORK_THREADPOOL_REACTOR_TASKQUEUE_H_
#include "MutexLock.h"
#include "Condition.h"
#include "Task.h"

#include <queue>
namespace concurrentserver {
class TaskQueue {
 public:
  explicit TaskQueue(size_t que_sz);

  bool Empty() const;
  bool Full() const;
  void Push(const Task &elem);

  Task Pop();
  void WakeUp();

 private:
  size_t que_sz_;
  std::queue<Task> que_;
  MutexLock mutex_;
  Condition not_empty_;
  Condition not_full_;
  bool flag_;
};
}

#endif //CPPHOMEWORK_THREADPOOL_REACTOR_TASKQUEUE_H_
