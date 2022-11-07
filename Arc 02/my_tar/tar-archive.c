#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "./helpers.h"
#include "./tar-archive.h"

// struct stat filestat;
  // if (fstat(file_descriptor, &filestat) < 0) {
  //   print_message(STDOUT_FILENO, "tar: '");
  //   print_message(STDOUT_FILENO, path);
  //   print_message(STDOUT_FILENO, "' : Cannot stat\n");
  //   return 1;
  // }

Tar_archive* read_archive(string_t filename) {
  int file_descriptor = open(filename, O_RDONLY);
  if (file_descriptor < 0) {
    print_message(STDOUT_FILENO, "my_tar: Error opening archive: Failed to open '");
    print_message(STDOUT_FILENO, filename);
    print_message(STDOUT_FILENO, "'\n");
    return NULL;
  }

  Tar_archive* tar_archive = malloc(sizeof(Tar_archive));
  int empty_block_amount = 0;
  Tar_file* active_file = NULL;

  while (empty_block_amount < 2) {
    char block[BLOCK_SIZE];
  
    if (read(file_descriptor, block, BLOCK_SIZE) < BLOCK_SIZE) {
      print_message(STDOUT_FILENO, "my_tar: Error block reading: '");
      print_message(STDOUT_FILENO, filename);
      print_message(STDOUT_FILENO, "'\n");
      close(file_descriptor);
      return NULL;
    }

    if (is_block_empty(block)) {
      empty_block_amount += 1;
      continue;
    }

    if (active_file) {
      active_file->next_file = create_tar_file();
      active_file->next_file->prev_file = active_file;
      active_file = active_file->next_file;
    } else {
      active_file = create_tar_file();
      tar_archive->first_file = active_file;
    }

    memory_copy(&active_file->header, &block, BLOCK_SIZE);

    int content_size_in_bytes = oct_str_to_bytes(active_file->header.size, SIZE_OF_FIELD_SIZE);
    int loaded_size_in_bytes = 0;

    while (loaded_size_in_bytes < content_size_in_bytes) {
      if (read(file_descriptor, block, BLOCK_SIZE) < BLOCK_SIZE) {
        print_message(STDOUT_FILENO, "my_tar: Error content reading: '");
        print_message(STDOUT_FILENO, filename);
        print_message(STDOUT_FILENO, "'\n");
        close(file_descriptor);
        return NULL;
      }

      int block_content_size = MIN(content_size_in_bytes - loaded_size_in_bytes, BLOCK_SIZE);
      loaded_size_in_bytes += block_content_size;
      string_t chunk_of_content = get_str_slice(block, 0, block_content_size);

      if (Tar_file__push_content(active_file, chunk_of_content) > 0) {
        print_message(STDOUT_FILENO, "my_tar: Unable to push content\n");
        close(file_descriptor);
        free(chunk_of_content);
        return NULL;
      }
      free(chunk_of_content);
    }
  }

  // TODO: debug an archive
  {
    Tar_file* file = tar_archive->first_file;

    while (file) {
      printf("------------------------\n");
      printf("Name: %s\n", file->header.name);
      printf("Size: %d\n", oct_str_to_bytes(file->header.size, SIZE_OF_FIELD_SIZE));
      printf("Content length: %d\n", get_str_length(file->content));
      printf("Type: %d\n", Tar_file__get_file_type(file));
      printf("Content: %s\n", file->content);
      printf("------------------------\n");
      file = file->next_file;
    }
  }

  close(file_descriptor);
  return tar_archive;
}

void Tar_archive__free(Tar_archive* this) {
  Tar_file__free(this->first_file);
  free(this);
}