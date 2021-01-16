// Authors: Handling
// Created by 15870 on 2020/10/22.
// This is 

#include "TcpServer.h"

#include <string>



#include <iostream>
using std::cout;
using std::endl;
using std::flush;

using namespace netlib;
void OnConnection(const TcpConnectionPtr &conn) {
#ifdef TEST
  cout << "void OnConnection(const TcpConnectionPtr &conn) " << endl;
#endif
  cout << ">> " << conn->ToString() << " has connected!" << endl;
  conn->Send("welcome to server!");
}

void OnMessage(const TcpConnectionPtr &conn) {
#ifdef TEST
  cout << "void OnConnection(const TcpConnectionPtr &conn)  " << endl;
#endif
  string msg = conn->Receive();
  cout << ">> receive: " << msg << endl;
  //回显服务器操作：发送再次回复
  conn->Send(msg);

  //decode
  //compute
  //encode
}

void OnClose(const TcpConnectionPtr &conn) {
#ifdef TEST
  cout << "void OnClose(const TcpConnectionPtr &conn) " << endl;
#endif
  cout << "> " << conn->ToString() << " has closed!" << endl;
}

int main() {
#ifdef TEST
  cout << "int main() " << endl;
#endif
  TcpServer server("172.17.47.226", 2000);

  server.set_connection_callback(OnConnection);
  server.set_message_callback(OnMessage);
  server.set_close_callback(OnClose);

  cout << "server has start!" << endl;
  server.Start();

  return 0;
}