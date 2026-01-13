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
nbt_tag_t *lstr2text_component(lstr text) {
  return nbt_new_tag_string(text.str, text.len);
}
lstr lstr_append(lstr text_1, lstr text_2) {
  int total_len = text_1.len + text_2.len;
  lstr ret;
  ret.str = malloc(total_len);
  ret.len = total_len;
  for(int i = 0; i < total_len; i++) {
    if(i < text_1.len) {
      ret.str[i] = text_1.str[i];
    } else
      ret.str[i] = text_2.str[i-text_1.len];
  }
  
  return ret;
}






 



