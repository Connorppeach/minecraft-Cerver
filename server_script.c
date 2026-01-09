#include <stdio.h>
#include "./simple_server/simple_server.h"

void on_tick(simple_server *server) {
  //puts("test");
}

void on_login(simple_server *server, int player_num) {
  printf("%s joined the game!\n", server->players[player_num]->username);
}

void on_packet(simple_server *server, int player_num, int packet_type, uint8_t *packet_buf, unsigned int buf_len) {

}
