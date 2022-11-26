#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./create_archive.h"
#include "./dir_ops.h"

int append_archive(char *tar_filename, Array *filenames) {
  if(validate_filestat(filenames) > 0) {
    return 1;
  }

  //Exit if no input files
  if(filenames->items == NULL && in_directory(tar_filename) > 0) {
    printf("No input files\n");
    return 0;
  }

  //Check if tar_filename is in current directory
  if(in_directory(tar_filename) > 0) {
    printf("%s in directory\n", tar_filename);
  }

  printf("tar mode -r entered here\n");
  printf("tar filename: %s\n", tar_filename);
  printf("first filename: %s\n", filenames->items[0]);
  //check_tar_file(arguments->included_files[0]);
  return 0;
}