// Authors: Handling
// Created by 15870 on 2020/10/23.
// This is 

#include "Eventfd.h"

#include <unistd.h>
#include <sys/eventfd.h>
#include <poll.h>

namespace netlib {

Eventfd::Eventfd(EventCallback &&cb)
: eventfd_(CreateEventfd())
, cb_(std::move(cb))
, is_started_(false) {

}
void Eventfd::Start() {
  struct pollfd pfd;
  pfd.fd = eventfd_;
  pfd.events = POLLIN;

  is_started_ = true;
  while(is_started_) {
    int nready = ::poll(&pfd, 1, 5000);
    if(nready == -1 && errno == EINTR) {
	  continue;
	} else if(nready == -1) {
      perror("poll");
	  return;
    } else if(nready == 0) {
      printf("poll timeout!\n");
    } else {
      if(pfd.events &POLLIN ) {
        HandleRead();
        if(cb_)
          cb_();
      }
    }

  }
}
void Eventfd::Stop() {
  if(is_started_)
    is_started_ = false;
}
void Eventfd::WakeUp() {
  uint64_t  one = 1;
  int ret = ::write(eventfd_, &one, sizeof(one));
  if(ret != sizeof(one))
    perror("write");
}
void Eventfd::HandleRead() {
  uint64_t howmany = 0;
  int ret = ::read(eventfd_, &howmany, sizeof(howmany));
  if(ret != sizeof(howmany))
    perror("read");
}
int Eventfd::CreateEventfd() {
  int ret = ::eventfd(0, 0);
  if(ret < 0)
    perror("eventfd");
  return ret;
}
}