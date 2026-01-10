#ifndef _PACKETS_H_
#define _PACKETS_H_

#include <stdint.h>
#include "rw.h"





#if defined(PACKET_READ_IMPL)

#define PACKET(name, ...)						\
  int read_##name (uint8_t **packet_buffer, unsigned int *pos, unsigned int max, name *out) { \
  int error = 0;							\
  (void)error;								\
  __VA_ARGS__								\
    return 0;								\
  }
// standard field
#define R(type, field_type, field_name)					\
  error = read_##type(packet_buffer, pos, max, &out->field_name);	\
  if(error) return error;
// optional field
#define O(type, field_type, field_name)					\
  uint8_t field_name##_error;						\
  error = read_bool(packet_buffer, pos, max, &field_name##_error);	\
  if(error) return error;						\
  if(field_name##_error) {						\
    out->field_name = malloc(sizeof(field_type));				\
    error = read_##type(packet_buffer, pos, max, out->field_name);	\
    if(error) return error;						\
  } else out->field_name = NULL

// list field
#define RL(type, field_type, field_name, len_field_name)		\
  error = read_var_int(packet_buffer, pos, max, &out->len_field_name);	\
  if (error) return error;						\
  out->field_name = (field_type*) malloc(out->len_field_name * sizeof(field_type)); \
  field_type *field_name##_ptr = out->field_name;			\
  for (int i = 0; i < out->len_field_name; i++) {			\
    error = read_##type(packet_buffer, pos, max, &(field_name##_ptr[i])); \
    if(error) return error;						\
  }									
#elif defined(PACKET_WRITE_IMPL)

#define PACKET(name, ...)						\
  int write_##name (uint8_t **packet_buffer, unsigned int *pos, unsigned int max, name out) { \
    int error = 0;							\
    (void)error;							\
    __VA_ARGS__								\
    return 0;								\
  }
#define R(type, field_type, field_name)					\
  error = write_##type(packet_buffer, pos, max, out.field_name);	\
  if(error) return error;

#define O(type, field_type, field_name)					\
  if(out.field_name != NULL) {						\
    write_bool(packet_buffer, pos, max, 1);				\
    error = write_##type(packet_buffer, pos, max, *out.field_name);	\
    if(error) return error;						\
  }


#define RL(type, field_type, field_name, len_field_name)		\
  error = write_var_int(packet_buffer, pos, max, out.len_field_name);	\
  if (error) return error;						\
  for (int i = 0; i < out.len_field_name; i++) {			\
    error = write_##type(packet_buffer, pos, max, *(out.field_name++)); \
    if(error) return error;						\
  }									


#elif defined(PACKET_FREE_IMPL)

#define PACKET(name, ...)						\
  int free_##name (name out) {						\
    __VA_ARGS__								\
    return 0;								\
  }
#define R(type, field_type, field_name)					\
  free_##type(out.field_name);	\

#define O(type, field_type, field_name)					\
  if(out.field_name != NULL) {						\
  free_##type(*out.field_name);						\
  }


#define RL(type, field_type, field_name, len_field_name)		\
  for (int i = 0; i < out.len_field_name; i++) {			\
    free_##type(out.field_name[i]);				\
  }									\
  if(out.field_name)							\
    free(out.field_name);



#elif defined(PACKET_PRINT_IMPL)

#define PACKET(name, ...)						\
  void print_##name (name out, int indentation) {			\
    puts(#name);							\
    __VA_ARGS__								\
      puts("");								\
  }

#define R(type, field_type, field_name)					\
  for (int j = 0; j < indentation+2; j++) {				\
    printf(" ");							\
  }									\
  printf("%s[%s]: ", #field_name, #type);				\
  print_##type(out.field_name, indentation+2);				\
  puts("");

#define O(type, field_type, field_name)					\
  for (int j = 0; j < indentation+2; j++) {				\
    printf(" ");							\
  }									\
  printf("%s[%s](O): ", #field_name, #type);				\
  if(out.field_name != NULL)						\
    print_##type(*out.field_name, indentation+2);			\
  else									\
    printf("N/A");							\
  puts("");


#define RL(type, field_type, field_name, len_field_name)		\
  for (int i = 0; i < out.len_field_name; i++) {			\
    for (int j = 0; j < indentation+2; j++) {				\
      printf(" ");							\
    }									\
    print_##type(out.field_name[i], indentation+2);			\
  }									\




#else
#define PACKET(name, ...)						\
  typedef struct name##_s {						\
    __VA_ARGS__								\
  } name;								\
  int read_##name (uint8_t **packet_buffer, unsigned int *pos, unsigned int max, name *out); \
  int write_##name (uint8_t **packet_buffer, unsigned int *pos, unsigned int max, name out); \
  int free_##name (name out);						\
  void print_##name (name out, int indentation); 
#define R(type, field_type, field_name)		\
  field_type field_name

#define O(type, field_type, field_name)		\
  field_type *field_name

#define RL(type, field_type, field_name, len_field_name)		\
  field_type *field_name;						\
  int len_field_name;


#endif








// now the packets


#if defined(_PACKETS_H_)
#include "packets/handshake.h"
#include "packets/login_clientbound.h"
#include "packets/login_serverbound.h"
#include "packets/configuration_serverbound.h"
#include "packets/configuration_clientbound.h"
#include "packets/play_serverbound.h"
#include "packets/play_clientbound.h"
#endif

// general structure for "custom" readers writers and printers
#if defined(PACKET_READ_IMPL)

#elif defined(PACKET_WRITE_IMPL)

#elif defined(PACKET_PRINT_IMPL)

#else

#endif



// these should probably not be defined globally, especially R and RL
#undef PACKET
#undef R
#undef O
#undef RL

#if defined(PACKET_IMPL)

#undef PACKET_IMPL
// include defs(and structs)

#undef _PACKETS_H_
// include read impls
#define PACKET_READ_IMPL
#include "packets.h"
#undef PACKET_READ_IMPL



#undef _PACKETS_H_
// include write impls
#define PACKET_WRITE_IMPL
#include "packets.h"
#undef PACKET_WRITE_IMPL

#undef _PACKETS_H_
// include write impls
#define PACKET_FREE_IMPL
#include "packets.h"
#undef PACKET_FREE_IMPL


#undef _PACKETS_H_
// define printers
#define PACKET_PRINT_IMPL
#include "packets.h"
#undef PACKET_PRINT_IMPL
#else

#endif

#endif


