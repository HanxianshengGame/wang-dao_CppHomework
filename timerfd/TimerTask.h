// Authors: Handling
// Created by 15870 on 2020/10/23.
// This is 

#ifndef CPPHOMEWORK_TIMERFD_TIMERTASK_H_
#define CPPHOMEWORK_TIMERFD_TIMERTASK_H_
namespace netlib {
class TimerTask {
 public:
  TimerTask(int seconds)
  : time_interval_(seconds)
  , count_(seconds)
  {}
  virtual ~TimerTask() { }

  virtual int time_interval() const { return time_interval_; }
  int count() const { return count_; }
  void set_count(int count) { count_ = count; }

  void InitCount() { count_ = time_interval_; }
  virtual void Process() = 0;
  void DecreaseCount() { --count_; }


 private:
  int time_interval_; //周期性的执行时间
  int count_;         // 距离下一次任务执行还剩下的时间
};
}
#endif //CPPHOMEWORK_TIMERFD_TIMERTASK_H_
