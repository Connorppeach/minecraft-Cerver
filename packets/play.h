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

// serverbound

#define CONFIRM_TELEPORTATION_ID 0
#define QUERY_BLOCK_ENTITY_TAG_ID (CONFIRM_TELEPORTATION_ID+1)
#define BUNDLE_ITEM_SELECTED_ID (QUERY_BLOCK_ENTITY_TAG_ID+1)
#define CHANGE_DIFFUCULTY_ID (BUNDLE_ITEM_SELECTED_ID+1)
#define CHANGE_GAME_MODE_ID (CHANGE_DIFFUCULTY_ID+1)
#define ACK_MESSAGE_ID (CHANGE_GAME_MODE_ID+1)
#define CHAT_COMMAND_ID (ACK_MESSAGE_ID+1)
#define SIGNED_CHAT_COMMAND_ID (CHAT_COMMAND_ID+1)
#define CHAT_MESSAGE_ID (SIGNED_CHAT_COMMAND_ID+1)
#define PLAYER_SESSION_ID (CHAT_MESSAGE_ID+1)
#define CHUNK_BATCH_RECIEVED_ID (PLAYER_SESSION_ID+1)
#define CLIENT_STATUS_ID (CHUNK_BATCH_RECIEVED_ID+1)
#define CLIENT_TICK_END_ID (CLIENT_STATUS_ID+1)
#define CLIENT_INFORMATION_PLAY_ID (CLIENT_TICK_END_ID+1)
#define COMMAND_SUGGESTIONS_REQUEST_ID (CLIENT_INFORMATION_PLAY_ID+1)
#define ACK_CONFIGURATION_ID (COMMAND_SUGGESTIONS_REQUEST_ID+1)
#define CLICK_CONTAINER_BUTTON_PLAY_ID (ACK_CONFIGURATION_ID+1)
#define CLICK_CONTAINER_PLAY_ID (CLICK_CONTAINER_BUTTON_PLAY_ID+1)
#define CLOSE_CONTAINER_PLAY_ID (CLICK_CONTAINER_PLAY_ID+1)
#define CHANGE_CONTAINER_SLOT_STATE_ID (CLOSE_CONTAINER_PLAY_ID+1)
#define COOKIE_RESPONSE_PLAY_ID (CHANGE_CONTAINER_SLOT_STATE_ID+1)
#define SERVERBOUND_PLUGIN_MESSAGE_PLAY_ID (COOKIE_RESPONSE_PLAY_ID+1)
#define DEBUG_SAMPLE_SUBSCRIPTION_ID (SERVERBOUND_PLUGIN_MESSAGE_PLAY_ID+1)
#define EDIT_BOOK_ID (DEBUG_SAMPLE_SUBSCRIPTION_ID+1)
#define QUERY_ENTITY_TAG_ID (EDIT_BOOK_ID+1)
#define INTERACT_ID (QUERY_ENTITY_TAG_ID+1)
#define JIGSAW_GENERATE_ID (INTERACT_ID+1)
#define SERVERBOUND_KEEP_ALIVE_ID (JIGSAW_GENERATE_ID+1)
#define LOCK_DIFFUCULTY_ID (SERVERBOUND_KEEP_ALIVE_ID+1)
#define SET_PLAYER_POSITION_ID (LOCK_DIFFUCULTY_ID+1)
#define SET_PLAYER_POSITION_AND_ROTATION_ID (SET_PLAYER_POSITION_ID+1)
#define SET_PLAYER_ROTATION_ID (SET_PLAYER_POSITION_AND_ROTATION_ID+1)
#define SET_PLAYER_MOVEMENT_FLAGS_ID (SET_PLAYER_ROTATION_ID+1)
#define MOVE_VEHICLE_SERVERBOUND_ID (SET_PLAYER_MOVEMENT_FLAGS_ID+1)
#define PADDLE_BOAT_ID (MOVE_VEHICLE_SERVERBOUND_ID+1)
#define PICK_ITEM_FROM_BLOCK_ID (PADDLE_BOAT_ID+1)
#define PICK_ITEM_FROM_ENTITY_ID (PICK_ITEM_FROM_BLOCK_ID+1)
#define PING_REQUEST_PLAY_ID (PICK_ITEM_FROM_ENTITY_ID+1)
#define PLACE_RECIPE_ID (PING_REQUEST_FROM_PLAY_ID+1)
#define PLAYER_ABILITIES_SERVERBOUND_ID (PLACE_RECIPE_ID+1)
#define PLAYER_ACTION_ID (PLAYER_ABILITIES_SERVERBOUND_ID+1)
#define PLAYER_COMMAND_ID (PLAYER_ACTION_ID+1)
#define PLAYER_INPUT_ID (PLAYER_COMMAND_ID+1)
#define PLAYER_LOADED_ID (PLAYER_INPUT_ID+1)
#define PONG_PLAY_ID (PLAYER_LOADED_ID+1)
#define CHANGE_RECIPIE_BOOK_SETTINGS_ID (PONG_PLAY_ID+1)
#define SET_SEEN_RECIPE_ID (CHANGE_RECIPIE_BOOK_SETTINGS_ID+1)
#define RENAME_ITEM_ID (SET_SEEN_RECIPE_ID+1)
#define RESOURCE_PACK_RESPONSE_PLAY_ID (RENAME_ITEM_ID+1)
#define SEEN_ADVANCEMENTS_ID (RESOURCE_PACK_RESPONSE_PLAY_ID+1)
#define SELECT_TRADE_ID (SEEN_ADVANCEMENTS_ID+1)
#define SET_BEACON_EFFECT_ID (SELECT_TRADE_ID+1)
#define SET_HELD_ITEM_SERVERBOUND_ID (SET_BEACON_EFFECT_ID+1)
#define PROGRAM_COMMAND_BLOCK_ID (SET_HELD_ITEM_SERVERBOUND_ID+1)
#define PROGRAM_COMMAND_BLOCK_MINECART_ID (PROGRAM_COMMAND_BLOCK_ID+1)
#define SET_CREATIVE_MODE_SLOT_ID (PROGRAM_COMMAND_BLOCK_MINECART_ID+1)
#define PROGRAM_JIGSAW_BLOCK_ID (SET_CREATIVE_MODE_SLOT_ID+1)
#define PROGRAM_STRUCTURE_BLOCK_ID (PROGRAM_JIGSAW_BLOCK_ID+1)
#define SET_TEST_BLOCK_ID (PROGRAM_STRUCTURE_BLOCK_ID+1)
#define UPDATE_SIGN_ID (SET_TEST_BLOCK_ID+1)
#define SWING_ARM_ID (UPDATE_SIGN_ID+1)
#define TELEPORT_TO_ENTITY_ID (SWING_ARM_ID+1)
#define TEST_INSTANCE_BLOCK_ACTION_ID (TELEPORT_TO_ENTITY_ID+1)
#define USE_ITEM_ON_ID (TEST_INSTANCE_BLOCK_ACTION_ID+1)
#define USE_ITEM_ID (USE_ITEM_ON_ID+1)
#define CUSTOM_CLICK_ACTION_ID (USE_ITEM_ID+1)


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
	 print_var_str(out.death_dimension_name);
	 print_position(out.death_location);
       }
