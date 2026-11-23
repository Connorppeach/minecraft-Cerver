#include "simple_server.h"
#include "registry.h"
#include <time.h>



simple_server* allocate_simple_server(int max_players, void *ctx) {
  simple_server *server = malloc(sizeof(simple_server));
  server->players = malloc(sizeof(player*)*max_players);
  server->player_slots = malloc(sizeof(uint8_t)*max_players);
  for(int i = 0; i < max_players; i++) {
    server->players[i] = NULL;
    server->player_slots[i] = 0;
  }
  server->max_players = max_players;
  server->should_stop = 0;
  server->ctx = ctx;
  server->world_data.world_height = 384;// default
  return server;
}
static inline int floor_chunk_coord(float block_coord) {
  return (int)floorf(block_coord / 16.0f);
}


// returns player id
int allocate_player(simple_server *server, int fd) { 
  for (int i = 0; i < server->max_players; i++) {
    if(server->player_slots[i] != 1) {
      server->players[i] = create_player(fd);
      server->players[i]->id = i;
      server->player_slots[i] = 1;
      return i;
    }
  }
  return -1;
}

void deallocate_player(simple_server *server, simple_server_callback cb, int player_id) {
  if(server->player_slots[player_id]) {
    puts("deallocating player");
    if(cb.player_disconnected)
      cb.player_disconnected(server, player_id);
    /* if(server->cb.player_leave) */
    /*   server->cb.player_leave(server, player_id); */
    FD_CLR(server->players[player_id]->conn.fd, &server->master); // remove from master set
    free_player(server->players[player_id]);
    server->players[player_id] = NULL;
    server->player_slots[player_id] = 0;
  }
}








#define WRITE_BUF_SIMPLE_SERVER_SIZE 2519
uint8_t write_buf_simple_server[WRITE_BUF_SIMPLE_SERVER_SIZE];

