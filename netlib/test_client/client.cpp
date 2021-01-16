// Authors: Handling
// Created by 15870 on 2020/10/22.
// This is test_client

#include <sys/socket.h>
#include <func.h>
#include <string>
#include <iostream>
int main() {
   int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
   struct sockaddr_in server_addr;

   server_addr.sin_family = AF_INET;
   server_addr.sin_addr.s_addr = inet_addr("172.17.47.226");
   server_addr.sin_port = htons(2000);

   int ret = connect(socket_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
   if(-1 == ret) {
     perror("connect");
     return -1;
   }


   using std::string;
   using std::cin;
   using std::cout;
   using std::endl;
   using std::flush;

   string str;
   char buff[1024];
   for(;;) {
	   memset(buff, 0, sizeof(buff));
	   cout << "recv: " << flush;
	   ret = recv(socket_fd, buff, sizeof(buff), 0);
	   if(ret == 0)
		 break;
	   cout << buff << endl;
	   cin >> str;
	   str += '\n';
	   cout << "str:" << str << endl;
	   if(str == "quit")
	     break;
	   ret = send(socket_fd, str.c_str(), str.size(), 0);
	   if(ret == -1)
		 break;
	   cout << "send success" << endl;
   }
  cout << "server has quit!" << endl;
  close(socket_fd);
   return 0;
}

