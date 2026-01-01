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
#define DEBUG_SAMPLE_ID (DAMAGE_EVENT_ID+1)
#define DELETE_MESSAGE_ID (DEBUG_SAMPLE_ID+1)
#define DISCONNECT_ID (DELETE_MESSAGE_ID+1)
#define DISGUISED_CHAT_MESSAGE_ID (DISCONNECT_ID+1)
#define ENTITY_EVENT_ID (DISGUISED_CHAT_MESSAGE_ID+1)
#define TELEPORT_ENTITY_ID (ENTITY_EVENT_ID+1)
#define EXPLOSION_ID (TELEPORT_ENTITY_ID+1)
#define UNLOAD_CHUNK_ID (EXPLOSION_ID+1)
#define GAME_EVENT_ID (UNLOAD_CHUNK_ID+1)
#define OPEN_HORSE_SCREEN_ID (GAME_EVENT_ID+1)
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