void on_chunk_move(simple_server *server, int player_num, mc_location old_location, mc_location new_location, simple_server_callback cb) {
  if(cb.player_load_chunks == NULL) return;
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

    int new_chunk_x = floor_chunk_coord(new_location.x);
    int new_chunk_z = floor_chunk_coord(new_location.z);

    /* new_chunk_x += direction[0]+WORLD_GEN_LIMIT; */
    /* new_chunk_z += direction[1]+WORLD_GEN_LIMIT; */
    send_set_center_chunk(write_buf_simple_server, WRITE_BUF_SIMPLE_SERVER_SIZE, server->players[player_num]->conn.fd, new_chunk_x, new_chunk_z);
    int to_add_x = direction[0]*server->world_data.view_distance;
    int final_x = new_chunk_x + to_add_x;

    int to_add_z = direction[1]*server->world_data.view_distance;
    int final_z = new_chunk_z + to_add_z;

    /* if(final_x > 0) */
    /*   final_x -= 1; */
    /* if(final_z > 0) */
    /*   final_z -= 1; */
    for(int j = -1; j < 1; j++)
      for(int i = -server->world_data.view_distance-1; i < server->world_data.view_distance+1; i++) {
	if(direction[1] != 0)
	  cb.player_load_chunks(server, player_num, new_chunk_x+i, final_z-(j*direction[1]));
	if(direction[0] != 0)
	  cb.player_load_chunks(server, player_num, final_x-(j*direction[0]), new_chunk_z+i);
      }

    //printf("%d, %d\n", final_x, final_z);
  }  
}
int handle_player_packet(simple_server *server, int player_num, uint8_t *packet_buf, unsigned int buf_len, simple_server_callback cb) {
  if(!server->player_slots[player_num])
    return 1;

  
  int packet_type;
  unsigned int pos = 0;
  int error = read_var_int(&packet_buf, &pos, buf_len, &packet_type);
  if(error) {
    printf("error in client, %d\n", error);
    deallocate_player(server, cb, player_num);
    return 1;
  }
  if(cb.packet_callback)
    cb.packet_callback(server, player_num, packet_type, packet_buf, buf_len);

  // make a copy of the packet(remember to free if you return)
  uint8_t *raw_data = malloc(buf_len*sizeof(uint8_t));
  uint8_t *buf_ptr = raw_data;
  for(int i = 0; i < buf_len; i++)
    raw_data[i] = packet_buf[i];

  // util write packet buffer
  uint32_t max = 0;
  player *m_player = server->players[player_num];
  
  //printf("got packet id %d with len %d\n", packet_type, buf_len);
  if (m_player->conn.connection_state == 0 && packet_type == HANDSHAKE_ID) {
    handshake shake;
    int error = read_handshake(&buf_ptr, &pos, buf_len, &shake);
    //print_handshake(shake, 0);

    // we dont handle anything other than login right now
    if (shake.intent != 2 && shake.intent != 1) {
      printf("error reading intent: %d\n", error);
      deallocate_player(server, cb, player_num);
      free(raw_data);
      return 1;
    }
    free_handshake(shake);
    m_player->conn.connection_state = shake.intent;
  } else if (m_player->conn.connection_state == 1) {
    if (packet_type == STATUS_REQUEST_ID) {
      send_status_response_packet(write_buf_simple_server, WRITE_BUF_SIMPLE_SERVER_SIZE, server->players[player_num]->conn.fd,
			   (status_response){
			     .json_response = lstr_static("{\n    \"version\": {\n        \"name\": \"26.2\",\n        \"protocol\": 776\n    },\n    \"players\": {\n        \"max\": 2028,\n        \"online\": 2026,\n        \"sample\": [\n            {\n                \"name\": \"thinkofdeath\",\n                \"id\": \"4566e69f-c907-48ee-8d71-d7ba5aa00d20\"\n            }\n        ]\n    },\n    \"description\": {\n        \"text\": \"Hello, world!\"\n    },\n    \"favicon\": \"data:image\/png;base64,<data>\",\n    \"enforcesSecureChat\": false\n}")
			   });
    }
  } else if (m_player->conn.connection_state == 2) {
    if (packet_type == LOGIN_START_ID) {
      login_start login_s;
      read_login_start(&buf_ptr, &pos, buf_len, &login_s);
      //print_login_start(login_s, 0);
      int i;
      for (i = 0; i < 16; i++) {
	if(i < login_s.name.len)
	  m_player->username[i] = login_s.name.str[i];
	else
	  m_player->username[i] = 0;
      }
      
      m_player->username[i++] = 0;
      m_player->uuid = login_s.uuid;
      //puts("\nplayer login\n");

      // you shall not pass
      //disconnect_player(player_num);

      // you may pass
      send_login_success_packet(write_buf_simple_server,
				WRITE_BUF_SIMPLE_SERVER_SIZE,
				server->players[player_num]->conn.fd,
				(login_success){ .profile = {.uuid = login_s.uuid, .username = login_s.name, .game_profile_property_count = 0}, .session_id = (uuid){}});
      free_login_start(login_s);
      
    } else if (packet_type == LOGIN_ACKNOWLEDGED_ID) {
      puts("\nlogin finish\n");
      m_player->conn.connection_state = 3;
      known_pack packs[] = { (known_pack){lstr_static("minecraft"), lstr_static("core"), lstr_static("26.2")} };

      send_clientbound_known_packs_packet(write_buf_simple_server,
					  WRITE_BUF_SIMPLE_SERVER_SIZE,
					  server->players[player_num]->conn.fd,
					  (clientbound_known_packs){packs, 1});

    } 
  } else if (m_player->conn.connection_state == 3) {
    if (packet_type == CLIENT_INFORMATION_CONFIGURATION_ID) {
      client_information_configuration config_s;
      read_client_information_configuration(&buf_ptr, &pos, buf_len, &config_s);
      //print_client_information_configuration(config_s, 0);
      free_client_information_configuration(config_s);
      
    } else if (packet_type == SERVERBOUND_KNOWN_PACKS_CONFIGURATION_ID) {
      serverbound_known_packs config_s;
      read_serverbound_known_packs(&buf_ptr, &pos, buf_len, &config_s);
      //print_serverbound_known_packs(config_s, 0);
      free_serverbound_known_packs(config_s);
      uint8_t *packet_ptr;
      send_registry_packet(server, player_num, write_buf_simple_server, WRITE_BUF_SIMPLE_SERVER_SIZE);

      {// finish configuration
	packet_ptr = write_buf_simple_server+4;
	max = 0;
	write_var_int(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, FINISH_CONFIGURATION_ID);
	//finish_configuration config;
	
	//write_finish_configuration(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, config);
	send_packet(write_buf_simple_server, max, m_player->conn.fd);
	puts("finishing login");
      }      
    } else if (packet_type == ACKGNOWLEDGE_SERVER_CONFIGURATION_ID) {
      puts("\nconfiguration finished\n");
      m_player->conn.connection_state = 4; // yippee, play state
      {
	login_play play;
	play.eid = player_num+1;
	play.is_hardcore = 0;
	lstr dim_names[] = { lstr_static("minecraft:overworld") };
	play.dimension_names = &*dim_names;
	play.dimension_name_count = 1;
	play.max_players = 1;
	play.view_distance = server->world_data.view_distance;
	play.simulation_distance = 10;
	play.reduced_debug_info = 0;
	play.enable_respawn_screen = 0;
	play.do_limited_crafting = 0;
	play.dimension_type = 0;
	play.dimension_name = lstr_static("minecraft:overworld");
	play.hashed_seed = 0;
	play.game_mode = 0;
	play.prev_game_mode = -1;
	play.is_debug = 0;
	play.is_flat = 0;
	play.has_death_location = 0;
	play.portal_cooldown = 10;
	play.sea_level = 10;
	play.enforces_secure_chat = 0;
	play.online_mode = 1;
	send_login_play_packet(write_buf_simple_server, WRITE_BUF_SIMPLE_SERVER_SIZE, m_player->conn.fd, play);
      }      
      if(cb.finish_login_play)
	cb.finish_login_play(server, player_num);
      int spawn_chunk_x = floor_chunk_coord(server->players[player_num]->loc.x);
      int spawn_chunk_z = floor_chunk_coord(server->players[player_num]->loc.z);
      send_set_center_chunk(write_buf_simple_server, WRITE_BUF_SIMPLE_SERVER_SIZE, server->players[player_num]->conn.fd, spawn_chunk_x, spawn_chunk_z);
      for(int x = -server->world_data.view_distance-1; x < server->world_data.view_distance+1; x++)
	for(int y = -server->world_data.view_distance-1; y < server->world_data.view_distance+1; y++)
	  cb.player_load_chunks(server, player_num, x+spawn_chunk_x, y+spawn_chunk_z);
    }
  } else if (m_player->conn.connection_state == 4) { // play
    if (packet_type == SET_PLAYER_POSITION_ID) {
      set_player_position packet;
      mc_location old_loc = m_player->loc;
      read_set_player_position(&buf_ptr, &pos, buf_len, &packet);
      m_player->loc.x = packet.x;
      m_player->loc.y = packet.y;
      m_player->loc.z = packet.z;

      m_player->velocity.x = old_loc.x-packet.x;
      m_player->velocity.y = old_loc.y-packet.y;
      m_player->velocity.z = old_loc.z-packet.z;

      if(cb.on_move)
	cb.on_move(server, player_num, old_loc, m_player->loc);
      on_chunk_move(server, player_num, old_loc, m_player->loc, cb);
    } else if(packet_type == SET_PLAYER_POSITION_AND_ROTATION_ID) {
      set_player_position_and_rotation packet;
      mc_location old_loc = m_player->loc;
      read_set_player_position_and_rotation(&buf_ptr, &pos, buf_len, &packet);

      m_player->velocity.x = old_loc.x-packet.x;
      m_player->velocity.y = old_loc.y-packet.y;
      m_player->velocity.z = old_loc.z-packet.z;

      m_player->loc.x = packet.x;
      m_player->loc.y = packet.y;
      m_player->loc.z = packet.z;
      m_player->loc.yaw = packet.yaw;
      m_player->loc.pitch = packet.pitch;
      if(cb.on_move)
	cb.on_move(server, player_num, old_loc, m_player->loc);
      on_chunk_move(server, player_num, old_loc, m_player->loc, cb);
    } else if(packet_type == SET_PLAYER_ROTATION_ID) {
      set_player_rotation packet;
      mc_location old_loc = m_player->loc;
      read_set_player_rotation(&buf_ptr, &pos, buf_len, &packet);
      m_player->loc.yaw = packet.yaw;
      m_player->loc.pitch = packet.pitch;
      if(cb.on_move)
	cb.on_move(server, player_num, old_loc, m_player->loc);
      on_chunk_move(server, player_num, old_loc, m_player->loc, cb);
    }

  }
    
  
  free(raw_data);
  return 0;
}

