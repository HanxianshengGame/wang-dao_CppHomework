// Authors: Handling
// Created by 15870 on 2020/10/26.
// This is 

#ifndef CPPHOMEWORK_THREADPOOL_REACTOR_TCPSERVER_H_
#define CPPHOMEWORK_THREADPOOL_REACTOR_TCPSERVER_H_

#include "Acceptor.h"
#include "EventLoop.h"
#include "TcpConnection.h"

namespace concurrentserver {

class TcpServer {
 public:
  TcpServer(const std::string &ip, unsigned short port);
  void Start();
  void Stop();

  void SetConnectionCallback(TcpConnectionCallback &&cb);
  void SetMessageCallback(TcpConnectionCallback &&cb);
  void SetCloseCallback(TcpConnectionCallback &&cb);

 private:
  Acceptor acceptor_;
  EventLoop loop_;
};
}

#endif //CPPHOMEWORK_THREADPOOL_REACTOR_TCPSERVER_H_
