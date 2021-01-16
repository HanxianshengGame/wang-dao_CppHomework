// Authors: Handling
// Created by 15870 on 2020/10/21.
// This is 

#ifndef CPPHOMEWORK_NETLIB_INETADDRESS_H_
#define CPPHOMEWORK_NETLIB_INETADDRESS_H_
#include <arpa/inet.h>
#include <string>
using std::string;
namespace netlib {

/* 网络地址的操作
 * 地址转换
*/

class InetAddress {
 public:
  explicit InetAddress(unsigned short port);
  InetAddress(const string &ip, unsigned int port);
  explicit InetAddress(const struct sockaddr_in &sockaddr);

  // get ip
  string ip() const { return string(::inet_ntoa(addr_.sin_addr)); }
  // get port
  unsigned short port() const { return ntohs(addr_.sin_port); }
  // get address point
  struct sockaddr_in *GetInetAddressPtr() { return &addr_; }
 private:
  struct sockaddr_in addr_;
};
}

#endif //CPPHOMEWORK_NETLIB_INETADDRESS_H_
