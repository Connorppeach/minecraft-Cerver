#include "./anvil.h"



int header_index_from_chunk_xz(int x, int z) {
  return (x & 31) + (z & 31) * 32;
}

region *allocate_region() {
  region *r = malloc(sizeof(region));
  for(int i = 0; i < 1024; i++) {
    r->timestamps[i] = 0;
    r->chunk_datas[i] = NULL;
    r->chunk_data_lens[i] = 0;
  }
  return r;
}

void free_region(region *r) {
  for(int i = 0; i < 1024; i++)
    if(r->chunk_datas[i])
      free(r->chunk_datas[i]);
  free(r);
}


#define MAX_REGION_DATA_SIZE 1024*2048
int write_region(FILE *file, region *r) {
  uint8_t region_data[MAX_REGION_DATA_SIZE] = { 0 };// stupid large buffer
  int error;
  uint32_t pos = 1024*4;

  uint8_t *region_data_ptr = region_data+(1024*4); // avoid writing locations for now
  
  for(int i = 0; i < 1024; i++) { // write timestamps
    error = write_int(&region_data_ptr, &pos, MAX_REGION_DATA_SIZE, r->timestamps[i]);
    if(error)
      return error;
  }
  // write data
  int32_t locations[1024];
  int current_location = 2;

  pos = 0;
  region_data_ptr = region_data;
  for(int i = 0; i < 1024; i++) {
    int current_chunk_len = r->chunk_data_lens[i];
    
    int len_rounded_up = (current_chunk_len + 4096 - 1) / 4096;
    locations[i] = len_rounded_up;
    int location_data = (current_location & 0xFFFFFF00) | (len_rounded_up & (~0xFFFFFF00));
    error = write_int(&region_data_ptr, &pos, MAX_REGION_DATA_SIZE, location_data);
    if(error) return error;
    
    current_location += len_rounded_up;
  }
  for(int i = 0; i < 1024; i++) {
    int loc = locations[i]*4096;
    region_data_ptr = region_data+loc;
    pos = loc;
    for(int j = 0; j < r->chunk_data_lens[i]; j++) {
      write_ubyte(&region_data_ptr, &pos, MAX_REGION_DATA_SIZE, r->chunk_datas[i][j]);
    }
  }
  int max = current_location*4096;
  region_data_ptr = region_data;
  printf("max: %d\n", max);

  size_t written_count = fwrite(region_data, 1, max, file);

  if (written_count != max) {
    return -1;
  }
  
  return 0;
}

// TODO -- rest



#define MAX_CHUNK_DATA_SIZE 1024*1024 // also pretty stupidly large
#define SET_TAG_NAME_CSTR(tag, name) nbt_set_tag_name(tag, name, strlen(name));

void add_chunk_to_region(region *r, int x, int z, int32_t *block_ids, int n_sections) {
  int header_index = header_index_from_chunk_xz(x, z);
  uint8_t region_data[MAX_CHUNK_DATA_SIZE] = { 0 };// stupid large buffer
  int pos = 0;
  nbt_tag_t *root_tag = nbt_new_tag_compound();
  {
    nbt_tag_t *data_ver_tag = nbt_new_tag_int(4671); // 1.21.11
    SET_TAG_NAME_CSTR(data_ver_tag, "DataVersion");
    nbt_tag_compound_append(root_tag, data_ver_tag);
  }
  {
    nbt_tag_t *tag = nbt_new_tag_int(x);
    SET_TAG_NAME_CSTR(tag, "xPos");
    nbt_tag_compound_append(root_tag, tag);
  }
  {
    nbt_tag_t *tag = nbt_new_tag_int(z);
    SET_TAG_NAME_CSTR(tag, "zPos");
    nbt_tag_compound_append(root_tag, tag);
  }
  {
    nbt_tag_t *tag = nbt_new_tag_int(0);
    SET_TAG_NAME_CSTR(tag, "yPos");
    nbt_tag_compound_append(root_tag, tag);
  }
  {
    nbt_tag_t *tag = nbt_new_tag_string("minecraft:full", strlen("minecraft:full"));
    SET_TAG_NAME_CSTR(tag, "Status");
    nbt_tag_compound_append(root_tag, tag);
  }
  {
    nbt_tag_t *tag = nbt_new_tag_long(0);
    SET_TAG_NAME_CSTR(tag, "LastUpdate");
    nbt_tag_compound_append(root_tag, tag);
  }
  {
    nbt_tag_t *tag = nbt_new_tag_list(NBT_TYPE_COMPOUND);
    SET_TAG_NAME_CSTR(tag, "sections");
    for(int i = 0; i < n_sections; i++) {
      //nbt_tag_list_append(root_tag, tag);
    }
  }

  // write final data
  
}
