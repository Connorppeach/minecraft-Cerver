#include "util.h"
#include "../protocol/packets.h"
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

int vi_size(int val) {
  uint8_t header[5];
  uint8_t *header_ptr = header;
  uint32_t header_len = 0;
  write_var_int(&header_ptr, &header_len, 5, val);
  return header_len;
}

static bit_set full_light_mask(int num_sections) {
  bit_set mask;
  mask.data_count = (num_sections + 63) / 64;
  mask.data = calloc(mask.data_count, sizeof(int64_t));
  for (int i = 0; i < num_sections; i++) {
    mask.data[i / 64] |= (int64_t)1 << (i % 64);
  }
  return mask;
}

static light_array *fullbright_light_arrays(int num_sections) {
  light_array *arrays = malloc(num_sections * sizeof(light_array));
  for (int i = 0; i < num_sections; i++) {
    arrays[i].data_len = 2048;
    arrays[i].data = malloc(2048);
    memset(arrays[i].data, 0xFF, 2048);
  }
  return arrays;
}

static void free_light_arrays(light_array *arrays, int num_sections) {
  for (int i = 0; i < num_sections; i++) {
    free(arrays[i].data);
  }
  free(arrays);
}
int sendall(int sockfd, const uint8_t *buf, size_t len) {
    int total = 0;        
    int bytesleft = len;  
    int n;

    while (total < len) {
        n = send(sockfd, buf + total, bytesleft, MSG_NOSIGNAL);
        if (n == -1) {
            // handle errors here, e.g., EAGAIN or EWOULDBLOCK for non-blocking sockets
	  if(n == ECONNRESET) {
	    perror("failed to send");
            break;
	  }
        } else {
	  total += n;
	  bytesleft -= n;
	}
    }

    return (n == -1) ? -1 : 0; 
}

void send_packet(uint8_t *packet_buf, int packet_len, int fd) {
  uint32_t header_len = vi_size(packet_len);
  int offset = 4 - header_len;
  
  uint8_t *write_ptr = packet_buf + offset;
  uint32_t bytes_written = 0;
  //printf("%d\n", header_len);
  write_var_int(&write_ptr, &bytes_written, header_len+1, packet_len);
  
  uint8_t *send_ptr = packet_buf + offset;
  int total_len = header_len + packet_len;
  
  int sent = sendall(fd, send_ptr, total_len);
  if(sent) {
    //puts("failed to send all data, very bad");
    perror("failed to send");
  }
  /* printf("header_len %d, packet_len %d, total_len %d, sent %d\n",  */
  /*        header_len, packet_len, total_len, sent); */
}



int send_chunk_packet(uint8_t *write_buf, uint32_t packet_max_len, int player_fd, cerver_chunk_section *sections, int num_sections, int32_t x, int32_t z) {
  chunk_data_and_update_light packet;
  packet.heightmap_count = 0;
  packet.block_entities_count = 0;
  packet.x = x;
  packet.y = z;

  packet.sky_light_mask = full_light_mask(num_sections);
  packet.block_light_mask = full_light_mask(num_sections);
  packet.empty_sky_light_mask = (bit_set){ .data = NULL, .data_count = 0 };
  packet.empty_block_light_mask = (bit_set){ .data = NULL, .data_count = 0 };
  packet.sky_light_arrays = fullbright_light_arrays(num_sections);
  packet.sky_light_array_count = num_sections;
  packet.block_light_arrays = fullbright_light_arrays(num_sections);
  packet.block_light_array_count = num_sections;


  uint8_t *packet_ptr = write_buf+4;
  uint32_t max = 0;
  uint32_t chunk_data_max_w = num_sections*4096*8;
  uint8_t chunk_data[chunk_data_max_w];
  uint8_t *chunk_data_ptr = chunk_data;
  uint32_t chunk_data_max = 0;
  
  for(int i = 0; i < num_sections; i++) {

    int error = write_cerver_chunk_section(&chunk_data_ptr, &chunk_data_max, chunk_data_max_w, sections[i]);
    if (error) {
      printf("error while writing chunk section: %d\n", error);
      free(packet.sky_light_mask.data);
      free(packet.block_light_mask.data);
      free_light_arrays(packet.sky_light_arrays, num_sections);
      free_light_arrays(packet.block_light_arrays, num_sections);
      return error;
    }    
  }
  packet.data = chunk_data;
  packet.data_len = chunk_data_max;
  write_var_int(&packet_ptr, &max, packet_max_len-4, CHUNK_DATA_AND_UPDATE_LIGHT_ID);
  int error = write_chunk_data_and_update_light(&packet_ptr, &max, packet_max_len-4, packet);
  free(packet.sky_light_mask.data);
  free(packet.block_light_mask.data);
  free_light_arrays(packet.sky_light_arrays, num_sections);
  free_light_arrays(packet.block_light_arrays, num_sections);
  if (error) {
    printf("error: %d\n", error);
    return error;
  }
  send_packet(write_buf, max, player_fd);
}


