// Authors: Handling
// Created by 15870 on 2020/10/21.
// This is 

#ifndef CPPHOMEWORK_NETLIB_ACCEPTOR_H_
#define CPPHOMEWORK_NETLIB_ACCEPTOR_H_
#include "InetAddress.h"
#include "Socket.h"

namespace netlib {
class Acceptor {
 public:
  explicit Acceptor(unsigned short port);
  Acceptor(const string &ip, unsigned short port);

  void Ready();

  int fd() const { return listen_sock_.fd(); };
  int Accept();

 private:
  void SetReuseAddr(bool on);
  void SetReusePort(bool on);
  void Bind();
  void Listen();

 private:
  InetAddress addr_;
  Socket listen_sock_;
};
}
#endif //CPPHOMEWORK_NETLIB_ACCEPTOR_H_
