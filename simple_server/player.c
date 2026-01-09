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
  m_player->loc.x = 0;
  m_player->loc.y = 0;
  m_player->loc.z = 0;
  m_player->loc.pitch = 0;
  m_player->loc.yaw = 0;

  m_player->velocity.x = 0;
  m_player->velocity.y = 0;
  m_player->velocity.z = 0;
  m_player->velocity.pitch = 0;
  m_player->velocity.yaw = 0;
  
  m_player->conn.backlog_len = 0;
  return m_player;
}

void free_player(player *m_player) {
  close(m_player->conn.fd);
  if(m_player->conn.backlog_len != 0)
    free(m_player->conn.backlog);
  free(m_player);
}
