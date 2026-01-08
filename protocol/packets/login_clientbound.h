// TODO -- rest of packets
#define DISCONNECT_LOGIN_ID 0
#define ENCRYPTION_REQEUST_ID (DISCONNECT_LOGIN_ID+1)
#define LOGIN_SUCCESS_ID (ENCRYPTION_REQEUST_ID+1)
#define SET_COMPRESSION_ID (LOGIN_SUCCESS_ID+1)
#define LOGIN_PLUGIN_REQUEST_ID (SET_COMPRESSION_ID+1)
#define LOGIN_COOKIE_REQUEST_ID (LOGIN_PLUGIN_REQUEST_ID+1)


PACKET(game_profile_property,
       R(var_str, lstr, name);
       R(var_str, lstr, value);
       )

PACKET(game_profile,
       R(uuid, uuid, uuid);
       R(var_str, lstr, username);
       RL(game_profile_property, game_profile_property, properties, game_profile_property_count);
       );



PACKET(login_success,
       R(game_profile, game_profile, profile);
       );




PACKET(disconnect_login,
       R(var_str, lstr, json);
       );
