#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h> 
#include <arpa/inet.h>
#include "../protocol/rw.h"
#include "util.h"
#include "player.h"
#include "../protocol/packets.h"



typedef struct {
  player **players;
  uint8_t *player_slots;
  int max_players;
  fd_set master;
  struct {
    int32_t world_height;
    int8_t view_distance;
  } world_data;
  uint8_t should_stop;
} simple_server;

typedef struct {
  void (*packet_callback)(simple_server *server, int player_num, int packet_type, uint8_t *packet_buf, unsigned int buf_len);
  void (*tick_callback)(simple_server *server);
  void (*finish_login_play)(simple_server *server, int player_num);
  void (*player_load_chunks)(simple_server *server, int player_num, int x, int z);
  void (*on_move)(simple_server *server, int player_num, mc_location old_location, mc_location new_location);
} simple_server_callback;

int allocate_player(simple_server *server, int fd);
void deallocate_player(simple_server *server, int player_id);


// todo -- deallocate simple servers
simple_server* allocate_simple_server(int max_players);
int start_server(simple_server *server, int port, simple_server_callback cb);


