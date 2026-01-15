#include <math.h>
#define BUNDLE_DELIMETER_ID 0
#define SPAWN_ENTITY_ID (BUNDLE_DELIMETER_ID+1)
#define ENTITY_ANIMATION_ID (SPAWN_ENTITY_ID+1)
#define AWARD_STATISTICS_ID (ENTITY_ANIMATION_ID+1)
#define ACK_BLOCK_CHANGE_ID (AWARD_STATISTICS_ID+1)
#define SET_BLOCK_DESTORY_STAGE_ID (ACK_BLOCK_CHANGE_ID+1)
#define BLOCK_ENTITY_DATA_ID (SET_BLOCK_DESTORY_STAGE_ID+1)
#define BLOCK_ACTION_ID (BLOCK_ENTITY_DATA_ID+1)
#define BLOCK_UPDATE_ID (BLOCK_ACTION_ID+1)
#define BOSS_BAR_ID (BLOCK_UPDATE_ID+1)
#define CHANGE_DIFFICULTY_ID (BOSS_BAR_ID+1)
#define CHUNK_BATCH_FINISHED_ID (CHANGE_DIFFICULTY_ID+1)
#define CHUNK_BATCH_START_ID (CHUNK_BATCH_FINISHED_ID+1)
#define CHUNK_BIOMES_ID (CHUNK_BATCH_START_ID+1)
#define CLEAR_TITLES_ID (CHUNK_BIOMES_ID+1)
#define COMMAND_SUGGESTIONS_RESPONSE_ID (CLEAR_TITLES_ID+1)
#define COMMANDS_ID (COMMAND_SUGGESTIONS_RESPONSE_ID+1)
#define CLOSE_CONTAINER_ID (COMMANDS_ID+1)
#define SET_CONTAINER_CONTENT_ID (CLOSE_CONTAINER_ID+1)
#define SET_CONTAINER_PROPERTY_ID (SET_CONTAINER_CONTENT_ID+1)
#define SET_CONTAINER_SLOT_ID (SET_CONTAINER_PROPERTY_ID+1)
#define COOKIE_RESPONSE_ID (SET_CONTAINER_SLOT_ID+1)
#define SET_COOLDOWN_ID (COOKIE_RESPONSE_ID+1)
#define CHAT_SUGGESTIONS_ID (SET_COOLDOWN_ID+1)
#define CLIENTBOUND_PLUGIN_MESSAGE_ID (CHAT_SUGGESTIONS_ID+1)
#define DAMAGE_EVENT_ID (CLIENTBOUND_PLUGIN_MESSAGE_ID+1)
#define DEBUG_BLOCK_VALUE_ID (DAMAGE_EVENT_ID+1)
#define DEBUG_CHUNK_VALUE_ID (DEBUG_BLOCK_VALUE_ID+1)
#define DEBUG_ENTITY_VALUE_ID (DEBUG_CHUNK_VALUE_ID+1)
#define DEBUG_EVENT_ID (DEBUG_ENTITY_VALUE_ID+1)
#define DEBUG_SAMPLE_ID (DEBUG_EVENT_ID+1)
#define DELETE_MESSAGE_ID (DEBUG_SAMPLE_ID+1)
#define DISCONNECT_ID (DELETE_MESSAGE_ID+1)
#define DISGUISED_CHAT_MESSAGE_ID (DISCONNECT_ID+1)
#define ENTITY_EVENT_ID (DISGUISED_CHAT_MESSAGE_ID+1)
#define TELEPORT_ENTITY_ID (ENTITY_EVENT_ID+1)
#define EXPLOSION_ID (TELEPORT_ENTITY_ID+1)
#define UNLOAD_CHUNK_ID (EXPLOSION_ID+1)
#define GAME_EVENT_ID (UNLOAD_CHUNK_ID+1)
#define GAME_TEST_HIGHLIGHT_POSITION_ID (GAME_EVENT_ID+1)
#define OPEN_HORSE_SCREEN_ID (GAME_TEST_HIGHLIGHT_POSITION_ID+1)
#define HURT_ANIMATION_ID (OPEN_HORSE_SCREEN_ID+1)
#define INIT_WORLD_BORDER_ID (HURT_ANIMATION_ID+1)
#define CLIENTBOUND_KEEP_ALIVE_PLAY_ID (INIT_WORLD_BORDER_ID+1)
#define CHUNK_DATA_AND_UPDATE_LIGHT_ID (CLIENTBOUND_KEEP_ALIVE_PLAY_ID+1)
#define WORLD_EVENT_ID (CHUNK_DATA_AND_UPDATE_LIGHT_ID+1)
#define PARTICLE_ID (WORLD_EVENT_ID+1)
#define UPDATE_LIGHT_ID (PARTICLE_ID+1)
#define LOGIN_PLAY_ID (UPDATE_LIGHT_ID+1)
#define MAP_DATA_ID (LOGIN_PLAY_ID+1)
#define MERCHANT_OFFERS_ID (MAP_DATA_ID+1)
#define UPDATE_ENTITY_POSITION_ID (MERCHANT_OFFERS_ID+1)
#define UPDATE_ENTITY_POSITION_AND_ROTATION_ID (UPDATE_ENTITY_POSITION_ID+1)
#define MOVE_MINECART_ALONG_TRACK_ID (UPDATE_ENTITY_POSITION_AND_ROTATION_ID+1)
#define UPDATE_ENTITY_ROTATION_ID (MOVE_MINECART_ALONG_TRACK_ID+1)
#define MOVE_VEHICLE_ID (UPDATE_ENTITY_ROTATION_ID+1)
#define OPEN_BOOK_ID (MOVE_VEHICLE_ID+1)
#define OPEN_SCREEN_ID (OPEN_BOOK_ID+1)
#define OPEN_SIGN_EDTIOR_ID (OPEN_SCREEN_ID+1)
#define PING_ID (OPEN_SIGN_EDTIOR_ID+1)
#define PING_RESPONSE_ID (PING_ID+1)
#define PLACE_GHOST_RECIPE_ID (PING_RESPONSE_ID+1)
#define PLAYER_ABILITIES_ID (PLACE_GHOST_RECIPE_ID+1)
#define PLAYER_CHAT_MESSAGE_ID (PLAYER_ABILITIES_ID+1)
#define END_COMBAT_ID (PLAYER_CHAT_MESSAGE_ID+1)
#define ENTER_COMBAT_ID (END_COMBAT_ID+1)
#define COMBAT_DEATH_ID (ENTER_COMBAT_ID+1)
#define PLAYER_INFO_REMOVE_ID (COMBAT_DEATH_ID+1)
#define PLAYER_INFO_UPDATE_ID (PLAYER_INFO_REMOVE_ID+1)
#define LOOK_AT_ID (PLAYER_INFO_UPDATE_ID+1)
#define SYNCRONIZE_PLAYER_POSITION_ID (LOOK_AT_ID+1)
#define PLAYER_ROTATION_ID (SYNCRONIZE_PLAYER_POSITION_ID+1)
#define RECIPE_ADD_ID (PLAYER_ROTATION_ID+1)
#define RECIPE_REMOVE_ID (RECIPE_ADD_ID+1)
#define RECIPE_SETTINGS_ID (RECIPE_REMOVE_ID+1)
#define REMOVE_ENTITIES_ID (RECIPE_SETTINGS_ID+1)
#define REMOVE_ENTITY_EFFECT_ID (REMOVE_ENTITIES_ID+1)
#define RESET_SCORE_ID (REMOVE_ENTITY_EFFECT_ID+1)
#define REMOVE_RESOURCE_PACK_ID (RESET_SCORE_ID+1)
#define ADD_RESOURCE_PACK_ID (REMOVE_RESOURCE_PACK_ID+1)
#define RESPAWN_ID (ADD_RESOURCE_PACK_ID+1)
#define SET_HEAD_ROTATION_ID (RESPAWN_ID+1)
#define UPDATE_SECTION_BLOCKS_ID (SET_HEAD_ROTATION_ID+1)
#define SELECT_ADVANCEMENTS_TAB_ID (UPDATE_SECTION_BLOCKS_ID+1)
#define SERVER_DATA_ID (SELECT_ADVANCEMENTS_TAB_ID+1)
#define SET_ACTION_BAR_TEXT_ID (SERVER_DATA_ID+1)
#define SET_BORDER_CENTER_ID (SET_ACTION_BAR_TEXT_ID+1)
#define SET_BORDER_LERP_SIZE_ID (SET_BORDER_CENTER_ID+1)
#define SET_BORDER_SIZE_ID (SET_BORDER_LERP_SIZE_ID+1)
#define SET_BORDER_WARNING_DELAY_ID (SET_BORDER_SIZE_ID+1)
#define SET_BORDER_WARNING_DISTANCE_ID (SET_BORDER_WARNING_DELAY_ID+1)
#define SET_CAMERA_ID (SET_BORDER_WARNING_DISTANCE_ID+1)
#define SET_CENTER_CHUNK_ID (SET_CAMERA_ID+1)
#define SET_RENDER_DISTANCE_ID (SET_CENTER_CHUNK_ID+1)
#define SET_CURSOR_ITEM_ID (SET_RENDER_DISTANCE_ID+1)
#define SET_DEFAULT_SPAWN_POSITION_ID (SET_CURSOR_ITEM_ID+1)
#define DISPLAY_OBJECTIVE_ID (SET_DEFAULT_SPAWN_POSITION_ID+1)
#define SET_ENTITY_METADATA_ID (DISPLAY_OBJECTIVE_ID+1)
#define LINK_ENTITIES_ID (SET_ENTITY_METADATA_ID+1)
#define SET_ENTITY_VELOCITY_ID (LINK_ENTITIES_ID+1)
#define SET_EQUIPMENT_ID (SET_ENTITY_VELOCITY_ID+1)
#define SET_EXPERIENCE_ID (SET_EQUIPMENT_ID+1)
#define SET_HEALTH_ID (SET_EXPERIENCE_ID+1)
#define SET_HELD_ITEM_ID (SET_HEALTH_ID+1)
#define UPDATE_OBJECTIVES_ID (SET_HELD_ITEM_ID+1)
#define SET_PASSENGERS_ID (UPDATE_OBJECTIVES_ID+1)
#define SET_PLAYER_INVENTORY_SLOT_ID (SET_PASSENGERS_ID+1)
#define UPDATE_TEAMS_ID (SET_PLAYER_INVENTORY_SLOT_ID+1)
#define UPDATE_SCORE_ID (UPDATE_TEAMS_ID+1)
#define SET_SIMULATION_DISTANCE_ID (UPDATE_SCORE_ID+1)
#define UPDATE_SUBTITLE_TEXT_ID (SET_SIMULATION_DISTANCE_ID+1)
#define UPDATE_TIME_ID (UPDATE_SUBTITLE_TEXT_ID+1)
#define UPDATE_TITLE_TEXT_ID (UPDATE_TIME_ID+1)
#define UPDATE_TITLE_ANIMATION_TIMES_ID (UPDATE_TITLE_TEXT_ID+1)
#define ENTITY_SOUND_EFFECT_ID (UPDATE_TITLE_ANIMATION_TIMES_ID+1)
#define SOUND_EFFECT_ID (ENTITY_SOUND_EFFECT_ID+1)
#define START_CONFIGURATION_ID (SOUND_EFFECT_ID+1)
#define STOP_SOUND_ID (START_CONFIGURATION_ID+1)
#define STORE_COOKIE_ID (STOP_SOUND_ID+1)
#define SYSTEM_CHAT_MESSAGE_ID (STORE_COOKIE_ID+1)

