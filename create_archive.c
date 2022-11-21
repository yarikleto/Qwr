#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "./arguments.h"
#include "./helpers.h"
#include "./tar-archive.h"
#include "./tar-file.h"

int create_archive(int file_descriptor, Array *filenames) {
  Tar_file *first_file = malloc(sizeof(Tar_file));
  first_file->prev_file = NULL;
  
}

int main() {
  return 0;
}