void send_raw_chunk_packet(uint8_t *write_buf, uint32_t packet_max_len, int player_fd, int32_t *section_datas, int num_sections, int32_t x, int32_t z) {
  chunk_data_and_update_light packet;
  packet.heightmap_count = 0;
  packet.block_entities_count = 0;
  packet.x = x;
  packet.y = z;

  packet.sky_light_mask = full_light_mask(num_sections);
  packet.block_light_mask = full_light_mask(num_sections);
  packet.empty_sky_light_mask = (bit_set){ .data = NULL, .data_count = 0 };
  packet.empty_block_light_mask = (bit_set){ .data = NULL, .data_count = 0 };
  packet.sky_light_arrays = fullbright_light_arrays(num_sections);
  packet.sky_light_array_count = num_sections;
  packet.block_light_arrays = fullbright_light_arrays(num_sections);
  packet.block_light_array_count = num_sections;


  uint8_t *packet_ptr = write_buf+4;
  uint32_t max = 0;
  uint32_t chunk_data_max_w = num_sections*4096*8;
  uint8_t chunk_data[chunk_data_max_w];
  uint8_t *chunk_data_ptr = chunk_data;
  uint32_t chunk_data_max = 0;
  

  cerver_chunk_section section;
  section.block_count = 4096;
  
  /* section.block_states.type = PALETTED_CONTAINER_TYPE_BLOCK; */
  /* section.block_states.min_max_bpe_indirect[0] = 4; */
  /* section.block_states.min_max_bpe_indirect[1] = 8; */
  /* section.block_states.bits_per_entry_direct = 15; */
  /* for(int i = 0; i < 4096; i++) */
  /*   section.block_states.data[i] = MINECRAFT_AIR; */


  /* section.biomes.type = PALETTED_CONTAINER_TYPE_BIOME; */
  /* section.biomes.min_max_bpe_indirect[0] = 1; */
  /* section.biomes.min_max_bpe_indirect[1] = 3; */
  /* section.biomes.bits_per_entry_direct = 7; */
  int32_t biomes[64] = { 0 };
  
  for(int i = 0; i < num_sections; i++) {
    // write chunk data to our array

    paletted_container p_blocks;
    create_paletted_container_from_entries(section_datas+(4096*i), 4, 8, 15, PALETTED_CONTAINER_TYPE_BLOCK, &p_blocks);
    paletted_container p_biomes;
    create_paletted_container_from_entries(biomes, 4, 8, 15, PALETTED_CONTAINER_TYPE_BIOME, &p_biomes);
      
    section.block_states = p_blocks;
    section.biomes = p_biomes;
    
    int error = write_cerver_chunk_section(&chunk_data_ptr, &chunk_data_max, chunk_data_max_w, section);
    if (error) {
      printf("error while writing chunk section: %d\n", error);
      free(packet.sky_light_mask.data);
      free(packet.block_light_mask.data);
      free_light_arrays(packet.sky_light_arrays, num_sections);
      free_light_arrays(packet.block_light_arrays, num_sections);
      return;
    }    
  }
  packet.data = chunk_data;
  packet.data_len = chunk_data_max;
  write_var_int(&packet_ptr, &max, packet_max_len-4, CHUNK_DATA_AND_UPDATE_LIGHT_ID);
  int error = write_chunk_data_and_update_light(&packet_ptr, &max, packet_max_len-4, packet);
  free(packet.sky_light_mask.data);
  free(packet.block_light_mask.data);
  free_light_arrays(packet.sky_light_arrays, num_sections);
  free_light_arrays(packet.block_light_arrays, num_sections);
  if (error) {
    printf("error: %d\n", error);
    return;
  }
  send_packet(write_buf, max, player_fd);
}


void send_set_center_chunk(uint8_t *write_buf, int32_t WRITE_BUF_SIZE, int fd, int32_t x, int32_t y) {
  set_center_chunk packet;
  packet.x = x;
  packet.y = y;
  uint8_t *packet_ptr = write_buf+4;
  uint32_t max = 0;
  
  write_var_int(&packet_ptr, &max, WRITE_BUF_SIZE, SET_CENTER_CHUNK_ID);
  int error = write_set_center_chunk(&packet_ptr, &max, WRITE_BUF_SIZE, packet);
  send_packet(write_buf, max, fd);
  if(error)
    printf("error setting center chunk: %d\n", error);
}

#define PACKET(name, ...)
#define PACKET_ID(name, id) void send_##name##_packet(uint8_t *write_buf, int buffer_len, int fd, name data) { \
  uint8_t *packet_ptr = write_buf+4;					\
  uint32_t max = 0;							\
  write_var_int(&packet_ptr, &max, buffer_len, id);			\
  write_##name(&packet_ptr, &max, buffer_len, data);			\
  send_packet(write_buf, max, fd);					\
									\
  }
#include "../protocol/all_packets.h"
#undef PACKET
#undef PACKET_ID
