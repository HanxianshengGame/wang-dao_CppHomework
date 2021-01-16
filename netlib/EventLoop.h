// Authors: Handling
// Created by 15870 on 2020/10/22.
// This is 

#ifndef CPPHOMEWORK_NETLIB_EVENTLOOP_H_
#define CPPHOMEWORK_NETLIB_EVENTLOOP_H_

#include <sys/epoll.h>
#include <vector>
#include <map>
#include <memory>
#include <functional>

namespace netlib {
class TcpConnection;

using TcpConnectionPtr = std::shared_ptr<TcpConnection>;
using TcpConnectionCallback = std::function<void(const TcpConnectionPtr &)>;

class Acceptor;
class EventLoop {
 public:
  explicit EventLoop(Acceptor &acceptor);
  void Loop();
  void UnLoop();

  void set_on_connection_callback(TcpConnectionCallback &&cb);
  void set_on_message_callback(TcpConnectionCallback &&cb);
  void set_on_close_callback(TcpConnectionCallback &&cb);

 private:
  int CreateEpollFd();
  void AddEpollReadFd(const int fd) const;
  void DelEpollReadFd(const int fd) const;

  void WaitEpollFd();
  void HandleNewConnection();
  void HandleMessage(const int fd);
  static bool IsConnectionClose(const int fd);
 private:
  int epoll_fd_;
  Acceptor &acceptor_;
  std::vector<struct epoll_event> event_list_;
  static std::map<int, TcpConnectionPtr> conns_;

  bool is_looping_;
  TcpConnectionCallback on_connection_;
  TcpConnectionCallback on_message_;
  TcpConnectionCallback on_close_;
};
}
#endif //CPPHOMEWORK_NETLIB_EVENTLOOP_H_
