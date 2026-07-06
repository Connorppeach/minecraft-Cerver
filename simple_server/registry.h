#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h> 
#include <arpa/inet.h>
#include "../protocol/rw.h"
#include "player.h"
#include "../protocol/packets.h"
#include "simple_server.h"
int send_registry_packet(simple_server *server, int player_num, uint8_t *write_buf_simple_server, unsigned int WRITE_BUF_SIMPLE_SERVER_SIZE);
