// Authors: Handling
// Created by 15870 on 2020/10/21.
// This is 

#ifndef CPPHOMEWORK_NETLIB_SOCKET_H_
#define CPPHOMEWORK_NETLIB_SOCKET_H_
namespace netlib {
class Socket {
 public:
  Socket();
  explicit Socket(const int fd);
  int fd() const { return fd_; }
  void ShutDownWrite() const;

  ~Socket();
 private:
  int fd_;
};
}

#endif //CPPHOMEWORK_NETLIB_SOCKET_H_
