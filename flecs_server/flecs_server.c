#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h> 
#include <arpa/inet.h>
#include <stdio.h>
#include <time.h>

#include "flecs_server.h"
#include "components.h"
#include "../protocol/packets.h"






int add_selectsocketcomponent(ecs_world_t *world, ecs_entity_t e, int port) {
  // main file descriptor list
  int yes=1;        // for setsockopt() SO_REUSEADDR, below
  selectsocketcomponent server;
  FD_ZERO(&server.main);    // clear the main and temp sets
  // get the listener
  if ((server.listener = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
    perror("socket");
    exit(1);
  }

  // lose the pesky "address already in use" error message
  if (setsockopt(server.listener, SOL_SOCKET, SO_REUSEADDR, &yes,
		 sizeof(int)) == -1) {
    perror("setsockopt");
    exit(1);
  }

  // bind
  server.myaddr.sin_family = AF_INET;
  server.myaddr.sin_addr.s_addr = INADDR_ANY;
  server.myaddr.sin_port = htons(port);
  memset(&(server.myaddr.sin_zero), '\0', 8);
  if (bind(server.listener, (struct sockaddr *)&server.myaddr, sizeof(server.myaddr)) == -1) {
    perror("bind");
    exit(1);
  }

  // listen
  if (listen(server.listener, 10) == -1) {
    perror("listen");
    exit(1);
  }

  FD_SET(server.listener, &server.main);

  // keep track of the biggest file descriptor
  server.fdmax = server.listener; // so far, it's this one
  ecs_set(world, e, selectsocketcomponent, { server.main, server.myaddr, server.fdmax, server.listener });

    
  return 0;
}







void handle_tcp_buf(ecs_world_t *world, ecs_entity_t e, mc_connection *c, uint8_t *buf, int nbytes) {
  //puts("new packet");
  uint8_t *read_buf;
  uint8_t *read_buf_original;
  if (c->backlog != NULL) {
    int total_bytes = nbytes+c->backlog_len;
    read_buf_original = malloc(total_bytes+1);
    read_buf = read_buf_original;
    int i2=0;
    for(int i = 0; i < total_bytes; i++) {
      
      if(i < c->backlog_len)
	read_buf[i] = c->backlog[i];
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
    //deallocate_player(server, player_num);
    return;
  }
  uint32_t remaining_data = nbytes-pos;


  if (remaining_data < packet_len) {
    /* printf("error: too little data supplied\ndata remaining after read: %d\n", remaining_data);// todo -- append to backlog */
    /* printf("data needed to read more: %d\n", packet_len); */
    /* printf("we have: %d\n", nbytes); */
    if (c->backlog != NULL)
      free(c->backlog);
    c->backlog_len = nbytes;
    c->backlog = malloc(nbytes);
    for(int i = 0; i < nbytes; i++)
      c->backlog[i] = read_buf_original[i];
    free(read_buf_original);
    //deallocate_player(server, player_num);
    //if(read_buf_2) free(read_buf_2);
    return;
  }
  int left = nbytes-packet_len-pos;
  uint8_t more = left>0;
  uint8_t *left_off = read_buf+packet_len;
  //printf("packet len: %d\nleft: %d\n", packet_len, left);
  //error = handle_player_packet(server, player_num, read_buf, packet_len, cb);
  ecs_entity_t child = ecs_new_w_pair(world, EcsChildOf, e);
  uint8_t *buf_copy = malloc(packet_len);
  memcpy(buf_copy, read_buf, packet_len);
  
  ecs_set(world, child, packetbuffer, { buf_copy, packet_len });
  if (error) {

    free(read_buf_original); // done, at last
    //deallocate_player(server, player_num);
    return;
  }
  if (more) {
    handle_tcp_buf(world, e, c, left_off, left);
  } else {
    if (c->backlog != NULL) {
	free(c->backlog);
	c->backlog = NULL;
	c->backlog_len = 0;
    }

  }
  free(read_buf_original);
  ecs_add_id(world, child, remove_on_end);


}

void select_loop(ecs_iter_t *it) {
  int yes=1;        // for setsockopt() SO_REUSEADDR, below

  selectsocketcomponent *s = ecs_field(it, selectsocketcomponent, 0);
  for (int i = 0; i < it->count; i++) {
    selectsocketcomponent *server = &s[i];
    fd_set read_fds; // temp file descriptor list for select()
    FD_ZERO(&read_fds);




    
    read_fds = server->main; // copy it
    //puts("waiting");
    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 0; // 20 milliseconds
    int select_ret = select(server->fdmax+1, &read_fds, NULL, NULL, &timeout);
    //clock_gettime(CLOCK_MONOTONIC, &current_time); // Get current time

    if (select_ret == -1) {
      perror("select");
      exit(1);
    } else if(select_ret == 0) {
      continue;
    }

    //puts("still going");
    // run through the existing connections looking for data to read
    for(int j = 0; j <= server->fdmax; j++) {
      if (FD_ISSET(j, &read_fds)) { // we got one!!
	if (j == server->listener) {
	  // handle new connections
	  struct sockaddr_in remoteaddr; // client address
	  socklen_t addrlen = sizeof(remoteaddr);
	  int newfd;
	  if ((newfd = accept(server->listener, (struct sockaddr *)&remoteaddr,
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



	    FD_SET(newfd, &server->main); // add to main set
	    
	    ecs_set(it->world, ecs_new(it->world), mc_connection, { newfd, NULL, 0, 0 });
	    server = ecs_get_mut(it->world, it->entities[i], selectsocketcomponent);
	    if (newfd > server->fdmax) {    // keep track of the maximum
	      server->fdmax = newfd;
	    }

	  }
	} else {
	  int nbytes;
	  // handle data from a client
	  uint8_t buf[1024];    // buffer for client data
	  
	  if ((nbytes = read(j, buf, sizeof(buf))) <= 0) {
	    // got error or connection closed by client
	    if (nbytes == 0) {
	      // connection closed
	      printf("server: socket %d hung up\n", j);
	      
	    } else {
	      perror("recv");
	    }
	    //printf("got %d bytes\n", nbytes);
	    // todo -- free players?
	    //deallocate_player(server, player_num);
	    FD_CLR(j, &server->main); // remove from main set
	  } else {
	    // we got some data from a client
	    // todo -- make this not stupid
	    
	    ecs_query_t *q = ecs_query(it->world, {
		.terms = { { ecs_id(mc_connection) } }
	      });
	    ecs_iter_t it_new = ecs_query_iter(it->world, q);
	    while (ecs_query_next(&it_new)) {
	      mc_connection *s = ecs_field(&it_new, mc_connection, 0);
	      for (int k = 0; k < it_new.count; k++) {
		ecs_entity_t entity = it_new.entities[k];	    
		
		if(s[k].fd == j) {
		  handle_tcp_buf(it->world, entity, &s[k], buf, nbytes);
		}
	      }
	    }
	  }
	}
      }
    }
  }
}


void handle_remove_on_end_system(ecs_iter_t *it) {
  for (int i = 0; i < it->count; i++) {
    ecs_delete(it->world, it->entities[i]);
  }
}


