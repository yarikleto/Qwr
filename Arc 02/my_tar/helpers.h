#include <stdbool.h>

#define MIN(x, y) (x < y ? x : y)

#ifndef STRING_T
#define STRING_T
typedef char* string_t;
#endif

int get_str_length(const string_t str);
void print_message(int file_descriptor, string_t message);
bool is_equal_strings(string_t str1, string_t str2);
string_t get_string_copy(string_t src);
string_t concat_chars(char a, char b);
bool is_char_included(string_t str, char c);
bool is_block_empty(char* block, int size);
int oct_str_to_bytes(string_t str, int size);
int my_pow(int n, int power);
string_t concat_strings(string_t str1, string_t str2, int str2_length);
void memory_copy(void* dest, void* src, int size);
string_t get_str_slice(string_t str, int from, int to);
char *reverse_string(char *input_string);
char *octal_string(long int n, int string_size);
int get_int_len(int n);
int oct_2_dec(int octal);
int my_recursive_pow(int base, int power);
int my_atoi(char *param_1);