#include <stdio.h>

#include "./arguments.h"
#include "./hash-table.h"

int main (int argc, char** argv) {
  //Hash table test

  // Hash_Table_str hash_table;
  // Hash_Table__constructor(&hash_table, 10);

  // Hash_Table__set(&hash_table, "test-hash-key", "test--hash-str-value");
  // Hash_Table__set(&hash_table, "test-hash-key2", 123);
  // printf("Result test-hash-key: %s\n", (char*)Hash_Table__get(&hash_table, "test-hash-key"));
  // printf("Result test-hash-key2: %ld\n", (long)Hash_Table__get(&hash_table, "test-hash-key2"));

  arguments_t* arguments = parse_arguments(argc, argv);

  if (validate_arguments(arguments, argc) > 0) return 1;
}
