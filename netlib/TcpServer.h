// Authors: Handling
// Created by 15870 on 2020/10/22.
// This is 

#ifndef CPPHOMEWORK_NETLIB_TCPSERVER_H_
#define CPPHOMEWORK_NETLIB_TCPSERVER_H_
#include "Acceptor.h"
#include "EventLoop.h"
#include "TcpConnection.h"

namespace netlib {
class TcpServer {
 public:
  TcpServer(const string &ip, unsigned short port);
  void Start();
  void Stop();

  void set_connection_callback(TcpConnectionCallback &&cb);
  void set_message_callback(TcpConnectionCallback &&cb);
  void set_close_callback(TcpConnectionCallback &&cb);

 private:
  Acceptor acceptor_;
  EventLoop loop_;
};
}

#endif //CPPHOMEWORK_NETLIB_TCPSERVER_H_
