// Authors: Handling
// Created by 15870 on 2020/10/23.
// This is 

#include "TimerManager.h"
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <cerrno>
#include <sys/timerfd.h>
#include <poll.h>
#include <string>
#include <algorithm>
#include <iostream>

namespace netlib {

TimerManager::TimerManager()
: fd_(CreateTimerfd())
, is_started_(false)
, current_index_(0)
{
  timer_wheel_list_.reserve(k_size);
  for(size_t idx = 0; idx != k_size; ++idx) {
    timer_wheel_list_.emplace_back();
  }
}
void TimerManager::Start() {
  struct pollfd pfd{};
  pfd.fd = fd_;
  pfd.events = POLLIN;

  //开启定时器
  SetTimerfd(1,1); // 每一秒超时一次
  is_started_ = true;
  while(is_started_) {
    int nready = ::poll(&pfd, 1, 5000);
    if(nready == -1 && errno == EINTR)
	  continue;
    else if(nready == -1) {
      perror("poll");
	  return;
    } else if(nready == 0) {
      printf("poll timeout!");
    } else {
      HandleRead();
      HandleTask();
    }
  }

}
void TimerManager::Stop() {
  SetTimerfd(0,0);
  if(is_started_)
    is_started_ = false;
}
void TimerManager::AddTask(TimerTask *timer_task) {
  if(timer_task) {
    //根据 seconds 确定在哪一个时间槽 slot
    int idx = (timer_task->time_interval() + current_index_) % k_size;
    //放入时间槽
    timer_wheel_list_[idx].push_back(timer_task);
    //确定圈数
    int count = timer_task->time_interval() / k_size;
    timer_task->set_count(count);
  }
}
void TimerManager::RemoveTask(TimerTask *timer_task) {
  if(timer_task)
    for(auto &slot : timer_wheel_list_)
      for(auto ptask : slot)
        if(ptask == timer_task) {
		  slot.remove(ptask);
		  return;
		}
}
int TimerManager::CreateTimerfd() {
  int fd = ::timerfd_create(CLOCK_REALTIME, 0);
  if(fd < 0)
    perror("timefd_create");
  return fd;
}
void TimerManager::SetTimerfd(int init_time, int periodic_time) const {
  struct itimerspec value{};
  value.it_value.tv_sec = init_time;
  value.it_value.tv_nsec = 0;
  value.it_interval.tv_sec = periodic_time;
  value.it_interval.tv_nsec = 0;

  int ret = ::timerfd_settime(fd_, 0, &value, nullptr);
  if(ret < 0) {
    perror("timerfd_settime");
  }
}
void TimerManager::HandleRead() {
  uint64_t howmany = 0;
  int ret = ::read(fd_, &howmany, sizeof(howmany));
  if(ret != sizeof(howmany))
    perror("read");
}
void TimerManager::HandleTask() {
  ++current_index_;
  current_index_ %= k_size;
  list<TimerTask *> cache_list;

  auto &slot = timer_wheel_list_[current_index_];
  for(auto iter = slot.begin(); iter != slot.end(); ) {
    if((*iter)->count() <= 0) {
      auto tmp = *iter;
      cache_list.push_back(tmp);
      iter = slot.erase(iter);
      AddTask(tmp);

    } else {
	  (*iter)->DecreaseCount();
	  ++iter;
    }
  }
  //执行所有的定时器任务
  for(auto ptask : cache_list)
    ptask->Process();

}
}
