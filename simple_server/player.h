#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <stdint.h>
#include "../protocol/rw.h"

typedef struct Player {
  int id; // default initialized to player slot, but intended to hold network id.
  struct {
    int fd;
    uint8_t* backlog;
    uint32_t backlog_len;
    int connection_state;
  } conn;
  char username[17];
  uuid uuid;
  mc_location loc;
  mc_location velocity;

} player;

player *create_player(int fd);

void free_player(player *player);
#endif
