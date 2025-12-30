#ifndef _TYPES_H_
#define _TYPES_H_

#include <stdint.h>
typedef struct L_str {
  char *str;
  int len;
} lstr;
#define lstr_static(str) (lstr){str, strlen(str)}

typedef struct Uuid {
  int64_t high;
  int64_t low;
} uuid;
#endif
