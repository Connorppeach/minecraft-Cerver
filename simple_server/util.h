#include "../protocol/rw.h"
#include "../protocol/packets.h"
// gets the size in bytes of a written var int
int vi_size(int val);
// sends a length prefixed packet to fd
void send_packet(uint8_t *packet_buf, int packet_len, int fd);

void send_chunk_packet(uint8_t *write_buf, uint32_t packet_max_len, int player_fd, int32_t *section_datas, int num_sections, int32_t x, int32_t z);
void send_set_center_chunk(uint8_t *write_buf, int32_t WRITE_BUF_SIZE, int fd, int32_t x, int32_t y);

#define PACKET(name, ...)
#define PACKET_ID(name, id) void send_##name##_packet(uint8_t *write_buf, int buffer_len, int fd, name data);
#include "../protocol/all_packets.h"
#undef PACKET
#undef PACKET_ID
