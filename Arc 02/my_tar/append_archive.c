#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include "./create_archive.h"
#include "./dir_ops.h"

int append_archive(char *tar_filename, Array *filenames) {
  int file_descriptor;
  
  if(validate_filestat(filenames) > 0) {
    return 1;
  }

  //Create a 20 block null byte file if tar_file doesn't exist and no input files
  if(filenames->items == NULL && in_directory(tar_filename) > 0) {
    file_descriptor = open(tar_filename, O_RDWR | O_CREAT, 
                        ((S_IWUSR | S_IRUSR) | (S_IRGRP | S_IWGRP) | S_IROTH));
    char null_pad[BLOCK_SIZE] = {0};
    for(int i = 0; i < BLOCK_FACTOR; i++) {
      write(file_descriptor, &null_pad, BLOCK_SIZE);
    }
    close(file_descriptor);
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