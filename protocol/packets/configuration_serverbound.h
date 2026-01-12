#define CLIENT_INFORMATION_CONFIGURATION_ID 0
#define COOKIE_RESPONSE_CONFIGURATION_ID (CLIENT_INFORMATION_CONFIGURATION_ID+1)
#define SERVERBOUND_PLUGIN_MESSAGE_CONFIGURATION_ID (COOKIE_RESPONSE_CONFIGURATION_ID+1)
#define ACKGNOWLEDGE_SERVER_CONFIGURATION_ID (SERVERBOUND_PLUGIN_MESSAGE_CONFIGURATION_ID+1)
#define SERVERBOUND_KEEP_ALIVE_CONFIGURATION_ID (ACKGNOWLEDGE_SERVER_CONFIGURATION_ID+1)
#define PONG_CONFIGURATION_ID (SERVERBOUND_KEEP_ALIVE_CONFIGURATION_ID+1)
#define RESOURCE_PACK_RESPONSE_ID (PONG_CONFIGURATION_ID+1)
#define SERVERBOUND_KNOWN_PACKS_CONFIGURATION_ID (RESOURCE_PACK_RESPONSE_ID+1)

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
PACKET_ID(client_information_configuration, CLIENT_INFORMATION_CONFIGURATION_ID)


PACKET(known_pack,
       R(var_str, lstr, namespace);
       R(var_str, lstr, id);
       R(var_str, lstr, version);
       );
PACKET(serverbound_known_packs,
       RL(known_pack, known_pack, packs, num_packs);
       );
PACKET_ID(serverbound_known_packs, SERVERBOUND_KNOWN_PACKS_CONFIGURATION_ID)



//


