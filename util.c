#include "util.h"
#include <sys/socket.h>
#include <stdio.h>

int vi_size(int val) {
  uint8_t header[5];
  uint8_t *header_ptr = header;
  uint32_t header_len = 0;
  write_var_int(&header_ptr, &header_len, 5, val);
  return header_len;
}
int sendall(int sockfd, const uint8_t *buf, size_t len) {
    int total = 0;        // how many bytes we've sent
    int bytesleft = len;  // how many we have left to send
    int n;

    while (total < len) {
        n = send(sockfd, buf + total, bytesleft, 0);
        if (n == -1) {
            // handle errors here, e.g., EAGAIN or EWOULDBLOCK for non-blocking sockets
            break; 
        }
        total += n;
        bytesleft -= n;
    }

    return (n == -1) ? -1 : 0; 
}

void send_packet(uint8_t *packet_buf, int packet_len, int fd) {
  uint32_t header_len = vi_size(packet_len);
  int offset = 4 - header_len;
  
  uint8_t *write_ptr = packet_buf + offset;
  uint32_t bytes_written = 0;
  //printf("%d\n", header_len);
  write_var_int(&write_ptr, &bytes_written, header_len+1, packet_len);
  
  uint8_t *send_ptr = packet_buf + offset;
  int total_len = header_len + packet_len;
  
  int sent = sendall(fd, send_ptr, total_len);
  if(sent)
    puts("failed to send all data, very bad");
  /* printf("header_len %d, packet_len %d, total_len %d, sent %d\n",  */
  /*        header_len, packet_len, total_len, sent); */
}
