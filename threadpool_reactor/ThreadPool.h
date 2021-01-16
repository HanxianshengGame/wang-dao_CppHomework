// Authors: Handling
// Created by 15870 on 2020/10/26.
// This is 

#ifndef CPPHOMEWORK_THREADPOOL_REACTOR_THREADPOOL_H_
#define CPPHOMEWORK_THREADPOOL_REACTOR_THREADPOOL_H_
#include <vector>
#include <memory>
#include "Thread.h"
#include "Task.h"
#include "TaskQueue.h"

namespace concurrentserver {


class ThreadPool {
 public:
  ThreadPool(size_t thread_num, size_t que_sz);
  ~ThreadPool();

  void Start();
  void Stop();

  void AddTask(Task &&task);

 private:

  Task GetTask();
  void ThreadFunc();

 private:

  size_t thread_num_;
  size_t que_sz_;
  std::vector<std::unique_ptr<Thread>> threads_;
  TaskQueue task_queue_;
  bool is_exit_;
};
}

#endif //CPPHOMEWORK_THREADPOOL_REACTOR_THREADPOOL_H_
