#include "../protocol/packets.h"

int vi_size(int val);
int sendall(int sockfd, const uint8_t *buf, size_t len);
void send_packet(uint8_t *packet_buf, int packet_len, int fd);

#define PACKET(name, ...)
#define PACKET_ID(name, id) void send_##name##_packet(uint8_t *write_buf, int buffer_len, int fd, name data);
#include "../protocol/all_packets.h"
#undef PACKET
#undef PACKET_ID
