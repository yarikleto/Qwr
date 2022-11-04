#include <stdbool.h>

#ifndef STRING_T
#define STRING_T
typedef char* string_t;
#endif

int get_str_length(const char *str);
void print_message(int file_descriptor, string_t message);
bool is_equal_strings(string_t str1, string_t str2);
string_t get_string_copy(string_t src);
string_t concat_chars(char a, char b);
bool is_char_included(string_t str, char c);