// clientbound
PACKET(login_play,
       R(int, int32_t, eid);
       R(bool, uint8_t, is_hardcore);
       RL(var_str, lstr, dimension_names, dimension_name_count);
       R(var_int, int32_t, max_players);
       R(var_int, int32_t, view_distance);
       R(var_int, int32_t, simulation_distance);
       R(bool, uint8_t, reduced_debug_info);
       R(bool, uint8_t, enable_respawn_screen);
       R(bool, uint8_t, do_limited_crafting);
       R(var_int, int32_t, dimension_type);
       R(var_str, lstr, dimension_name);
       R(long, int64_t, hashed_seed);
       R(ubyte, uint8_t, game_mode);
       R(byte, int8_t, prev_game_mode);
       R(bool, uint8_t, is_debug);
       R(bool, uint8_t, is_flat);
       R(bool, uint8_t, has_death_location);
#if defined(PACKET_READ_IMPL)
       if(out->has_death_location) {
	 error = write_var_str(packet_buffer, pos, max, out->death_dimension_name);
	 if(error) return error;
	 error = write_position(packet_buffer, pos, max, out->death_location);
	 if(error) return error;
       }
#elif defined(PACKET_WRITE_IMPL)
       if(out.has_death_location) {
	 error = read_var_str(packet_buffer, pos, max, &out.death_dimension_name);
	 if(error) return error;
	 error = read_position(packet_buffer, pos, max, &out.death_location);
	 if(error) return error;
       }
#elif defined(PACKET_PRINT_IMPL)
       if(out.has_death_location) {
	 print_var_str(out.death_dimension_name, indentation);
	 print_position(out.death_location, indentation);
       }
#else
       lstr death_dimension_name;
       position death_location;
#endif
       R(var_int, int32_t, portal_cooldown);
       R(var_int, int32_t, sea_level);
       R(bool, uint8_t, enforces_secure_chat);
       );