#else
       lstr death_dimension_name;
       position death_location;
#endif
       R(var_int, int32_t, portal_cooldown);
       R(var_int, int32_t, sea_level);
       R(bool, uint8_t, enforces_secure_chat);
       );

PACKET(clientbound_keep_alive,
       R(long, int64_t, id);
       );

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

PACKET(game_event,
       R(ubyte, uint8_t, event_id);
       R(float, float, value);
       );

PACKET(set_center_chunk,
       R(var_int, int32_t, x);
       R(var_int, int32_t, y);
       );

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
       R(ubyte, uint8_t, bits_per_entry);
#if defined(PACKET_READ_IMPL)
       // todo -- read
#elif defined(PACKET_WRITE_IMPL)
       // todo -- more than single valued palettes
       if (out.format == 0) {
	 write_var_int(packet_buffer, pos, max, out.value);	
       } else if (out.format == 2) { // direct
	 int number_of_entries = 4096;
	 int entries_per_long = floor((float)64 / out.bits_per_entry);
	 int number_of_longs = ceil((float)number_of_entries / entries_per_long);

	 uint64_t entry_mask = ((uint64_t)1 << out.bits_per_entry) - 1;
	 
	 uint64_t data[4096];
	 for(int i = 0; i < number_of_longs; i++) data[i] = 0;
	 for(int i = 0; i < number_of_entries; i++) {
	   int long_index = i / entries_per_long;
	   int bit_index = i % entries_per_long * out.bits_per_entry;

	   //printf("%d\n", long_index);
	   data[long_index] &= ~(entry_mask << bit_index);
	   // if value has a smaller integer type, it may again be necessary to cast it to 64 bits.
	   data[long_index] |= (uint64_t)out.data[i] << bit_index;
	 }
	 
	 for(int i = 0; i < number_of_longs; i++) {
	   error = write_long(packet_buffer, pos, max, data[i]);
	   if(error)
	     return error;
	 }
	 

       }
       
#elif defined(PACKET_PRINT_IMPL)
       // todo -- print
#else
       int32_t data[4096];  // only does stuff in format 1 and 2
       int32_t value; // only does stuff in format 0
       int32_t palette_length; // only does stuff in format 1
       uint8_t format; // only does stuff in format 1
#endif
       );
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

// serverbound

PACKET(confirm_teleportation,
       R(var_int, int32_t, teleport_id);
       );

PACKET(set_player_position,
       R(double, double, x);
       R(double, double, y);
       R(double, double, z);
       R(byte, int8_t, flags);
       );
PACKET(set_player_position_and_rotation,
       R(double, double, x);
       R(double, double, y);
       R(double, double, z);
       R(float, float, yaw);
       R(float, float, pitch);
       R(byte, int8_t, flags);
       );

PACKET(set_player_rotation,
       R(float, float, yaw);
       R(float, float, pitch);
       R(byte, int8_t, flags);
       );