void handle_packet(simple_server *server, int player_num, uint8_t *buf, int nbytes, simple_server_callback cb) {
  //puts("new packet");
  player *m_player = server->players[player_num];
  uint8_t *read_buf;
  uint8_t *read_buf_original;
  if (m_player->conn.backlog != NULL) {
    int total_bytes = nbytes+m_player->conn.backlog_len;
    read_buf_original = malloc(total_bytes+1);
    read_buf = read_buf_original;
    int i2=0;
    for(int i = 0; i < total_bytes; i++) {
      
      if(i < m_player->conn.backlog_len)
	read_buf[i] = m_player->conn.backlog[i];
      else {
	read_buf[i] = buf[i2];
	i2++;
      }
    }
    nbytes = total_bytes;
  } else {
    int total_bytes = nbytes;
    read_buf_original = malloc(total_bytes+1); // no backlog
    read_buf = read_buf_original;
    for(int i = 0; i < total_bytes; i++)
      read_buf_original[i] = buf[i];
  }
  uint32_t pos = 0;
  int packet_len;
		      
  int error = read_var_int(&read_buf, &pos, nbytes, &packet_len);
  if (error) {
    printf("error reading len: %d\n", error); // todo -- append to backlog
    deallocate_player(server, cb, player_num);
    return;
  }
  uint32_t remaining_data = nbytes-pos;


  if (remaining_data < packet_len) {
    /* printf("error: too little data supplied\ndata remaining after read: %d\n", remaining_data);// todo -- append to backlog */
    /* printf("data needed to read more: %d\n", packet_len); */
    /* printf("we have: %d\n", nbytes); */
    if (m_player->conn.backlog != NULL)
      free(m_player->conn.backlog);
    m_player->conn.backlog_len = nbytes;
    m_player->conn.backlog = malloc(nbytes);
    for(int i = 0; i < nbytes; i++)
      m_player->conn.backlog[i] = read_buf_original[i];
    free(read_buf_original);
    //deallocate_player(server, player_num);
    //if(read_buf_2) free(read_buf_2);
    return;
  }
  int left = nbytes-packet_len-pos;
  uint8_t more = left>0;
  uint8_t *left_off = read_buf+packet_len;
  //printf("packet len: %d\nleft: %d\n", packet_len, left);
  error = handle_player_packet(server, player_num, read_buf, packet_len, cb);
  if (error) {

    free(read_buf_original); // done, at last
    deallocate_player(server, cb, player_num);
    return;
  }
  if (more) {
    /* printf("error: too much data supplied\ndata left: %d\n", remaining_data); */
    /* printf("data left: %d\n", left); */
    /* deallocate_player(player_num) */;
    //printf("more\n");
    handle_packet(server, player_num, left_off, left, cb);
  } else {
    if (m_player->conn.backlog != NULL) {
	free(m_player->conn.backlog);
	m_player->conn.backlog = NULL;
	m_player->conn.backlog_len = 0;
    }

  }
  free(read_buf_original);

}


