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
  //Create a new archive if the tar_file doesn't exist and input files are provided
  else if(filenames->items != NULL && in_directory(tar_filename) > 0) {
    Tar_file *files = NULL;
    files = load_from_filenames(files, filenames);
    create_archive(files, tar_filename);
    Tar_file__free(files);
  }

  //Add new entries to the Tar_file linked list and create a new archive
  else if(filenames->items != NULL && in_directory(tar_filename) == 0) {
    Tar_archive *tar_archive = read_archive(tar_filename);
    
  }

  return 0;
}