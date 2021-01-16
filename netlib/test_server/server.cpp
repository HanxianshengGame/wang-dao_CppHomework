// Authors: Handling
// Created by 15870 on 2020/10/23.
// This is

#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <func.h>
#include <iostream>
using std::cout;
using std::endl;

int main() {
  int server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in server_addr;

  memset(&server_addr, 0, sizeof(server_addr));

  server_addr.sin_addr.s_addr = inet_addr("172.17.47.226");
  server_addr.sin_port = htons(2000);
  server_addr.sin_family = AF_INET;

  int ret = 0;
  ret = bind(server_sockfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
  if(ret == -1) {
	perror("bind");
	return -1;
  }

  ret = listen(server_sockfd, 10);

  int client_sfd = accept(server_sockfd, nullptr, nullptr);
  ret = send(client_sfd, "welcome", 10, 0);
  if(ret == -1) {
    cout << "test_client is close" << endl;
    return -1;
  }

  char buff[1024];
  memset(buff, 0 , sizeof(buff));

  do {
	ret = recv(client_sfd, buff, sizeof(buff), 0);
  } while(ret == -1 && errno == EINTR);

  if(ret == 0) {
    cout << "test_client has closed!" << endl;
    return -1;
  }

  cout << "recv: " << buff << endl;
}

