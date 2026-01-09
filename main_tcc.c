#include <errno.h>

#include "protocol/rw.h"
#include "protocol/packets.h"
#include "blocks.h"
#include "simple_server/util.h"
#include "simple_server/player.h"
#include "simple_server/simple_server.h"

#include "include/FastNoiseLite.h"
#include "include/komihash.h"



#define PORT 25545   // port we're listening on
#define WRITE_BUF_SIZE 1310720

// settings
#define MAX_PLAYERS 10
#include <libtcc.h>




uint8_t write_buf[WRITE_BUF_SIZE];





// https://stackoverflow.com/a/70409447
// got lazy -- todo -- rewrite
// Read the file into allocated memory.
// Return NULL on error.
char* readfile(FILE *f) {
  // f invalid? fseek() fail?
  if (f == NULL || fseek(f, 0, SEEK_END)) {
    return NULL;
  }

  long length = ftell(f);
  rewind(f);
  // Did ftell() fail?  Is the length too long?
  if (length == -1 || (unsigned long) length >= SIZE_MAX) {
    return NULL;
  }

  // Convert from long to size_t
  size_t ulength = (size_t) length;
  char *buffer = malloc(ulength + 1);
  // Allocation failed? Read incomplete?
  if (buffer == NULL || fread(buffer, 1, ulength, f) != ulength) {
    free(buffer);
    return NULL;
  }
  buffer[ulength] = '\0'; // Now buffer points to a string

  return buffer;
}
simple_server_callback create_server_callback_from_script(char *filename) {
  simple_server_callback cb = { NULL, NULL, NULL, NULL };
  TCCState *s = tcc_new();
  tcc_set_output_type(s, TCC_OUTPUT_MEMORY);
  tcc_add_include_path(s, ".");
  FILE *f = fopen(filename, "r");
  if(!f) return cb;
  char *data = readfile(f);
  if(!data) return cb;
  int err = tcc_compile_string(s, data);
  if(err == -1) return cb;
  err = tcc_relocate(s);
  if(err == -1) return cb;

  void (*tick_callback)(simple_server *server) = tcc_get_symbol(s, "on_tick");
  if(tick_callback) cb.tick_callback = tick_callback;
  void (*packet_callback)(simple_server *server, int player_num, int packet_type, uint8_t *packet_buf, unsigned int buf_len) = tcc_get_symbol(s, "on_packet");
  if(packet_callback) cb.packet_callback = packet_callback;

  void (*on_move)(simple_server *server, int player_num, mc_location old_location, mc_location new_location) = tcc_get_symbol(s, "on_move");
  if(on_move) cb.on_move = on_move;

  void (*finish_configuration)(simple_server *server, int player_num)  = tcc_get_symbol(s, "on_login");
  if(finish_configuration) cb.finish_configuration = finish_configuration;

  return cb;
}

int main(void)
{
  simple_server *server =  allocate_simple_server(MAX_PLAYERS);
  puts("starting server");
  simple_server_callback cb = create_server_callback_from_script("./server_script.c");
  
  start_server(server, PORT, cb);
}
