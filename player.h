#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <stdint.h>
#include <types.h>

typedef struct Player {
  struct {
    int fd;
    uint8_t* backlog;
    uint32_t backlog_len;
    int connection_state;
  } conn;
  char username[17];
  mc_location loc;
} player;

player *create_player(int fd);

void free_player(player *player);
#endif
