// Authors: Handling
// Created by 15870 on 2020/10/24.
// This is 负责套接字间的 IO 操作

#ifndef CPPHOMEWORK_THREADPOOL_REACTOR_SOCKETIO_H_
#define CPPHOMEWORK_THREADPOOL_REACTOR_SOCKETIO_H_
namespace concurrentserver {
class SocketIO {
 public:
  explicit SocketIO(int fd);
  ~SocketIO() = default;

  int ReadN(char *buff, int len) const;
  int ReadLine(char *buff, int max_len);
  int WriteN(const char *buff, int len) const;

 private:
  int RecvPeek(char *buff, int len) const;

 private:
  int fd_;
};
}

#endif //CPPHOMEWORK_THREADPOOL_REACTOR_SOCKETIO_H_
