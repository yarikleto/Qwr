#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "./arguments.h"
#include "./helpers.h"
#include "./tar-archive.h"
#include "./tar-file.h"
#include "./t_file_info.h"

int create_archive(char *tar_filename, Array *filenames) {
  int index = 0;
  Tar_file *first_file = create_tar_file();
  
  //Create header
  file_info f_info = t_file_constructor();
  t_file_initialize(f_info);
  f_info = get_file_info(f_info, filenames->items[0]);  //store 1 filename
  fill_tar_header(&first_file->header, f_info);

  //Fill content
  
  return 0;
}

int main(int argc, char **argv) {
  char *tar_name;
  Array *filename = create_array();
  if(argc < 3) {
    printf("ERROR: Must enter a tar name and file name\n");
    return 1;
  }
  tar_name = strdup(argv[1]);
  Array__push(filename, argv[2]);

  create_archive(tar_name, filename);

  free(tar_name);
  Array__free(filename);
  return 0;
}