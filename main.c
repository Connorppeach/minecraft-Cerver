#include <errno.h>

#include "protocol/rw.h"
#include "protocol/packets.h"
#include "blocks.h"
#include "simple_server/util.h"
#include "simple_server/player.h"
#include "simple_server/simple_server.h"

#include "include/FastNoiseLite.h"
#include "include/komihash.h"
#include "include/hashmap.h"
#include "util.h"
#define FILTER_IMPLEMENTATION
#include "filter.h"
#define PORT 25545   // port we're listening on
#define WRITE_BUF_SIZE 40000
#define CONSOLE_READ_BUF_SIZE 256

// settings
#define MAX_PLAYERS 10
#define WORLD_GEN_LIMIT 16

#define VIEW_DISTANCE 5

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

#define WORLD_SEED 124

struct hashmap_s chunk_data;

char buffer[CONSOLE_READ_BUF_SIZE];
int stdin_fd;
uint8_t write_buf[WRITE_BUF_SIZE];
int total_ticks = 0;

uint64_t get_hash_at_point(int x, int y, int z, int seed) {
  int to_hash[3] = { x, y, z };
  return komihash(to_hash, sizeof(to_hash), seed);
}





void send_chunks(simple_server *server, int player_num, int32_t x, int32_t z) {
  if(-WORLD_GEN_LIMIT+1 > x || WORLD_GEN_LIMIT < x || -WORLD_GEN_LIMIT+1 > z || WORLD_GEN_LIMIT < z) return;
  int32_t chunkpos[2] = {x,z};
  int32_t *chunk_data_ptr = hashmap_get(&chunk_data, &chunkpos, sizeof(chunkpos));
  /* for(int i = 0; i < 4096*24; i++) */
  /*   chunk_data[i] = MINECRAFT_AIR; */
  if(chunk_data_ptr == NULL) {
    chunk_data_ptr = malloc(sizeof(int32_t)*(4096*24));
    //printf("%s\n", "getting");
    //chunk_data_ptr = hashmap_get(&chunk_data, &((chunkpos){x, z}), sizeof(chunkpos));
    fnl_state noise_2d = fnlCreateState();
    noise_2d.noise_type = FNL_NOISE_PERLIN;
    noise_2d.frequency = 0.05;
    noise_2d.seed = WORLD_SEED+3;

    fnl_state noise_2d_2 = fnlCreateState();
    noise_2d_2.noise_type = FNL_NOISE_PERLIN;
    noise_2d_2.frequency = 0.05;
    noise_2d_2.seed = WORLD_SEED+21;
  
    fnl_state noise_caves = fnlCreateState();
    noise_caves.noise_type = FNL_NOISE_OPENSIMPLEX2;
    noise_caves.domain_warp_type = FNL_DOMAIN_WARP_OPENSIMPLEX2;
    noise_caves.domain_warp_amp = 3.0;
    noise_caves.octaves = 2;
    noise_caves.seed = WORLD_SEED+32;
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
	        chunk_data_ptr[idx] = MINECRAFT_AIR;
	      } else {
		uint64_t hash1 = get_hash_at_point((int)block_x, (int)block_y, (int)block_z, WORLD_SEED);
		chunk_data_ptr[idx] = MINECRAFT_STONE;
		int ore_to_spawn = (hash1&255);
		if(ore_to_spawn == 0)
		  chunk_data_ptr[idx] = MINECRAFT_GOLD_ORE;
		else if(ore_to_spawn == 1)
		  chunk_data_ptr[idx] = MINECRAFT_DIAMOND_ORE;
		  
		if((int)heightmap[local_x][local_z]-1 <= block_y)
		  chunk_data_ptr[idx] = MINECRAFT_GRASS_BLOCK__SNOWY_FALSE;
		else if((int)heightmap[local_x][local_z]-3 <= block_y)
		  chunk_data_ptr[idx] = MINECRAFT_DIRT;
		
	      }
	    } else
	      chunk_data_ptr[idx] = MINECRAFT_AIR;

	  }
	}
      }
    }
    int32_t *chunkpos_copy = malloc(sizeof(chunkpos));
    chunkpos_copy[0] = x;
    chunkpos_copy[1] = z;
    if(0 != hashmap_put(&chunk_data, chunkpos_copy, sizeof(chunkpos), chunk_data_ptr)){
      perror("putting in chunk hashmap failed");
      return;
    }
    
  } 
  send_chunk_packet(write_buf, WRITE_BUF_SIZE, server->players[player_num]->conn.fd, chunk_data_ptr, 24, x, z);
}
void send_set_entity_metadata(uint8_t *write_buf, int32_t write_buf_size, simple_server *server, int player_num, int32_t entity_id, entity_metadata meta) {
  set_entity_metadata packet;
  packet.entity_id = entity_id;
  entity_metadata meta_list[1] = { meta };
  packet.data = meta_list;
  packet.data_len = 1;
  uint8_t *packet_ptr = write_buf+4;
  uint32_t max = 0;
  write_var_int(&packet_ptr, &max, write_buf_size, SET_ENTITY_METADATA_ID);
  write_set_entity_metadata(&packet_ptr, &max, write_buf_size, packet);
  send_packet(write_buf, max, server->players[player_num]->conn.fd);
}
void handle_packet_cb(simple_server *server, int player_num, int packet_type, uint8_t *packet_buf, unsigned int buf_len) {
  player* m_player = server->players[player_num];
  if(m_player->conn.connection_state != 4) return;
  uint32_t pos = 0;
  if (packet_type == CHAT_MESSAGE_ID) {
    uint8_t should_send = 1;
    chat_message packet;
    read_chat_message(&packet_buf, &pos, buf_len, &packet);
    int filter_res = filter_str(packet.message.str, packet.message.len);
    if (filter_res) {
      should_send = 0;
      puts("didnt send: ");
    }
    lstr username = lstr_static(m_player->username);
    lstr delim = lstr_static(": ");
    lstr username_and_delim = lstr_append(username, delim);

    lstr message = lstr_append(username_and_delim, packet.message);
    free(username_and_delim.str);
    
    print_var_str(message, 0);
    
    nbt_tag_t *message_component = lstr2text_component(message);
    free(message.str);
    if(should_send)
      for(int i = 0; i < server->max_players; i++) {
	if(server->player_slots[i] != NULL) {
	  send_system_chat_message_packet(write_buf, WRITE_BUF_SIZE, server->players[player_num]->conn.fd,
					  (system_chat_message){.content = message_component,
								.overlay = 0});        
	}
      }
    nbt_free_tag(message_component);
    
    puts("");
    free_chat_message(packet);
  }
  if (packet_type == PLAYER_INPUT_ID) {
    player_input packet;
    read_player_input(&packet_buf, &pos, buf_len, &packet);
    /* uint8_t forward = packet.flags&0x1; */
    /* uint8_t backward = packet.flags&0x2; */
    /* uint8_t left = packet.flags&0x4; */
    /* uint8_t right = packet.flags&0x8; */
    /* uint8_t jump = packet.flags&0x10; */
    uint8_t is_sneaking = packet.flags&0x20;
    uint8_t is_sprinting = packet.flags&0x40;
    entity_metadata meta;
    meta.index = 0;
    meta.type = 0;
    meta.value.byte = 0;

    entity_metadata meta_2;
    meta_2.index = 6;
    meta_2.type = 20;
    meta_2.value.pose = 0;

    if(is_sneaking) {
      meta.value.byte |= 0x02;
      meta_2.value.pose = 5;
    }
    if(is_sprinting)
      meta.value.byte |= 0x08;
    
    for(int i = 0; i < server->max_players; i++) {
      if(server->player_slots[i] && i != player_num) {
	send_set_entity_metadata(write_buf, WRITE_BUF_SIZE, server, i, player_num, meta);
	send_set_entity_metadata(write_buf, WRITE_BUF_SIZE, server, i, player_num, meta_2);
      }
    }
    free_player_input(packet);
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

void tick_callback(simple_server *server) {
  for (int i = 0; i < server->max_players; i++) {
    if (server->player_slots[i]) {
      player* m_player = server->players[i];
      if(m_player->conn.connection_state == 4) {
	/* if(total_ticks % 5 == 0) // like, 1 seconds */
	/*   teleport_player(server, i, 0, y++, 0); */

	// send keepalives
	if(total_ticks % 400 == 0) {// like, 16 seconds
	  //send_all_players_to_players(server);
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
  for(int j = 0; j < server->max_players; j++)
    if(server->player_slots[j] &&
       server->players[j]->conn.connection_state == 4 &&
       j != player_num) {
      send_update_entity_position_and_rotation_packet(write_buf, WRITE_BUF_SIZE, server->players[j]->conn.fd,
						      (update_entity_position_and_rotation){
							.entity_id = player_num,
							.delta_x = new_location.x * 4096 - old_location.x,
							.delta_y = new_location.y * 4096 - old_location.y,
							.delta_z = new_location.z * 4096 - old_location.z,
							.yaw = new_location.yaw/1.41,
							.pitch = new_location.pitch/1.41,
							.on_ground = true});
      send_set_head_rotation_packet(write_buf, WRITE_BUF_SIZE, server->players[j]->conn.fd,
				    (set_head_rotation){
				      .entity_id = player_num,
				      .yaw = new_location.yaw
				    });
    }
};




void finish_configuration_cb(simple_server *server, int player_num) {
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
      entity_metadata meta;
      /* meta.index = 18; */
      /* meta.type = 9; */
      /* meta.value.rotations.x = 120; */
      /* meta.value.rotations.y = -120; */
      /* meta.value.rotations.z = 0; */
      /* send_set_entity_metadata(write_buf, WRITE_BUF_SIZE, server, player_num, new_id, meta); */
      meta.index = 15;
      meta.type = 0;
      meta.value.byte = 0x04;
      send_set_entity_metadata(write_buf, WRITE_BUF_SIZE, server, player_num, new_id, meta);

    }
    update_tab_list(write_buf, WRITE_BUF_SIZE, server);
    send_all_players_to_players(server);

  }
}


int main(void)
{
  if (0 != hashmap_create(32, &chunk_data)) {
    perror("failed to allocate chunk hashmap");
    return 1;
  }
  int filter_error = init_filter();
  if(filter_error) {
    printf("filter error: %d\nnot starting the server without the filter\n", filter_error);
    return 1;
  }
  stdin_fd = fileno(stdin); // Get file descriptor for stdin
  fcntl(stdin_fd, F_SETFL, fcntl(stdin_fd, F_GETFL) | O_NONBLOCK);
  simple_server *server =  allocate_simple_server(MAX_PLAYERS);
  server->world_data.view_distance = VIEW_DISTANCE;
  puts("starting server");
  simple_server_callback cb = (simple_server_callback){ handle_packet_cb, tick_callback, finish_configuration_cb, send_chunks, on_move_cb };
  
  start_server(server, PORT, cb);
  fcntl(stdin_fd, F_SETFL, fcntl(stdin_fd, F_GETFL) & ~O_NONBLOCK);
}




