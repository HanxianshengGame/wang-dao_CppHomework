// Authors: Handling
// Created by 15870 on 2020/10/24.
// This is 对事件的监听

#include "EventLoop.h"
#include <unistd.h>
#include <cstdio>
#include <cassert>
#include <sys/eventfd.h>

#include <iostream>
#include "Acceptor.h"
#include "TcpConnection.h"
using std::cout;
using std::endl;
using std::flush;
using std::vector;


namespace concurrentserver {

EventLoop::EventLoop(Acceptor &acceptor)
: epoll_fd_(CreateEpollfd())
, event_fd_(CreateEventfd())
, acceptor_(acceptor)
, event_list_(1024)
, is_looping(false) {
#ifdef TEST
  cout << "EventLoop::EventLoop(Acceptor &acceptor)" << endl;
#endif
  AddEpollReadfd(acceptor_.fd());
  AddEpollReadfd(event_fd_);

}
void EventLoop::Loop() {
#ifdef TEST
  cout << "void EventLoop::Loop()" << endl;
#endif
  is_looping = true;
  while(is_looping)
    WaitEpollfd();
}
void EventLoop::RunInLoop(Functor &&cb) {
#ifdef TEST
cout << "void EventLoop::RunInLoop(Functor &&cb)" << endl;
#endif
  {
    MutexLockGuard auto_lock(mutex_);
    pending_functors_.push_back(std::move(cb));
  }
  WakeUpEventfd();
}
void EventLoop::UnLoop() {
#ifdef TEST
  cout << "void EventLoop::UnLoop() " << endl;
#endif
  if(is_looping)
    is_looping = false;
}

int EventLoop::CreateEpollfd() {
#ifdef TEST
  cout << "int EventLoop::CreateEpollfd()" << endl;
#endif
  int ret = epoll_create1(0);
  if(ret == -1)
    perror("epoll_create1");
  return ret;
}
void EventLoop::AddEpollReadfd(int fd) const {
#ifdef TEST
  cout << "void EventLoop::AddEpollReadfd(int fd) const" << endl;
#endif
  struct epoll_event value{};
  value.data.fd = fd;
  value.events = EPOLLIN;
  int ret = epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, fd, &value);
  if(ret == -1)
    perror("epoll_ctl");
}
void EventLoop::DelEpollReadfd(int fd) const {
#ifdef TEST
  cout << "void EventLoop::DelEpollReadfd(int fd) const" << endl;
#endif
  struct epoll_event value{};
  value.data.fd = fd;
  int ret = epoll_ctl(epoll_fd_, EPOLL_CTL_DEL, fd, &value);
  if(ret == -1)
    perror("epoll_ctl");

}
void EventLoop::WaitEpollfd() {
#ifdef TEST
  cout << "void EventLoop::WaitEpollfd()" << endl;
#endif
  int nready = 0;
  do {
	nready = epoll_wait(epoll_fd_,
					    &*event_list_.begin(),
					    event_list_.size(),
					    5000);

  } while (nready == -1 && errno == EINTR);

  if(nready == -1) {
    perror("epoll wait");
	return;
  } else if(nready == 0) {
    printf(">> epoll_wait timeout!\n");
  } else {
    //进行扩容操作
    if(nready == event_list_.size())
      event_list_.resize(2 * nready);

    for(int idx= 0; idx != nready; ++idx) {
      int fd = event_list_[idx].data.fd;
      if(fd == acceptor_.fd()) {
        if(event_list_[idx].events & EPOLLIN)
          HandleNewConnection();

      } else if(fd == event_fd_) {
        if(event_list_[idx].events & EPOLLIN) {
          HandleEventfdRead();
          cout << "DoPendingFunctors..." << endl;
          DoPendingFunctors();
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
  cout << "void EventLoop::HandleNewConnection()" << endl;
#endif
  int peer_fd = acceptor_.Accpect();
  AddEpollReadfd(peer_fd);

  TcpConnectionPtr conn(new TcpConnection(peer_fd, this));
  conn->set_connection_callback(connection_callback_);
  conn->set_message_callback(message_callback_);
  conn->set_close_callback(close_callback_);

  conns_.insert(std::make_pair(peer_fd, conn));

  //... do something

  //连接建立时，执行回调函数
  conn->HandleConnectionCallback();
}
void EventLoop::HandleMessage(int fd) {
#ifdef TEST
  cout << "void EventLoop::HandleMessage(int fd) " << endl;
#endif
  auto iter = conns_.find(fd);
  assert(iter != conns_.end()); //错误直接崩溃

  //判断连接是否断开
  auto is_closed = iter->second->IsConnectionClosed();
  if(is_closed) {
    //... do something
    DelEpollReadfd(fd);
    iter->second->HandleCloseCallback();
    conns_.erase(iter);
  } else {
    iter->second->HandleMessageCallback();
  }
}
bool EventLoop::IsConnectionClose(int fd) {
#ifdef TEST
  cout << "bool EventLoop::IsConnectionClose(int fd)" << endl;
#endif
  auto iter = conns_.find(fd);
  assert(iter != conns_.end());
  return iter->second->IsConnectionClosed();
}
int EventLoop::CreateEventfd() {
#ifdef TEST
  cout << "int EventLoop::CreateEventfd() " << endl;
#endif
  int ret = eventfd(0,0);
  if(ret == -1)
    perror("eventfd");
  return ret;
}
void EventLoop::HandleEventfdRead() const {
#ifdef TEST
  cout << "void EventLoop::HandleEventfdRead() const" << endl;
#endif
  uint64_t howmany = 0;
  int ret =read(event_fd_, &howmany, sizeof(howmany));
  if(ret != sizeof(howmany))
    perror("write");
}
void EventLoop::WakeUpEventfd() const {
#ifdef TEST
  cout << "void EventLoop::WakeUpEventfd() const" << endl;
#endif
  uint64_t one = 1;
  int ret = write(event_fd_, &one, sizeof(one));
  if(ret != sizeof(one))
    perror("write");
}
void EventLoop::DoPendingFunctors() {
#ifdef TEST
  cout << "void EventLoop::DoPendingFunctors()" << endl;
#endif
  vector<Functor> tmp;
  {
    MutexLockGuard auto_lock(mutex_);
    tmp.swap(pending_functors_);
  }

  for(auto & functor :tmp)
    functor();
}
void EventLoop::set_connection_callback(TcpConnectionCallback &&cb) {
#ifdef TEST
  cout << "void EventLoop::set_connection_callback(TcpConnectionCallback &&cb)" << endl;
#endif
  connection_callback_ = std::move(cb);
}
void EventLoop::set_message_callback(TcpConnectionCallback &&cb) {
#ifdef TEST
  cout << "void EventLoop::set_message_callback(TcpConnectionCallback &&cb)" << endl;
#endif

  message_callback_ = std::move(cb);
}
void EventLoop::set_close_callback(TcpConnectionCallback &&cb) {
#ifdef TEST
  cout << "void EventLoop::set_close_callback(TcpConnectionCallback &&cb)" << endl;
#endif
  close_callback_ = std::move(cb);
}
}
