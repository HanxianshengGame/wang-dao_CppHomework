// Authors: Handling
// Created by 15870 on 2020/10/21.
// This is 

#ifndef CPPHOMEWORK_NETLIB_SOCKETIO_H_
#define CPPHOMEWORK_NETLIB_SOCKETIO_H_
namespace netlib {
class SocketIO {
 public:
  explicit SocketIO(const int fd);

  int ReadN(char *buff, const int len) const;
  int ReadLine(char *buff, const int max_len) const;
  int WriteN(const char *buff, const int len) const;

 private:
  int RecvPeek(char *buff, const int len) const;

 private:
  int fd_;
};
}

#endif //CPPHOMEWORK_NETLIB_SOCKETIO_H_
