#include "rw.h"
// gets the size in bytes of a written var int
int vi_size(int val);
// sends a length prefixed packet to fd
void send_packet(uint8_t *packet_buf, int packet_len, int fd);
