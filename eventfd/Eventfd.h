// Authors: Handling
// Created by 15870 on 2020/10/23.
// This is 线程同步工作

#ifndef CPPHOMEWORK_EVENTFD_EVENTFD_H_
#define CPPHOMEWORK_EVENTFD_EVENTFD_H_

#include <functional>
namespace netlib {
using EventCallback = std::function<void()>;

class Eventfd {
 public:
  explicit Eventfd(EventCallback &&cb);

  void Start(); //托管poll 进行监听描述符
  void Stop(); // 停止poll 监听

  void WakeUp(); //唤醒一次eventfd

 private:
  void HandleRead();
  int CreateEventfd();

 private:
  int eventfd_;
  EventCallback cb_;
  bool is_started_;
};
}

#endif //CPPHOMEWORK_EVENTFD_EVENTFD_H_
