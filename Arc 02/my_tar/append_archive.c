#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./create_archive.h"

int append_archive(char *tar_filename, Array *filenames) {
  if(filenames->items == NULL) {
    return 0;
  }
  printf("tar mode -r entered here\n");
  printf("tar filename: %s\n", tar_filename);
  printf("first filename: %s\n", filenames->items[0]);
  //check_tar_file(arguments->included_files[0]);
  return 0;
}