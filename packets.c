#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define print_uuid(uuid) {printf("uuid: %ld, %ld\n", (uuid).low, (uuid).high);}


#define PACKET_IMPL
#define PACKET_READ_IMPL
#include "packets.h"
#undef PACKET_READ_IMPL
#define PACKET_WRITE_IMPL
#include "packets.h"


void print_handshake(handshake shake) {
  puts("handshake:");
  printf("protocol version: %d\n", shake.protocol_version);
  printf("hostname: %.*s\n", shake.server_address.len, shake.server_address.str);
  printf("port: %d\n", shake.port);
  printf("intent: %d\n", shake.intent);
}



void print_login_start(login_start login_s) {
  puts("login start:");
  printf("name: %.*s\n", login_s.name.len, login_s.name.str);
  print_uuid(login_s.uuid);
}
void print_client_information_configuration(client_information_configuration config_s) {
  puts("client_information_configuration:");
  printf("locale: %.*s\n", config_s.locale.len, config_s.locale.str);
  printf("view_distance: %d\n", config_s.view_distance);
  printf("chat_mode: %d\n", config_s.chat_mode);
  printf("chat_colors: %d\n", config_s.chat_colors);
  printf("displayed_skin_parts: %d\n", config_s.displayed_skin_parts);
  printf("main_hand: %d\n", config_s.main_hand);
  printf("enable_text_filtering: %d\n", config_s.enable_text_filtering);
  printf("allow_server_listings: %d\n", config_s.allow_server_listings);
  printf("particle_status: %d\n", config_s.particle_status);
}



/* int read_packet_f(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, void *out, char *format_str) { */
/*   ((generic_packet *)out)->raw_data = *packet_buffer; */
/*   int len = strlen(format_str); */
/*   void *data = out+sizeof(generic_packet); */
/*   int error; */
  
/*   for (int i = 0; i < len; i++) { */
/*     if (format_str[i] == '%') { // single-stuff */
/*       i+=1; */
/*       if(format_str[i] == 'v') { // var-stuff */
/* 	i+=1; */
/* 	if(format_str[i] == 'i') { //var-int */
/* 	  error = read_var_int(packet_buffer, pos, max, data); */
/* 	  data += sizeof(int32_t); */
/* 	} else if(format_str[i] == 'l') { //var-long */
/* 	  error = read_var_long(packet_buffer, pos, max, data); */
/* 	  data += sizeof(int64_t); */
/* 	} else if(format_str[i] == 's') { //var-str */
/* 	  error = read_var_str(packet_buffer, pos, max, data); */
/* 	  data += sizeof(lstr); */
/* 	} else { */
/* 	  printf("unknown var char: %c\n", format_str[i]); */
/* 	  return ERR_BAD_FORMAT_SPECIFIER; */
/* 	} */
/*       } else if (format_str[i] == 'u') { // unsigned stuff */
/* 	i+=1; */
/*         if(format_str[i] == 's') { //ushort */
/* 	  error = read_ushort(packet_buffer, pos, max, data); */
/* 	  data += sizeof(uint16_t); */
/* 	} else { */
/* 	  printf("unknown unsigned char: %c\n", format_str[i]); */
/* 	  return ERR_BAD_FORMAT_SPECIFIER; */
/* 	} */
/*       } */
/*       // if we got an error reading any of those, return and complain */
/*       if(error) return error; */
/*     } else { */
/*       printf("unknown char: %c\n", format_str[i]); */
/*       return ERR_BAD_FORMAT_SPECIFIER; */
/*     } */
/*   } */
/*   return 0; */
/* } */

/* int read_handshake(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, handshake *out) { */
/*   out->raw_data = *packet_buffer; */
/*   int error = read_var_int(packet_buffer, pos, max, &out->protocol_version); */
/*   if (error) return error; */
/*   error = read_var_str(packet_buffer, pos, max, &out->server_address); */
/*   if (error) return error; */
/*   error = read_ushort(packet_buffer, pos, max, &out->port); */
/*   if (error) return error; */
/*   error = read_var_int(packet_buffer, pos, max, &out->intent); */
/*   if (error) return error; */

/*   return 0; */
/* } */
