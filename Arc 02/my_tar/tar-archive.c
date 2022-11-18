#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "./helpers.h"
#include "./tar-archive.h"
#include "./tar-file.h"

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

    if (is_block_empty(block, BLOCK_SIZE)) {
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

      if (Tar_file__push_content(active_file, block, block_content_size) > 0) {
        print_message(STDOUT_FILENO, "my_tar: Unable to push content\n");
        close(file_descriptor);
        return NULL;
      }
    }
  }

  close(file_descriptor);
  return tar_archive;
}

void Tar_archive__print_files(Tar_archive* this) {
  Tar_file* file = this->first_file;
  while (file) {
    print_message(STDOUT_FILENO, file->header.name);
    print_message(STDOUT_FILENO, "\n");
    file = file->next_file;
  }
}

int Tar_archive__save(Tar_archive* this, int file_descriptor) {
  Tar_file* file = this->first_file;
  char empty_block[BLOCK_SIZE] = {0};

  while (file) {
    write(file_descriptor, &file->header, BLOCK_SIZE);

    int content_size_in_bytes = oct_str_to_bytes(file->header.size, SIZE_OF_FIELD_SIZE);
    int saved_size_in_bytes = 0;
    while (saved_size_in_bytes < content_size_in_bytes) {
      string_t str_slice = get_str_slice(
        file->content,
        saved_size_in_bytes,
        saved_size_in_bytes + BLOCK_SIZE
      );
      int slice_length = get_str_length(str_slice);
      write(file_descriptor, str_slice, slice_length);
      write(file_descriptor, empty_block, BLOCK_SIZE - slice_length);

      saved_size_in_bytes += BLOCK_SIZE;
      free(str_slice);
    }

    file = file->next_file;
  }

  write(file_descriptor, empty_block, BLOCK_SIZE);
  write(file_descriptor, empty_block, BLOCK_SIZE);

  return 0;
}

void Tar_archive__free(Tar_archive* this) {
  Tar_file__free(this->first_file);
  free(this);
}