PACKET_ID(login_play, LOGIN_PLAY_ID)


PACKET(clientbound_keep_alive,
       R(long, int64_t, id);
       );
PACKET_ID(clientbound_keep_alive, CLIENTBOUND_KEEP_ALIVE_PLAY_ID)

PACKET(syncronize_player_position,
       R(var_int, int32_t, teleport_id);
       R(double, double, x);
       R(double, double, y);
       R(double, double, z);
       R(double, double, velocity_x);
       R(double, double, velocity_y);
       R(double, double, velocity_z);
       R(float, float, yaw);
       R(float, float, pitch);
       R(int, int32_t, flags);
       );
PACKET_ID(syncronize_player_position, SYNCRONIZE_PLAYER_POSITION_ID)

PACKET(update_entity_position_and_rotation,
       R(var_int, int32_t, entity_id);
       R(short, int16_t, delta_x);
       R(short, int16_t, delta_y);
       R(short, int16_t, delta_z);
       R(ubyte, uint8_t, yaw);
       R(ubyte, uint8_t, pitch);
       R(bool, uint8_t, on_ground);
       );
PACKET_ID(update_entity_position_and_rotation, UPDATE_ENTITY_POSITION_AND_ROTATION_ID)

PACKET(set_head_rotation,
       R(var_int, int32_t, entity_id);
       R(ubyte, uint8_t, yaw);
       );
