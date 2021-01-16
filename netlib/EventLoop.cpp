// Authors: Handling
// Created by 15870 on 2020/10/22.
// This is 

#include "EventLoop.h"
#include "TcpConnection.h"
#include "Acceptor.h"
#include <cstdio>
#include <cassert>

#ifdef TEST
#include <iostream>
using std::cout;
using std::endl;
using std::flush;
#endif
namespace netlib {
std::map<int, TcpConnectionPtr> EventLoop::conns_{};
EventLoop::EventLoop(Acceptor &acceptor)
: epoll_fd_(CreateEpollFd()),
  acceptor_(acceptor),
  event_list_(1024),
  is_looping_(false) {
#ifdef TEST
  cout << "EventLoop::EventLoop(Acceptor &acceptor)" << endl;
#endif
  event_list_.reserve(1024);
  AddEpollReadFd(acceptor_.fd());
}
void EventLoop::Loop() {
#ifdef TEST
  cout << "void EventLoop::Loop()" << endl;
#endif
  is_looping_ = true;
  while(is_looping_)
    WaitEpollFd();
}
void EventLoop::UnLoop() {
#ifdef TEST
  cout << "void EventLoop::UnLoop()" << endl;
#endif
  if(is_looping_)
    is_looping_ = false;
}
void EventLoop::set_on_connection_callback(TcpConnectionCallback &&cb) {
#ifdef TEST
  cout << "void EventLoop::set_on_connection_callback(TcpConnectionCallback &&cb)" << endl;
#endif
  on_connection_ = std::move(cb);
}
void EventLoop::set_on_message_callback(TcpConnectionCallback &&cb) {
#ifdef TEST
  cout << "void EventLoop::set_on_message_callback(TcpConnectionCallback &&cb)" << endl;
#endif
  on_message_ = std::move(cb);
}
void EventLoop::set_on_close_callback(TcpConnectionCallback &&cb) {
#ifdef TEST
  cout << "void EventLoop::set_on_close_callback(TcpConnectionCallback &&cb)" << endl;
#endif
  on_close_ = std::move(cb);
}
int EventLoop::CreateEpollFd() {
#ifdef TEST
  cout << "int EventLoop::CreateEpollFd()" << endl;
#endif
  int ret = ::epoll_create1(0);
  if(ret == -1)
    perror("epoll_create1");

  return ret;
}
void EventLoop::AddEpollReadFd(const int fd) const {
#ifdef TEST
  cout << "void EventLoop::AddEpollReadFd(const int fd)" << endl;
#endif
  struct epoll_event value{};
  value.data.fd = fd;
  value.events = EPOLLIN;
  int ret = ::epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, fd, &value);
  if(ret == -1)
    perror("epoll_ctl");
}
void EventLoop::DelEpollReadFd(const int fd) const {
#ifdef TEST
  cout << "void EventLoop::DelEpollReadFd(const int fd) const" << endl;
#endif
  struct epoll_event value{};
  value.data.fd = fd;
  int ret = ::epoll_ctl(epoll_fd_, EPOLL_CTL_DEL, fd, &value);
  if(ret == -1)
    perror("epoll_ctl");
}
void EventLoop::WaitEpollFd() {
#ifdef TEST
  cout << "void EventLoop::WaitEpollFd() " << endl;
#endif
  int nready = 0;
  do {
    nready = ::epoll_wait(epoll_fd_, &*event_list_.begin(), event_list_.size(), 5000);
  } while(nready == -1 && errno == EINTR);

  if(nready == -1) {
    perror("epoll_wait");
	return;
  } else if(nready == 0) {
    printf(">> epoll_wait timeout!\n");
  } else {

    if(nready == event_list_.size()) {
      event_list_.resize(2 * nready);
    }

    for(int idx = 0; idx != nready; ++idx) {
      int fd = event_list_[idx].data.fd;
      if(fd == acceptor_.fd()) {
        //新连接
        if(event_list_[idx].events & EPOLLIN) {
          HandleNewConnection();
        }
      } else {
        //针对于已经建立了连接的处理
        if(event_list_[idx].events & EPOLLIN) {
          HandleMessage(fd);

        }
      }
    }
  }
}
void EventLoop::HandleNewConnection() {
#ifdef TEST
  cout << "void EventLoop::HandleNewConnection() " << endl;
#endif
  int peer_fd = acceptor_.Accept();
  AddEpollReadFd(peer_fd);

  TcpConnectionPtr conn(new TcpConnection(peer_fd));
  conn->SetConnectionCallback(on_connection_);
  conn->SetMessageCallback(on_message_);
  conn->SetCloseCallback(on_close_);

  conns_.insert(std::make_pair(peer_fd, conn));

  // do something
  conn->HandleConnectionCallback();
}
void EventLoop::HandleMessage(const int fd) {
#ifdef TEST
  cout << "void EventLoop::HandleMessage(const int fd)" << endl;
#endif
  auto iter = conns_.find(fd);
  assert(iter != conns_.end());
  // 判断连接是否断开
  auto is_closed = iter->second->IsConnectionClose();
  if(is_closed) {
    //...做事情
    DelEpollReadFd(fd);
    iter->second->HandleCloseCallback();
    conns_.erase(iter);

  } else {

    iter->second->HandleMessageCallback();
  }
}

bool EventLoop::IsConnectionClose(const int fd) {
#ifdef TEST
  cout << "bool EventLoop::IsConnectionClose(const int fd)" << endl;
#endif
  auto iter = conns_.find(fd);
  assert(iter != conns_.end());
  // 判断连接是否断开
  return iter->second->IsConnectionClose();
}
}