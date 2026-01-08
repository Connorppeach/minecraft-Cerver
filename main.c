#include <errno.h>

#include "protocol/rw.h"
#include "protocol/packets.h"
#include "blocks.h"
#include "simple_server/util.h"
#include "simple_server/player.h"
#include "simple_server/simple_server.h"

#define MAZELIB_IMPLEMENTATION
#include "include/mazelib.h"
#include "include/komihash.h"

#include "include/FastNoiseLite.h"

void teleport_player(simple_server *server, int player_num, double x, double y, double z);
void send_game_event(simple_server *server, int player_num, uint8_t event, float value);
void send_set_center_chunk(simple_server *server, int player_num, int32_t x, int32_t y);
void send_chunks(simple_server *server, int player_num, int32_t x, int32_t z);
void send_chunks_maze(simple_server *server, int player_num, int32_t x, int32_t z);
void send_spawn_entity(simple_server *server, int player_num, int32_t entity_id, uuid entity_uuid, int32_t type, double x, double y, double z, uint8_t pitch, uint8_t yaw, uint8_t head_yaw, int32_t data, uint16_t velocity_x, uint16_t velocity_y, uint16_t velocity_z);

#define PORT 25545   // port we're listening on
#define WRITE_BUF_SIZE 1310720
#define CONSOLE_READ_BUF_SIZE 256

// settings
#define MAX_PLAYERS 10
#define WORLD_GEN_LIMIT 6
// world gen settings
// cave settings
#define CAVE_SCALE 0.2
#define CAVE_CENTER 40
#define CAVE_BOOST_AT_CENTER 0.8
// heightmap settings
#define HEIGHTMAP_INITIAL_HEIGHT_MAX 32
#define HEIGHTMAP_XZ_SCALE 2
#define HEIGHTMAP_XZ_MULT_SCALE 128
#define HEIGHTMAP_Y_ADD 60

#define BIOME_SCALE 1024


char buffer[CONSOLE_READ_BUF_SIZE];
int stdin_fd;
uint8_t write_buf[WRITE_BUF_SIZE];
int total_ticks = 0;

void handle_packet_cb(simple_server *server, int player_num, int packet_type, uint8_t *packet_buf, unsigned int buf_len) {
  player* m_player = server->players[player_num];
  uint32_t pos = 0;
  if(packet_type == SERVERBOUND_KNOWN_PACKS_CONFIGURATION_ID) {
    /* serverbound_known_packs packet; */
    /* read_serverbound_known_packs(&packet_buf, &pos, buf_len, &packet); */
    /* print_serverbound_known_packs(packet, 0) */;
  }
  //printf("got packet %d\n", packet_type);
}
void read_console_command(simple_server *server) {
  fd_set read_fds;
  struct timeval tv;
  int retval;

  FD_ZERO(&read_fds);
  FD_SET(stdin_fd, &read_fds);

  tv.tv_sec = 0;
  tv.tv_usec = 500;
  fflush(stdout);
  retval = select(stdin_fd + 1, &read_fds, NULL, NULL, &tv);

  if (retval == -1) {
    perror("select()");
  } else if (retval) {
    if (fgets(buffer, CONSOLE_READ_BUF_SIZE, stdin) != NULL) {
      if(strcmp(buffer, "stop\n") == 0)
	server->should_stop = true;
      else if(strcmp(buffer, "minehut\n") == 0)
	freopen("log.txt", "a", stdout);

    } else if (feof(stdin)) {
      // todo -- do something
    } else if (errno == EAGAIN || errno == EWOULDBLOCK) {
    }
  } 
}


