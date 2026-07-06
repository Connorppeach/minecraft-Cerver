#define STATUS_RESPONSE_ID 0
#define PONG_RESPONSE_ID (STATUS_RESPONSE_ID+1) 




PACKET(status_response,
       R(var_str, lstr, json_response);
       );
PACKET_ID(status_response, STATUS_RESPONSE_ID)

PACKET(pong_response,
       R(long, long, timestamp);
       );
PACKET_ID(pong_response, PONG_RESPONSE_ID)
