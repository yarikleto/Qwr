#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include "./arguments.h"
#include "./helpers.h"
#include "./tar-archive.h"
#include "./tar-file.h"
#include "./t_file_info.h"

int create_header(tar_header_ptr tar_file_header, char *filename) {
  file_info f_info = t_file_constructor();
  t_file_initialize(f_info);
  f_info = get_file_info(f_info, filename);
  if(f_info->name[0] == '\0') {
    print_message(STDERR_FILENO, "Error creating header\n");
    t_file_destructor(f_info);
    return 1;
  }
  t_file_destructor(f_info);
  return 0;
}

int read_file_contents(string_t content, char *filename, char *file_size) {
  int size = atoi(file_size);
  int fd = open(filename, O_RDONLY);
  if(fd == -1) {
    print_message(STDERR_FILENO, "Error: cannot read file\n");
    return 1;
  }

  return 0;
}

Tar_file *load_from_filenames(Tar_file *this, Array *filenames) {
  this = create_tar_file();

  //Creates header from single filename only
  create_header(&this->header, filenames->items[0]);

  return this;
}

int create_archive(char *tar_filename, Array *filenames) {
  return 0;
}

int main(int argc, char **argv) {
  char *tar_name;
  Array *filename = create_array();
  Tar_file *files = NULL;
  if(argc < 3) {
    printf("ERROR: Must enter a tar name and file name\n");
    return 1;
  }
  tar_name = strdup(argv[1]);
  Array__push(filename, argv[2]);
  files = load_from_filenames(files, filename);
  if(files->header.name[0] != '\0') {
    print_message(STDOUT_FILENO, "load from filename successful!\n");
  }
  else {
    print_message(STDERR_FILENO, "load from filename NOT sucessful\n");
  }

  Tar_file__free(files);
  free(tar_name);
  Array__free(filename);
  return 0;
}