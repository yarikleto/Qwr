#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

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
  int str_length = get_str_length(str);

  if (from < 0) from = 0;
  if (to > str_length) to = str_length;

  int new_size;
  if (from > to) {
    new_size = 0;
  } else {
    new_size = to - from;
  }

  string_t new_str = malloc(sizeof(char) * (new_size + 1));
  new_str[new_size] = '\0';

  for (int i = 0; i < new_size; ++i) {
    new_str[i] = str[i + from];
  }

  return new_str;
}

char *reverse_string(char *input_string) {
  char *head = input_string;
  char *end = input_string + strlen(input_string) - 1;
  char temp;

  while(head < end) {
    temp = *head;
    *head = *end;
    *end = temp;

    head++;
    end--;
  }
  return input_string;
}

char *octal_string(long int n, int string_size) {
  int i = 0;
  int remainder;
  int num_zeros;
  char *octal_string = malloc(string_size * sizeof(char));
  char *octal = malloc(20 * sizeof(char));
  //Add each octal digit to the octal String. NOTE: the string will be backwards and needs to be reversed.
  while(n != 0) {
    remainder = n % 8;
    octal[i] = remainder + '0';
    n = n / 8; 
    i++;
  }
  octal[i] = '\0';
  reverse_string(octal);
  num_zeros = (string_size - 1) - strlen(octal);

  for(int i = 0; i < num_zeros; i++) {
    octal_string[i] = '0';
  }
  octal_string[num_zeros] = '\0';
  strcat(octal_string, octal);
  free(octal);
  return octal_string;
}

int get_int_len(int n) {
  int int_len = 1;

  if(n < 0) {
    n = -n;
  }
  while(n > 9) {
    int_len++;
    n = n / 10;
  }
  return int_len;
}

int oct_2_dec(int octal) {
  int n_len = get_int_len(octal);
  int dec = 0;

  for(int i = 0; i < n_len; i++) {
    dec += (octal % 10) * my_pow(8, i);
    octal = octal / 10;
  }
  return dec;
}

int my_recursive_pow(int base, int power) {
    int ans;
    if(power == 0) {
        return 1;
    }

    if(power == 1) {
        ans = base;
    }
    else {
        ans = base * my_recursive_pow(base, power - 1);
    }
    return ans;
}

int my_atoi(char *param_1) {
    int integer = 0;
    int sign = 1;
    int int_len = strlen(param_1) - 1;

    while(*param_1) {
        if(*param_1 == '-') {
            sign *= -1;
            param_1++;
            int_len--;
        }
        else {
            integer += (*param_1 - '0') * my_recursive_pow(10, int_len);
            param_1++;
            int_len--;
        }
    }
    return integer * sign;
}