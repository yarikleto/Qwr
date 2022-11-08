#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "./helpers.h"
#include "./tar-file.h"

int get_str_length(const string_t str) {
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

bool is_block_empty(char* block, int size) {
  for (int i = 0; i < size; ++i) {
    if (block[i]) return false;
  }

  return true;
}

int my_pow(int n, int power) {
  if (power == 0) return 1;

  int result = n;
  for (int i = 1; i < power; ++i) {
    result *= n;
  }

  return result;
}

int oct_str_to_bytes(string_t str, int size) {
  int n = 0;
  char *c = str;
  while (size > 1) {
    size -= 1;
    n *= 8;
    n += *c - '0';
    c++;
  }

  return n;
}

string_t concat_strings(string_t str1, string_t str2, int str2_length) {
  int str1_length = get_str_length(str1);
  int new_length = str1_length + str2_length;

  string_t new_str = malloc(sizeof(char) * (new_length + 1));
  if (!new_str) return NULL;

  new_str[new_length] = '\0';

  int result_index = 0;
  for (int i = 0; i < str1_length; ++i, ++result_index) new_str[result_index] = str1[i];
  for (int i = 0; i < str2_length; ++i, ++result_index) new_str[result_index] = str2[i];

  return new_str;
}

void memory_copy(void* dest, void* src, int size) {
  for (int i = 0; i < size; ++i) {
    ((char*)dest)[i] = ((char*)src)[i];
  }
}

string_t get_str_slice(string_t str, int from, int to) {
  if (from >= to) return NULL;

  int new_size = to - from;
  string_t new_str = malloc(sizeof(char) * (new_size + 1));
  new_str[new_size] = '\0';

  for (int i = 0; i < new_size; ++i) {
    new_str[i] = str[i + from];
  }

  return new_str;
}