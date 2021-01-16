// Authors: Handling
// Created by 15870 on 2020/10/24.
// This is 禁止拷贝的基类机制

#ifndef CPPHOMEWORK_THREADPOOL_REACTOR_NONCOPYABLE_H_
#define CPPHOMEWORK_THREADPOOL_REACTOR_NONCOPYABLE_H_
namespace concurrentserver {
class Noncopyable {
 protected:
  Noncopyable() = default;
  ~Noncopyable() = default;
  Noncopyable(const Noncopyable &) = delete;
  Noncopyable& operator=(const Noncopyable &) = delete;
};
}
#endif //CPPHOMEWORK_THREADPOOL_REACTOR_NONCOPYABLE_H_