int start_server(simple_server *server, int port, simple_server_callback cb)
{
  //server->cb = cb;
  // master file descriptor list
  struct sockaddr_in myaddr;     // server address
  int fdmax;        // maximum file descriptor number
  int listener;     // listening socket descriptor
  int yes=1;        // for setsockopt() SO_REUSEADDR, below
  server->should_stop = 0;
  FD_ZERO(&server->master);    // clear the master and temp sets

  // get the listener
  if ((listener = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
    perror("socket");
    exit(1);
  }

  // lose the pesky "address already in use" error message
  if (setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes,
		 sizeof(int)) == -1) {
    perror("setsockopt");
    exit(1);
  }

  // bind
  myaddr.sin_family = AF_INET;
  myaddr.sin_addr.s_addr = INADDR_ANY;
  myaddr.sin_port = htons(port);
  memset(&(myaddr.sin_zero), '\0', 8);
  if (bind(listener, (struct sockaddr *)&myaddr, sizeof(myaddr)) == -1) {
    perror("bind");
    exit(1);
  }

  // listen
  if (listen(listener, 10) == -1) {
    perror("listen");
    exit(1);
  }

  // add the listener to the master set
  FD_SET(listener, &server->master);

  // keep track of the biggest file descriptor
  fdmax = listener; // so far, it's this one
  struct timespec start_time, current_time;
  long elapsed_ns; // Nanoseconds

  clock_gettime(CLOCK_MONOTONIC, &start_time); // Get start time
    
  // Main loop
  for(;;) {
    if(server->should_stop)
      break;
    fd_set read_fds; // temp file descriptor list for select()
    FD_ZERO(&read_fds);
      
    read_fds = server->master; // copy it
    //puts("waiting");
    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = server->target_ns; // 20 milliseconds
    if(cb.loop_callback)
      cb.loop_callback(server);
    int select_ret = select(fdmax+1, &read_fds, NULL, NULL, &timeout);
    clock_gettime(CLOCK_MONOTONIC, &current_time); // Get current time

    elapsed_ns = ((int64_t)current_time.tv_sec - (int64_t)start_time.tv_sec) * (int64_t)1000000000
         + ((int64_t)current_time.tv_nsec - (int64_t)start_time.tv_nsec);

    if (elapsed_ns >= server->target_ns) {
      // user tick callback
      if(cb.tick_callback)
	cb.tick_callback(server);


      clock_gettime(CLOCK_MONOTONIC, &start_time); // reset clock
    }

    if (select_ret == -1) {
      perror("select");
      exit(1);
    } else if(select_ret == 0) {
      continue;
    }

    //puts("still going");
    // run through the existing connections looking for data to read
    for(int i = 0; i <= fdmax; i++) {
	  
      if (FD_ISSET(i, &read_fds)) { // we got one!!
	if (i == listener) {
	  // handle new connections
	  struct sockaddr_in remoteaddr; // client address
	  socklen_t addrlen = sizeof(remoteaddr);
	  int newfd;
	  if ((newfd = accept(listener, (struct sockaddr *)&remoteaddr,
			      &addrlen)) == -1) { 
	    perror("accept");

	  } else {
	    if (setsockopt(newfd, SOL_TCP, TCP_NODELAY, &yes, sizeof(yes)) < 0) {
	      perror("setsockopt(TCP_NODELAY) failed");
	      close(newfd);
	    }

	    int flags = fcntl(newfd, F_GETFL, 0);
	    if (flags == -1) {
	      // Handle error
	      perror("fcntl F_GETFL");
	    }

	    // Set the O_NONBLOCK flag
	    if (fcntl(newfd, F_SETFL, flags | O_NONBLOCK) == -1) {
	      // Handle error
	      perror("fcntl F_SETFL");
	    }



	    FD_SET(newfd, &server->master); // add to master set
	    allocate_player(server, newfd);


	    if (newfd > fdmax) {    // keep track of the maximum
	      fdmax = newfd;
	    }

			
	    /* printf("server: new connection from %s on " */
	    /* 	   "socket %d\n", inet_ntoa(remoteaddr.sin_addr), newfd); */
	  }
	} else {
	  int player_num = -1;
	  for (int k = 0; k < server->max_players; k++) {
	    if (server->player_slots[k] && server->players[k]->conn.fd == i) {
	      player_num = k;
	    }
	  }
	  if(player_num == -1)
	    puts("very bad stuff, no player id found");
	  int nbytes;
	  // handle data from a client
	  uint8_t buf[2048];    // buffer for client data
	  if ((nbytes = read(i, buf, sizeof(buf))) <= 0) {
	    // got error or connection closed by client
	    if (nbytes == 0) {
	      // connection closed
	      printf("server: socket %d hung up\n", i);
	      
	    } else {
	      perror("recv");
	    }
	    deallocate_player(server, cb, player_num);
	    FD_CLR(i, &server->master); // remove from master set
		    
	  } else {
	    // we got some data from a client
		    
	    handle_packet(server, player_num, buf, nbytes, cb);
	  }
	}
      }
    }
  }
    
  return 0;
} 




