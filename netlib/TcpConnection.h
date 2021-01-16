// Authors: Handling
// Created by 15870 on 2020/10/21.
// This is 

#ifndef CPPHOMEWORK_NETLIB_TCPCONNECTION_H_
#define CPPHOMEWORK_NETLIB_TCPCONNECTION_H_
#include "Socket.h"
#include "InetAddress.h"
#include "SocketIO.h"
#include "Noncopyable.h"

#include <string>
#include <memory>
#include <functional>

namespace netlib {
class TcpConnection;
using TcpConnectionPtr = std::shared_ptr<TcpConnection>;
using TcpConnectionCallback = std::function<void(const TcpConnectionPtr &conn)>;


class TcpConnection
: public Noncopyable,
  public std::enable_shared_from_this<TcpConnection> {
 public:
  explicit TcpConnection(int fd);
  ~TcpConnection();

  string Receive();
  void Send(const string &msg);
  string ToString() const;
  void ShutDown();

  void SetConnectionCallback(const TcpConnectionCallback &cb);
  void SetMessageCallback(const TcpConnectionCallback &cb);
  void SetCloseCallback(const TcpConnectionCallback &cb);

  void HandleConnectionCallback();
  void HandleMessageCallback();
  void HandleCloseCallback();

  bool IsConnectionClose();

  int fd() const { return sock_.fd(); }
 private:
  InetAddress GetLocalAddr(const int fd);
  InetAddress GetPeerAddr(const int fd);

 private:
  Socket sock_;
  SocketIO sock_io_;
  InetAddress local_addr;
  InetAddress peer_addr;
  bool is_shutdown_write_;

  TcpConnectionCallback on_connection_;
  TcpConnectionCallback on_message_;
  TcpConnectionCallback on_close_;

};
}
#endif //CPPHOMEWORK_NETLIB_TCPCONNECTION_H_
