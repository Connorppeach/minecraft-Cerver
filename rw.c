#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "rw.h"

#define NBT_IMPLEMENTATION
#include "libnbt/nbt.h"



#define SEGMENT_BITS 0x7F
#define CONTINUE_BIT 0x80

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))


int read_bool(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, uint8_t *out) {
  if (*pos+1 > max)
    return ERR_TOO_FEW_BYTES;
  (*pos)++;
  uint8_t m_out = *((*packet_buffer)++);
  if (m_out > 1)
    return ERR_INVALID_RANGE;
  *out = m_out;
  
  return 0;
}




int read_byte(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, int8_t *out) {
  if (*pos+1 >= max)
    return ERR_TOO_FEW_BYTES;

  (*pos)++;
  *out = *((*packet_buffer)++);
  
  return 0;
}

struct buffer_data {
  uint8_t **packet_buffer;
  unsigned int *pos;
  unsigned int max;
};
size_t read_nbt_inner(void* userdata, uint8_t* data, size_t size) {
  struct buffer_data *s_data = userdata;
  for(int i = 0; i < size; i++) {
    int error = read_ubyte(s_data->packet_buffer, s_data->pos, s_data->max, &data[i]);;
    if(error)
      return i;
  }
  return size;
}

int read_nbt(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, nbt_tag_t **out) {
  nbt_reader_t reader;
  struct buffer_data data;
  data.packet_buffer = packet_buffer;
  data.pos = pos;
  data.max = max;

  reader.read = read_nbt_inner;
  reader.userdata = &data;
  *out = nbt_parse(reader, 0);
  return 0;
}
// todo -- make sure this works
int read_network_nbt(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, nbt_tag_t **out) {
  return read_nbt(packet_buffer, pos, max, out);
}


int read_ubyte(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, uint8_t *out) {
  if (*pos+1 > max)
    return ERR_TOO_FEW_BYTES;

  (*pos)++;
  *out = *((*packet_buffer)++);
  
  return 0;
}

int read_short(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, int16_t *out) {
  if (*pos+2 > max)
    return ERR_TOO_FEW_BYTES;

  (*pos)+=2;
  *out = *((*packet_buffer)++)<<8;
  *out |= *((*packet_buffer)++);
  
  return 0;
}
int read_ushort(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, uint16_t *out) {
  if (*pos+2 > max)
    return ERR_TOO_FEW_BYTES;

  (*pos)+=2;
  *out = *((*packet_buffer)++)<<8;
  *out |= *((*packet_buffer)++);
  
  return 0;
}

int read_int(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, int32_t *out) {
  if (*pos+4 > max)
    return ERR_TOO_FEW_BYTES;

  (*pos)+=4;
  *out = *((*packet_buffer)++)<<24;
  *out |= *((*packet_buffer)++)<<16;
  *out |= *((*packet_buffer)++)<<8;
  *out |= *((*packet_buffer)++);
  
  return 0;
}
int read_uint(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, uint32_t *out) {
  if (*pos+4 > max)
    return ERR_TOO_FEW_BYTES;

  (*pos)+=4;
  *out = *((*packet_buffer)++)<<24;
  *out |= *((*packet_buffer)++)<<16;
  *out |= *((*packet_buffer)++)<<8;
  *out |= *((*packet_buffer)++);
  
  return 0;
}
int read_long(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, int64_t *out) {
  if (*pos+8 > max)
    return ERR_TOO_FEW_BYTES;

  (*pos)+=8;
  *out = ((uint64_t)*((*packet_buffer)++))<<56;
  *out |= ((uint64_t)*((*packet_buffer)++))<<48;
  *out |= ((uint64_t)*((*packet_buffer)++))<<40;
  *out |= ((uint64_t)*((*packet_buffer)++))<<32;
  *out |= ((uint64_t)*((*packet_buffer)++))<<24;
  *out |= ((uint64_t)*((*packet_buffer)++))<<16;
  *out |= ((uint64_t)*((*packet_buffer)++))<<8;
  *out |= ((uint64_t)*((*packet_buffer)++));
  
  return 0;
}
int read_float(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, float *out) {
  if (*pos+4 > max)
    return ERR_TOO_FEW_BYTES;
  uint32_t out_l;
  (*pos)+=4;
  out_l = *((*packet_buffer)++)<<24;
  out_l |= *((*packet_buffer)++)<<16;
  out_l |= *((*packet_buffer)++)<<8;
  out_l |= *((*packet_buffer)++);
  memcpy(out, &out_l, sizeof(out_l));
  return 0;
}

