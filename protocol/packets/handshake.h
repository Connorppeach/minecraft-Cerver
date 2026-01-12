#define HANDSHAKE_ID 0
PACKET(handshake,
       R(var_int, int32_t, protocol_version);
       R(var_str, lstr, server_address);
       R(ushort, uint16_t, port);
       R(var_int, int32_t, intent);
       );
PACKET_ID(handshake, HANDSHAKE_ID)
