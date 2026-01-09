void teleport_player(uint8_t *write_buf, int32_t WRITE_BUF_SIZE, simple_server *server, int player_num, double x, double y, double z, double vx, double vy, double vz);
void send_game_event(uint8_t *write_buf, int32_t WRITE_BUF_SIZE, simple_server *server, int player_num, uint8_t event, float value);
void send_set_center_chunk(uint8_t *write_buf, int32_t WRITE_BUF_SIZE, simple_server *server, int player_num, int32_t x, int32_t y);
void send_spawn_entity(uint8_t *write_buf, int32_t WRITE_BUF_SIZE, simple_server *server, int player_num, int32_t entity_id, uuid entity_uuid, int32_t type, double x, double y, double z, uint8_t pitch, uint8_t yaw, uint8_t head_yaw, int32_t data, double velocity_x, double velocity_y, double velocity_z);
void send_update_entity_posrot(uint8_t *write_buf, int32_t WRITE_BUF_SIZE, simple_server *server, int player_num, int eid, double x, double y, double z, double prev_x, double prev_y, double prev_z, float yaw, float pitch, uint8_t on_ground);
void send_set_head_rotation(uint8_t *write_buf, int32_t WRITE_BUF_SIZE, simple_server *server, int player_num, int32_t eid, float value);
void update_tab_list(uint8_t *write_buf, int32_t WRITE_BUF_SIZE, simple_server *server);
