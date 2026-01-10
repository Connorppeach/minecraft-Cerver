#ifndef _H_RW_CERVER_
#define _H_RW_CERVER_
#include <stdint.h>
#include "error_codes.h"
typedef struct {
  char *str;
  int len;
} lstr;
#define lstr_static(str) (lstr){str, strlen(str)}

typedef struct {
  int64_t high;
  int64_t low;
} uuid;

typedef struct {
  double x, y, z;
  float pitch, yaw;
} mc_location;

typedef struct {
  double x, y, z;
} lpvec3;

typedef struct {
  int32_t x, y, z;
} position;

#include "../libnbt/nbt.h"

int read_bool(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, uint8_t *out);
int read_byte(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, int8_t *out);
int read_ubyte(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, uint8_t *out);
int read_short(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, int16_t *out);
int read_ushort(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, uint16_t *out);
int read_int(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, int32_t *out);
int read_uint(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, uint32_t *out);
int read_long(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, int64_t *out);
int read_float(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, float *out);
int read_double(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, double *out);
int read_var_int(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, int32_t *out);
int read_var_long(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, int64_t *out);
int read_var_str(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, lstr *out);
int read_uuid(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, uuid *out);
int read_nbt(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, nbt_tag_t **out);
int read_network_nbt(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, nbt_tag_t **out);
int read_lpvec3(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, lpvec3 *out);
int read_position(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, position *out);


int write_bool(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, uint8_t val);
int write_byte(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, int8_t val);
int write_ubyte(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, uint8_t val);
int write_short(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, int16_t val);
int write_ushort(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, uint16_t val);
int write_int(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, int32_t val);
int write_uint(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, uint32_t val);
int write_long(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, int64_t val);
int write_float(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, float val_float);
int write_double(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, double val_double);
int write_var_int(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, int32_t value);
int write_var_long(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, int64_t value);
int write_var_str(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, lstr value);
int write_uuid(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, uuid value);
int write_network_nbt(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, nbt_tag_t *val);
int write_lpvec3(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, lpvec3 value);
int write_position(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, position value);


void print_bool(uint8_t val, int indentation);
void print_byte(int8_t val, int indentation);
void print_ubyte(uint8_t val, int indentation);
void print_short(int16_t val, int indentation);
void print_ushort(uint16_t val, int indentation);
void print_int(int32_t val, int indentation);
void print_uint(uint32_t val, int indentation);
void print_long(int64_t val, int indentation);
void print_float(float val_float, int indentation);
void print_double(double val_double, int indentation);
void print_var_int(int32_t value, int indentation);
void print_var_long(int64_t value, int indentation);
void print_var_str(lstr value, int indentation);
void print_uuid(uuid value, int indentation);
void print_network_nbt(nbt_tag_t *val, int indentation);
void print_lpvec3(lpvec3 value, int indentation);
void print_position(position value, int indentation);


// dummy freers
#define free_var_int(x) 0
#define free_bool(x) 0
#define free_uuid(x) 0
#define free_var_str(x) 0
#define free_short(x) 0
#define free_ushort(x) 0
#define free_network_nbt(x) nbt_free_tag(x)
#define free_long(x) 0
#define free_byte(x) 0
#define free_ubyte(x) 0
#define free_int(x) 0
#define free_float(x) 0
#define free_double(x) 0
#define free_lpvec3(x) 0

#endif // _H_RW_CERVER_
