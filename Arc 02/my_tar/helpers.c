#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

#include "./helpers.h"

int get_str_length(const char *str) {
  if (str == NULL) return 0;

  int i = 0;
  while (str[i]) i += 1;

  return i;
}

void print_message(int file_descriptor, char* message) {
  write(file_descriptor, message, get_str_length(message));
}

void push_to_str_arr(array_of_str_t* str_arr, char* str) {
  int new_size = str_arr->size + 1;
  char** result = malloc(sizeof(char**) * new_size);
  int i = 0;
  for (; i < str_arr->size; ++i) {
    result[i] = str_arr->items[i];
  }
  result[i] = str;

  free_str_arr(str_arr);
  str_arr->items = result;
  str_arr->size = new_size;
}

void free_str_arr(array_of_str_t* str_arr) {
  str_arr->size = 0;
  if (str_arr->items == NULL) return;
  free(str_arr->items);
  str_arr->items = NULL;
}

bool is_equal_strings(char* str1, char* str2) {
  int i = 0;
  while (true) {
    if (str1[i] == '\0' && str2[i] == '\0') return true;
    if (str1[i] != str2[i]) return false;
    i += 1;
  }
}

char* get_string_copy(char* src) {
  int length = get_str_length(src);

  char* result = malloc(sizeof(char) * (length + 1));
  result[length] = '\0';

  for (int i = 0; i < length; ++i) {
    result[i] = src[i];
  }

  return result;
}