PACKET_ID(set_head_rotation, SET_HEAD_ROTATION_ID)

PACKET(update_entity_position,
       R(var_int, int32_t, entity_id);
       R(short, int16_t, delta_x);
       R(short, int16_t, delta_y);
       R(short, int16_t, delta_z);
       R(bool, uint8_t, on_ground);
       );
PACKET_ID(update_entity_position, UPDATE_ENTITY_POSITION_ID)

PACKET(game_event,
       R(ubyte, uint8_t, event_id);
       R(float, float, value);
       );
PACKET_ID(game_event, GAME_EVENT_ID)

PACKET(set_center_chunk,
       R(var_int, int32_t, x);
       R(var_int, int32_t, y);
       );
PACKET_ID(set_center_chunk, SET_CENTER_CHUNK_ID)

PACKET(heightmap,
       R(var_int, int32_t, type);
       RL(long, int64_t, data, data_count);
       );
PACKET(chunk_block_entity,
       R(ubyte, uint8_t, packed_xz);
       R(short, int16_t, y);
       R(var_int, int32_t, type);
       O(network_nbt, nbt_tag_t*, data);
       );




PACKET(paletted_container,
#if defined(PACKET_READ_IMPL)
#elif defined(PACKET_WRITE_IMPL)
       for(int i = 0; i < out.data_len; i++) {
	 error = write_ubyte(packet_buffer, pos, max, out.data[i]);
	 if(error) return error;
       }
       
#elif defined(PACKET_PRINT_IMPL)
       // todo -- print
#else
       uint8_t *data;
       uint32_t data_len; // 0 for chunk, 1 for biome(determines the number of entries)
#endif
       );

#if defined(PACKET_READ_IMPL)
int read_paletted_container_to_array(uint8_t *packet_buf, int32_t max, uint8_t min_bpe_indirect, uint8_t max_bpe_indirect, uint8_t bits_per_entry_direct, int8_t palette_variant, int32_t *out) {
  uint32_t pos = 0;
  uint8_t *packet_buffer = packet_buf;
  int error = 0;
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

  int number_of_entries;
  if(palette_variant == 0)
    number_of_entries = 4096;
  else if(palette_variant == 1)
    number_of_entries = 64;
  else number_of_entries = 0;
  int8_t bits_per_entry = 0;
  error = read_byte(&packet_buffer, &pos, max, &bits_per_entry);
  if(error) return error;
  
  if (bits_per_entry == 0) {
    int32_t block;
    error = read_var_int(&packet_buffer, &pos, max, &block);	
    if(error) return error;
    for(int i = 0; i < number_of_entries; i++)
      out[i] = block;
  } else if (bits_per_entry <= max_bpe_indirect) { // paletted
    int32_t palette_len;
    error = read_var_int(&packet_buffer, &pos, max, &palette_len);	
    int32_t palette[palette_len];
    for(int i = 0; i < palette_len; i++) {
      error = read_var_int(&packet_buffer, &pos, max, &palette[i]);
      //printf("%d\n", n_distinct_values);
      if(error) return error;
    }

    int entries_per_long = 64 / bits_per_entry;
    int number_of_longs = ceil((float)number_of_entries / entries_per_long);
    int64_t data[number_of_longs];
    for(int i = 0; i < number_of_longs; i++){
      error = read_long(&packet_buffer, &pos, max, data+i);
    }
    uint64_t entry_mask = ((uint64_t)1 << bits_per_entry) - 1;
    for(int i = 0; i < number_of_entries; i++) {
      int long_index = i / entries_per_long;
      int bit_index = (i % entries_per_long) * bits_per_entry;
      
      // if value has a smaller integer type, it may again be necessary to cast it to 64 bits.
      out[i] = palette[((data[long_index] >> bit_index) & entry_mask)];
    }
	 

	 

  } else { // direct

    int entries_per_long = floor((float)64 / bits_per_entry_direct);
    int number_of_longs = ceil((float)number_of_entries / entries_per_long);
    int64_t data[number_of_longs];
    for(int i = 0; i < number_of_longs; i++){
      error = read_long(&packet_buffer, &pos, max, data+i);
    }

    uint64_t entry_mask = ((uint64_t)1 << bits_per_entry_direct) - 1;
	 
    //for(int i = 0; i < number_of_longs; i++) data[i] = 0;
    for(int i = 0; i < number_of_entries; i++) {
      int long_index = i / entries_per_long;
      int bit_index = i % entries_per_long * bits_per_entry_direct;

      out[i] = (data[long_index] >> bit_index) & entry_mask;
    }
  }
#undef MIN
#undef MAX
}

