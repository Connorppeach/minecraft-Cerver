#include "rw.h"
#include "util.h"
#include "player.h"
#include "packets.h"
#include "simple_server.h"
#define STB_PERLIN_IMPLEMENTATION
#include "stb_perlin.h"

#define PORT 25545   // port we're listening on

#define MAX_PLAYERS 10
#define WRITE_BUF_SIZE 1310720

uint8_t write_buf[WRITE_BUF_SIZE];
int total_ticks = 0;
int y = 0;
void handle_packet_cb(simple_server *server, int player_num, int packet_type, uint8_t *packet_buf, unsigned int buf_len) {
  //printf("got packet %d\n", packet_type);
}

void teleport_player(simple_server *server, int player_num, double x, double y, double z) {
  syncronize_player_position packet;
  packet.teleport_id = 10;
  packet.x = x;
  packet.y = y;
  packet.z = z;
  packet.velocity_x = 0.0;
  packet.velocity_y = 0.0;
  packet.velocity_z = 0.0;
  packet.yaw = 0.0;
  packet.pitch = 0.0;
  packet.flags = 0;

  uint8_t *packet_ptr = write_buf+4;
  uint32_t max = 0;
  write_var_int(&packet_ptr, &max, WRITE_BUF_SIZE, SYNCRONIZE_PLAYER_POSITION_ID);
  write_syncronize_player_position(&packet_ptr, &max, WRITE_BUF_SIZE, packet);
  send_packet(write_buf, max, server->players[player_num]->conn.fd);
}

void send_game_event(simple_server *server, int player_num, uint8_t event, float value) {
  game_event packet;
  packet.event_id = event;
  packet.value = value;
  uint8_t *packet_ptr = write_buf+4;
  uint32_t max = 0;
  
  write_var_int(&packet_ptr, &max, WRITE_BUF_SIZE, GAME_EVENT_ID);
  write_game_event(&packet_ptr, &max, WRITE_BUF_SIZE, packet);
  send_packet(write_buf, max, server->players[player_num]->conn.fd);
}

void send_set_center_chunk(simple_server *server, int player_num, int32_t x, int32_t y) {
  set_center_chunk packet;
  packet.x = x;
  packet.y = y;
  uint8_t *packet_ptr = write_buf+4;
  uint32_t max = 0;
  
  write_var_int(&packet_ptr, &max, WRITE_BUF_SIZE, SET_CENTER_CHUNK_ID);
  write_set_center_chunk(&packet_ptr, &max, WRITE_BUF_SIZE, packet);
  send_packet(write_buf, max, server->players[player_num]->conn.fd);
}

#define MAX_CHUNK_SIZE 1310720
void send_test_chunks(simple_server *server, int player_num, int32_t x, int32_t z, int block_id) {
  chunk_data_and_update_light packet;
  packet.heightmap_count = 0;
  packet.block_entities_count = 0;
  packet.x = x;
  packet.y = z;

  packet.o1 = 0;
  packet.o2 = 0;
  packet.o3 = 0;
  packet.o4 = 0;
  packet.o5 = 0;
  packet.o6 = 0;


  uint8_t *packet_ptr = write_buf+4;
  uint32_t max = 0;
  uint8_t chunk_data[MAX_CHUNK_SIZE];
  uint8_t *chunk_data_ptr = chunk_data;
  uint32_t chunk_data_max = 0;
  

  chunk_section section;
  section.block_count = 4096;

  section.block_states.bits_per_entry = 15;
  section.block_states.format = 2;
  for(int i = 0; i < 4096; i++)
    section.block_states.data[i] = 0;

  section.biomes.bits_per_entry = 0;
  section.biomes.format = 0;
  section.biomes.value = 0;

  for(int i = 0; i < 24; i++) {
    for(int local_y = 0; local_y < 16; local_y++) {
      for(int local_z = 0; local_z < 16; local_z++) {
	for(int local_x = 0; local_x < 16; local_x++) {
	  float block_x = (x*16)+local_x;
	  float block_y = (i*16)+local_y;
	  float block_z = (z*16)+local_z;
	  int idx = (local_z*16*16)+(local_y*16)+local_x;
	  float noise1 = stb_perlin_noise3_seed(block_x/10, block_y/10, block_z/10, 0, 0, 0, 0);
	  if (noise1 > 0.0)
	    section.block_states.data[idx] = 0;
	  else
	    section.block_states.data[idx] = 1;
	}
      }
    }
    
    int error = write_chunk_section(&chunk_data_ptr, &chunk_data_max, MAX_CHUNK_SIZE, section);
    if (error) {
      printf("error while writing chunk section: %d\n", error);
      return;
    }    
  }
  packet.data = chunk_data;
  packet.data_len = chunk_data_max;
  write_var_int(&packet_ptr, &max, WRITE_BUF_SIZE-4, CHUNK_DATA_AND_UPDATE_LIGHT_ID);
  int error = write_chunk_data_and_update_light(&packet_ptr, &max, WRITE_BUF_SIZE-4, packet);
  if (error) {
    printf("error: %d\n", error);
    return;
  }
  send_packet(write_buf, max, server->players[player_num]->conn.fd);
}


void tick_callback(simple_server *server) {
  for(int i = 0; i < server->max_players; i++) {
    if (server->player_slots[i]) {
      player* m_player = server->players[i];
      if(m_player->connection_state == 4) {
	// send keepalives
	/* if(total_ticks % 5 == 0) // like, 1 seconds */
	/*   teleport_player(server, i, 0, y++, 0); */

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



void finish_configuration_cb(simple_server *server, int player_num) {
  
  login_play play;
  play.eid = 0;
  play.is_hardcore = 0;
  lstr dim_names[] = { lstr_static("minecraft:overworld") };
  play.dimension_names = &*dim_names;
  play.dimension_name_count = 1;
  play.max_players = 1;
  play.view_distance = 10;
  play.simulation_distance = 10;
  play.reduced_debug_info = false;
  play.enable_respawn_screen = false;
  play.do_limited_crafting = false;
  play.dimension_type = 0;
  play.dimension_name = lstr_static("minecraft:overworld");
  play.hashed_seed = 0;
  play.game_mode = 1;
  play.prev_game_mode = -1;
  play.is_debug = false;
  play.is_flat = false;
  play.has_death_location = false;
  play.portal_cooldown = 10;
  play.sea_level = 10;
  play.enforces_secure_chat = false;

  uint8_t *packet_ptr = write_buf+4;
  uint32_t max = 0;
  write_var_int(&packet_ptr, &max, WRITE_BUF_SIZE, LOGIN_PLAY_ID);
  write_login_play(&packet_ptr, &max, WRITE_BUF_SIZE, play);
  send_packet(write_buf, max, server->players[player_num]->conn.fd);

  send_game_event(server, player_num, 13, 0.0);
  send_set_center_chunk(server, player_num, 0, 0);
  int block_id = 1;
  for(int x = -8; x < 8; x++)
    for(int y = -8; y < 8; y++)
      send_test_chunks(server, player_num, x, y, block_id);
  teleport_player(server, player_num, 0, 384, 0);
}

int main(void)
{
  simple_server *server =  allocate_simple_server(MAX_PLAYERS);
  start_server(server, PORT, (simple_server_callback){ handle_packet_cb, tick_callback, finish_configuration_cb });
} 

