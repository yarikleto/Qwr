#include <stdio.h>
#include <stdlib.h>

#include "./array.h"

Array* create_array() {
  Array* array = malloc(sizeof(Array));
  array->size = 0;
  array->items = NULL;

  return array;
}

void Array__push(Array* this, void* value) {  
  int new_size = this->size + 1;
  char** result = malloc(sizeof(char*) * new_size);
  int i = 0;
  for (; i < this->size; ++i) {
    result[i] = this->items[i];
  }
  result[i] = value;

  if (this->items) free(this->items);
  this->items = result;
  this->size = new_size;
}

void Array__clear(Array* this) {
  this->size = 0;
  if (this->items) {
    free(this->items);
  }
  this->items = NULL;
}

void Array__free(Array* this) {
  Array__clear(this);
  free(this);
}