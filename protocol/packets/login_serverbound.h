// TODO -- rest of packets
#define LOGIN_START_ID 0
#define ENCRYPTION_RESPONSE_ID (LOGIN_START_ID+1)
#define LOGIN_PLUGIN_RESPONSE_ID (ENCRYPTION_RESPONSE_ID+1)
#define LOGIN_ACKNOWLEDGED_ID (LOGIN_PLUGIN_RESPONSE_ID+1)
#define LOGIN_COOKIE_RESPONSE_ID (LOGIN_ACKNOWLEDGED_ID+1)




PACKET(login_start,
       R(var_str, lstr, name);
       R(uuid, uuid, uuid);
       );

