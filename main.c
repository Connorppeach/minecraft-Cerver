#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h> 
#include <arpa/inet.h>
#include "rw.h"
#include "player.h"
#include "packets.h"

#define PORT 25565   // port we're listening on

#define MAX_PLAYERS 10
player *players[MAX_PLAYERS];
char player_slots[MAX_PLAYERS] = { 0 };
fd_set master;

// returns player id
int allocate_player(int fd) { 
  for (int i = 0; i < MAX_PLAYERS; i++) {
    if(player_slots[i] != 1) {
      players[i] = create_player(fd);
      player_slots[i] = 1;
      return i;
    }
  }
  return -1;
}
void deallocate_player(int player_id) {
  puts("deallocating player");
  FD_CLR(players[player_id]->conn.fd, &master); // remove from master set
  free_player(players[player_id]);
  players[player_id] = NULL;
  player_slots[player_id] = 0;
}



int vi_size(int val) {
  uint8_t header[5];
  uint8_t *header_ptr = header;
  uint32_t header_len = 0;
  write_var_int(&header_ptr, &header_len, 5, val);
  return header_len;
}

void send_packet(uint8_t *packet_buf, int packet_len, int fd) {
  // get header len
  uint32_t header_len = vi_size(packet_len);
  int offset = 4-header_len;
  
  uint8_t *packet_ptr = packet_buf+offset;
  
  write_var_int(&packet_ptr, &header_len, 4, packet_len);
  packet_ptr = packet_buf+offset;
  // get the final packet length for send()
  int len = header_len+packet_len;
  
  // send it off
  int sent = send(fd, packet_ptr, len, 0);
  
  printf("header_len %d, packet_len %d,len %d, sent %d\n", header_len, packet_len, len, sent);
}

void disconnect_player(int player_num) {
  if (players[player_num]->connection_state == 2) {
    char disconnect_message[] = "{\"type\": \"text\", \"text\": \"reason here\"}";
    lstr json = lstr_static(disconnect_message);
    disconnect_login packet;
    packet.json = json;
    // write initial packet
    uint8_t packet_buf[512];
    uint32_t max = 0;
    uint8_t *packet_ptr = packet_buf+4;
    
    write_var_int(&packet_ptr, &max, 512, DISCONNECT_LOGIN_ID);
    write_disconnect_login(&packet_ptr, &max, 512, packet);
    send_packet(packet_buf, max, players[player_num]->conn.fd);
  } else
    deallocate_player(player_num);
}

void handle_player_packet(int player_num, uint8_t *packet_buf, unsigned int buf_len) {
  int packet_type;
  unsigned int pos = 0;
  int error = read_var_int(&packet_buf, &pos, buf_len, &packet_type);
  if(error) {
    printf("error in client: %d\n", error);
    deallocate_player(player_num);
    return;
  }
  // make a copy of the packet(remember to free if you return)
  uint8_t *raw_data = malloc(buf_len*sizeof(uint8_t));
  uint8_t *buf_ptr = raw_data;
  for(int i = 0; i < buf_len; i++)
    raw_data[i] = packet_buf[i];


  // util write packet buffer
  uint8_t write_buf[512];
  uint32_t max = 0;

  
  printf("got packet id %d with len %d\n", packet_type, buf_len);
  if (players[player_num]->connection_state == 0 && packet_type == HANDSHAKE_ID) {
    handshake shake;
    int error = read_handshake(&buf_ptr, &pos, buf_len, &shake);
    print_handshake(shake);

    // we dont handle anything other than login right now
    if (shake.intent != 2) {
      printf("error: %d\n", error);
      deallocate_player(player_num);
      free(raw_data);
      return;
    }
    
    players[player_num]->connection_state = shake.intent;
  } else if (players[player_num]->connection_state == 2) {
    if (packet_type == LOGIN_START_ID) {
      login_start login_s;
      read_login_start(&buf_ptr, &pos, buf_len, &login_s);
      print_login_start(login_s);
      
      puts("login");
      uint8_t *packet_ptr = write_buf+4;

      // you shall not pass
      //disconnect_player(player_num);

      // you may pass
      write_var_int(&packet_ptr, &max, 512, LOGIN_SUCCESS_ID);
      write_login_success(&packet_ptr, &max, 512, (login_success){{login_s.uuid, lstr_static("test"), NULL, 0}});
      send_packet(write_buf, max, players[player_num]->conn.fd);
      
    } else if (packet_type == LOGIN_ACKNOWLEDGED_ID) {
      puts("login ack");
      players[player_num]->connection_state = 3;
    } 
  } else if (players[player_num]->connection_state == 3) {
    if (packet_type == CLIENT_INFORMATION_CONFIGURATION_ID) {
      puts("config");
      //
      client_information_configuration config_s;
      read_client_information_configuration(&buf_ptr, &pos, buf_len, &config_s);
      print_client_information_configuration(config_s);
      // send our known packs
      uint8_t *packet_ptr = write_buf+4;
      write_var_int(&packet_ptr, &max, 512, CLIENTBOUND_KNOWN_PACKS_ID);
      clientbound_known_pack packs[] = { (clientbound_known_pack){lstr_static("minecraft"), lstr_static("core"), lstr_static("1.21.8")} };
      write_clientbound_known_packs(&packet_ptr, &max, 512, (clientbound_known_packs){packs, 1});
      print_clientbound_known_packs((clientbound_known_packs){packs, 1});
      send_packet(write_buf, max, players[player_num]->conn.fd);
    }
  }
    
  
  free(raw_data);
  
}


