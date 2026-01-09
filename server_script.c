#include <stdio.h>
#include <stdbool.h>
#include "./simple_server/simple_server.h"
#include "./util.h"
#include "./blocks.h"

#define WORLD_GEN_LIMIT 4

#define WRITE_BUF_SIZE 10000

uint8_t write_buf[WRITE_BUF_SIZE]; 
int total_ticks = 0;


void init(simple_server *server) {
  server->world_data.view_distance = WORLD_GEN_LIMIT;
}

void player_load_chunks(simple_server *server, int player_num, int32_t x, int32_t z) {
  int32_t chunk_data[4096*24];
  for(int i = 0; i < 24; i++) {
    for(int local_y = 0; local_y < 16; local_y++) {
      float block_y = (i*16)+local_y;
      for(int local_z = 0; local_z < 16; local_z++) {
	float block_z = (z*16)+local_z;
	for(int local_x = 0; local_x < 16; local_x++) {
	  float block_x = (x*16)+local_x;
	  int idx = (i*4096)+(local_y*16*16)+(local_z*16)+local_x;
	  if(block_y > 60)
	    chunk_data[idx] = MINECRAFT_AIR;
	  else
	    chunk_data[idx] = MINECRAFT_STONE;
	      
	}
      }
    }
  }
  send_chunk_packet(write_buf, WRITE_BUF_SIZE, server->players[player_num]->conn.fd, chunk_data, 24, x, z);
}
void send_all_players_to_players(simple_server *server) {
  for(int i = 0; i < server->max_players; i++) {
    if(server->player_slots[i]) {
      for(int j = 0; j < server->max_players; j++)
	if(server->player_slots[j] && server->players[j]->conn.connection_state == 4 && j != i) {
	  send_spawn_entity(write_buf, WRITE_BUF_SIZE, server, j, i, server->players[i]->uuid, 155,
			    server->players[i]->loc.x, server->players[i]->loc.y, server->players[i]->loc.z,
			    server->players[i]->loc.pitch, server->players[i]->loc.yaw, server->players[i]->loc.yaw/1.41, 0, 0, 0, 0);
	}
    }
  }
}

void on_tick(simple_server *server) {
  for (int i = 0; i < server->max_players; i++) {
    if (server->player_slots[i]) {
      player* m_player = server->players[i];
      if(m_player->conn.connection_state == 4) {
	// send keepalives
	if(total_ticks % 400 == 0) {// like, 16 seconds
	  clientbound_keep_alive alive;
	  alive.id = total_ticks;
	  uint8_t *packet_ptr = write_buf+4;
	  uint32_t max = 0;
	  write_var_int(&packet_ptr, &max, WRITE_BUF_SIZE, CLIENTBOUND_KEEP_ALIVE_PLAY_ID);
	  write_clientbound_keep_alive(&packet_ptr, &max, WRITE_BUF_SIZE, alive);
	  send_packet(write_buf, max, m_player->conn.fd);
	}
      }
    }
  }
  total_ticks++;
}

void on_login(simple_server *server, int player_num) {
  printf("%s joined the game!\n", server->players[player_num]->username);
  {
    send_game_event(write_buf, WRITE_BUF_SIZE, server, player_num, 13, 0.0);
    teleport_player(write_buf, WRITE_BUF_SIZE, server, player_num, 8.5, 61, 8.5, 0, 0, 0);

    update_tab_list(write_buf, WRITE_BUF_SIZE, server);
    
    send_all_players_to_players(server);

  }
}


