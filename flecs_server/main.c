#include <stdio.h>
#include "./components.h"
#include "./network.h"
#include "../protocol/packets.h"
#include "./flecs_server.h"
#include "./flecs/flecs.h"
#include "./util.h"
#define WRITE_BUF_SIZE 100000
uint8_t write_buf[WRITE_BUF_SIZE];



void handle_handshake(ecs_iter_t *it) {
  handshake *s = ecs_field(it, handshake, 0);
  for (int i = 0; i < it->count; i++) {
    ecs_entity_t mc_player = ecs_get_parent(it->world, it->entities[i]);
    mc_connection *c = ecs_get_mut_id(it->world, mc_player, ecs_id(mc_connection));
    print_handshake(s[i], 0);
    if(s[i].intent != 2) {
      continue;
    }
    c->connection_state = s[i].intent;
  }
}

void handle_login_start(ecs_iter_t *it) {
  login_start *s = ecs_field(it, login_start, 0);
  for (int i = 0; i < it->count; i++) {
    ecs_entity_t mc_player = ecs_get_parent(it->world, it->entities[i]);
    mc_connection *c = ecs_get_mut_id(it->world, mc_player, ecs_id(mc_connection));

    print_login_start(s[i], 0);

    uuidcomponent *u = ecs_ensure(it->world, it->entities[i], uuidcomponent);
    namecomponent *n = ecs_ensure(it->world, it->entities[i], namecomponent);
    u->uuid = s[i].uuid;
    n->name.len = s[i].name.len;
    n->name.str = malloc(s[i].name.len);
    memcpy(n->name.str, s[i].name.str, s[i].name.len);
    // send a login success
    login_success packet = { .profile = { .uuid = u->uuid,
					  .game_profile_property_count = 0,
					  .properties = NULL,
					  .username = n->name } } ;
    send_login_success_packet(write_buf, WRITE_BUF_SIZE, c->fd, packet);
    c->connection_state = 3;
  }
}





int main() {
  ecs_world_t *world = ecs_init();
  register_mc_components(world, 25545);
  
  
  //printf("%d\n", ecs_using_task_threads(world));
  
  /* ECS_SYSTEM(world, handle_handshake, EcsPreFrame, handshake); */
  /* ECS_SYSTEM(world, handle_login_start, EcsPreFrame, login_start); */
  ECS_OBSERVER(world, handle_handshake, EcsOnAdd, handshake);
  ECS_OBSERVER(world, handle_login_start, EcsOnAdd, login_start);

  while (ecs_progress(world, 0)) { };
  return 0;
}
