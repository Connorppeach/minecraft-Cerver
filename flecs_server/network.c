#include "../protocol/packets.h"
#include "./components.h"
#include "./flecs_server.h"
#include "flecs/flecs.h"

#define PACKET(name, ...) ECS_COMPONENT_DECLARE(name);


#define PACKET_ID(name, id)						\
  void destroy_##name(void *v, int32_t count, const ecs_type_info_t *ti) { \
  name *data = v;							\
    for (int i = 0; i < count; i++) {					\
      free_##name(data[i]);						\
    }									\
  }    

#include "../protocol/all_packets.h"
#undef PACKET
#undef PACKET_ID


typedef int (*read_fn)(uint8_t **buf, uint32_t *pos, size_t len, void *out);

typedef struct {
  ecs_entity_t component_id;
  read_fn read_fn;
  int32_t struct_size;
} PacketHandler;

PacketHandler packet_handlers_handshake[1] = {0};
PacketHandler packet_handlers_login[16] = {0}; // todo -- size these properly
PacketHandler packet_handlers_configuration[32] = {0};
PacketHandler packet_handlers_play[256] = {0};


void handle_packet_system(ecs_iter_t *it) {
  packetbuffer *s = ecs_field(it, packetbuffer, 0);

  for (int i = 0; i < it->count; i++) {
    ecs_entity_t mc_player = ecs_get_parent(it->world, it->entities[i]);
    const mc_connection *c = ecs_get_id(it->world, mc_player, ecs_id(mc_connection));
    
    uint8_t *reader_buf = s[i].buf;
    uint32_t reader_pos = 0;
    
    int32_t packet_type;
    int error = read_var_int(&reader_buf, &reader_pos, s[i].nbytes, &packet_type);

    ecs_entity_t evt = ecs_new(it->world);
    if (c->connection_state == 0) {
      if (error || packet_type >= 1 || packet_handlers_handshake[packet_type].component_id == 0) {
        continue;
      }

      PacketHandler handler = packet_handlers_handshake[packet_type];

    
      void *comp_ptr = ecs_ensure_id(it->world, evt, handler.component_id, packet_handlers_handshake[packet_type].struct_size);
    
      error = handler.read_fn(&reader_buf, &reader_pos, s[i].nbytes, comp_ptr);
      ecs_add_id(it->world, evt, remove_on_end);

      ecs_add_pair(it->world, evt, EcsChildOf, mc_player);

      if (!error) {
	//printf("%s\n", ecs_get_path(it->world, evt));
      } else {
	ecs_delete(it->world, evt); // Parse failed, cleanup
	ecs_delete(it->world, mc_player); // Parse failed, cleanup

	printf("error from parsing packet %d\n", error);
      }
    }
    else if (c->connection_state == 2) {
      if (error || packet_type >= sizeof(packet_handlers_login) / sizeof(packet_handlers_login[0]) || packet_handlers_login[packet_type].component_id == 0) {
        continue;
      }

      PacketHandler handler = packet_handlers_login[packet_type];

    
      void *comp_ptr = ecs_ensure_id(it->world, evt, handler.component_id, packet_handlers_login[packet_type].struct_size);
    
      error = handler.read_fn(&reader_buf, &reader_pos, s[i].nbytes, comp_ptr);
      ecs_add_id(it->world, evt, remove_on_end);

      ecs_add_pair(it->world, evt, EcsChildOf, mc_player);

      if (!error) {
	//printf("%s\n", ecs_get_path(it->world, evt));
      } else {
	ecs_delete(it->world, evt); // Parse failed, cleanup
	ecs_delete(it->world, mc_player); // Parse failed, cleanup

	printf("error from parsing packet %d\n", error);
      }
    }
    else if (c->connection_state == 3) {
      if (error || packet_type >= sizeof(packet_handlers_configuration) / sizeof(packet_handlers_configuration[0]) || packet_handlers_login[packet_type].component_id == 0) {
        continue;
      }

      PacketHandler handler = packet_handlers_configuration[packet_type];

    
      void *comp_ptr = ecs_ensure_id(it->world, evt, handler.component_id, packet_handlers_configuration[packet_type].struct_size);
    
      error = handler.read_fn(&reader_buf, &reader_pos, s[i].nbytes, comp_ptr);
      ecs_add_id(it->world, evt, remove_on_end);

      ecs_add_pair(it->world, evt, EcsChildOf, mc_player);

      if (!error) {
	//printf("%s\n", ecs_get_path(it->world, evt));
      } else {
	ecs_delete(it->world, evt); // Parse failed, cleanup
	ecs_delete(it->world, mc_player); // Parse failed, cleanup

	printf("error from parsing packet %d\n", error);
      }
    }
    
  }
}
ECS_DTOR(packetbuffer, ptr, free(ptr->buf););
ECS_DTOR(namecomponent, ptr, free(ptr->name.str););

