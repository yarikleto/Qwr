#include <stdlib.h>
#include <stdio.h>

#include "./hash-table.h"
#include "./helpers.h"

unsigned int calc_index(const char *s, unsigned int max);
void free_node(Hash_Table_Node_str* node);

void Hash_Table__constructor(Hash_Table_str* this, unsigned int size) {
  this->SIZE = size;
  this->nodes = malloc(sizeof(Hash_Table_Node_str*) * size);
  for (unsigned int i = 0; i < size; ++i) {
    this->nodes[i] = NULL;
  }
}

void Hash_Table__destructor(Hash_Table_str* this) {
  for (unsigned int i = 0; i < this->SIZE; ++i) {
    free_node(this->nodes[i]);
  }

  free(this->nodes);
}

void* Hash_Table__get(Hash_Table_str* this, char* key) {
  unsigned int index = calc_index(key, this->SIZE);

  Hash_Table_Node_str* node = this->nodes[index];
  while (node) {
    if (is_equal_strings(node->key, key)) {
      return node->value;
    }
    node = node->next;
  }
  
  return NULL;
}

Hash_Table_Set_Codes_e Hash_Table__set(Hash_Table_str* this, char* key, void* value) {
  unsigned int index = calc_index(key, this->SIZE);
  Hash_Table_Node_str* node = this->nodes[index];

  if (node == NULL) {
    node = malloc(sizeof(Hash_Table_Node_str));
    if (node == NULL) return HASH_TABLE_SET_ERROR;
    node->key = key;
    this->nodes[index] = node;
  }

  while (node) {
    if (is_equal_strings(node->key, key)) {
      node->value = value;
    }
    node = node->next;
  }

  return HASH_TABLE_SET_SUCCESS;
}

unsigned int calc_index(const char *s, unsigned int max) {
  unsigned int index = 0;
  const unsigned int PRIME_NUMBER = 263;

  while(*s) {
      index = (index * PRIME_NUMBER + *s) % max;
      s++;
  }

  return index;
}

void free_node(Hash_Table_Node_str* node) {
  if (node == NULL) return;

  free_node(node->next);
  free(node);
}
