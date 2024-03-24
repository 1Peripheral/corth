#ifndef KV_H_
#define KV_H_

#include "common.h"
#include "value.h"

#define MAX_KEY_LENGTH 32
#define GROW_FACTOR 2 

#define GROW_ARRAY()

typedef struct {
  char key[MAX_KEY_LENGTH];
  Reference value;
} KvPair;

typedef struct {
  KvPair* store;
  int size; 
  int capacity;
} KV;

void kv_init(KV* kv);
void kv_add_value(KV* kv, const char* key, Value value);
void kv_add_definition(KV* kv, const char* key, const char* def);
Reference* kv_get(KV* kv, const char* key);
void kv_destroy(KV* kv);


#endif //KV_H_