void tick_callback(simple_server *server) {
  for (int i = 0; i < server->max_players; i++) {
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

  // read fron console
  read_console_command(server);

}

void on_move_cb(simple_server *server, int player_num, mc_location old_location, mc_location new_location) {
  //player *m_player = server->players[player_num];
  uint8_t crossed_x_chunk_bound = ((int)new_location.x%16 == 0 && (int)old_location.x%16 != 0);
  uint8_t crossed_z_chunk_bound = ((int)new_location.z%16 == 0 && (int)old_location.z%16 != 0);
  /* printf("username: %s\n  x: %lf\n  y: %lf\n  z: %lf\n  pitch: %f\n  yaw: %f\n  x: %lf\n  y: %lf\n  z: %lf\n  pitch: %f\n  yaw: %f\n", */
  /* 	   m_player->username, */
  /* 	   m_player->loc.x, */
  /* 	   m_player->loc.y, */
  /* 	   m_player->loc.z, */
  /* 	   m_player->loc.pitch, */
  /* 	   m_player->loc.yaw, */
  /* 	   old_location.x, */
  /* 	   old_location.y, */
  /* 	   old_location.z, */
  /* 	   old_location.pitch, */
  /* 	   old_location.yaw) */ ;

  if((old_location.x != new_location.x && old_location.z != new_location.z) && (crossed_x_chunk_bound || crossed_z_chunk_bound)) { // crossed a chunk boundry
    //printf("more_than_16: %f, %f\n", old_location.z - new_location.z, old_location.x - new_location.x);
    int8_t direction[2] = {0, 0};
    if(crossed_x_chunk_bound)
      direction[0] = (new_location.x < old_location.x) ? -1 : 1;
    if(crossed_z_chunk_bound)
      direction[1] = (new_location.z < old_location.z) ? -1 : 1;

    int new_chunk_x = (int)round(new_location.x/16);
    int new_chunk_z = (int)round(new_location.z/16);
    /* new_chunk_x += direction[0]+WORLD_GEN_LIMIT; */
    /* new_chunk_z += direction[1]+WORLD_GEN_LIMIT; */
    send_set_center_chunk(server, player_num, new_chunk_x, new_chunk_z);
    int to_add_x = direction[0]*WORLD_GEN_LIMIT;
    int final_x = new_chunk_x + to_add_x;

    int to_add_z = direction[1]*WORLD_GEN_LIMIT;
    int final_z = new_chunk_z + to_add_z;

    /* if(final_x > 0) */
    /*   final_x -= 1; */
    /* if(final_z > 0) */
    /*   final_z -= 1; */
    for(int j = -1; j < 1; j++)
      for(int i = -WORLD_GEN_LIMIT-1; i < WORLD_GEN_LIMIT+1; i++) {
	if(direction[1] != 0)
	  send_chunks(server, player_num, new_chunk_x+i, final_z-(j*direction[1]));
	if(direction[0] != 0)
	  send_chunks(server, player_num, final_x-(j*direction[0]), new_chunk_z+i);
      }

      //printf("%d, %d\n", final_x, final_z);
  }
  
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
  teleport_player(server, player_num, 8.5, 70, 8.5);
  for(int x = -WORLD_GEN_LIMIT-1; x < WORLD_GEN_LIMIT+1; x++)
    for(int y = -WORLD_GEN_LIMIT-1; y < WORLD_GEN_LIMIT+1; y++)
      send_chunks(server, player_num, x, y);
  teleport_player(server, player_num, 8.5, 70, 8.5);

  //uuid rand_uuid = (uuid){ 0, 0 }; // funny trick
  //send_spawn_entity(server, player_num, 1, rand_uuid, 4, -18, 1, -2, 0, 0, 192, 0, 0, 0, 0);
}

int main(void)
{
  stdin_fd = fileno(stdin); // Get file descriptor for stdin
  fcntl(stdin_fd, F_SETFL, fcntl(stdin_fd, F_GETFL) | O_NONBLOCK);
  simple_server *server =  allocate_simple_server(MAX_PLAYERS);
  puts("starting server");
  start_server(server, PORT, (simple_server_callback){ handle_packet_cb, tick_callback, finish_configuration_cb, on_move_cb });
  fcntl(stdin_fd, F_SETFL, fcntl(stdin_fd, F_GETFL) & ~O_NONBLOCK);
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
  packet.velocity.x = 0.0;
  packet.velocity.y = 0.0;
  packet.velocity.z = 0.0;
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
  int error = write_set_center_chunk(&packet_ptr, &max, WRITE_BUF_SIZE, packet);
  send_packet(write_buf, max, server->players[player_num]->conn.fd);
  if(error)
    printf("error setting center chunk: %d\n", error);
}


uint64_t get_hash_at_point(int x, int y, int z, int seed) {
  int to_hash[3] = { x, y, z };
  return komihash(to_hash, sizeof(to_hash), seed);
}

// send basic world data
void send_chunks(simple_server *server, int player_num, int32_t x, int32_t z) {
  int32_t chunk_data[4096*24];
  /* for(int i = 0; i < 4096*24; i++) */
  /*   chunk_data[i] = MINECRAFT_AIR; */
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
  
  float heightmap[16][16];
  float biome_map[16][16];
  for(int x2 = 0; x2 < 16; x2++)
    for(int z2 = 0; z2 < 16; z2++){
      heightmap[x2][z2] = ((fnlGetNoise2D(&noise_2d, ((float)(x*16)+x2)/HEIGHTMAP_XZ_SCALE, ((float)(z*16)+z2)/HEIGHTMAP_XZ_SCALE)+1)/2)*HEIGHTMAP_INITIAL_HEIGHT_MAX;
      heightmap[x2][z2] *= ((fnlGetNoise2D(&noise_2d_2, ((float)(x*16)+x2)/HEIGHTMAP_XZ_MULT_SCALE, ((float)(z*16)+z2)/HEIGHTMAP_XZ_MULT_SCALE)+1)/2);
      heightmap[x2][z2] += HEIGHTMAP_Y_ADD;

      biome_map[x2][z2] = ((fnlGetNoise2D(&noise_2d, ((float)(x*16)+x2)/BIOME_SCALE, ((float)(z*16)+z2)/BIOME_SCALE)+1)/2);
    }
  
  for(int i = 0; i < 24; i++) {
    // write chunk data to our array
      for(int local_y = 0; local_y < 16; local_y++) {
	float block_y = (i*16)+local_y;
	for(int local_z = 0; local_z < 16; local_z++) {
	  float block_z = (z*16)+local_z;
	  for(int local_x = 0; local_x < 16; local_x++) {
	    float block_x = (x*16)+local_x;
	    int idx = (i*4096)+(local_y*16*16)+(local_z*16)+local_x;

	    float block_x_warped = block_x;
	    float block_y_warped = block_y;
	    float block_z_warped = block_z;
	    fnlDomainWarp3D(&noise_caves, &block_x_warped, &block_y_warped, &block_z_warped);
	    float noise1 = (fnlGetNoise3D(&noise_caves, block_x_warped/CAVE_SCALE, block_y_warped/CAVE_SCALE, block_z_warped/CAVE_SCALE)+1)/2;
	    // make caves much more likely at cave center
	    float height_offset = fabsf((float)(block_y - CAVE_CENTER) / HEIGHTMAP_INITIAL_HEIGHT_MAX) + 1.0f;
	    float cave_multiplier = (1.0f / height_offset) * CAVE_BOOST_AT_CENTER;
	    if((int)heightmap[local_x][local_z] > block_y) {
	      //section.block_states.data[idx] = 1;
	      //printf("%f, %f\n", cave_multiplier, block_y);
	      if (noise1*cave_multiplier > 0.45) {//noise2 < 0.5 && 
	        chunk_data[idx] = MINECRAFT_AIR;
	      } else {
		uint64_t hash1 = get_hash_at_point((int)block_x, (int)block_y, (int)block_z, 0);
		chunk_data[idx] = MINECRAFT_STONE;
		int ore_to_spawn = (hash1&255);
		if(ore_to_spawn == 0)
		  chunk_data[idx] = MINECRAFT_GOLD_ORE;
		else if(ore_to_spawn == 1)
		  chunk_data[idx] = MINECRAFT_DIAMOND_ORE;
		  
		if((int)heightmap[local_x][local_z]-1 <= block_y)
		  chunk_data[idx] = MINECRAFT_GRASS_BLOCK__SNOWY_FALSE;
		else if((int)heightmap[local_x][local_z]-3 <= block_y)
		  chunk_data[idx] = MINECRAFT_DIRT;
		
	      }
	    } else
	      chunk_data[idx] = MINECRAFT_AIR;

	  }
	}
      }

      
    
    
  }
  /* region *r = allocate_region(); */
  /* add_chunk_to_region(r, x, z, chunk_data, 24); */
  /* FILE *fptr; */
  /* fptr = fopen("test.mcr", "wb"); */
  /* if (fptr == NULL) { */
  /*   // Error handling (e.g., print error message, exit program) */
  /*   printf("Error opening file!\n"); */
  /*   return; */
  /* } */
  
  /* write_region(fptr, r); */
  /* fclose(fptr); */

  /* free_region(r); */

  send_chunk_packet(write_buf, WRITE_BUF_SIZE, server->players[player_num]->conn.fd, chunk_data, 24, x, z);
}


 