#define PACKET(name ...)
void register_mc_components(ecs_world_t *world, int port) {
  ECS_COMPONENT_DEFINE(world, position3);
  ECS_COMPONENT_DEFINE(world, velocity3);
  ECS_COMPONENT_DEFINE(world, rotation3);
  ECS_COMPONENT_DEFINE(world, packetbuffer);
  ECS_COMPONENT_DEFINE(world, selectsocketcomponent);

  ecs_set_hooks(world, packetbuffer, {
      .dtor = packetbuffer_dtor
    });

  ecs_set_hooks(world, packetbuffer, {
      .dtor = namecomponent_dtor
    });
  
  ECS_COMPONENT_DEFINE(world, namecomponent);
  ECS_COMPONENT_DEFINE(world, uuidcomponent);
  
  ECS_TAG_DEFINE(world, remove_on_end);
  ECS_COMPONENT_DEFINE(world, mc_connection);
  //ECS_COMPONENT(world, remove_on_end);
  ecs_entity_t e = ecs_new(world);
  add_selectsocketcomponent(world, e, port);
  ECS_SYSTEM(world, select_loop, EcsOnUpdate, selectsocketcomponent);
  ECS_SYSTEM(world, handle_packet_system, EcsOnUpdate, packetbuffer);
  
  ecs_system(world, {
      .entity = ecs_entity(world, {
	  .name = "garbage collector",
	  .add = ecs_ids( ecs_dependson(EcsPostFrame) )
        }),
      .query.terms = {
	{ ecs_id(remove_on_end), .inout = EcsOut }
      },
      .callback = handle_remove_on_end_system,
    });
  

  
  

#define zero_packet_implemented(packet_handlers)  for(int i = 0; i < sizeof(packet_handlers)/sizeof(packet_handlers[0]); i++) packet_handlers[i].implemented = 0
#undef zero_packet_implemented
  // handshake

#define PACKET_ID(Type, ID) {						\
    ECS_COMPONENT_DEFINE(world, Type);						\
    ecs_entity_t comp = ecs_component_init(world, &(ecs_component_desc_t){ \
	.entity = ecs_entity(world, { .name = #Type }),			\
	.type.size = sizeof(Type),					\
	.type.alignment = _Alignof(Type),				\
	.type.hooks.dtor = destroy_##Type				\
      });								\
    packet_handlers_handshake[ID] =(PacketHandler){.component_id = comp, .read_fn = (read_fn)read_##Type, .struct_size = sizeof(Type)}; \
  }    
#include "../protocol/packets/handshake.h"
#undef PACKET_ID

    // login
#define PACKET_ID(Type, ID) {						\
    ECS_COMPONENT_DEFINE(world, Type);						\
    ecs_entity_t comp = ecs_component_init(world, &(ecs_component_desc_t){ \
	.entity = ecs_entity(world, { .name = #Type }),			\
	.type.size = sizeof(Type),					\
	.type.alignment = _Alignof(Type),				\
	.type.hooks.dtor = destroy_##Type				\
      });								\
    packet_handlers_login[ID] =(PacketHandler){.component_id = comp, .read_fn = (read_fn)read_##Type, .struct_size = sizeof(Type)}; \
  }    
#include "../protocol/packets/login_serverbound.h"
#undef PACKET_ID

    // configuration
#define PACKET_ID(Type, ID) {						\
    ECS_COMPONENT_DEFINE(world, Type);						\
    ecs_entity_t comp = ecs_component_init(world, &(ecs_component_desc_t){ \
	.entity = ecs_entity(world, { .name = #Type }),			\
	.type.size = sizeof(Type),					\
	.type.alignment = _Alignof(Type),				\
	.type.hooks.dtor = destroy_##Type				\
      });								\
    packet_handlers_configuration[ID] =(PacketHandler){.component_id = comp, .read_fn = (read_fn)read_##Type, .struct_size = sizeof(Type)}; \
  }    
#include "../protocol/packets/configuration_serverbound.h"
#undef PACKET_ID


    // play
#define PACKET_ID(Type, ID) {						\
    ECS_COMPONENT_DEFINE(world, Type);						\
    ecs_entity_t comp = ecs_component_init(world, &(ecs_component_desc_t){ \
	.entity = ecs_entity(world, { .name = #Type }),			\
	.type.size = sizeof(Type),					\
	.type.alignment = _Alignof(Type),				\
	.type.hooks.dtor = destroy_##Type				\
      });								\
    packet_handlers_play[ID] =(PacketHandler){.component_id = comp, .read_fn = (read_fn)read_##Type, .struct_size = sizeof(Type)}; \
  }    
#include "../protocol/packets/play_serverbound.h"
#undef PACKET_ID
}



#undef PACKET
