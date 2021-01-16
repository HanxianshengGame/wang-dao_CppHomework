// Authors: Handling
// Created by 15870 on 2020/10/17.
// This is 

#ifndef CPPHOMEWORK_THREADPOOL_TASK_H_
#define CPPHOMEWORK_THREADPOOL_TASK_H_
#include <functional>
using std::function;
namespace threadpool {
  using Task = function<void()>;
}

#endif //CPPHOMEWORK_THREADPOOL_TASK_H_