#elif defined(PACKET_WRITE_IMPL)
int create_paletted_container_from_entries(int32_t *block_states, uint8_t min_bpe_indirect, uint8_t max_bpe_indirect, uint8_t bits_per_entry_direct, int8_t palette_variant, paletted_container *out) {
  uint8_t _packet_buffer[4096];
  uint32_t pos = 0;
  int32_t max = 4096;
  uint8_t *packet_buffer = _packet_buffer;
  int error = 0;
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

  int number_of_entries;
  if(palette_variant == 0)
    number_of_entries = 4096;
  else if(palette_variant == 1)
    number_of_entries = 64;
  else number_of_entries = 0;

  int32_t n_distinct_values = 0;
  int32_t distinct_values[4096];
  for(int i = 0; i < number_of_entries; i++) {
    int32_t value = block_states[i];
    int8_t found_data = 0;
    for(int j = 0; j < n_distinct_values; j++)
      if(distinct_values[j] == value)
	found_data = 1;
    if(!found_data) { // distinct
      distinct_values[n_distinct_values++] = value;
    }
  }
  int n_distinct_values_2 = n_distinct_values;
  int bits_per_entry = 0;
  //printf("%d\n%d\n", bits_per_entry, n_distinct_values);

  while (n_distinct_values_2 > 0) {
    n_distinct_values_2 &= (n_distinct_values_2 - 1); // Unsets the rightmost set bit
    bits_per_entry++;      // Increment count
  }
  bits_per_entry = MAX(min_bpe_indirect, bits_per_entry);

  if (n_distinct_values == 1) {
    error = write_ubyte(&packet_buffer, &pos, max, 0);
    if(error) return error;
    error = write_var_int(&packet_buffer, &pos, max, distinct_values[0]);	
    if(error) return error;
  } else if (bits_per_entry <= max_bpe_indirect) { // paletted

    error = write_ubyte(&packet_buffer, &pos, max, bits_per_entry);
    if(error) return error;
    error = write_var_int(&packet_buffer, &pos, max, n_distinct_values);	
    for(int i = 0; i < n_distinct_values; i++) {
      error = write_var_int(&packet_buffer, &pos, max, distinct_values[i]);
      //printf("%d\n", n_distinct_values);
      if(error) return error;
    }

    int entries_per_long = 64 / bits_per_entry;
    int number_of_longs = ceil((float)number_of_entries / entries_per_long);

    uint64_t entry_mask = ((uint64_t)1 << bits_per_entry) - 1;
    //printf("entry_mask: %ld\n", entry_mask);
    uint64_t data[4096] = { };
    //for(int i = 0; i < number_of_longs; i++) data[i] = 0;
    for(int i = 0; i < number_of_entries; i++) {
      int long_index = i / entries_per_long;
      int bit_index = (i % entries_per_long) * bits_per_entry;

      data[long_index] &= ~(entry_mask << bit_index);
      // if value has a smaller integer type, it may again be necessary to cast it to 64 bits.
      int data_idx = 0;
      for(int j = 0; j < n_distinct_values; j++)
	if(block_states[i] == distinct_values[j])
	  data_idx = j;
	     
      data[long_index] |= (uint64_t)data_idx << bit_index;
    }
	 
    for(int i = 0; i < number_of_longs; i++) {
      error = write_long(&packet_buffer, &pos, max, data[i]);
      if(error)
	return error;
    }
	 

  } else { // direct
    error = write_ubyte(&packet_buffer, &pos, max, bits_per_entry_direct);
    if(error) return error;

    int entries_per_long = floor((float)64 / bits_per_entry_direct);
    int number_of_longs = ceil((float)number_of_entries / entries_per_long);

    uint64_t entry_mask = ((uint64_t)1 << bits_per_entry_direct) - 1;
	 
    uint64_t data[4096] = { 0 };
    //for(int i = 0; i < number_of_longs; i++) data[i] = 0;
    for(int i = 0; i < number_of_entries; i++) {
      int long_index = i / entries_per_long;
      int bit_index = i % entries_per_long * bits_per_entry_direct;

      //printf("%d\n", long_index);
      data[long_index] &= ~(entry_mask << bit_index);
      // if value has a smaller integer type, it may again be necessary to cast it to 64 bits.
      data[long_index] |= (uint64_t)block_states[i] << bit_index;
    }
	 
    for(int i = 0; i < number_of_longs; i++) {
      error = write_long(&packet_buffer, &pos, max, data[i]);
      if(error)
	return error;
    }
	 

  }
#undef MIN
#undef MAX
  out->data = malloc(pos);
  memcpy(out->data, _packet_buffer, pos);
  out->data_len = pos;
}
#elif defined(PACKET_PRINT_IMPL)
       // todo -- print
