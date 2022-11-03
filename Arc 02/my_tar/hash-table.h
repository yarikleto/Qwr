#ifndef HASH_TABLE_NODE_STR
#define HASH_TABLE_NODE_STR
typedef struct hash_table_node {
  char* key;
  void* value;
  struct hash_table_node* next;
} Hash_Table_Node_str;
#endif

#ifndef HASH_TABLE_SET_CODES_E
#define HASH_TABLE_SET_CODES_E
typedef enum {
  HASH_TABLE_SET_SUCCESS,
  HASH_TABLE_SET_ERROR
} Hash_Table_Set_Codes_e;
#endif

#ifndef HASH_TABLE_STR
#define HASH_TABLE_STR
typedef struct {
    Hash_Table_Node_str** nodes;
    unsigned int SIZE;
} Hash_Table_str;
#endif

void Hash_Table__constructor(Hash_Table_str* self, unsigned int size);
void Hash_Table__destructor(Hash_Table_str* self);
void* Hash_Table__get(Hash_Table_str* self, char* key);
Hash_Table_Set_Codes_e Hash_Table__set(Hash_Table_str* self, char* key, void* value);