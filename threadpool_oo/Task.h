// Authors: Handling
// Created by 15870 on 2020/10/17.
// This is 

#ifndef CPPHOMEWORK_THREADPOOL_TASK_H_
#define CPPHOMEWORK_THREADPOOL_TASK_H_
namespace threadpool {
class Task {
 public:
  virtual void process() = 0;
};
}

#endif //CPPHOMEWORK_THREADPOOL_TASK_H_
