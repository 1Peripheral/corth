#include "include/kv.h"
#include <stdlib.h>

void kv_init(KV* kv) {
  kv->capacity = 8;
  kv->size = 0;
  kv->store = (KvPair*) malloc(sizeof(KvPair) * kv->capacity);
}

void kv_add_value(KV* kv, const char* key, Value value) {
  if (!kv) return;
  if (kv->size >= kv->capacity) {
    kv->store = realloc(kv->store,
                        kv->capacity * GROW_FACTOR);
    kv->capacity = kv->capacity * GROW_FACTOR;
  }
  strncpy(kv->store[kv->size].key, key, MAX_KEY_LENGTH - 1);
  kv->store[kv->size++].value.as = VALUE_TYPE;
  kv->store[kv->size++].value.var = value;
}

void kv_add_definition(KV* kv, const char* key, const char* def) {
  if (!kv) return;
  if (kv->size >= kv->capacity) {
    kv->store = realloc(kv->store,
                        kv->capacity * GROW_FACTOR);
    kv->capacity = kv->capacity * GROW_FACTOR;
  }
  strncpy(kv->store[kv->size].key, key, MAX_KEY_LENGTH - 1);
  strcpy(kv->store[kv->size].value.expression, def);
  kv->store[kv->size++].value.as = DEFINITION_TYPE;
}

Reference* kv_get(KV* kv, const char* key) {
  if (!kv) return NULL;
  for (int i =  0 ; i < kv->size ; i++) {
    if (!strcmp(kv->store[i].key, key))
      return &kv->store[i].value;
  }
  return NULL;
}

void kv_destroy(KV* kv) {
  free(kv->store);
  kv->size = 0;
  kv->capacity = 0;
}