int read_double(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, double *out) {
  if (*pos+8 > max)
    return ERR_TOO_FEW_BYTES;

  uint64_t out_l;
  (*pos)+=8;
  out_l = ((uint64_t)*((*packet_buffer)++))<<56;
  out_l |= ((uint64_t)*((*packet_buffer)++))<<48;
  out_l |= ((uint64_t)*((*packet_buffer)++))<<40;
  out_l |= ((uint64_t)*((*packet_buffer)++))<<32;
  out_l |= ((uint64_t)*((*packet_buffer)++))<<24;
  out_l |= ((uint64_t)*((*packet_buffer)++))<<16;
  out_l |= ((uint64_t)*((*packet_buffer)++))<<8;
  out_l |= ((uint64_t)*((*packet_buffer)++));
  memcpy(out, &out_l, sizeof(out_l));
  return 0;
}

int read_var_int(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, int32_t *out) {
  if (*pos+1 > max)
    return ERR_TOO_FEW_BYTES;

  int32_t value = 0;
  int32_t position = 0;
  uint8_t currentByte;
  
  while (1) {
    int read_err = read_ubyte(packet_buffer, pos, max, &currentByte);
    if (read_err)
      return read_err;
    value |= (currentByte & SEGMENT_BITS) << position;
    
    if ((currentByte & CONTINUE_BIT) == 0) break;
    
    position += 7;
    
    if (position >= 32) return ERR_VAR_NUM_TOO_LARGE;
  }
  *out = value;
  return 0;
}

int read_var_long(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, int64_t *out) {
  if (*pos+1 > max)
    return ERR_TOO_FEW_BYTES;

  int64_t value = 0;
  int32_t position = 0;
  uint8_t currentByte;
  
  while (1) {
    int read_err = read_ubyte(packet_buffer, pos, max, &currentByte);
    if (read_err)
      return read_err;
    value |= (currentByte & (int64_t)SEGMENT_BITS) << position;
    
    if ((currentByte & CONTINUE_BIT) == 0) break;
    
    position += 7;
    
    if (position >= 64) return ERR_VAR_NUM_TOO_LARGE;
  }
  *out = value;
  return 0;
}

int read_var_str(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, lstr *out) {
  int len;
  int error = read_var_int(packet_buffer, pos, max, &len);
  if(error) return error;
  out->len = len;
  out->str = (char *)*packet_buffer;
  *packet_buffer += len;
  return 0;
}
int read_uuid(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, uuid *out) {
  int error = read_long(packet_buffer, pos, max, &out->high);
  if(error) return error;
  error = read_long(packet_buffer, pos, max, &out->low);
  return error;
}

#define unpack(x) (MIN((long)x & (long)32767, 32766.0) * 2.0 / 32766.0 - 1.0)
int read_lpvec3(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, lpvec3 *out) {
  uint8_t lowest;
  int error;
  error = read_ubyte(packet_buffer, pos, max, &lowest);
  if(error) return error;
  if (lowest == 0) {
    out->x = 0;
    out->y = 0;
    out->z = 0;
    return 0;
  } else {
    uint8_t middle;
    error = read_ubyte(packet_buffer, pos, max, &middle);
    if(error) return error;
    uint32_t highest;
    error = read_uint(packet_buffer, pos, max, &highest);
    if(error) return error;
    long buffer = highest << 16 | middle << 8 | lowest;
    long scale = lowest & 3;
    if ((lowest & 4) == 4) {
      int32_t input;
      error = read_var_int(packet_buffer, pos, max, &input);
      if(error) return error;
      scale |= (input & 4294967295L) << 2;
    }
    out->x = unpack(buffer >> 3) * scale;
    out->y = unpack(buffer >> 18) * scale;
    out->z = unpack(buffer >> 33) * scale;
    return 0;
  }
}

