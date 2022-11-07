#include <stdlib.h>
#include <unistd.h>

#include "./hash-table.h"
#include "./helpers.h"
#include "./array.h"

unsigned int calc_index(const char *s, unsigned int max);
void free_node(Hash_table_node* node);

Hash_table* create_hash_table(unsigned int size) {
  Hash_table* hash_table = malloc(sizeof(Hash_table));
  hash_table->SIZE = size;
  hash_table->nodes = malloc(sizeof(Hash_table_node*) * size);
  for (unsigned int i = 0; i < size; ++i) {
    hash_table->nodes[i] = NULL;
  }

  return hash_table;
}

void Hash_table__free(Hash_table* this) {
  for (unsigned int i = 0; i < this->SIZE; ++i) {
    free_node(this->nodes[i]);
  }

  free(this->nodes);
  free(this);
}

void* Hash_table__get(Hash_table* this, char* key) {
  unsigned int index = calc_index(key, this->SIZE);

  Hash_table_node* node = this->nodes[index];
  while (node) {
    if (is_equal_strings(node->key, key)) {
      return node->value;
    }
    node = node->next;
  }
  
  return NULL;
}

void Hash_table__print_keys(Hash_table* this) {
  for (unsigned int i = 0; i < this->SIZE; ++i) {
    Hash_table_node* node = this->nodes[i];
    while (node) {
      print_message(STDOUT_FILENO, "Key: ");
      print_message(STDOUT_FILENO, node->key);
      print_message(STDOUT_FILENO, "\n");
      node = node->next;
    }
  }
}

Array* Hash_table__keys(Hash_table* this) {
  Array* keys = create_array();

  for (unsigned int i = 0; i < this->SIZE; ++i) {
    Hash_table_node* node = this->nodes[i];
    while (node) {
      Array__push(keys, node->key);
      node = node->next;
    }
  }

  return keys;
}

hash_table_set_codes_e Hash_table__set(Hash_table* this, char* key, void* value) {
  unsigned int index = calc_index(key, this->SIZE);
  Hash_table_node* node = this->nodes[index];

  if (node == NULL) {
    node = malloc(sizeof(Hash_table_node));
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

void free_node(Hash_table_node* node) {
  if (node == NULL) return;

  free_node(node->next);
  free(node);
}
