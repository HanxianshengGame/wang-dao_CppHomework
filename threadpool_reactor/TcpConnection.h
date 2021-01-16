// Authors: Handling
// Created by 15870 on 2020/10/24.
// This is 管理与客户端的连接

#ifndef CPPHOMEWORK_THREADPOOL_REACTOR_TCPCONNECTION_H_
#define CPPHOMEWORK_THREADPOOL_REACTOR_TCPCONNECTION_H_
#include <string>
#include <memory>
#include <functional>

#include "Socket.h"
#include "InetAddress.h"
#include "SocketIO.h"
#include "Noncopyable.h"

namespace concurrentserver {

class EventLoop;
class TcpConnection;

using TcpConnectionPtr = std::shared_ptr<TcpConnection>;
using TcpConnectionCallback = std::function<void(const TcpConnectionPtr &conn)>;

class TcpConnection
:public Noncopyable
,public std::enable_shared_from_this<TcpConnection> {

 public:
  TcpConnection(int fd, EventLoop *loop);
  ~TcpConnection();

  std::string Receive();
  void Send(const std::string &msg);
  void SendInLoop(const std::string &msg);

  std::string ToString() const;
  void ShutDown();

  void set_connection_callback(const TcpConnectionCallback &cb);
  void set_message_callback(const TcpConnectionCallback &cb);
  void set_close_callback(const TcpConnectionCallback &cb);

  void HandleConnectionCallback();
  void HandleMessageCallback();
  void HandleCloseCallback();

  bool IsConnectionClosed();
 private:
  InetAddress local_addr() const;
  InetAddress peer_addr() const;
 private:
  EventLoop   *loop_;
  Socket      sock_;
  SocketIO    sock_io_;
  InetAddress local_addr_;
  InetAddress peer_addr_;
  bool        is_shutdown_write_;

  TcpConnectionCallback  connection_callback_;
  TcpConnectionCallback  message_callback_;
  TcpConnectionCallback  close_callback_;
};
}

#endif //CPPHOMEWORK_THREADPOOL_REACTOR_TCPCONNECTION_H_
