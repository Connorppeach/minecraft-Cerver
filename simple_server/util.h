#include "../protocol/rw.h"
// gets the size in bytes of a written var int
int vi_size(int val);
// sends a length prefixed packet to fd
void send_packet(uint8_t *packet_buf, int packet_len, int fd);

void send_chunk_packet(uint8_t *write_buf, uint32_t packet_max_len, int player_fd, int32_t *section_datas, int num_sections, int32_t x, int32_t z);