int read_position(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, position *out) {
  int64_t value;
  int error = read_long(packet_buffer, pos, max, &value);
  if(error) return error;
  out->x = value >> 38;
  out->y = value << 52 >> 52;
  out->z = value << 26 >> 38;

  
  return 0;
};

// writers should go here
int write_bool(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, uint8_t val) {
  if (*pos+1 > max)
    return ERR_TOO_FEW_BYTES;
  if (val > 1)
    return ERR_INVALID_RANGE;

  (*pos)++;

  *((*packet_buffer)++) = val;

  
  return 0;
}

int write_byte(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, int8_t val) {
  if (*pos+1 >= max)
    return ERR_TOO_FEW_BYTES;

  (*pos)++;
  *((*packet_buffer)++) = val;
  
  return 0;
}

int write_ubyte(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, uint8_t val) {
  if (*pos+1 > max)
    return ERR_TOO_FEW_BYTES;

  (*pos)++;
  *((*packet_buffer)++) = val;
  
  return 0;
}

size_t write_nbt_inner(void* userdata, uint8_t* data, size_t size) {
  struct buffer_data *s_data = userdata;
  for(int i = 0; i < size; i++) {
    int error = write_ubyte(s_data->packet_buffer, s_data->pos, s_data->max, data[i]);;
    if(error)
      return i;
  }
  return size;
}

int _write_nbt(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, nbt_tag_t *val, uint8_t write_name) {
  nbt_writer_t writer;
  struct buffer_data data;
  data.packet_buffer = packet_buffer;
  data.pos = pos;
  data.max = max;

  writer.write = write_nbt_inner;
  writer.userdata = &data;
  nbt_write(writer, val, NBT_WRITE_FLAG_USE_RAW, false);
  return 0;
}
int write_nbt(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, nbt_tag_t *val) {
  return _write_nbt(packet_buffer, pos, max, val, true);
}

int write_network_nbt(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, nbt_tag_t *val) {
  return _write_nbt(packet_buffer, pos, max, val, false);
}


int write_short(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, int16_t val) {
  if (*pos+2 > max)
    return ERR_TOO_FEW_BYTES;

  (*pos)+=2;
  *((*packet_buffer)++) = (val>>8)&255;
  *((*packet_buffer)++) = (val)&255;
  
  return 0;
}

int write_ushort(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, uint16_t val) {
  if (*pos+2 > max)
    return ERR_TOO_FEW_BYTES;

  (*pos)+=2;
  *((*packet_buffer)++) = (val>>8)&255;
  *((*packet_buffer)++) = (val)&255;
  
  return 0;
}


int write_int(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, int32_t val) {
  if (*pos+4 > max)
    return ERR_TOO_FEW_BYTES;

  (*pos)+=4;
  *((*packet_buffer)++) = (val>>24)&255;
  *((*packet_buffer)++) = (val>>16)&255;
  *((*packet_buffer)++) = (val>>8)&255;
  *((*packet_buffer)++) = (val)&255;
  
  return 0;
}

int write_uint(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, uint32_t val) {
  if (*pos+4 > max)
    return ERR_TOO_FEW_BYTES;

  (*pos)+=4;
  *((*packet_buffer)++) = (val>>24)&255;
  *((*packet_buffer)++) = (val>>16)&255;
  *((*packet_buffer)++) = (val>>8)&255;
  *((*packet_buffer)++) = (val)&255;
  
  return 0;
}

int write_long(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, int64_t val) {
  if (*pos+8 > max)
    return ERR_TOO_FEW_BYTES;

  (*pos)+=8;
  *((*packet_buffer)++) = (val>>56)&255;
  *((*packet_buffer)++) = (val>>48)&255;
  *((*packet_buffer)++) = (val>>40)&255;
  *((*packet_buffer)++) = (val>>32)&255;
  *((*packet_buffer)++) = (val>>24)&255;
  *((*packet_buffer)++) = (val>>16)&255;
  *((*packet_buffer)++) = (val>>8)&255;
  *((*packet_buffer)++) = (val)&255;
  
  return 0;
}


