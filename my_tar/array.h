#ifndef ARRAY_T
#define ARRAY_T
typedef struct {
  int size;
  char** items;
} Array;
#endif

Array* create_array();
void Array__push(Array* self, char* value);
void Array__free(Array* self);
void Array__clear(Array* self);