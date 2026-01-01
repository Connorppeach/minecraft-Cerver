#include "util.h"
#include <sys/socket.h>

int vi_size(int val) {
  uint8_t header[5];
  uint8_t *header_ptr = header;
  uint32_t header_len = 0;
  write_var_int(&header_ptr, &header_len, 5, val);
  return header_len;
}
void send_packet(uint8_t *packet_buf, int packet_len, int fd) {
  uint32_t header_len = vi_size(packet_len);
  int offset = 4 - header_len;
  
  uint8_t *write_ptr = packet_buf + offset;
  uint32_t bytes_written = 0;
  write_var_int(&write_ptr, &bytes_written, 4, packet_len);
  
  uint8_t *send_ptr = packet_buf + offset;
  int total_len = header_len + packet_len;
  
  int sent = send(fd, send_ptr, total_len, 0);
  
  printf("header_len %d, packet_len %d, total_len %d, sent %d\n", 
         header_len, packet_len, total_len, sent);
}
