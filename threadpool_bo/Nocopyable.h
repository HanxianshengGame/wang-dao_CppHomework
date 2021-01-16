// Authors: Handling
// Created by 15870 on 2020/10/17.
// This is 

#ifndef CPPHOMEWORK_THREADPOOL_NOCOPYABLE_H_
#define CPPHOMEWORK_THREADPOOL_NOCOPYABLE_H_
namespace threadpool {
class Nocopyable {
 protected:
  Nocopyable() { }
  ~Nocopyable() { }
  Nocopyable(const Nocopyable &rhs) = delete;
  Nocopyable& operator=(const Nocopyable &rhs) = delete;
};
}

#endif //CPPHOMEWORK_THREADPOOL_NOCOPYABLE_H_
