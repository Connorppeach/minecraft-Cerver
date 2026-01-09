#include "simple_server/simple_server.h"
#include "util.h"
void update_tab_list(uint8_t *write_buf_simple_server, int32_t WRITE_BUF_SIMPLE_SERVER_SIZE, simple_server *server) {
  for(int i = 0; i < server->max_players; i++) {
    if(server->player_slots[i]) {
      player_action ac = { server->players[i]->uuid, { lstr_static(server->players[i]->username), NULL, 0} };
      ac.update_listed.listed = 1;
      player_action action_list[1] = { ac };
      player_info_update update_packet = {0x01 | 0x08, action_list, 1};
    
      uint8_t *packet_ptr = write_buf_simple_server+4;
      uint32_t max = 0;
      write_var_int(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, PLAYER_INFO_UPDATE_ID);
      write_player_info_update(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, update_packet);
      for(int j = 0; j < server->max_players; j++)
	if(server->player_slots[j])
	  send_packet(write_buf_simple_server, max, server->players[j]->conn.fd);
    }
  }
}
void teleport_player(uint8_t *write_buf, int32_t WRITE_BUF_SIZE, simple_server *server, int player_num, double x, double y, double z, double vx, double vy, double vz) {
  syncronize_player_position packet;
  packet.teleport_id = 10;
  server->players[player_num]->loc.x = x;
  server->players[player_num]->loc.y = y;
  server->players[player_num]->loc.z = z;
  packet.x = x;
  packet.y = y;
  packet.z = z;
  packet.velocity_x = vx;
  packet.velocity_y = vy;
  packet.velocity_z = vz;
  packet.yaw = 0.0;
  packet.pitch = 0.0;
  packet.flags = 0;

  uint8_t *packet_ptr = write_buf+4;
  uint32_t max = 0;
  write_var_int(&packet_ptr, &max, WRITE_BUF_SIZE, SYNCRONIZE_PLAYER_POSITION_ID);
  write_syncronize_player_position(&packet_ptr, &max, WRITE_BUF_SIZE, packet);
  send_packet(write_buf, max, server->players[player_num]->conn.fd);
}

void send_spawn_entity(uint8_t *write_buf, int32_t WRITE_BUF_SIZE, simple_server *server, int player_num, int32_t entity_id, uuid entity_uuid, int32_t type, double x, double y, double z, uint8_t pitch, uint8_t yaw, uint8_t head_yaw, int32_t data, double velocity_x, double velocity_y, double velocity_z) {
  spawn_entity packet;
  packet.eid = entity_id;
  packet.entity_uuid = entity_uuid;
  packet.type = type;
  packet.x = x;
  packet.y = y;
  packet.z = z;
  packet.pitch = pitch/1.41;
  packet.yaw = yaw/1.41;
  packet.head_angle = head_yaw/1.41;
  packet.velocity.x = velocity_x;
  packet.velocity.y = velocity_y;
  packet.velocity.z = velocity_z;
  packet.data = data;

  uint8_t *packet_ptr = write_buf+4;
  uint32_t max = 0;
  write_var_int(&packet_ptr, &max, WRITE_BUF_SIZE, SPAWN_ENTITY_ID);
  write_spawn_entity(&packet_ptr, &max, WRITE_BUF_SIZE, packet);
  send_packet(write_buf, max, server->players[player_num]->conn.fd);
}

void send_game_event(uint8_t *write_buf, int32_t WRITE_BUF_SIZE, simple_server *server, int player_num, uint8_t event, float value) {
  game_event packet;
  packet.event_id = event;
  packet.value = value;
  uint8_t *packet_ptr = write_buf+4;
  uint32_t max = 0;
  
  write_var_int(&packet_ptr, &max, WRITE_BUF_SIZE, GAME_EVENT_ID);
  write_game_event(&packet_ptr, &max, WRITE_BUF_SIZE, packet);
  send_packet(write_buf, max, server->players[player_num]->conn.fd);
}

void send_set_head_rotation(uint8_t *write_buf, int32_t WRITE_BUF_SIZE, simple_server *server, int player_num, int32_t eid, float value) {
  set_head_rotation packet;
  packet.entity_id = eid;
  packet.yaw = value/1.41;
  uint8_t *packet_ptr = write_buf+4;
  uint32_t max = 0;
  
  write_var_int(&packet_ptr, &max, WRITE_BUF_SIZE, SET_HEAD_ROTATION_ID);
  write_set_head_rotation(&packet_ptr, &max, WRITE_BUF_SIZE, packet);
  send_packet(write_buf, max, server->players[player_num]->conn.fd);
}

void send_set_center_chunk(uint8_t *write_buf, int32_t WRITE_BUF_SIZE, simple_server *server, int player_num, int32_t x, int32_t y) {
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

void send_update_entity_posrot(uint8_t *write_buf, int32_t WRITE_BUF_SIZE, simple_server *server, int player_num, int eid, double x, double y, double z, double prev_x, double prev_y, double prev_z, float yaw, float pitch, uint8_t on_ground) {
  update_entity_position_and_rotation packet;
  packet.entity_id = eid;
  packet.delta_x = x * 4096 - prev_x * 4096;
  packet.delta_y = y * 4096 - prev_y * 4096;
  packet.delta_z = z * 4096 - prev_z * 4096;
  packet.pitch = pitch/1.41;
  packet.yaw = yaw/1.41;
  packet.on_ground = on_ground;
  uint8_t *packet_ptr = write_buf+4;
  uint32_t max = 0;
  
  write_var_int(&packet_ptr, &max, WRITE_BUF_SIZE, UPDATE_ENTITY_POSITION_AND_ROTATION_ID);
  int error = write_update_entity_position_and_rotation(&packet_ptr, &max, WRITE_BUF_SIZE, packet);
  /* print_set_entity_velocity(packet, 0); */
  send_packet(write_buf, max, server->players[player_num]->conn.fd);
  if(error)
    printf("error setting center chunk: %d\n", error);
}





 