int write_float(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, float val_float) {
  if (*pos+4 > max)
    return ERR_TOO_FEW_BYTES;
  uint32_t val = 0;
  memcpy(&val, &val_float, sizeof(val_float));
  (*pos)+=4;
  *((*packet_buffer)++) = (val>>24)&255;
  *((*packet_buffer)++) = (val>>16)&255;
  *((*packet_buffer)++) = (val>>8)&255;
  *((*packet_buffer)++) = (val)&255;
  
  
  return 0;
}

int write_double(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, double val_double) {
  if (*pos+8 > max)
    return ERR_TOO_FEW_BYTES;
  uint64_t val = 0;
  memcpy(&val, &val_double, sizeof(val_double));

  (*pos)+=8;
  *((*packet_buffer)++) = (val>>56)&255;
  *((*packet_buffer)++) = (val>>48)&255;
  *((*packet_buffer)++) = (val>>40)&255;
  *((*packet_buffer)++) = (val>>32)&255;
  *((*packet_buffer)++) = (val>>24)&255;
  *((*packet_buffer)++) = (val>>16)&255;
  *((*packet_buffer)++) = (val>>8)&255;
  *((*packet_buffer)++) = (val)&255;
  
  return 0;
}

int write_var_int(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, int32_t value) {
  uint32_t x = value;
  if (*pos+1 > max)
    return ERR_TOO_FEW_BYTES;
  int error;
  while (1) {
    
    if ((x & ~SEGMENT_BITS) == 0) {
      error = write_ubyte(packet_buffer, pos, max, x);
      return error;
    }
    
    error = write_ubyte(packet_buffer, pos, max, (x & SEGMENT_BITS) | CONTINUE_BIT);
    if(error) return error;
    x >>= 7;
  };
  
}
int write_var_long(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, int64_t value) {
  uint64_t x = value;
  if (*pos+1 > max)
    return ERR_TOO_FEW_BYTES;
  int error;
  while (1) {
    if ((x & ~((int64_t)SEGMENT_BITS)) == 0) {
      error = write_byte(packet_buffer, pos, max, x);
      return error;
    }
    
    error = write_byte(packet_buffer, pos, max, (x & SEGMENT_BITS) | CONTINUE_BIT);
    if(error) return error;
    x >>= 7;
  };
}

int write_var_str(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, lstr value) {
  if (*pos+( value.len+1) > max)
    return ERR_TOO_FEW_BYTES;
  int error;
  error = write_var_int(packet_buffer, pos, max, value.len);
  if (error)
    return error;
  if (*pos+(value.len) > max)
    return ERR_TOO_FEW_BYTES;
  for (int i = 0; i < value.len; i++)
    *((*packet_buffer)++) = value.str[i];
  *pos += value.len;
  return 0;
}

int write_uuid(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, uuid val) {
  int error = write_long(packet_buffer, pos, max, val.high);
  if(error) return error;
  error = write_long(packet_buffer, pos, max, val.low);
  return error;
}
#define pack(x) (long)round((x * 0.5 + 0.5) * 32766.0)
int write_lpvec3(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, lpvec3 to_write) {
  double x = to_write.x;
  double y = to_write.y;
  double z = to_write.z;
  double chessboardLength = MAX(abs(x), MAX(abs(y), abs(z)));
  if (chessboardLength < 3.051944088384301E-5) {
    return write_byte(packet_buffer, pos, max, 0);
  } else {
    long scale = ceil(chessboardLength);
    uint8_t isPartial = (scale & 3L) != scale;
    long markers = isPartial ? (scale & 3L) | 4L : scale;
    long xn = pack(x / scale) << 3;
    long yn = pack(y / scale) << 18;
    long zn = pack(z / scale) << 33;
    long buffer = markers | xn | yn | zn;
    int error = write_byte(packet_buffer, pos, max, (int8_t)buffer);
    if(error) return error;
    error = write_byte(packet_buffer, pos, max, (int8_t)(buffer >> 8));
    if(error) return error;
    error = write_int(packet_buffer, pos, max,(int)(buffer >> 16));
    if(error) return error;
    if (isPartial) {
      error = write_var_int(packet_buffer, pos, max, (int)(scale >> 2));
      if(error) return error;
    }
    return 0;
  }
}
int write_position(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, position value) {
  int64_t val = (((int64_t)value.x & 0x3FFFFFF) << 38) | (((int64_t)value.z & 0x3FFFFFF) << 12) | ((int64_t)value.y & 0xFFF);
  return write_long(packet_buffer, pos, max, val);
};

