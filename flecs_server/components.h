#ifndef _SELECT_SERVER_
#define _SELECT_SERVER_

#include "flecs/flecs.h"
#include "../protocol/packets.h"
#include <netinet/in.h>
#include <stdint.h>

typedef struct {
  float x, y, z;
} position3, velocity3, rotation3;



typedef struct {
  int fd;
  uint8_t* backlog;
  uint32_t backlog_len;
  int connection_state;
} mc_connection;


typedef struct {
  fd_set main;
  struct sockaddr_in myaddr;     // server address
  int fdmax;        // maximum file descriptor number
  int listener;     // listening socket descriptor
} selectsocketcomponent;

typedef struct {
  uint8_t *buf;
  int nbytes;
} packetbuffer;

typedef struct {
  uuid uuid;
} uuidcomponent;

typedef struct {
  lstr name;
} namecomponent;




extern ECS_COMPONENT_DECLARE(namecomponent); 
extern ECS_COMPONENT_DECLARE(uuidcomponent); 

extern ECS_COMPONENT_DECLARE(mc_connection); 
extern ECS_COMPONENT_DECLARE(position3);
extern ECS_COMPONENT_DECLARE(selectsocketcomponent);
extern ECS_COMPONENT_DECLARE(velocity3); 
extern ECS_COMPONENT_DECLARE(rotation3); 
extern ECS_COMPONENT_DECLARE(packetbuffer); 
extern ECS_TAG_DECLARE(remove_on_end);
#endif
