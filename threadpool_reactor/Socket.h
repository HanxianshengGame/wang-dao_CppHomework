// Authors: Handling
// Created by 15870 on 2020/10/24.
// This is 负责socket的创建与关闭

#ifndef CPPHOMEWORK_THREADPOOL_REACTOR_SOCKET_H_
#define CPPHOMEWORK_THREADPOOL_REACTOR_SOCKET_H_
namespace concurrentserver {

class Socket {
 public:
  Socket();
  explicit Socket(const int fd);

  ~Socket();

  int fd() const { return fd_; }

  void ShutDownWrite() const;

 private:
  int fd_;
};

}
#endif //CPPHOMEWORK_THREADPOOL_REACTOR_SOCKET_H_
