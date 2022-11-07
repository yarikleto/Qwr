#include "./array.h"

#ifndef HASH_TABLE_NODE
#define HASH_TABLE_NODE
typedef struct hash_table_node {
  char* key;
  void* value;
  struct hash_table_node* next;
} Hash_table_node;
#endif

#ifndef HASH_TABLE_SET_CODES_E
#define HASH_TABLE_SET_CODES_E
typedef enum {
  HASH_TABLE_SET_SUCCESS,
  HASH_TABLE_SET_ERROR
} hash_table_set_codes_e;
#endif

#ifndef HASH_TABLE
#define HASH_TABLE
typedef struct {
    Hash_table_node** nodes;
    unsigned int SIZE;
} Hash_table;
#endif

Hash_table* create_hash_table(unsigned int size);
void Hash_table__free(Hash_table* self);
void* Hash_table__get(Hash_table* self, char* key);
hash_table_set_codes_e Hash_table__set(Hash_table* self, char* key, void* value);
void Hash_table__print_keys(Hash_table* this);
Array* Hash_table__keys(Hash_table* this);