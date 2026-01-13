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
	if(server->player_slots[j] &&
	   server->players[j]->conn.connection_state == 4 &&
	   j != i) {
	  //printf("%d\n%d\n\n", i, j);
	  send_spawn_entity_packet(write_buf, WRITE_BUF_SIZE, server->players[j]->conn.fd,
			    (spawn_entity){ .eid = i,
					    .entity_uuid = server->players[i]->uuid,
					    .type = 155,
					    .x = server->players[i]->loc.x,
					    .y = server->players[i]->loc.y,
					    .z = server->players[i]->loc.z,
					    .pitch = server->players[i]->loc.pitch/1.41,
					    .yaw = server->players[i]->loc.yaw/1.41,
					    .head_angle = server->players[i]->loc.yaw/1.41,
					    .velocity.x = 0,
					    .velocity.y = 0,
					    .velocity.z = 0,
					    .data = 0});
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
  // update tab list
  {

    send_game_event_packet(write_buf, WRITE_BUF_SIZE, server->players[player_num]->conn.fd,
			   (game_event){
			     .event_id = 13,
			     .value = 0.0
			   });
    
    send_syncronize_player_position_packet(write_buf, WRITE_BUF_SIZE, server->players[player_num]->conn.fd,
					   (syncronize_player_position){
					     .x = 8.5,
					     .y = 67,
					     .z = 8.5,
					     .velocity_x = 0,
					     .velocity_y = 0,
					     .velocity_z = 0,
					     .flags = 0,
					     .pitch = 0,
					     .yaw = 0,
					   });
    server->players[player_num]->loc.x = 8.5;
    server->players[player_num]->loc.y = 67;
    server->players[player_num]->loc.z = 8.5;
    
    {
      int new_id = MAX_PLAYERS+1;
      uuid temp_uuid = { -1, -1 };
      send_spawn_entity_packet(write_buf, WRITE_BUF_SIZE, server->players[player_num]->conn.fd, // send to me
			       (spawn_entity){
				 .eid = new_id, // entity id
				 .entity_uuid = temp_uuid, // uuid
				 .type = 5, // entity type
				 .x = 8.5,
				 .y = 66,
				 .z = 11, // loc x y z
				 .pitch = 0,
				 .yaw = 180/1.41,
				 .head_angle = 180/1.41,// pitch yaw head yaw
				 .data = 0, // data
				 .velocity.x = 0,
				 .velocity.y = 0,
				 .velocity.z = 0}); // velocity
      //entity_metadata meta;
      /* meta.index = 18; */
      /* meta.type = 9; */
      /* meta.value.rotations.x = 120; */
      /* meta.value.rotations.y = -120; */
      /* meta.value.rotations.z = 0; */
      /* send_set_entity_metadata(write_buf, WRITE_BUF_SIZE, server, player_num, new_id, meta); */
      /* meta.index = 15; */
      /* meta.type = 0; */
      /* meta.value.byte = 0x04; */
      //send_set_entity_metadata(write_buf, WRITE_BUF_SIZE, server, player_num, new_id, meta);

    }
    update_tab_list(write_buf, WRITE_BUF_SIZE, server);
    send_all_players_to_players(server);

  }
}


