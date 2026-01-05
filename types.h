#ifndef _TYPES_H_
#define _TYPES_H_

#include <stdint.h>
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

#endif
