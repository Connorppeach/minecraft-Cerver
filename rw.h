#ifndef _H_RW_CERVER_
#define _H_RW_CERVER_
#include <stdint.h>
#include "error_codes.h"
#include "types.h"
#include "libnbt/nbt.h"

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
int write_nbt(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, nbt_tag_t *val);


void print_bool(uint8_t val);
void print_byte(int8_t val);
void print_ubyte(uint8_t val);
void print_short(int16_t val);
void print_ushort(uint16_t val);
void print_int(int32_t val);
void print_uint(uint32_t val);
void print_long(int64_t val);
void print_float(float val_float);
void print_double(double val_double);
void print_var_int(int32_t value);
void print_var_long(int64_t value);
void print_var_str(lstr value);
void print_uuid(uuid value);
void print_nbt(nbt_tag_t *val);

#endif // _H_RW_CERVER_
