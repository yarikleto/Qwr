#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include "./arguments.h"
#include "./helpers.h"
#include "./tar-file.h"
#include "./t_file_info.h"

int create_header(tar_header_ptr tar_file_header, char *filename) {
  file_info f_info = t_file_constructor();
  t_file_initialize(f_info);
  f_info = get_file_info(f_info, filename);

  if(f_info->name[0] == '\0') {
    print_message(STDERR_FILENO, "Error: cannot create header\n");
    t_file_destructor(f_info);
    return 1;
  }
  fill_tar_header(tar_file_header, f_info);
  t_file_destructor(f_info);
  return 0;
}

int read_file_contents(string_t content, char *filename, char *file_size) {
  int size = oct_2_dec(my_atoi(file_size));
  int content_to_read = size;
  int fd = open(filename, O_RDONLY);

  if(fd == -1) {
    print_message(STDERR_FILENO, "Error: cannot read file\n");
    return 1;
  }

  if(size < 512) {
    read(fd, content, 512);
  }

  while(content_to_read > 0) {
    read(fd, content, content_to_read);
    content_to_read -= 512;
  }

  //Debug: print contents stored in content
  // write(1, content, size);
  // write(1, "\n", 1);
  return 0;
}

//Build one doubly linked list Tar_file node
Tar_file *build_tar_file(Tar_file *this, char *filename, Tar_file *next, Tar_file *prev) {
  this = create_tar_file();
  create_header(&this->header, filename);
  this->content = calloc(my_atoi(this->header.size)+1,sizeof(char));
  read_file_contents(this->content, filename, this->header.size);
  this->next_file = next;
  this->prev_file = prev;
  return this;
}

//Build Tar_file linked list from array of valid filenames
Tar_file *load_from_filenames(Tar_file *this, Array *filenames) {
  this = NULL;
  Tar_file *tail;
  int i;
  
  this = build_tar_file(this, filenames->items[0], NULL, NULL);
  tail = this;

  for(i = 1; i < filenames->size; i++) {
    tail->next_file = build_tar_file(tail->next_file, filenames->items[i], NULL, tail);
    tail = tail->next_file;
  }
  tail = NULL;
  return this;
}

int create_archive(char *tar_filename, Array *filenames) {
  return 0;
}

//main function for debugging above functions
int main(int argc, char **argv) {
  char *tar_name;
  int load_success_flag = 0;
  Array *filename = create_array();
  Tar_file *files;
  
  if(argc < 3) {
    printf("ERROR: Must enter a tar name and file name\n");
    return 1;
  }
  
  tar_name = strdup(argv[1]);
  for(int i = 2; i < argc; i++) {
    Array__push(filename, argv[i]);
  }
  files = load_from_filenames(files, filename);
  
  //Check each node has properly loaded the Tar_file properties
  for(Tar_file *current_node = files; current_node != NULL; current_node = current_node->next_file){
    if(current_node->header.typeflag == '5') {
      continue;
    }
    if(current_node->header.name[0] == '\0' || current_node->content[0] == '\0') {
      load_success_flag = 1;
    }
  }

  if(load_success_flag > 0) {
    print_message(STDERR_FILENO, "Error: load from filename NOT sucessful\n");
  }
  else {
    //Debug: write contents of each Tar_file node to a text file
    char *output_text_file = "tar-test2.txt";
    FILE *file_ptr = fopen(output_text_file, "w");
    print_message(STDOUT_FILENO, "Printing Tar_file contents to file\n");
    for(Tar_file *current_node = files; current_node != NULL; current_node = current_node->next_file) {
      fwrite(current_node->content, 1, oct_2_dec(my_atoi(current_node->header.size)), file_ptr);
    }
    fclose(file_ptr);
    print_message(STDOUT_FILENO, "load from filename successful!\n");
  }

  Tar_file__free(files);
  free(tar_name);
  Array__free(filename);
  return 0;
}