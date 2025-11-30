#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <stdint.h>
typedef struct Connection {
  int fd;
  uint8_t* backlog;
  uint32_t backlog_len;
} connection;

typedef struct Player {
  connection conn;
  int connection_state;
} player;

player *create_player(int fd);

void free_player(player *player);
#endif
