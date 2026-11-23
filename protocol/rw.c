#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "rw.h"

#define NBT_IMPLEMENTATION
#include "../libnbt/nbt.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))




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
  nbt_write(writer, val, NBT_WRITE_FLAG_USE_RAW, 0);
  return 0;
}
int write_nbt(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, nbt_tag_t *val) {
  return _write_nbt(packet_buffer, pos, max, val, 1);
}

int write_network_nbt(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, nbt_tag_t *val) {
  return _write_nbt(packet_buffer, pos, max, val, 0);
}



#define pack(x) (long)round((((double)x) * 0.5 + 0.5) * 32766.0)
int write_lpvec3(uint8_t **packet_buffer, unsigned int *pos, unsigned int max, lpvec3 to_write) {
  double x = to_write.x;
  double y = to_write.y;
  double z = to_write.z;
  double chessboardLength = MAX(fabs(x), MAX(fabs(y), fabs(z)));

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

void print_nbt(nbt_tag_t *val, int indentation) {
  puts("");
  print_nbt_tree(val, indentation);
}
void print_network_nbt(nbt_tag_t *val, int indentation) {
  puts("");
  print_nbt_tree(val, indentation);
}


void print_lpvec3(lpvec3 val, int indentation) {
  printf("[%lf, %lf, %lf]", val.x, val.y, val.z);
}

void print_position(position val, int indentation) {
  printf("[%d, %d, %d]", val.x, val.y, val.z);
  
}


