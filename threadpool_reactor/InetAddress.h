// Authors: Handling
// Created by 15870 on 2020/10/24.
// This is 网络地址转换类

#ifndef CPPHOMEWORK_THREADPOOL_REACTOR_INETADDRESS_H_
#define CPPHOMEWORK_THREADPOOL_REACTOR_INETADDRESS_H_

#include <arpa/inet.h>
#include <string>

namespace concurrentserver {

class InetAddress {
 public:
  //构造函数
  explicit InetAddress(const struct sockaddr_in &addr);
  explicit InetAddress(unsigned short port);
  InetAddress(const std::string &ip, unsigned short port);


  //存取函数
  std::string ip() const { return std::string(inet_ntoa(addr_.sin_addr)); }
  unsigned short port() const { return ntohs(addr_.sin_port); }
  struct sockaddr_in *address_pointer() { return &addr_; }

 private:
  struct sockaddr_in addr_{};
};

}
#endif //CPPHOMEWORK_THREADPOOL_REACTOR_INETADDRESS_H_
