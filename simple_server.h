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
