#include "rw.h"
#include "util.h"
#include "player.h"
#include "packets.h"
#include "simple_server.h"

#define MAZELIB_IMPLEMENTATION
#include "mazelib.h"

#include "FastNoiseLite.h"

void teleport_player(simple_server *server, int player_num, double x, double y, double z);
void send_game_event(simple_server *server, int player_num, uint8_t event, float value);
void send_set_center_chunk(simple_server *server, int player_num, int32_t x, int32_t y);
void send_chunks(simple_server *server, int player_num, int32_t x, int32_t z, int block_id);
void send_chunks_maze(simple_server *server, int player_num, int32_t x, int32_t z, int block_id);
void send_spawn_entity(simple_server *server, int player_num, int32_t entity_id, uuid entity_uuid, int32_t type, double x, double y, double z, uint8_t pitch, uint8_t yaw, uint8_t head_yaw, int32_t data, uint16_t velocity_x, uint16_t velocity_y, uint16_t velocity_z);

#define PORT 25545   // port we're listening on

#define MAX_PLAYERS 10
#define WRITE_BUF_SIZE 1310720
#define WORLD_GEN_LIMIT 5

uint8_t write_buf[WRITE_BUF_SIZE];
int total_ticks = 0;

void handle_packet_cb(simple_server *server, int player_num, int packet_type, uint8_t *packet_buf, unsigned int buf_len) {
  //printf("got packet %d\n", packet_type);
}

