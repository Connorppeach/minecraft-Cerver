#define COOKIE_REQUEST_ID 0
#define CLIENTBOUND_PLUGIN_MESSAGE_ID (COOKIE_REQUEST_ID+1)
#define DISCONNECT_CONFIGURATION_ID (CLIENTBOUND_PLUGIN_MESSAGE_ID+1)
#define FINISH_CONFIGURATION_ID (DISCONNECT_CONFIGURATION_ID+1)
#define CLIENTBOUND_KEEPALIVE_CONFIGURATION_ID (FINISH_CONFIGURATION_ID+1)
#define PING_CONFIGURATION_ID (CLIENTBOUND_KEEPALIVE_CONFIGURATION_ID+1)
#define RESET_CHAT_ID (PING_CONFIGURATION_ID+1)
#define REGISTRY_DATA_ID (RESET_CHAT_ID+1)
#define REMOVE_RESOURCE_PACK_CONFIGURATION_ID (REGISTRY_DATA_ID+1)
#define ADD_RESOURCE_PACK_CONFIGURATION_ID (REMOVE_RESOURCE_PACK_CONFIGURATION_ID+1)
#define STORE_COOKIE_CONFIGURATION_ID (ADD_RESOURCE_PACK_CONFIGURATION_ID+1)
#define TRANSFER_CONFIGURATION_ID (STORE_COOKIE_CONFIGURATION_ID+1)
#define FEATURE_FLAGS_ID (TRANSFER_CONFIGURATION_ID+1)
#define UPDATE_TAGS_ID (FEATURE_FLAGS_ID+1)
#define CLIENTBOUND_KNOWN_PACKS_ID (UPDATE_TAGS_ID+1)
#define CUSTOM_REPORT_DETAILS_CONFIGURATION_ID (CLIENTBOUND_KNOWN_PACKS_ID+1)
#define SERVER_LINKS_CONFIGURATION_ID (CUSTOM_REPORT_DETAILS_CONFIGURATION_ID+1)
#define CLEAR_DIALOG_CONFIGURATION_ID (SERVER_LINKS_CONFIGURATION_ID+1)
#define SHOW_DIALOG_CONFIGURATION_ID (CLEAR_DIALOG_CONFIGURATION_ID+1)

// client ones
#define CLIENT_INFORMATION_CONFIGURATION_ID 0
//
PACKET(client_information_configuration,
       R(var_str, lstr, locale);
       R(byte, int8_t, view_distance);
       R(var_int, int32_t, chat_mode);
       R(bool, uint8_t, chat_colors);
       R(ubyte, uint8_t, displayed_skin_parts);
       R(var_int, int32_t, main_hand);
       R(bool, uint8_t, enable_text_filtering);
       R(bool, uint8_t, allow_server_listings);
       R(var_int, int32_t, particle_status);
       );
//

PACKET(clientbound_known_pack,
       R(var_str, lstr, namespace);
       R(var_str, lstr, id);
       R(var_str, lstr, version);
       );
PACKET(clientbound_known_packs,
       RL(clientbound_known_pack, clientbound_known_pack, packs, num_packs);
       );

//
PACKET(registry_data_entry,
       R(var_str, lstr, entry_id);
       O(NBT, NBT, data);
       );
PACKET(registry_data,
       R(var_str, lstr, registry_id);
       RL(clientbound_known_pack, clientbound_known_pack, packs, num_packs);
       );
