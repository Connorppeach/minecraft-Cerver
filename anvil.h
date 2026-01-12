#include <stdio.h>
#include "protocol/rw.h"
#include "protocol/packets.h"

typedef struct {
  uint32_t timestamps[1024];
  uint8_t *chunk_datas[1024];
  int32_t chunk_data_lens[1024];
} region;

region *allocate_region();

void free_region(region *r);

void add_chunk_to_region(region *r, int x, int z, int32_t *block_ids, int n_sections);

int write_region(FILE *file, region *r);
