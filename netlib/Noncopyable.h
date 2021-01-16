// Authors: Handling
// Created by 15870 on 2020/10/21.
// This is 

#ifndef CPPHOMEWORK_NETLIB_NONCOPYABLE_H_
#define CPPHOMEWORK_NETLIB_NONCOPYABLE_H_

class Noncopyable {
 protected:
  Noncopyable() = default;
  Noncopyable(const Noncopyable &) = delete;
  Noncopyable &operator=(const Noncopyable &) = delete;
  ~Noncopyable() = default;

};

#endif //CPPHOMEWORK_NETLIB_NONCOPYABLE_H_
