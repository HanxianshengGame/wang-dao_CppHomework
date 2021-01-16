// Authors: Handling
// Created by 15870 on 2020/10/26.
// This is 

#ifndef CPPHOMEWORK_THREADPOOL_REACTOR_TASK_H_
#define CPPHOMEWORK_THREADPOOL_REACTOR_TASK_H_
#include <functional>
namespace concurrentserver {
using Task = std::function<void()>;
}
#endif //CPPHOMEWORK_THREADPOOL_REACTOR_TASK_H_
