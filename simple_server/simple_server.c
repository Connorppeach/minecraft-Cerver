#include "simple_server.h"
#include <time.h>



simple_server* allocate_simple_server(int max_players) {
  simple_server *server = malloc(sizeof(simple_server));
  server->players = malloc(sizeof(player*)*max_players);
  server->player_slots = malloc(sizeof(uint8_t)*max_players);
  for(int i = 0; i < max_players; i++) {
    server->players[i] = NULL;
    server->player_slots[i] = 0;
  }
  server->max_players = max_players;
  server->should_stop = 0;
  server->world_data.world_height = 384;// default
  return server;
}


// returns player id
int allocate_player(simple_server *server, int fd) { 
  for (int i = 0; i < server->max_players; i++) {
    if(server->player_slots[i] != 1) {
      server->players[i] = create_player(fd);
      server->player_slots[i] = 1;
      return i;
    }
  }
  return -1;
}

void deallocate_player(simple_server *server, int player_id) {
  if(server->player_slots[player_id]) {
    puts("deallocating player");
    FD_CLR(server->players[player_id]->conn.fd, &server->master); // remove from master set
    free_player(server->players[player_id]);
    server->players[player_id] = NULL;
    server->player_slots[player_id] = 0;
  }
}








#define WRITE_BUF_SIMPLE_SERVER_SIZE 1024
uint8_t write_buf_simple_server[WRITE_BUF_SIMPLE_SERVER_SIZE];
int handle_player_packet(simple_server *server, int player_num, uint8_t *packet_buf, unsigned int buf_len, simple_server_callback cb) {
  if(!server->player_slots[player_num])
    return 1;

  
  int packet_type;
  unsigned int pos = 0;
  int error = read_var_int(&packet_buf, &pos, buf_len, &packet_type);
  if(error) {
    printf("error in client: %d\n", error);
    deallocate_player(server, player_num);
    return 1;
  }
  cb.packet_callback(server, player_num, packet_type, packet_buf, buf_len);

  // make a copy of the packet(remember to free if you return)
  uint8_t *raw_data = malloc(buf_len*sizeof(uint8_t));
  uint8_t *buf_ptr = raw_data;
  for(int i = 0; i < buf_len; i++)
    raw_data[i] = packet_buf[i];

  // util write packet buffer
  uint32_t max = 0;
  player *m_player = server->players[player_num];
  
  //printf("got packet id %d with len %d\n", packet_type, buf_len);
  if (m_player->conn.connection_state == 0 && packet_type == HANDSHAKE_ID) {
    handshake shake;
    int error = read_handshake(&buf_ptr, &pos, buf_len, &shake);
    //print_handshake(shake);

    // we dont handle anything other than login right now
    if (shake.intent != 2) {
      printf("error reading intent: %d\n", error);
      deallocate_player(server, player_num);
      free(raw_data);
      return 1;
    }
    free_handshake(shake);
    m_player->conn.connection_state = shake.intent;
  } else if (m_player->conn.connection_state == 2) {
    if (packet_type == LOGIN_START_ID) {
      login_start login_s;
      read_login_start(&buf_ptr, &pos, buf_len, &login_s);
      //print_login_start(login_s);
      int i;
      for(i = 0; i < 16; i++) {
	if(i < login_s.name.len)
	  m_player->username[i] = login_s.name.str[i];
	else
	  m_player->username[i] = 0;
      }
      
      m_player->username[i++] = 0;
      m_player->uuid = login_s.uuid;
      //puts("\nplayer login\n");
      uint8_t *packet_ptr = write_buf_simple_server+4;

      // you shall not pass
      //disconnect_player(player_num);

      // you may pass
      write_var_int(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, LOGIN_SUCCESS_ID);
      write_login_success(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, (login_success){{login_s.uuid, login_s.name, NULL, 0}});
      send_packet(write_buf_simple_server, max, m_player->conn.fd);
      free_login_start(login_s);
      
    } else if (packet_type == LOGIN_ACKNOWLEDGED_ID) {
      //puts("\nlogin finish\n");
      m_player->conn.connection_state = 3;
      uint8_t *packet_ptr = write_buf_simple_server+4;
      write_var_int(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, CLIENTBOUND_KNOWN_PACKS_ID);
      known_pack packs[] = { (known_pack){lstr_static("minecraft"), lstr_static("core"), lstr_static("1.21.11")} };
      write_clientbound_known_packs(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, (clientbound_known_packs){packs, 1});
      //print_clientbound_known_packs((clientbound_known_packs){packs, 1});
      send_packet(write_buf_simple_server, max, m_player->conn.fd);
      // send moar
    } 
  } else if (m_player->conn.connection_state == 3) {
    if (packet_type == CLIENT_INFORMATION_CONFIGURATION_ID) {
      //puts("\nplayer enter config\n");
      //
      client_information_configuration config_s;
      read_client_information_configuration(&buf_ptr, &pos, buf_len, &config_s);
      free_client_information_configuration(config_s);
      //print_client_information_configuration(config_s);
      // send our known packs
      
    } else if (packet_type == SERVERBOUND_KNOWN_PACKS_CONFIGURATION_ID) {
      serverbound_known_packs config_s;
      read_serverbound_known_packs(&buf_ptr, &pos, buf_len, &config_s);
      //print_serverbound_known_packs(config_s);
      free_serverbound_known_packs(config_s);
      registry_data reg_packet;
      uint8_t *packet_ptr;
      // send emtpy registries
      {
	packet_ptr = write_buf_simple_server+4;
	max = 0;
	reg_packet.registry_id = lstr_static("minecraft:banner_pattern");
	reg_packet.entries = NULL;
	reg_packet.num_entries = 0;

	write_var_int(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, REGISTRY_DATA_ID);
	write_registry_data(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, reg_packet);
	//print_registry_data(reg_packet);
	send_packet(write_buf_simple_server, max, m_player->conn.fd);
      }
      {
	packet_ptr = write_buf_simple_server+4;
	max = 0;
	reg_packet.registry_id = lstr_static("minecraft:chat_type");

	write_var_int(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, REGISTRY_DATA_ID);
	write_registry_data(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, reg_packet);
	//print_registry_data(reg_packet);
	send_packet(write_buf_simple_server, max, m_player->conn.fd);
      }
      char damage_types_str[][32] = { "minecraft:player_attack", "minecraft:cactus", "minecraft:campfire", "minecraft:cramming", "minecraft:dragon_breath", "minecraft:drown", "minecraft:dry_out", "minecraft:ender_pearl", "minecraft:fall", "minecraft:fly_into_wall", "minecraft:freeze", "minecraft:generic", "minecraft:generic_kill", "minecraft:hot_floor", "minecraft:in_fire", "minecraft:in_wall", "minecraft:lava", "minecraft:lightning_bolt", "minecraft:magic", "minecraft:on_fire", "minecraft:out_of_world", "minecraft:outside_border", "minecraft:stalagmite", "minecraft:starve", "minecraft:sweet_berry_bush", "minecraft:wither"}; 
      for (int i = 0; i < sizeof(damage_types_str) / sizeof(damage_types_str[0]); i++)
	{
	  packet_ptr = write_buf_simple_server+4;
	  max = 0;
	  reg_packet.registry_id = lstr_static("minecraft:damage_type");
	  /* reg_packet.entries = NULL; */
	  /* reg_packet.num_entries = 0; */
	  nbt_tag_t* cactus_damage = nbt_new_tag_compound();
	  nbt_tag_t* message_id = nbt_new_tag_string(damage_types_str[i], strlen(damage_types_str[i]));
	  nbt_tag_t* scaling = nbt_new_tag_string("never", strlen("never"));
	  nbt_tag_t* exhaustion = nbt_new_tag_float(0.0);
	  nbt_set_tag_name(message_id, "message_id", strlen("message_id"));
	  nbt_set_tag_name(scaling, "scaling", strlen("scaling"));
	  nbt_set_tag_name(exhaustion, "exhaustion", strlen("exhaustion"));
	  
	  nbt_tag_compound_append(cactus_damage, scaling);
	  nbt_tag_compound_append(cactus_damage, message_id);
	  nbt_tag_compound_append(cactus_damage, exhaustion);
	
	
	registry_data_entry damage_types[] = { { lstr_static(damage_types_str[i]), &cactus_damage } };
	reg_packet.entries = damage_types;
	reg_packet.num_entries = sizeof(damage_types) / sizeof(damage_types[0]);

	write_var_int(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, REGISTRY_DATA_ID);
	write_registry_data(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, reg_packet);
	//print_registry_data(reg_packet);
	nbt_free_tag(cactus_damage);
	
	send_packet(write_buf_simple_server, max, m_player->conn.fd);
      }
      {
	packet_ptr = write_buf_simple_server+4;
	max = 0;
	reg_packet.registry_id = lstr_static("minecraft:dialog");
	reg_packet.entries = NULL;
	reg_packet.num_entries = 0;

	write_var_int(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, REGISTRY_DATA_ID);
	write_registry_data(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, reg_packet);
	//print_registry_data(reg_packet);
	send_packet(write_buf_simple_server, max, m_player->conn.fd);
      }
      {
	packet_ptr = write_buf_simple_server+4;
	max = 0;
	reg_packet.registry_id = lstr_static("minecraft:dimension_type");
	/* reg_packet.entries = NULL; */
	/* reg_packet.num_entries = 0; */
	nbt_tag_t* overworld = nbt_new_tag_compound();
	{
	  nbt_tag_t* coordinate_scale = nbt_new_tag_float(1.0);
	  nbt_set_tag_name(coordinate_scale, "coordinate_scale", strlen("coordinate_scale"));
	  nbt_tag_compound_append(overworld, coordinate_scale);

	  nbt_tag_t* has_skylight = nbt_new_tag_byte(0);
	  nbt_set_tag_name(has_skylight, "has_skylight", strlen("has_skylight"));
	  nbt_tag_compound_append(overworld, has_skylight);

	  nbt_tag_t* has_ceiling = nbt_new_tag_byte(0);
	  nbt_set_tag_name(has_ceiling, "has_ceiling", strlen("has_ceiling"));
	  nbt_tag_compound_append(overworld, has_ceiling);

	  nbt_tag_t* has_fixed_time = nbt_new_tag_byte(0);
	  nbt_set_tag_name(has_fixed_time, "has_fixed_time", strlen("has_fixed_time"));
	  nbt_tag_compound_append(overworld, has_fixed_time);

	  // todo -- move to enviromental flags for .11
	  
	  nbt_tag_t* piglin_safe = nbt_new_tag_byte(0);
	  nbt_set_tag_name(piglin_safe, "piglin_safe", strlen("piglin_safe"));
	  nbt_tag_compound_append(overworld, piglin_safe);

	  nbt_tag_t* has_raids = nbt_new_tag_byte(0);
	  nbt_set_tag_name(has_raids, "has_raids", strlen("has_raids"));
	  nbt_tag_compound_append(overworld, has_raids);

	  nbt_tag_t* respawn_anchor_works = nbt_new_tag_byte(0);
	  nbt_set_tag_name(respawn_anchor_works, "respawn_anchor_works", strlen("respawn_anchor_works"));
	  nbt_tag_compound_append(overworld, respawn_anchor_works);

	  nbt_tag_t* bed_works = nbt_new_tag_byte(0);
	  nbt_set_tag_name(bed_works, "bed_works", strlen("bed_works"));
	  nbt_tag_compound_append(overworld, bed_works);

	  nbt_tag_t* ultrawarm = nbt_new_tag_byte(0);
	  nbt_set_tag_name(ultrawarm, "ultrawarm", strlen("ultrawarm"));
	  nbt_tag_compound_append(overworld, ultrawarm);

	  nbt_tag_t* natural = nbt_new_tag_byte(0);
	  nbt_set_tag_name(natural, "natural", strlen("natural"));
	  nbt_tag_compound_append(overworld, natural);
	  
	  
	  nbt_tag_t* cloud_height = nbt_new_tag_int(100);
	  nbt_set_tag_name(cloud_height, "cloud_height", strlen("cloud_height"));
	  nbt_tag_compound_append(overworld, cloud_height);

	  // end
	  
	  nbt_tag_t* ambient_light = nbt_new_tag_float(1.0);
	  nbt_set_tag_name(ambient_light, "ambient_light", strlen("ambient_light"));
	  nbt_tag_compound_append(overworld, ambient_light);

	  nbt_tag_t* min_y = nbt_new_tag_int(0);
	  nbt_set_tag_name(min_y, "min_y", strlen("min_y"));
	  nbt_tag_compound_append(overworld, min_y);
	  
	  nbt_tag_t* height = nbt_new_tag_int(server->world_data.world_height);
	  nbt_set_tag_name(height, "height", strlen("height"));
	  nbt_tag_compound_append(overworld, height);

	  nbt_tag_t* logical_height = nbt_new_tag_int(0);
	  nbt_set_tag_name(logical_height, "logical_height", strlen("logical_height"));
	  nbt_tag_compound_append(overworld, logical_height);

	  nbt_tag_t* monster_spawn_light_level = nbt_new_tag_int(0);
	  nbt_set_tag_name(monster_spawn_light_level, "monster_spawn_light_level", strlen("monster_spawn_light_level"));
	  nbt_tag_compound_append(overworld, monster_spawn_light_level);

	  nbt_tag_t* monster_spawn_block_light_limit = nbt_new_tag_int(0);
	  nbt_set_tag_name(monster_spawn_block_light_limit, "monster_spawn_block_light_limit", strlen("monster_spawn_block_light_limit"));
	  nbt_tag_compound_append(overworld, monster_spawn_block_light_limit);

	  nbt_tag_t* infiniburn = nbt_new_tag_string("#infiniburn_overworld", strlen("#infiniburn_overworld"));
	  nbt_set_tag_name(infiniburn, "infiniburn", strlen("infiniburn"));
	  nbt_tag_compound_append(overworld, infiniburn);

	  nbt_tag_t* skybox = nbt_new_tag_string("overworld", strlen("overworld"));
	  nbt_set_tag_name(skybox, "skybox", strlen("skybox"));
	  nbt_tag_compound_append(overworld, skybox);

	  /* nbt_tag_t* cardinal_light = nbt_new_tag_string("cardinal_light", strlen("cardinal_light")); */
	  /* nbt_set_tag_name(cardinal_light, "cardinal_light", strlen("cardinal_light")); */
	  /* nbt_tag_compound_append(overworld, cardinal_light); */

	  
	}
	
	registry_data_entry damage_types[] = { { lstr_static("minecraft:overworld"), &overworld } };
	reg_packet.entries = damage_types;
	reg_packet.num_entries = sizeof(damage_types) / sizeof(damage_types[0]);

	write_var_int(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, REGISTRY_DATA_ID);
	write_registry_data(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, reg_packet);
	//print_registry_data(reg_packet);
	nbt_free_tag(overworld);
	
	send_packet(write_buf_simple_server, max, m_player->conn.fd);
      }
      {
	packet_ptr = write_buf_simple_server+4;
	max = 0;
	reg_packet.registry_id = lstr_static("minecraft:enchantment");
	reg_packet.entries = NULL;
	reg_packet.num_entries = 0;

	write_var_int(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, REGISTRY_DATA_ID);
	write_registry_data(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, reg_packet);
	//print_registry_data(reg_packet);
	send_packet(write_buf_simple_server, max, m_player->conn.fd);
      }
      {
	packet_ptr = write_buf_simple_server+4;
	max = 0;
	reg_packet.registry_id = lstr_static("minecraft:instrument");
	reg_packet.entries = NULL;
	reg_packet.num_entries = 0;

	write_var_int(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, REGISTRY_DATA_ID);
	write_registry_data(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, reg_packet);
	//print_registry_data(reg_packet);
	send_packet(write_buf_simple_server, max, m_player->conn.fd);
      }      
      {
	packet_ptr = write_buf_simple_server+4;
	max = 0;
	reg_packet.registry_id = lstr_static("minecraft:jukebox_song");
	reg_packet.entries = NULL;
	reg_packet.num_entries = 0;

	write_var_int(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, REGISTRY_DATA_ID);
	write_registry_data(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, reg_packet);
	//print_registry_data(reg_packet);
	send_packet(write_buf_simple_server, max, m_player->conn.fd);
      }
      {
	packet_ptr = write_buf_simple_server+4;
	max = 0;
	reg_packet.registry_id = lstr_static("minecraft:painting_variant");
	/* reg_packet.entries = NULL; */
	/* reg_packet.num_entries = 0; */
	nbt_tag_t* overworld = nbt_new_tag_compound();
	{
	  nbt_tag_t* asset_id = nbt_new_tag_string("minecraft:earth", strlen("minecraft:earth"));
	  nbt_set_tag_name(asset_id, "asset_id", strlen("asset_id"));
	  nbt_tag_compound_append(overworld, asset_id);
	  
	  nbt_tag_t* width = nbt_new_tag_int(16);
	  nbt_set_tag_name(width, "width", strlen("width"));
	  nbt_tag_compound_append(overworld, width);

	  
	  nbt_tag_t* height = nbt_new_tag_int(16);
	  nbt_set_tag_name(height, "height", strlen("height"));
	  nbt_tag_compound_append(overworld, height);



	  nbt_tag_t* title = nbt_new_tag_string("title", strlen("title"));
	  nbt_set_tag_name(title, "title", strlen("title"));
	  nbt_tag_compound_append(overworld, title);

	  nbt_tag_t* author = nbt_new_tag_string("author", strlen("author"));
	  nbt_set_tag_name(author, "author", strlen("author"));
	  nbt_tag_compound_append(overworld, author);

	  
	}
	
	registry_data_entry damage_types[] = { { lstr_static("minecraft:earth"), &overworld } };
	reg_packet.entries = damage_types;
	reg_packet.num_entries = sizeof(damage_types) / sizeof(damage_types[0]);

	write_var_int(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, REGISTRY_DATA_ID);
	write_registry_data(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, reg_packet);
	//print_registry_data(reg_packet);
	nbt_free_tag(overworld);
	
	send_packet(write_buf_simple_server, max, m_player->conn.fd);
      }
      
      {
	packet_ptr = write_buf_simple_server+4;
	max = 0;
	reg_packet.registry_id = lstr_static("minecraft:test_environment");
	reg_packet.entries = NULL;
	reg_packet.num_entries = 0;

	write_var_int(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, REGISTRY_DATA_ID);
	write_registry_data(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, reg_packet);
	//print_registry_data(reg_packet);
	send_packet(write_buf_simple_server, max, m_player->conn.fd);
      }
      {
	packet_ptr = write_buf_simple_server+4;
	max = 0;
	reg_packet.registry_id = lstr_static("minecraft:test_instance");
	reg_packet.entries = NULL;
	reg_packet.num_entries = 0;

	write_var_int(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, REGISTRY_DATA_ID);
	write_registry_data(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, reg_packet);
	//print_registry_data(reg_packet);
	send_packet(write_buf_simple_server, max, m_player->conn.fd);
      }
      {
	packet_ptr = write_buf_simple_server+4;
	max = 0;
	reg_packet.registry_id = lstr_static("minecraft:trim_material");
	reg_packet.entries = NULL;
	reg_packet.num_entries = 0;

	write_var_int(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, REGISTRY_DATA_ID);
	write_registry_data(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, reg_packet);
	//print_registry_data(reg_packet);
	send_packet(write_buf_simple_server, max, m_player->conn.fd);
      }
      {
	packet_ptr = write_buf_simple_server+4;
	max = 0;
	reg_packet.registry_id = lstr_static("minecraft:trim_pattern");
	reg_packet.entries = NULL;
	reg_packet.num_entries = 0;

	write_var_int(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, REGISTRY_DATA_ID);
	write_registry_data(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, reg_packet);
	//print_registry_data(reg_packet);
	send_packet(write_buf_simple_server, max, m_player->conn.fd);
      }
      {
	packet_ptr = write_buf_simple_server+4;
	max = 0;
	reg_packet.registry_id = lstr_static("minecraft:worldgen/biome");
	nbt_tag_t* overworld = nbt_new_tag_compound();
	{
	  nbt_tag_t* has_precipitation = nbt_new_tag_byte(0);
	  nbt_set_tag_name(has_precipitation, "has_precipitation", strlen("has_precipitation"));
	  nbt_tag_compound_append(overworld, has_precipitation);

	  nbt_tag_t* temperature = nbt_new_tag_float(0.2);
	  nbt_set_tag_name(temperature, "temperature", strlen("temperature"));
	  nbt_tag_compound_append(overworld, temperature);

	  nbt_tag_t* downfall = nbt_new_tag_float(0.2);
	  nbt_set_tag_name(downfall, "downfall", strlen("downfall"));
	  nbt_tag_compound_append(overworld, downfall);
	  {
	    nbt_tag_t* effects = nbt_new_tag_compound();
	    nbt_set_tag_name(effects, "effects", strlen("effects"));

	    nbt_tag_t* water_color = nbt_new_tag_int(1);
	    nbt_set_tag_name(water_color, "water_color", strlen("water_color"));
	    nbt_tag_compound_append(effects, water_color);

	    nbt_tag_t* fog_color = nbt_new_tag_int(32);
	    nbt_set_tag_name(fog_color, "fog_color", strlen("fog_color"));
	    nbt_tag_compound_append(effects, fog_color);


	    nbt_tag_t* water_fog_color = nbt_new_tag_int(32);
	    nbt_set_tag_name(water_fog_color, "water_fog_color", strlen("water_fog_color"));
	    nbt_tag_compound_append(effects, water_fog_color);

	    nbt_tag_t* sky_color = nbt_new_tag_int(3200252);
	    nbt_set_tag_name(sky_color, "sky_color", strlen("sky_color"));
	    nbt_tag_compound_append(effects, sky_color);
	    
	    
	    
	    nbt_tag_compound_append(overworld, effects);
	    
	  }
	  
	}
	
	registry_data_entry damage_types[] = { { lstr_static("minecraft:plains"), &overworld } };
	reg_packet.entries = damage_types;
	reg_packet.num_entries = sizeof(damage_types) / sizeof(damage_types[0]);

	write_var_int(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, REGISTRY_DATA_ID);
	write_registry_data(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, reg_packet);
	//print_registry_data(reg_packet);
	nbt_free_tag(overworld);
	
	send_packet(write_buf_simple_server, max, m_player->conn.fd);
      }
      {
	packet_ptr = write_buf_simple_server+4;
	max = 0;
	reg_packet.registry_id = lstr_static("minecraft:cat_variant");
	/* reg_packet.entries = NULL; */
	/* reg_packet.num_entries = 0; */
	nbt_tag_t* overworld = nbt_new_tag_compound();
	{
	  nbt_tag_t* asset_id = nbt_new_tag_string("minecraft:pig", strlen("minecraft:pig"));
	  nbt_set_tag_name(asset_id, "asset_id", strlen("asset_id"));
	  nbt_tag_compound_append(overworld, asset_id);
	}
	
	registry_data_entry damage_types[] = { { lstr_static("minecraft:cat"), &overworld } };
	reg_packet.entries = damage_types;
	reg_packet.num_entries = sizeof(damage_types) / sizeof(damage_types[0]);

	write_var_int(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, REGISTRY_DATA_ID);
	write_registry_data(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, reg_packet);
	//print_registry_data(reg_packet);
	nbt_free_tag(overworld);
	
	send_packet(write_buf_simple_server, max, m_player->conn.fd);
      }
      {
	packet_ptr = write_buf_simple_server+4;
	max = 0;
	reg_packet.registry_id = lstr_static("minecraft:zombie_nautilus_variant");
	/* reg_packet.entries = NULL; */
	/* reg_packet.num_entries = 0; */
	nbt_tag_t* overworld = nbt_new_tag_compound();
	{
	  nbt_tag_t* asset_id = nbt_new_tag_string("minecraft:pig", strlen("minecraft:pig"));
	  nbt_set_tag_name(asset_id, "asset_id", strlen("asset_id"));
	  nbt_tag_compound_append(overworld, asset_id);
	}
	
	registry_data_entry damage_types[] = { { lstr_static("minecraft:cat"), &overworld } };
	reg_packet.entries = damage_types;
	reg_packet.num_entries = sizeof(damage_types) / sizeof(damage_types[0]);

	write_var_int(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, REGISTRY_DATA_ID);
	write_registry_data(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, reg_packet);
	//print_registry_data(reg_packet);
	nbt_free_tag(overworld);
	
	send_packet(write_buf_simple_server, max, m_player->conn.fd);
      }
      {
	packet_ptr = write_buf_simple_server+4;
	max = 0;
	reg_packet.registry_id = lstr_static("minecraft:chicken_variant");
	/* reg_packet.entries = NULL; */
	/* reg_packet.num_entries = 0; */
	nbt_tag_t* overworld = nbt_new_tag_compound();
	{
	  nbt_tag_t* asset_id = nbt_new_tag_string("minecraft:chicken_variant", strlen("minecraft:chicken_variant"));
	  nbt_set_tag_name(asset_id, "asset_id", strlen("asset_id"));
	  nbt_tag_compound_append(overworld, asset_id);

	  nbt_tag_t* model = nbt_new_tag_string("normal", strlen("normal"));
	  nbt_set_tag_name(model, "model", strlen("model"));
	  nbt_tag_compound_append(overworld, model);
	}
	
	registry_data_entry damage_types[] = { { lstr_static("minecraft:cat"), &overworld } };
	reg_packet.entries = damage_types;
	reg_packet.num_entries = sizeof(damage_types) / sizeof(damage_types[0]);

	write_var_int(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, REGISTRY_DATA_ID);
	write_registry_data(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, reg_packet);
	//print_registry_data(reg_packet);
	nbt_free_tag(overworld);
	
	send_packet(write_buf_simple_server, max, m_player->conn.fd);
      }
      {
	packet_ptr = write_buf_simple_server+4;
	max = 0;
	reg_packet.registry_id = lstr_static("minecraft:cow_variant");
	/* reg_packet.entries = NULL; */
	/* reg_packet.num_entries = 0; */
	nbt_tag_t* overworld = nbt_new_tag_compound();
	{
	  nbt_tag_t* asset_id = nbt_new_tag_string("minecraft:chicken_variant", strlen("minecraft:chicken_variant"));
	  nbt_set_tag_name(asset_id, "asset_id", strlen("asset_id"));
	  nbt_tag_compound_append(overworld, asset_id);

	  nbt_tag_t* model = nbt_new_tag_string("normal", strlen("normal"));
	  nbt_set_tag_name(model, "model", strlen("model"));
	  nbt_tag_compound_append(overworld, model);
	}
	
	registry_data_entry damage_types[] = { { lstr_static("minecraft:cat"), &overworld } };
	reg_packet.entries = damage_types;
	reg_packet.num_entries = sizeof(damage_types) / sizeof(damage_types[0]);

	write_var_int(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, REGISTRY_DATA_ID);
	write_registry_data(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, reg_packet);
	//print_registry_data(reg_packet);
	nbt_free_tag(overworld);
	
	send_packet(write_buf_simple_server, max, m_player->conn.fd);
      }
      {
	packet_ptr = write_buf_simple_server+4;
	max = 0;
	reg_packet.registry_id = lstr_static("minecraft:frog_variant");
	/* reg_packet.entries = NULL; */
	/* reg_packet.num_entries = 0; */
	nbt_tag_t* overworld = nbt_new_tag_compound();
	{
	  nbt_tag_t* asset_id = nbt_new_tag_string("minecraft:pig", strlen("minecraft:pig"));
	  nbt_set_tag_name(asset_id, "asset_id", strlen("asset_id"));
	  nbt_tag_compound_append(overworld, asset_id);
	}
	
	registry_data_entry damage_types[] = { { lstr_static("minecraft:cat"), &overworld } };
	reg_packet.entries = damage_types;
	reg_packet.num_entries = sizeof(damage_types) / sizeof(damage_types[0]);

	write_var_int(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, REGISTRY_DATA_ID);
	write_registry_data(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, reg_packet);
	//print_registry_data(reg_packet);
	nbt_free_tag(overworld);
	
	send_packet(write_buf_simple_server, max, m_player->conn.fd);
      }
      {
	packet_ptr = write_buf_simple_server+4;
	max = 0;
	reg_packet.registry_id = lstr_static("minecraft:pig_variant");
	/* reg_packet.entries = NULL; */
	/* reg_packet.num_entries = 0; */
	nbt_tag_t* overworld = nbt_new_tag_compound();
	{
	  nbt_tag_t* asset_id = nbt_new_tag_string("minecraft:chicken_variant", strlen("minecraft:chicken_variant"));
	  nbt_set_tag_name(asset_id, "asset_id", strlen("asset_id"));
	  nbt_tag_compound_append(overworld, asset_id);

	  nbt_tag_t* model = nbt_new_tag_string("normal", strlen("normal"));
	  nbt_set_tag_name(model, "model", strlen("model"));
	  nbt_tag_compound_append(overworld, model);
	}
	
	registry_data_entry damage_types[] = { { lstr_static("minecraft:cat"), &overworld } };
	reg_packet.entries = damage_types;
	reg_packet.num_entries = sizeof(damage_types) / sizeof(damage_types[0]);

	write_var_int(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, REGISTRY_DATA_ID);
	write_registry_data(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, reg_packet);
	//print_registry_data(reg_packet);
	nbt_free_tag(overworld);
	
	send_packet(write_buf_simple_server, max, m_player->conn.fd);
      }
      {
	packet_ptr = write_buf_simple_server+4;
	max = 0;
	reg_packet.registry_id = lstr_static("minecraft:wolf_variant");
	/* reg_packet.entries = NULL; */
	/* reg_packet.num_entries = 0; */
	nbt_tag_t* overworld_root = nbt_new_tag_compound();
	nbt_tag_t* overworld = nbt_new_tag_compound();
	nbt_set_tag_name(overworld, "assets", strlen("assets"));
	{
	  nbt_tag_t* angry = nbt_new_tag_string("angry", strlen("angry"));
	  nbt_set_tag_name(angry, "angry", strlen("angry"));
	  nbt_tag_compound_append(overworld, angry);

	  nbt_tag_t* wild = nbt_new_tag_string("angry", strlen("angry"));
	  nbt_set_tag_name(wild, "wild", strlen("wild"));
	  nbt_tag_compound_append(overworld, wild);

	  nbt_tag_t* tame = nbt_new_tag_string("angry", strlen("angry"));
	  nbt_set_tag_name(tame, "tame", strlen("tame"));
	  nbt_tag_compound_append(overworld, tame);

	}
	nbt_tag_compound_append(overworld_root, overworld);
	
	registry_data_entry damage_types[] = { { lstr_static("minecraft:cat"), &overworld_root } };
	reg_packet.entries = damage_types;
	reg_packet.num_entries = sizeof(damage_types) / sizeof(damage_types[0]);

	write_var_int(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, REGISTRY_DATA_ID);
	write_registry_data(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, reg_packet);
	//print_registry_data(reg_packet);
	nbt_free_tag(overworld_root);
	
	send_packet(write_buf_simple_server, max, m_player->conn.fd);
      }
      {
	packet_ptr = write_buf_simple_server+4;
	max = 0;
	reg_packet.registry_id = lstr_static("minecraft:wolf_sound_variant");
	/* reg_packet.entries = NULL; */
	/* reg_packet.num_entries = 0; */
	nbt_tag_t* overworld = nbt_new_tag_compound();
	{
	  nbt_tag_t* ambient_sound = nbt_new_tag_string("ambient.crimson_forest.loop", strlen("ambient.crimson_forest.loop"));
	  nbt_set_tag_name(ambient_sound, "ambient_sound", strlen("ambient_sound"));
	  nbt_tag_compound_append(overworld, ambient_sound);

	  nbt_tag_t* death_sound = nbt_new_tag_string("ambient.crimson_forest.loop", strlen("ambient.crimson_forest.loop"));
	  nbt_set_tag_name(death_sound, "death_sound", strlen("death_sound"));
	  nbt_tag_compound_append(overworld, death_sound);
	  
	  nbt_tag_t* growl_sound = nbt_new_tag_string("ambient.crimson_forest.loop", strlen("ambient.crimson_forest.loop"));
	  nbt_set_tag_name(growl_sound, "growl_sound", strlen("growl_sound"));
	  nbt_tag_compound_append(overworld, growl_sound);

	  nbt_tag_t* hurt_sound = nbt_new_tag_string("ambient.crimson_forest.loop", strlen("ambient.crimson_forest.loop"));
	  nbt_set_tag_name(hurt_sound, "hurt_sound", strlen("hurt_sound"));
	  nbt_tag_compound_append(overworld, hurt_sound);

	  nbt_tag_t* pant_sound = nbt_new_tag_string("ambient.crimson_forest.loop", strlen("ambient.crimson_forest.loop"));
	  nbt_set_tag_name(pant_sound, "pant_sound", strlen("pant_sound"));
	  nbt_tag_compound_append(overworld, pant_sound);

	  nbt_tag_t* whine_sound = nbt_new_tag_string("ambient.crimson_forest.loop", strlen("ambient.crimson_forest.loop"));
	  nbt_set_tag_name(whine_sound, "whine_sound", strlen("whine_sound"));
	  nbt_tag_compound_append(overworld, whine_sound);
	  
	}
	
	registry_data_entry damage_types[] = { { lstr_static("minecraft:cat"), &overworld } };
	reg_packet.entries = damage_types;
	reg_packet.num_entries = sizeof(damage_types) / sizeof(damage_types[0]);

	write_var_int(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, REGISTRY_DATA_ID);
	write_registry_data(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, reg_packet);
	//print_registry_data(reg_packet);
	nbt_free_tag(overworld);
	
	send_packet(write_buf_simple_server, max, m_player->conn.fd);
      }

      {// finish configuration
	packet_ptr = write_buf_simple_server+4;
	max = 0;
	write_var_int(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, FINISH_CONFIGURATION_ID);
	finish_configuration config;
	write_finish_configuration(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, config);
	send_packet(write_buf_simple_server, max, m_player->conn.fd);
      }      
    } else if (packet_type == ACKGNOWLEDGE_SERVER_CONFIGURATION_ID) {
      //puts("\nconfiguration finished\n");
      m_player->conn.connection_state = 4; // yippee, play state
      cb.finish_configuration(server, player_num);
    }
  } else if  (m_player->conn.connection_state == 4) { // play
    if (packet_type == SET_PLAYER_POSITION_ID) {
      set_player_position packet;
      mc_location old_loc = m_player->loc;
      read_set_player_position(&buf_ptr, &pos, buf_len, &packet);
      m_player->loc.x = packet.x;
      m_player->loc.y = packet.y;
      m_player->loc.z = packet.z;

      m_player->velocity.x = old_loc.x-packet.x;
      m_player->velocity.y = old_loc.y-packet.y;
      m_player->velocity.z = old_loc.z-packet.z;

      if(cb.on_move)
	cb.on_move(server, player_num, old_loc, m_player->loc);
    } else if(packet_type == SET_PLAYER_POSITION_AND_ROTATION_ID) {
      set_player_position_and_rotation packet;
      mc_location old_loc = m_player->loc;
      read_set_player_position_and_rotation(&buf_ptr, &pos, buf_len, &packet);

      m_player->velocity.x = old_loc.x-packet.x;
      m_player->velocity.y = old_loc.y-packet.y;
      m_player->velocity.z = old_loc.z-packet.z;

      m_player->loc.x = packet.x;
      m_player->loc.y = packet.y;
      m_player->loc.z = packet.z;
      m_player->loc.yaw = packet.yaw;
      m_player->loc.pitch = packet.pitch;
      if(cb.on_move)
	cb.on_move(server, player_num, old_loc, m_player->loc);
    } else if(packet_type == SET_PLAYER_ROTATION_ID) {
      set_player_rotation packet;
      mc_location old_loc = m_player->loc;
      read_set_player_rotation(&buf_ptr, &pos, buf_len, &packet);
      m_player->loc.yaw = packet.yaw;
      m_player->loc.pitch = packet.pitch;
      if(cb.on_move)
	cb.on_move(server, player_num, old_loc, m_player->loc);
    }

  }
    
  
  free(raw_data);
  return 0;
}

