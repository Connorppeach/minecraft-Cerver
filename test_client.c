#include <stdio.h>
#include <unistd.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#include "rw.h"
#include "player.h"
#include "packets.h"

#define PORT 25565   // port we're listening on
uint8_t id_buf[6];
char hostname[] = "localhost";
int main()
{
  handshake shake;
  shake.protocol_version = 772;
  shake.server_address.str = hostname;
  shake.server_address.len = strlen(hostname);
  shake.port = 25565;
  shake.intent = 2;
  
  int sockfd;
  struct sockaddr_in servaddr;
  
  // socket create and varification
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    printf("socket creation failed...\n");
    exit(0);
  }

  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
  servaddr.sin_port = htons(PORT);
  
  // connect the client socket to server socket
  if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0) {
    printf("connection with the server failed...\n");
    exit(0);
  } else{
    printf("connected to the server..\n");
  }
  
  uint8_t buf[1024];
  uint8_t *buf_ptr = buf+4;
  unsigned int pos = 0;


  write_var_int(&buf_ptr, &pos, sizeof(buf_ptr), 0);  
  write_handshake(&buf_ptr, &pos, sizeof(buf), shake);

  uint8_t *id_buf_ptr = id_buf;
  unsigned int pos_2 = 0;
  write_var_int(&id_buf_ptr, &pos_2, sizeof(id_buf), pos);  
  int offset = 4-pos_2;
  buf_ptr = buf+offset;
  pos_2 = 0;
  write_var_int(&buf_ptr, &pos_2, 4, pos_2);  
  buf_ptr = buf+offset;
  


  write(sockfd, buf_ptr, pos+1); 

  //printf("read %d bytes from socket\n",len);
  close(sockfd);
}
