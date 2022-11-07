#ifndef ARRAY_T
#define ARRAY_T
typedef struct {
  int size;
  void** items;
} Array;
#endif

Array* create_array();
void Array__push(Array* self, void* value);
void Array__free(Array* self);
void Array__clear(Array* self);