void handle_packet(simple_server *server, int player_num, uint8_t *buf, int nbytes, simple_server_callback cb) {
  //puts("new packet");
  player *m_player = server->players[player_num];
  uint8_t *read_buf;
  uint8_t *read_buf_original;
  if (m_player->conn.backlog != NULL) {
    int total_bytes = nbytes+m_player->conn.backlog_len;
    read_buf_original = malloc(total_bytes+1);
    read_buf = read_buf_original;
    int i2=0;
    for(int i = 0; i < total_bytes; i++) {
      
      if(i < m_player->conn.backlog_len)
	read_buf[i] = m_player->conn.backlog[i];
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
    deallocate_player(server, player_num);
    return;
  }
  uint32_t remaining_data = nbytes-pos;


  if (remaining_data < packet_len) {
    /* printf("error: too little data supplied\ndata remaining after read: %d\n", remaining_data);// todo -- append to backlog */
    /* printf("data needed to read more: %d\n", packet_len); */
    /* printf("we have: %d\n", nbytes); */
    if (m_player->conn.backlog != NULL)
      free(m_player->conn.backlog);
    m_player->conn.backlog_len = nbytes;
    m_player->conn.backlog = malloc(nbytes);
    for(int i = 0; i < nbytes; i++)
      m_player->conn.backlog[i] = read_buf_original[i];
    free(read_buf_original);
    //deallocate_player(server, player_num);
    //if(read_buf_2) free(read_buf_2);
    return;
  }
  int left = nbytes-packet_len-1;
  uint8_t more = left>0;
  uint8_t *left_off = read_buf+packet_len;
  //printf("packet len: %d\nleft: %d\n", packet_len, left);
  error = handle_player_packet(server, player_num, read_buf, packet_len, cb);
  if (error) {

    free(read_buf_original); // done, at last
    deallocate_player(server, player_num);
    return;
  }
  if (more) {
    /* printf("error: too much data supplied\ndata left: %d\n", remaining_data); */
    /* printf("data left: %d\n", left); */
    /* deallocate_player(player_num) */;
    //printf("more\n");
    handle_packet(server, player_num, left_off, left, cb);
  } else {
    if (m_player->conn.backlog != NULL) {
	free(m_player->conn.backlog);
	m_player->conn.backlog = NULL;
	m_player->conn.backlog_len = 0;
    }

  }
  free(read_buf_original);

}


int start_server(simple_server *server, int port, simple_server_callback cb)
{
  // master file descriptor list
  struct sockaddr_in myaddr;     // server address
  int fdmax;        // maximum file descriptor number
  int listener;     // listening socket descriptor
  int yes=1;        // for setsockopt() SO_REUSEADDR, below
  server->should_stop = 0;
  FD_ZERO(&server->master);    // clear the master and temp sets

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
  myaddr.sin_port = htons(port);
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
  FD_SET(listener, &server->master);

  // keep track of the biggest file descriptor
  fdmax = listener; // so far, it's this one
  struct timespec start_time, current_time;
  long elapsed_ns; // Nanoseconds
  const long target_ns = 20000; // 20 milliseconds in nanoseconds

  clock_gettime(CLOCK_MONOTONIC, &start_time); // Get start time
    
  // Main loop
  for(;;) {
    if(server->should_stop)
      break;
    fd_set read_fds; // temp file descriptor list for select()
    FD_ZERO(&read_fds);
      
    read_fds = server->master; // copy it
    //puts("waiting");
    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 20000; // 20 milliseconds
    int select_ret = select(fdmax+1, &read_fds, NULL, NULL, &timeout);
    clock_gettime(CLOCK_MONOTONIC, &current_time); // Get current time

    elapsed_ns = ((int64_t)current_time.tv_sec - (int64_t)start_time.tv_sec) * (int64_t)1000000000
         + ((int64_t)current_time.tv_nsec - (int64_t)start_time.tv_nsec);

    if (elapsed_ns >= target_ns) {
      // user tick callback
      cb.tick_callback(server);


      clock_gettime(CLOCK_MONOTONIC, &start_time); // reset clock
    }

    if (select_ret == -1) {
      perror("select");
      exit(1);
    } else if(select_ret == 0) {
      continue;
    }

    //puts("still going");
    // run through the existing connections looking for data to read
    for(int i = 0; i <= fdmax; i++) {
	  
      if (FD_ISSET(i, &read_fds)) { // we got one!!
	if (i == listener) {
	  // handle new connections
	  struct sockaddr_in remoteaddr; // client address
	  socklen_t addrlen = sizeof(remoteaddr);
	  int newfd;
	  if ((newfd = accept(listener, (struct sockaddr *)&remoteaddr,
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



	    FD_SET(newfd, &server->master); // add to master set
	    allocate_player(server, newfd);


	    if (newfd > fdmax) {    // keep track of the maximum
	      fdmax = newfd;
	    }

			
	    /* printf("server: new connection from %s on " */
	    /* 	   "socket %d\n", inet_ntoa(remoteaddr.sin_addr), newfd); */
	  }
	} else {
	  int player_num = -1;
	  for (int k = 0; k < server->max_players; k++) {
	    if (server->player_slots[k] && server->players[k]->conn.fd == i) {
	      player_num = k;
	    }
	  }
	  if(player_num == -1)
	    puts("very bad stuff, no player id found");
	  int nbytes;
	  // handle data from a client
	  uint8_t buf[1024];    // buffer for client data
	  if ((nbytes = read(i, buf, sizeof(buf))) <= 0) {
	    // got error or connection closed by client
	    if (nbytes == 0) {
	      // connection closed
	      printf("server: socket %d hung up\n", i);
	      
	    } else {
	      perror("recv");
	    }
	    deallocate_player(server, player_num);
	    FD_CLR(i, &server->master); // remove from master set
		    
	  } else {
	    // we got some data from a client
		    
	    handle_packet(server, player_num, buf, nbytes, cb);
	  }
	}
      }
    }
  }
    
  return 0;
} 