void tick_callback(simple_server *server) {
  for(int i = 0; i < server->max_players; i++) {
    if (server->player_slots[i]) {
      player* m_player = server->players[i];
      if(m_player->conn.connection_state == 4) {
	/* if(total_ticks % 5 == 0) // like, 1 seconds */
	/*   teleport_player(server, i, 0, y++, 0); */

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

void on_move_cb(simple_server *server, int player_num) {
  player *m_player = server->players[player_num];
  /* printf("username: %s\n  x: %lf\n  y: %lf\n  z: %lf\n  pitch: %f\n  yaw: %f\n", */
  /* 	 m_player->username, */
  /* 	 m_player->loc.x, */
  /* 	 m_player->loc.y, */
  /* 	 m_player->loc.z, */
  /* 	 m_player->loc.pitch, */
  /* 	 m_player->loc.yaw); */
};

void finish_configuration_cb(simple_server *server, int player_num) {
  printf("%s joined the game!\n", server->players[player_num]->username);
  
  login_play play;
  play.eid = 0;
  play.is_hardcore = 0;
  lstr dim_names[] = { lstr_static("minecraft:overworld") };
  play.dimension_names = &*dim_names;
  play.dimension_name_count = 1;
  play.max_players = 1;
  play.view_distance = WORLD_GEN_LIMIT;
  play.simulation_distance = 10;
  play.reduced_debug_info = false;
  play.enable_respawn_screen = false;
  play.do_limited_crafting = false;
  play.dimension_type = 0;
  play.dimension_name = lstr_static("minecraft:overworld");
  play.hashed_seed = 0;
  play.game_mode = 2;
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
  for(int x = -WORLD_GEN_LIMIT; x < WORLD_GEN_LIMIT; x++)
    for(int y = -WORLD_GEN_LIMIT; y < WORLD_GEN_LIMIT; y++)
      send_chunks_maze(server, player_num, x, y, block_id);
  teleport_player(server, player_num, -17.5, 1, 18.5);

  uuid rand_uuid; // funny trick
  send_spawn_entity(server, player_num, 1, rand_uuid, 4, -18, 1, -2, 0, 0, 192, 0, 0, 0, 0);
}

int main(void)
{
  simple_server *server =  allocate_simple_server(MAX_PLAYERS);
  start_server(server, PORT, (simple_server_callback){ handle_packet_cb, tick_callback, finish_configuration_cb, on_move_cb });
}

// utility senders
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

void send_spawn_entity(simple_server *server, int player_num, int32_t entity_id, uuid entity_uuid, int32_t type, double x, double y, double z, uint8_t pitch, uint8_t yaw, uint8_t head_yaw, int32_t data, uint16_t velocity_x, uint16_t velocity_y, uint16_t velocity_z) {
  spawn_entity packet;
  packet.eid = entity_id;
  packet.entity_uuid = entity_uuid;
  packet.type = type;
  packet.x = x;
  packet.y = y;
  packet.z = z;
  packet.pitch = pitch;
  packet.yaw = yaw;
  packet.head_angle = head_yaw;
  packet.velocity_x = velocity_x;
  packet.velocity_y = velocity_y;
  packet.velocity_z = velocity_z;
  packet.data = data;

  uint8_t *packet_ptr = write_buf+4;
  uint32_t max = 0;
  write_var_int(&packet_ptr, &max, WRITE_BUF_SIZE, SPAWN_ENTITY_ID);
  write_spawn_entity(&packet_ptr, &max, WRITE_BUF_SIZE, packet);
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


// send basic world data
#define MAX_CHUNK_SIZE 1310720
void send_chunks(simple_server *server, int player_num, int32_t x, int32_t z, int block_id) {
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


  fnl_state noise_2d = fnlCreateState();
  noise_2d.noise_type = FNL_NOISE_PERLIN;
  noise_2d.frequency = 0.05;


  fnl_state noise_2d_2 = fnlCreateState();
  noise_2d_2.noise_type = FNL_NOISE_PERLIN;
  noise_2d_2.frequency = 0.05;
  noise_2d_2.seed = 21;
  
  fnl_state noise_caves = fnlCreateState();
  noise_caves.noise_type = FNL_NOISE_OPENSIMPLEX2;
  noise_caves.domain_warp_type = FNL_DOMAIN_WARP_OPENSIMPLEX2;
  noise_caves.domain_warp_amp = 3.0;
  noise_caves.octaves = 2;
  fnl_state noise_caves_2 = fnlCreateState();
  noise_caves.noise_type = FNL_NOISE_OPENSIMPLEX2;
  noise_caves.seed = 2;
  
  float heightmap[16][16];
#define NOISE_DEC_2D 2
#define NOISE_DEC_2D_2 128
  for(int x2 = 0; x2 < 16; x2++)
    for(int z2 = 0; z2 < 16; z2++){
      heightmap[x2][z2] = ((fnlGetNoise2D(&noise_2d, ((float)(x*16)+x2)/NOISE_DEC_2D, ((float)(z*16)+z2)/NOISE_DEC_2D)+1)/2)*32;
      heightmap[x2][z2] *= ((fnlGetNoise2D(&noise_2d_2, ((float)(x*16)+x2)/NOISE_DEC_2D_2, ((float)(z*16)+z2)/NOISE_DEC_2D_2)+1)/2);
      heightmap[x2][z2] += 30;
    }
  
  for(int i = 0; i < 24; i++) {
    // write chunk data to our array
    if(x+1 != WORLD_GEN_LIMIT && z+1 != WORLD_GEN_LIMIT &&
       x != -WORLD_GEN_LIMIT && z != -WORLD_GEN_LIMIT)
      for(int local_y = 0; local_y < 16; local_y++) {
	float block_y = (i*16)+local_y;
	for(int local_z = 0; local_z < 16; local_z++) {
	  float block_z = (z*16)+local_z;
	  for(int local_x = 0; local_x < 16; local_x++) {
	    float block_x = (x*16)+local_x;

	    int idx = (local_y*16*16)+(local_z*16)+local_x;
#define NOISE_DEC 0.2
#define NOISE_DEC_2 2
	    float block_x_warped = block_x;
	    float block_y_warped = block_y;
	    float block_z_warped = block_z;
	    fnlDomainWarp3D(&noise_caves, &block_x_warped, &block_y_warped, &block_z_warped);
	    float noise1 = (fnlGetNoise3D(&noise_caves, block_x_warped/NOISE_DEC, block_y_warped/NOISE_DEC, block_z_warped/NOISE_DEC)+1)/2;
	    float noise2 = (fnlGetNoise3D(&noise_caves_2, block_x/NOISE_DEC_2, block_y/NOISE_DEC_2, block_z/NOISE_DEC_2)+1)/2;
	    if((int)heightmap[local_x][local_z] > block_y) {
	      //section.block_states.data[idx] = 1;
	      //printf("%f\n", noise1);
	      if (noise2 < 0.5 && noise1 < 0.4) {
		section.block_states.data[idx] = 0;
	      } else {
		section.block_states.data[idx] = 1;
		if((int)heightmap[local_x][local_z]-1 <= block_y) {
		  section.block_states.data[idx] = 9;
		}
	      }
	    } else
	      section.block_states.data[idx] = 0;

	  }
	}
      }
    else {
      section.block_states.format = 0;
      section.block_states.bits_per_entry = 0;
      section.block_states.value = 0;

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


 

void send_chunks_maze(simple_server *server, int player_num, int32_t x, int32_t z, int block_id) {
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


  uint8_t blockwise = 1;
  uint32_t width = 48/2;
  uint32_t height = 48/2;
  uint64_t result;
  uint64_t buffer_size = mazelib_get_required_buffer_size ( width, height, blockwise );
  uint8_t* buffer = ( uint8_t* ) malloc ( buffer_size );
  if ( buffer == NULL )
    {
      printf ( "Failed to allocate memory.\n" );
      return;
    }
  result = mazelib_generate ( width, height, ( uint64_t ) 32, 25, blockwise, buffer, buffer_size );
  if ( result == 0 )
    {
      printf ( "Generation failed.\n" );
      free ( buffer );
      return;
    }  

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


  
  width *= 2;
  ++width;
  height *= 2;  
  ++height;
  for(int i = 0; i < 24; i++) {
    // write chunk data to our array
    if(x+1 != WORLD_GEN_LIMIT && z+1 != WORLD_GEN_LIMIT &&
       x != -WORLD_GEN_LIMIT && z != -WORLD_GEN_LIMIT)
      for(int local_y = 0; local_y < 16; local_y++) {
	int block_y = (i*16)+local_y;
	for(int local_z = 0; local_z < 16; local_z++) {
	  int block_z = (z*16)+local_z;
	  for(int local_x = 0; local_x < 16; local_x++) {
	    int block_x = (x*16)+local_x;

	    int idx = (local_y*16*16)+(local_z*16)+local_x;
#define NOISE_DEC 0.2
#define NOISE_DEC_2 2
	    int is_filled = buffer[mazelib_get_cell_index ( ((block_x/2)+48/2)%width, ((block_z/2)+48/2)%height, height )];
	    if(block_y < 1)
	      section.block_states.data[idx] = 9;
	    else if(abs(block_x) > 48 || abs(block_z) > 48)
	      section.block_states.data[idx] = 0;
	    else if(is_filled && block_y < 3) {
	      //section.block_states.data[idx] = 1;
	      //printf("%f\n", noise1);
		section.block_states.data[idx] = 1;
	      
	    } else
	      section.block_states.data[idx] = 0;

	  }
	}
      }
    else {
      section.block_states.format = 0;
      section.block_states.bits_per_entry = 0;
      section.block_states.value = 1;

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