#else
#define PALETTED_CONTAINER_TYPE_BLOCK 0
#define PALETTED_CONTAINER_TYPE_BIOME 1
int create_paletted_container_from_entries(int32_t *block_states, uint8_t min_bpe_indirect, uint8_t max_bpe_indirect, uint8_t bits_per_entry_direct, int8_t palette_variant, paletted_container *out);
#endif

PACKET(chunk_section,
       R(short, int16_t, block_count);
       R(paletted_container, paletted_container, block_states);
       R(paletted_container, paletted_container, biomes);
       );
PACKET(chunk_data_and_update_light,
       R(int, int32_t, x);
       R(int, int32_t, y);
       RL(heightmap, heightmap, heightmaps, heightmap_count);
       RL(ubyte, uint8_t, data, data_len);
       RL(chunk_block_entity, chunk_block_entity, block_entities, block_entities_count);
       R(var_int, int32_t, o1);
       R(var_int, int32_t, o2);
       R(var_int, int32_t, o3);
       R(var_int, int32_t, o4);
       R(var_int, int32_t, o5);
       R(var_int, int32_t, o6);
       );
PACKET_ID(chunk_data_and_update_light, CHUNK_DATA_AND_UPDATE_LIGHT_ID)

PACKET(spawn_entity,
       R(var_int, int32_t, eid);
       R(uuid, uuid, entity_uuid);
       R(var_int, int32_t, type);
       R(double, double, x);
       R(double, double, y);
       R(double, double, z);
       R(lpvec3, lpvec3, velocity);
       R(ubyte, uint8_t, pitch);
       R(ubyte, uint8_t, yaw);
       R(ubyte, uint8_t, head_angle);
       R(var_int, int32_t, data);
       );
PACKET_ID(spawn_entity, SPAWN_ENTITY_ID)

PACKET(player_info_remove,
       RL(uuid, uuid, player_ids, player_id_len);
       );
PACKET_ID(player_info_remove, PLAYER_INFO_REMOVE_ID)




PACKET(set_entity_velocity,
       R(var_int, int32_t, entity_id);
       R(lpvec3, lpvec3, velocity);
       );
PACKET_ID(set_entity_velocity, SET_ENTITY_VELOCITY_ID)

PACKET(player_action_add_player_property,
       R(var_str, lstr, name);
       R(var_str, lstr, value);
       );


PACKET(player_action,
       R(uuid, uuid, uuid);
#if defined(PACKET_READ_IMPL)
// todo -- impelement
#elif defined(PACKET_WRITE_IMPL)
       if(out.actions & 0x01) {
	 error = write_var_str(packet_buffer, pos, max, out.add_player.name);
	 if(error) return error;
	 error = write_var_int(packet_buffer, pos, max, out.add_player.num_properties);
	 if(error) return error;
	 for(int i = 0; i < out.add_player.num_properties; i++) {
	   error = write_player_action_add_player_property(packet_buffer, pos, max, out.add_player.properties[i]);
	   if(error) return error;
	   
	 }
       }
       if(out.actions & 0x02) {
	 // todo -- do
       }
       if(out.actions & 0x04) {
	 error = write_var_int(packet_buffer, pos, max, out.update_game_mode.game_mode);
	 if(error) return error;
       }
       if(out.actions & 0x08) {
	 error = write_bool(packet_buffer, pos, max, out.update_listed.listed);
	 if(error) return error;
       }
       if(out.actions & 0x10) {
	 error = write_var_int(packet_buffer, pos, max, out.update_latency.latency);
	 if(error) return error;
       }
       if(out.actions & 0x20) {
	 // todo -- do
       }       
       

#elif defined(PACKET_PRINT_IMPL)

#else
       struct {
	 lstr name;
	 player_action_add_player_property *properties;
	 int32_t num_properties;
       } add_player;
       struct {
	 // todo -- do
       } initialize_chat;
       struct {
	 int32_t game_mode;
       } update_game_mode;
       struct {
	 uint8_t listed;
       } update_listed;
       struct {
	 int32_t latency;
       } update_latency;
       struct {
	 uint8_t has_display_name;
	 // todo -- implement chat type
       } update_display_name;
       int8_t actions;
       
#endif       
       );





