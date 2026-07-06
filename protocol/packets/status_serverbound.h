#define STATUS_REQUEST_ID 0 
#define PING_REQUEST_ID (STATUS_REQUEST_ID+1) 




PACKET(ping_request,
       R(long, long, timestamp);
       );
PACKET_ID(ping_request, PING_REQUEST_ID)

