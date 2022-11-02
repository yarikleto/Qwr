#ifndef ARRAY_OF_STR_T
#define ARRAY_OF_STR_T
typedef struct {
  int size;
  char** items;
} array_of_str_t;
#endif

int get_str_length(const char *str);
void print_message(int file_descriptor, char* message);
void free_str_arr(array_of_str_t* str_arr);
void push_to_str_arr(array_of_str_t* str_arr, char* str);