PACKET(player_info_update,
       R(byte, int8_t, actions);
#if defined(PACKET_READ_IMPL)
       // todo -- implement
#elif defined(PACKET_WRITE_IMPL)
       error = write_var_int(packet_buffer, pos, max, out.player_action_count);
       if(error) return error;
       for(int i = 0; i < out.player_action_count; i++) {
	 out.player_actions[i].actions = out.actions;
	 error = write_player_action(packet_buffer, pos, max, out.player_actions[i]);
	 if(error) return error;
       }

#elif defined(PACKET_PRINT_IMPL)
       // todo -- implement
#else
       player_action *player_actions;
       int32_t player_action_count;
#endif
       );
PACKET_ID(player_info_update, PLAYER_INFO_UPDATE_ID)


PACKET(entity_metadata,
#if defined(PACKET_READ_IMPL)
       // todo -- implement
#elif defined(PACKET_WRITE_IMPL)
       error = write_ubyte(packet_buffer, pos, max, out.index);
       if(error) return error;
       error = write_var_int(packet_buffer, pos, max, out.type);
       if(error) return error;
       switch (out.type) {
       case 0:
	 error = write_byte(packet_buffer, pos, max, out.value.byte);
	 if(error) return error;
	 break;
       case 1:
	 error = write_var_int(packet_buffer, pos, max, out.value.var_int);
	 if(error) return error;
	 break;
       case 2:
	 error = write_var_long(packet_buffer, pos, max, out.value.var_long);
	 if(error) return error;
	 break;
       case 3:
	 error = write_float(packet_buffer, pos, max, out.value.float_value);
	 if(error) return error;
	 break;
       case 4:
	 error = write_var_str(packet_buffer, pos, max, out.value.string);
	 if(error) return error;
	 break;
       case 8:
	 error = write_bool(packet_buffer, pos, max, out.value.boolean);
	 if(error) return error;
	 break;
       case 9:
	 error = write_float(packet_buffer, pos, max, out.value.rotations.x);
	 if(error) return error;
	 error = write_float(packet_buffer, pos, max, out.value.rotations.y);
	 if(error) return error;
	 error = write_float(packet_buffer, pos, max, out.value.rotations.z);
	 if(error) return error;
	 break;
       case 10:
	 error = write_position(packet_buffer, pos, max, out.value.position);
	 if(error) return error;
	 break;
       case 11:
	 error = write_bool(packet_buffer, pos, max, out.value.optional_position.has_position);
	 if(error) return error;
	 if(out.value.optional_position.has_position) {
	   error = write_position(packet_buffer, pos, max, out.value.optional_position.position);
	   if(error) return error;
	 }
	 break;
       case 12:
	 error = write_var_int(packet_buffer, pos, max, out.value.direction);
	 if(error) return error;
	 break;
       case 13:
	 error = write_bool(packet_buffer, pos, max, out.value.optional_living_entity_reference.has_uuid);
	 if(error) return error;
	 if(out.value.optional_position.has_position) {
	   error = write_uuid(packet_buffer, pos, max, out.value.optional_living_entity_reference.entity_uuid);
	   if(error) return error;
	 }
	 break;
       case 14:
	 error = write_var_int(packet_buffer, pos, max, out.value.block_state);
	 if(error) return error;
	 break;
       case 15:
	 error = write_var_int(packet_buffer, pos, max, out.value.optional_block_state);
	 if(error) return error;
	 break;
       case 19:
	 error = write_var_int(packet_buffer, pos, max, out.value.optional_var_int);
	 if(error) return error;
	 break;
       case 20:
	 error = write_var_int(packet_buffer, pos, max, out.value.pose);
	 if(error) return error;
	 break;
       case 21:
	 error = write_var_int(packet_buffer, pos, max, out.value.cat_variant);
	 if(error) return error;
	 break;
       case 22:
	 error = write_var_int(packet_buffer, pos, max, out.value.cow_variant);
	 if(error) return error;
	 break;
       case 23:
	 error = write_var_int(packet_buffer, pos, max, out.value.wolf_variant);
	 if(error) return error;
	 break;
       case 24:
	 error = write_var_int(packet_buffer, pos, max, out.value.wolf_sound_variant);
	 if(error) return error;
	 break;
       case 25:
	 error = write_var_int(packet_buffer, pos, max, out.value.frog_variant);
	 if(error) return error;
	 break;
       case 26:
	 error = write_var_int(packet_buffer, pos, max, out.value.pig_variant);
	 if(error) return error;
	 break;
       case 27:
	 error = write_var_int(packet_buffer, pos, max, out.value.chicken_variant);
	 if(error) return error;
	 break;
       case 28:
	 error = write_var_int(packet_buffer, pos, max, out.value.zombie_natalis_variant);
	 if(error) return error;
	 break;
       case 29:
	 error = write_bool(packet_buffer, pos, max, out.value.optional_global_position.has_global_position);
	 if(error) return error;
	 if(out.value.optional_position.has_position) {
	   error = write_var_str(packet_buffer, pos, max, out.value.optional_global_position.identifier);
	   if(error) return error;
	   error = write_position(packet_buffer, pos, max, out.value.optional_global_position.position);
	   if(error) return error;
	 }
	 break;
       case 31:
	 error = write_var_int(packet_buffer, pos, max, out.value.sniffer_state);
	 if(error) return error;
	 break;
       case 32:
	 error = write_var_int(packet_buffer, pos, max, out.value.armadillo_state);
	 if(error) return error;
	 break;
       case 33:
	 error = write_var_int(packet_buffer, pos, max, out.value.copper_golem_state);
	 if(error) return error;
	 break;
       case 34:
	 error = write_var_int(packet_buffer, pos, max, out.value.weathering_copper_state);
	 if(error) return error;
	 break;
       case 35:
	 error = write_float(packet_buffer, pos, max, out.value.vector_3.x);
	 if(error) return error;
	 error = write_float(packet_buffer, pos, max, out.value.vector_3.y);
	 if(error) return error;
	 error = write_float(packet_buffer, pos, max, out.value.vector_3.z);
	 if(error) return error;
	 break;
       case 36:
	 error = write_float(packet_buffer, pos, max, out.value.quat.x);
	 if(error) return error;
	 error = write_float(packet_buffer, pos, max, out.value.quat.y);
	 if(error) return error;
	 error = write_float(packet_buffer, pos, max, out.value.quat.z);
	 if(error) return error;
	 error = write_float(packet_buffer, pos, max, out.value.quat.w);
	 if(error) return error;
	 break;

       }
       
#elif defined(PACKET_PRINT_IMPL)
       // todo -- implement
#else
       uint8_t index;
       int32_t type;
       union {
	 int8_t byte;
	 int32_t var_int;
	 int64_t var_long;
	 float float_value;
	 lstr string;
	 // todo -- text component
	 // todo -- slot
	 uint8_t boolean;
	 struct {
	   float x, y, z;
	 } rotations;
	 position position;
	 struct {
	   position position;
	   uint8_t has_position;
	 } optional_position;
	 int32_t direction;
	 struct {
	   uuid entity_uuid;
	   uint8_t has_uuid;
	 } optional_living_entity_reference;
	 int32_t block_state;
	 int32_t optional_block_state;
	 // todo -- particle 1 and 2
	 int32_t optional_var_int;
	 int32_t pose;
	 int32_t cat_variant;
	 int32_t cow_variant;
	 int32_t wolf_variant;
	 int32_t wolf_sound_variant;
	 int32_t frog_variant;
	 int32_t pig_variant;
	 int32_t chicken_variant;
	 int32_t zombie_natalis_variant; // todo -- spell
	 struct {
	   uint8_t has_global_position;
	   lstr identifier;
	   position position;
	 } optional_global_position;
	 // todo -- painting variants
	 int32_t sniffer_state;
	 int32_t armadillo_state;
	 int32_t copper_golem_state;
	 int32_t weathering_copper_state;
	 struct {
	   float x, y, z;
	 } vector_3;
	 struct {
	   float x, y, z, w;
	 } quat;

	 // todo -- resolvable profile and humanoid arm
	 
       } value;
#endif
       
       );


PACKET(set_entity_metadata,
       R(var_int, int32_t, entity_id);
#if defined(PACKET_READ_IMPL)
       // todo -- implement
#elif defined(PACKET_WRITE_IMPL)
       for(int i = 0; i < out.data_len; i++) {
	 write_entity_metadata(packet_buffer, pos, max, out.data[i]);
       }
       write_ubyte(packet_buffer, pos, max, 0xFF);
#elif defined(PACKET_PRINT_IMPL)
       // todo -- implement
#else
       entity_metadata *data;
       int32_t data_len;
#endif
       
       );
PACKET_ID(set_entity_metadata, SET_ENTITY_METADATA_ID)


PACKET(system_chat_message,
       R(network_nbt, nbt_tag_t*, content);
       R(bool, uint8_t, overlay);
       );
PACKET_ID(system_chat_message, SYSTEM_CHAT_MESSAGE_ID)
