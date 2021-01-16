// Authors: Handling
// Created by 15870 on 2020/10/24.
// This is 

#ifndef CPPHOMEWORK_THREADPOOL_REACTOR_EVENTLOOP_H_
#define CPPHOMEWORK_THREADPOOL_REACTOR_EVENTLOOP_H_
#include <sys/epoll.h>
#include <vector>
#include <map>
#include <memory>
#include <functional>

#include "MutexLock.h"
namespace concurrentserver {

class TcpConnection;
using TcpConnectionPtr = std::shared_ptr<TcpConnection>;
using TcpConnectionCallback = std::function<void(const TcpConnectionPtr &conn)>;
using Functor = std::function<void()>;

class Acceptor;
class EventLoop {
 public:
  explicit EventLoop(Acceptor &acceptor);

  void Loop();
  void RunInLoop(Functor &&cb);
  void UnLoop();

  void set_connection_callback(TcpConnectionCallback &&cb);
  void set_message_callback(TcpConnectionCallback &&cb);
  void set_close_callback(TcpConnectionCallback &&cb);
 private:
  static int  CreateEpollfd();
  void AddEpollReadfd(int fd) const;
  void DelEpollReadfd(int fd) const;

  void WaitEpollfd();
  void HandleNewConnection();
  void HandleMessage(int fd);
  bool IsConnectionClose(int fd);

  static int CreateEventfd();
  void HandleEventfdRead() const;
  void WakeUpEventfd() const;
  void DoPendingFunctors();

 private:

  int epoll_fd_;
  int event_fd_;
  Acceptor &acceptor_;
  std::vector<struct epoll_event> event_list_;
  std::map<int, TcpConnectionPtr> conns_;
  bool is_looping;
  std::vector<Functor> pending_functors_;
  MutexLock mutex_;

  TcpConnectionCallback connection_callback_;
  TcpConnectionCallback message_callback_;
  TcpConnectionCallback close_callback_;
};
}
#endif //CPPHOMEWORK_THREADPOOL_REACTOR_EVENTLOOP_H_
