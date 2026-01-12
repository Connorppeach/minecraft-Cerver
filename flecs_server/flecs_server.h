#include "flecs/flecs.h"


int add_selectsocketcomponent(ecs_world_t *world, ecs_entity_t e, int port);
void select_loop(ecs_iter_t *it);
void free_packets(ecs_iter_t *it);
void handle_remove_on_end_system(ecs_iter_t *it);
void handle_remove_packetbuffers(ecs_iter_t *it);