void print_bool(uint8_t val) {
  if(val)
    printf("true");
  else
    printf("false");
};


void print_byte(int8_t val) {
  printf("%d", val);
};
void print_nbt_tree(nbt_tag_t* tag, int indentation) {
  for (int i = 0; i < indentation; i++) {
    printf(" ");
  }

  if (tag->name) {
    printf("%s: ", tag->name);
  }

  switch (tag->type) {
    case NBT_TYPE_END: {
      printf("[end]");
      break;
    }
    case NBT_TYPE_BYTE: {
      printf("%hhd", tag->tag_byte.value);
      break;
    }
    case NBT_TYPE_SHORT: {
      printf("%hd", tag->tag_short.value);
      break;
    }
    case NBT_TYPE_INT: {
      printf("%d", tag->tag_int.value);
      break;
    }
    case NBT_TYPE_LONG: {
      printf("%ld", tag->tag_long.value);
      break;
    }
    case NBT_TYPE_FLOAT: {
      printf("%f", tag->tag_float.value);
      break;
    }
    case NBT_TYPE_DOUBLE: {
      printf("%f", tag->tag_double.value);
      break;
    }
    case NBT_TYPE_BYTE_ARRAY: {
      printf("[byte array]");
      break;
      for (size_t i = 0; i < tag->tag_byte_array.size; i++) {
        printf("%hhd ", tag->tag_byte_array.value[i]);
      }
      break;
    }
    case NBT_TYPE_STRING: {
      printf("%s", tag->tag_string.value);
      break;
    }
    case NBT_TYPE_LIST: {
      printf("\n");
      for (size_t i = 0; i < tag->tag_list.size; i++) {
        print_nbt_tree(tag->tag_list.value[i], indentation + tag->name_size + 2);
      }
      break;
    }
    case NBT_TYPE_COMPOUND: {
      printf("\n");
      for (size_t i = 0; i < tag->tag_compound.size; i++) {
        print_nbt_tree(tag->tag_compound.value[i], indentation + tag->name_size + 2);
      }
      break;
    }
    case NBT_TYPE_INT_ARRAY: {
      printf("[int array]");
      break;
      for (size_t i = 0; i < tag->tag_int_array.size; i++) {
        printf("%d ", tag->tag_int_array.value[i]);
      }
      break;
    }
    case NBT_TYPE_LONG_ARRAY: {
      printf("[long array]");
      break;
      for (size_t i = 0; i < tag->tag_long_array.size; i++) {
        printf("%ld ", tag->tag_long_array.value[i]);
      }
      break;
    }
    default: {
      printf("[error]");
    }
  }

  printf("\n");
}

void print_nbt(nbt_tag_t *val) {
  print_nbt_tree(val, 0);
}
void print_network_nbt(nbt_tag_t *val) {
  print_nbt_tree(val, 0);
}

void print_ubyte(uint8_t val) {
  printf("%hhu", val);
};
void print_short(int16_t val) {
  printf("%hd", val);
};
void print_ushort(uint16_t val) {
  printf("%hu", val);
};
void print_int(int32_t val) {
  printf("%d", val);
};
void print_uint(uint32_t val) {
  printf("%d", val);
};
void print_long(int64_t val) {
  printf("%ld", val);
};
void print_float(float val_float) {
  printf("%g", val_float);
};
void print_double(double val_double) {
  printf("%g", val_double);
};
void print_var_int(int32_t value) {
  print_int(value);
};
void print_var_long(int64_t value) {
  print_long(value);
};
void print_var_str(lstr value) {
  printf("%.*s", value.len, value.str);
};
void print_uuid(uuid value) {
  print_long(value.high);
  printf(" ");
  print_long(value.low);
};

void print_lpvec3(lpvec3 val) {
  printf("[%lf, %lf, %lf]", val.x, val.y, val.z);
}

void print_position(position val) {
  printf("[%d, %d, %d]", val.x, val.y, val.z);
}
