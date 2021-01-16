// Authors: Handling
// Created by 15870 on 2020/10/23.
// This is 

#ifndef CPPHOMEWORK_TIMERFD_TIMERMANAGER_H_
#define CPPHOMEWORK_TIMERFD_TIMERMANAGER_H_
#include "TimerTask.h"
#include <list>
#include <vector>

using std::vector;
using std::list;
namespace netlib {
class TimerManager {
 public:
  TimerManager();

  void Start();
  void Stop();

  void AddTask(TimerTask *timer_task);
  void RemoveTask(TimerTask *timer_task);

 private:
  static int CreateTimerfd();
  void SetTimerfd(int init_time, int periodic_time) const;

  void HandleRead();
  void HandleTask();

 private:
  int fd_;
  bool is_started_;
  int current_index_;
  vector<list<TimerTask *>> timer_wheel_list_;

  static const int k_size = 10;
};
}

#endif //CPPHOMEWORK_TIMERFD_TIMERMANAGER_H_
