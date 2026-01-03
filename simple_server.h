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
#include "rw.h"
#include "util.h"
#include "player.h"
#include "packets.h"

#define PORT 25545   // port we're listening on


#define MAX_PLAYERS 10
typedef struct {
  player **players;
  uint8_t *player_slots;
  int max_players;
  fd_set master;
} simple_server;


typedef struct {
  void (*packet_callback)(simple_server *server, int player_num, int packet_type, uint8_t *packet_buf, unsigned int buf_len);
  void (*tick_callback)(simple_server *server);
  void (*finish_configuration)(simple_server *server, int player_num);
} simple_server_callback;
int allocate_player(simple_server *server, int fd);
void deallocate_player(simple_server *server, int player_id);


// todo -- deallocate simple servers
simple_server* allocate_simple_server(int max_players);
int start_server(simple_server *server, int port, simple_server_callback cb);

