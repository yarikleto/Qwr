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

void print_message(int file_descriptor, string_t message) {
  write(file_descriptor, message, get_str_length(message));
}

bool is_equal_strings(string_t str1, string_t str2) {
  int i = 0;
  while (true) {
    if (str1[i] == '\0' && str2[i] == '\0') return true;
    if (str1[i] != str2[i]) return false;
    i += 1;
  }
}

string_t get_string_copy(string_t src) {
  int length = get_str_length(src);

  char* result = malloc(sizeof(char) * (length + 1));
  result[length] = '\0';

  for (int i = 0; i < length; ++i) {
    result[i] = src[i];
  }

  return result;
}

string_t concat_chars(char a, char b) {
  string_t str = malloc(sizeof(char) * 3);
  str[0] = a;
  str[1] = b;
  str[2] = '\0';

  return str;
}

bool is_char_included(string_t str, char c) {
  for (int i = 0; str[i]; ++i) {
    if (str[i] == c) return true;
  }

  return false;
}