#include "registry.h"
#define STRNLEN(str) str, strlen(str)
int send_registry_packet(simple_server *server, int player_num, uint8_t *write_buf_simple_server, unsigned int WRITE_BUF_SIMPLE_SERVER_SIZE) {
  player *m_player = server->players[player_num];
  registry_data reg_packet;
  uint8_t *packet_ptr;
  unsigned int max = 0;
  // send emtpy registries
  {
    packet_ptr = write_buf_simple_server+4;
    max = 0;
    reg_packet.registry_id = lstr_static("minecraft:pattern_item");
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
    char banner_types_str[][64] = {"minecraft:test"}; 
    for (int i = 0; i < sizeof(banner_types_str) / sizeof(banner_types_str[0]); i++)
      {
	packet_ptr = write_buf_simple_server+4;
	max = 0;
	reg_packet.registry_id = lstr_static("minecraft:banner_pattern");
	nbt_tag_t *compound = nbt_new_tag_compound();
	nbt_tag_t *key1 = nbt_new_tag_int(1);
	nbt_tag_compound_append(compound, key1);
	nbt_set_tag_name(key1, STRNLEN("test"));
	reg_packet.entries =  (registry_data_entry[]){
	  (registry_data_entry){.entry_id = banner_types_str[i], .data = &compound}
	};
	reg_packet.num_entries = 0;
	/* reg_packet.entries = NULL; */
	/* reg_packet.num_entries = 0; */

	write_var_int(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, REGISTRY_DATA_ID);
	write_registry_data(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, reg_packet);
	//print_registry_data(reg_packet);
	nbt_free_tag(compound);
	
	send_packet(write_buf_simple_server, max, m_player->conn.fd);
      }
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
  {
    char damage_types_str[][64] = {"minecraft:spear", "minecraft:player_attack", "minecraft:cactus", "minecraft:campfire", "minecraft:cramming", "minecraft:dragon_breath", "minecraft:drown", "minecraft:dry_out", "minecraft:ender_pearl", "minecraft:fall", "minecraft:fly_into_wall", "minecraft:freeze", "minecraft:generic", "minecraft:generic_kill", "minecraft:hot_floor", "minecraft:in_fire", "minecraft:in_wall", "minecraft:lava", "minecraft:lightning_bolt", "minecraft:magic", "minecraft:on_fire", "minecraft:out_of_world", "minecraft:outside_border", "minecraft:stalagmite", "minecraft:starve", "minecraft:sweet_berry_bush", "minecraft:wither"}; 
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
    reg_packet.registry_id = lstr_static("minecraft:root");
    nbt_tag_t *c = nbt_new_tag_compound();
    registry_data_entry damage_types[] = { { lstr_static("minecraft:pattern_item"), &c } };
    reg_packet.entries = damage_types;
    reg_packet.num_entries = sizeof(damage_types) / sizeof(damage_types[0]);
    reg_packet.num_entries = 1;

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

      nbt_tag_t* has_ender_dragon_fight = nbt_new_tag_byte(0);
      nbt_set_tag_name(has_ender_dragon_fight, "has_ender_dragon_fight", strlen("has_ender_dragon_fight"));
      nbt_tag_compound_append(overworld, has_ender_dragon_fight);
	  
	  
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
      lstr trims[] = {lstr_static("minecraft:ponder_goat_horn")};
    for (int i = 0; i < sizeof(trims)/sizeof(trims[0]); i++ ) {
      packet_ptr = write_buf_simple_server+4;
      max = 0;
      reg_packet.registry_id = lstr_static("minecraft:instrument");
      nbt_tag_t *c = nbt_new_tag_compound();
      nbt_tag_t *n = nbt_new_tag_string("ambient.crimson_forest.loop", strlen("ambient.crimson_forest.loop"));
      nbt_tag_t *description = nbt_new_tag_string(STRNLEN("t"));
      nbt_tag_t *desc = nbt_new_tag_int(2);
      nbt_tag_t *len = nbt_new_tag_float(1.0);
	
      nbt_set_tag_name(len, STRNLEN("use_duration"));
      nbt_set_tag_name(desc, STRNLEN("range"));
      nbt_set_tag_name(n, STRNLEN("sound_event"));
      nbt_set_tag_name(description, STRNLEN("description"));
      nbt_tag_compound_append(c, n);
      nbt_tag_compound_append(c, desc);
      nbt_tag_compound_append(c, len);
      nbt_tag_compound_append(c, description);
      reg_packet.entries = (registry_data_entry[]){
	(registry_data_entry){
	  .data = &c,
	  .entry_id = trims[i]
	}
      };
      reg_packet.num_entries = 1;

      write_var_int(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, REGISTRY_DATA_ID);
      write_registry_data(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, reg_packet);
      //print_registry_data(reg_packet);
      send_packet(write_buf_simple_server, max, m_player->conn.fd);
    }
  }
  {
      lstr trims[] = {lstr_static("minecraft:13"), lstr_static("minecraft:cat"), lstr_static("minecraft:blocks"), lstr_static("minecraft:bounce"), lstr_static("minecraft:chirp"), lstr_static("minecraft:creator"), lstr_static("minecraft:creator_music_box"), lstr_static("minecraft:far"), lstr_static("minecraft:lava_chicken"), lstr_static("minecraft:mall"), lstr_static("minecraft:mellohi"), lstr_static("minecraft:stal"), lstr_static("minecraft:strad"), lstr_static("minecraft:ward"), lstr_static("minecraft:11"), lstr_static("minecraft:pigstep"), lstr_static("minecraft:wait"), lstr_static("minecraft:otherside"), lstr_static("minecraft:relic"), lstr_static("minecraft:5"), lstr_static("minecraft:4"), lstr_static("minecraft:3"), lstr_static("minecraft:2"), lstr_static("minecraft:1"), lstr_static("minecraft:0"), lstr_static("minecraft:precipice"), lstr_static("minecraft:tears")};
    for (int i = 0; i < sizeof(trims)/sizeof(trims[0]); i++ ) {
      packet_ptr = write_buf_simple_server+4;
      max = 0;
      reg_packet.registry_id = lstr_static("minecraft:jukebox_song");
      nbt_tag_t *c = nbt_new_tag_compound();
      nbt_tag_t *n = nbt_new_tag_string("ambient.crimson_forest.loop", strlen("ambient.crimson_forest.loop"));
      nbt_tag_t *desc = nbt_new_tag_int(0);
      nbt_tag_t *desc2 = nbt_new_tag_string("0", strlen("0"));
      nbt_tag_t *len = nbt_new_tag_float(1.0);
	
      nbt_set_tag_name(len, "length_in_seconds", strlen("length_in_seconds"));
      nbt_set_tag_name(n, "sound_event", strlen("sound_event"));
      nbt_set_tag_name(desc, "comparator_output", strlen("comparator_output"));
      nbt_set_tag_name(desc2, "description", strlen("description"));
      nbt_tag_compound_append(c, n);
      nbt_tag_compound_append(c, desc);
      nbt_tag_compound_append(c, desc2);
      nbt_tag_compound_append(c, len);
      reg_packet.entries = (registry_data_entry[]){
	(registry_data_entry){
	  .data = &c,
	  .entry_id = trims[i]
	}
      };
      reg_packet.num_entries = 1;

      write_var_int(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, REGISTRY_DATA_ID);
      write_registry_data(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, reg_packet);
      //print_registry_data(reg_packet);
      send_packet(write_buf_simple_server, max, m_player->conn.fd);
    }
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
    lstr trims[] = {lstr_static("minecraft:redstone"), lstr_static("minecraft:diamond"), lstr_static("minecraft:emerald"), lstr_static("minecraft:lapis"), lstr_static("minecraft:quartz"), lstr_static("minecraft:amethyst"), lstr_static("minecraft:iron"), lstr_static("minecraft:gold"), lstr_static("minecraft:copper"), lstr_static("minecraft:netherite"), lstr_static("minecraft:resin")};
    for (int i = 0; i < sizeof(trims)/sizeof(trims[0]); i++ ) {
      packet_ptr = write_buf_simple_server+4;
      max = 0;
      reg_packet.registry_id = lstr_static("minecraft:trim_material");
      nbt_tag_t *c = nbt_new_tag_compound();
      nbt_tag_t *n = nbt_new_tag_string("redstone", strlen("redstone"));
      nbt_tag_t *desc = nbt_new_tag_string("#971607", strlen("#971607"));
	
      nbt_set_tag_name(n, "asset_name", strlen("asset_name"));
      nbt_set_tag_name(desc, "description", strlen("description"));
      nbt_tag_compound_append(c, n);
      nbt_tag_compound_append(c, desc);
      reg_packet.entries = (registry_data_entry[]){
	(registry_data_entry){
	  .data = &c,
	  .entry_id = trims[i]
	}
      };
      reg_packet.num_entries = 1;

      write_var_int(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, REGISTRY_DATA_ID);
      write_registry_data(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, reg_packet);
      //print_registry_data(reg_packet);
      send_packet(write_buf_simple_server, max, m_player->conn.fd);
    }
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

      nbt_tag_t* baby_asset_id = nbt_new_tag_string("minecraft:baby_asset_id", strlen("minecraft:baby_asset_id"));
      nbt_set_tag_name(baby_asset_id, "baby_asset_id", strlen("baby_asset_id"));
      nbt_tag_compound_append(overworld, baby_asset_id);

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
      nbt_tag_t* baby_asset_id = nbt_new_tag_string("baby_asset_id", strlen("baby_asset_id"));
      nbt_set_tag_name(baby_asset_id, "baby_asset_id", strlen("baby_asset_id"));
      nbt_tag_compound_append(overworld, baby_asset_id);

    }
	
    registry_data_entry damage_types[] = {
      { lstr_static("minecraft:temperate"), &overworld },
      { lstr_static("minecraft:cold"), &overworld },
      { lstr_static("minecraft:warm"), &overworld }};
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
      nbt_tag_t* baby_asset_id = nbt_new_tag_string("baby_asset_id", strlen("baby_asset_id"));
      nbt_set_tag_name(baby_asset_id, "baby_asset_id", strlen("baby_asset_id"));
      nbt_tag_compound_append(overworld, baby_asset_id);
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
      nbt_tag_t* baby_asset_id = nbt_new_tag_string("baby_asset_id", strlen("baby_asset_id"));
      nbt_set_tag_name(baby_asset_id, "baby_asset_id", strlen("baby_asset_id"));
      nbt_tag_compound_append(overworld, baby_asset_id);
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
    char *keys[] = {"baby_assets", "assets"};;
    for(int i = 0; i < 2; i++) {
      nbt_tag_t* overworld = nbt_new_tag_compound();
      nbt_set_tag_name(overworld, keys[i], strlen(keys[i]));
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
    }
	
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
    char keys[][32] = {"minecraft:wolf_sound_variant", "minecraft:pig_sound_variant", "minecraft:cow_sound_variant", "minecraft:cat_sound_variant", "minecraft:chicken_sound_variant"};
    for (int j = 0; j < 5; j++) {
      max = 0;
      packet_ptr = write_buf_simple_server+4;
      reg_packet.registry_id = lstr_static(keys[j]);
      /* reg_packet.entries = NULL; */
      /* reg_packet.num_entries = 0; */
      nbt_tag_t* overworld_old = nbt_new_tag_compound();
      char *keys_2[] = {"baby_sounds", "adult_sounds"};;
      for (int i = 0; i < 2; i++) {
	nbt_tag_t* overworld = nbt_new_tag_compound();
	nbt_set_tag_name(overworld, keys_2[i], strlen(keys_2[i]));
	char keys_3[][32] = {"ambient_sound", "purr_sound", "beg_for_food_sound", "hiss_sound", "stray_ambient_sound", "purreow_sound", "eat_sound", "step_sound", "death_sound", "growl_sound", "hurt_sound", "pant_sound", "whine_sound"};
	for(int k = 0; k < sizeof(keys_3)/sizeof(keys_3[0]); k++) {
	  nbt_tag_t* ambient_sound = nbt_new_tag_string("ambient.crimson_forest.loop", strlen("ambient.crimson_forest.loop"));
	  nbt_set_tag_name(ambient_sound, keys_3[k], strlen(keys_3[k]));
	  nbt_tag_compound_append(overworld, ambient_sound);
	}
	    
	for(int k = 0; k < sizeof(keys_3)/sizeof(keys_3[0]); k++) {
	  nbt_tag_t* ambient_sound = nbt_new_tag_string("ambient.crimson_forest.loop", strlen("ambient.crimson_forest.loop"));
	  nbt_set_tag_name(ambient_sound, keys_3[k], strlen(keys_3[k]));
	  nbt_tag_compound_append(overworld_old, ambient_sound);
	}
	  
	nbt_tag_compound_append(overworld_old, overworld);
	  
      }
	
      registry_data_entry damage_types[] = { { lstr_static("minecraft:cat"), &overworld_old } };
      reg_packet.entries = damage_types;
      reg_packet.num_entries = sizeof(damage_types) / sizeof(damage_types[0]);
      write_var_int(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, REGISTRY_DATA_ID);
      write_registry_data(&packet_ptr, &max, WRITE_BUF_SIMPLE_SERVER_SIZE, reg_packet);
      nbt_free_tag(overworld_old);
	
      send_packet(write_buf_simple_server, max, m_player->conn.fd);
    }
  }
  send_update_tags_packet(write_buf_simple_server, WRITE_BUF_SIMPLE_SERVER_SIZE, m_player->conn.fd,
			  (update_tags){
			    .tag_list = (update_tags_tag_list[]){
			      (update_tags_tag_list){
				.tag_name = lstr_static("minecraft:damage_type"),
				.tags = (update_tags_tag[]) {
				  (update_tags_tag){
				    .tag_name = lstr_static("minecraft:is_fire")
				  },
				  (update_tags_tag){
				    .tag_name = lstr_static("minecraft:is_explosion")
				  },
				  (update_tags_tag){
				    .tag_name = lstr_static("minecraft:bypasses_shield")
				  }
				},
				.tags_count = 3
			      },
			      (update_tags_tag_list){
				.tag_name = lstr_static("minecraft:block"),
				.tags = (update_tags_tag[]) {
				  (update_tags_tag){
				    .tag_name = lstr_static("minecraft:infiniburn_overworld")
				  }
				},
				.tags_count = 1
			      },
			      (update_tags_tag_list){
				.tag_name = lstr_static("minecraft:banner_pattern"),
				.tags = (update_tags_tag[]) {
				  (update_tags_tag){
				    .tag_name = lstr_static("minecraft:pattern_item/flower")
				  },
				  (update_tags_tag){
				    .tag_name = lstr_static("minecraft:pattern_item/bordure_indented")
				  },
				  (update_tags_tag){
				    .tag_name = lstr_static("minecraft:pattern_item/creeper")
				  },
				  (update_tags_tag){
				    .tag_name = lstr_static("minecraft:pattern_item/field_masoned")
				  },
				  (update_tags_tag){
				    .tag_name = lstr_static("minecraft:pattern_item/flow")
				  },
				  (update_tags_tag){
				    .tag_name = lstr_static("minecraft:pattern_item/flower")
				  },
				  (update_tags_tag){
				    .tag_name = lstr_static("minecraft:pattern_item/globe")
				  },
				  (update_tags_tag){
				    .tag_name = lstr_static("minecraft:pattern_item/guster")
				  },
				  (update_tags_tag){
				    .tag_name = lstr_static("minecraft:pattern_item/mojang")
				  },
				  (update_tags_tag){
				    .tag_name = lstr_static("minecraft:pattern_item/piglin")
				  },
				  (update_tags_tag){
				    .tag_name = lstr_static("minecraft:pattern_item/skull")
				  },
				},
				.tags_count = 11
			      },
			      
			    },
			    .tag_list_count = 3

			  });
}
