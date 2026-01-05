#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "player.h"

player *create_player(int fd) {
  player *m_player = (player*)malloc(sizeof(player));
  m_player->conn.fd = fd;
  m_player->conn.backlog = NULL;
  m_player->conn.connection_state = 0;
  m_player->conn.backlog_len = 0;
  return m_player;
}

void free_player(player *m_player) {
  close(m_player->conn.fd);
  free(m_player);
}
