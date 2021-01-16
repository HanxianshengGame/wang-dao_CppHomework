// Authors: Handling
// Created by 15870 on 2020/10/24.
// This is 接收者/负责绑定监听新连接

#ifndef CPPHOMEWORK_THREADPOOL_REACTOR_ACCEPTOR_H_
#define CPPHOMEWORK_THREADPOOL_REACTOR_ACCEPTOR_H_
#include "InetAddress.h"
#include "Socket.h"

namespace concurrentserver {

class Acceptor {
 public:
  explicit Acceptor(unsigned short port);
  Acceptor(const std::string &ip, unsigned short port);

  void Ready();
  int Accpect() const;

  int fd() const { return listen_sock_.fd(); }

 private:
  void SetReuseAddr(bool on) const;
  void SetReusePort(bool on) const;
  void Bind();
  void Listen() const;

 private:
  InetAddress addr_;
  Socket      listen_sock_;
};
}
#endif //CPPHOMEWORK_THREADPOOL_REACTOR_ACCEPTOR_H_