int main(void)
{
       // master file descriptor list
    fd_set read_fds; // temp file descriptor list for select()
    struct sockaddr_in myaddr;     // server address
    struct sockaddr_in remoteaddr; // client address
    int fdmax;        // maximum file descriptor number
    int listener;     // listening socket descriptor
    int newfd;        // newly accept()ed socket descriptor
    uint8_t buf[1024];    // buffer for client data
    int nbytes;
    int yes=1;        // for setsockopt() SO_REUSEADDR, below
    socklen_t addrlen;
    int i;

    FD_ZERO(&master);    // clear the master and temp sets
    FD_ZERO(&read_fds);

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
    myaddr.sin_port = htons(PORT);
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
    FD_SET(listener, &master);

    // keep track of the biggest file descriptor
    fdmax = listener; // so far, it's this one
    
    // main loop
    for(;;) {
        read_fds = master; // copy it
        if (select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1) {
            perror("select");
            exit(1);
        }

        // run through the existing connections looking for data to read
        for(i = 0; i <= fdmax; i++) {
	  int player_num = -1;
	  for (int k = 0; k < MAX_PLAYERS; k++) {
	    if (player_slots[k] && players[k]->conn.fd == i) {
	      player_num = k;
	    }
	  }
	  
	  if (FD_ISSET(i, &read_fds)) { // we got one!!
                if (i == listener) {
                    // handle new connections
                    addrlen = sizeof(remoteaddr);
                    if ((newfd = accept(listener, (struct sockaddr *)&remoteaddr,
                                                             &addrlen)) == -1) { 
                        perror("accept");
			int flag = 1;
			if (setsockopt(newfd, IPPROTO_TCP, TCP_NODELAY, (char *)&flag, sizeof(int)) < 0) {
			  perror("setsockopt(TCP_NODELAY) failed");
			  close(newfd);
			}

                    } else {
                        FD_SET(newfd, &master); // add to master set
			allocate_player(newfd);
                        if (newfd > fdmax) {    // keep track of the maximum
                            fdmax = newfd;
                        }
                        printf("server: new connection from %s on "
                            "socket %d\n", inet_ntoa(remoteaddr.sin_addr), newfd);
                    }
                } else {
                    // handle data from a client
                    if ((nbytes = recv(i, buf, sizeof(buf), 0)) <= 0) {
                        // got error or connection closed by client
                        if (nbytes == 0) {
                            // connection closed
                            printf("server: socket %d hung up\n", i);
                        } else {
                            perror("recv");
                        }
			deallocate_player(player_num);
                        FD_CLR(i, &master); // remove from master set
			
                    } else {
		      // we got some data from a client
		      
		      uint8_t *read_buf = buf;
		      uint32_t pos = 0;
		      int packet_len;
		      
		      int error = read_var_int(&read_buf, &pos, nbytes, &packet_len);
		      if (error) {
			printf("error: %d\n", error); // todo -- append to backlog
			deallocate_player(player_num);
			continue;
		      }
		      uint32_t remaining_data = nbytes-(read_buf - buf); 


		      if (remaining_data < packet_len) {
			printf("error: too little data supplied\ndata remaining after read: %d\n", remaining_data);// todo -- append to backlog
			printf("data needed to read more: %d\n", packet_len);
			deallocate_player(player_num);
			continue;
		      }
		      if (remaining_data > packet_len) {
			printf("error: too much data supplied\ndata remaining after read: %d\n", remaining_data);
			printf("data needed to read more: %d\n", packet_len);
			deallocate_player(player_num);
			continue;
		      }
		      handle_player_packet(player_num, read_buf, remaining_data);
		      
                    }
                }
            }
        }
    }
    
    return 0;
} 

