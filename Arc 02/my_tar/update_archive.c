#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include "./arguments.h"
#include "./create_archive.h"
#include "./dir_ops.h"

int append_archive(char *tar_filename, Array *filenames, bool update_flag) {
  int file_descriptor;
  
  if(validate_filestat(filenames) > 0) {
    return 1;
  }
  if(is_directory(tar_filename) > 0) {
    print_message(STDERR_FILENO, "my_tar: ");
    print_message(STDERR_FILENO, tar_filename);
    print_message(STDERR_FILENO, ": Cannot read: Bad file descriptor\n");
    print_message(STDERR_FILENO, "my_tar: Error is not recoverable: exiting now\n");
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
    Tar_file *last_file = NULL;
    Tar_archive *tar_archive = read_archive(tar_filename);
    Tar_file *current_file = tar_archive->first_file;
    Tar_file *new_entries = NULL;
    new_entries = load_from_filenames(new_entries, filenames);
    Tar_file *new_entries_head = new_entries;
    Tar_file *current_file_head = current_file;
    Tar_file *temp_tar_file_ptr = NULL;

    //If -u is true,remove new entries if it is not newer than the archive entry
    if(update_flag == true) {
      while(new_entries) {
        while(current_file) {
          if(strcmp(current_file->header.name, new_entries->header.name) == 0
            && current_file->header.mtime >= new_entries->header.mtime) {
            temp_tar_file_ptr = new_entries;
            new_entries->next_file->prev_file = new_entries->prev_file;
            new_entries->prev_file->next_file = new_entries->next_file;
            new_entries = new_entries->next_file;
            Tar_file__free(temp_tar_file_ptr);
          }
          current_file = current_file->next_file;
        }
        new_entries = new_entries->next_file;
      }
      new_entries = new_entries_head;
      current_file = current_file_head;
    }
    
    //Point to the last file in the tar archive
    while(current_file) {
      last_file = current_file;
      current_file = current_file->next_file;
    }

    new_entries->prev_file = last_file;
    last_file->next_file = new_entries;
    create_archive(tar_archive->first_file, tar_filename);
    Tar_archive__free(tar_archive);
  }

  //Append 20 block null byte file to a non-tar file
  else if(filenames->items == NULL && in_directory(tar_filename) == 0) {
    Tar_archive *tar_archive = read_archive(tar_filename);
    char *tar_file_size = get_file_size(tar_filename);
    string_t tar_file_contents = malloc(my_atoi(tar_file_size) + 1 *sizeof(char));
    read_file_contents(tar_file_contents, tar_filename, tar_file_size);

    if(tar_archive == NULL) {
      int file_descriptor = open(tar_filename, O_RDWR | O_CREAT, 
                    ((S_IWUSR | S_IRUSR) | (S_IRGRP | S_IWGRP) | S_IROTH));
      char null_pad[BLOCK_SIZE] = {0};

      write(file_descriptor, tar_file_contents, oct_2_dec(my_atoi(tar_file_size)));
      for(int i = 0; i < BLOCK_FACTOR; i++) {
        write(file_descriptor, &null_pad, BLOCK_SIZE);
      }
      close(file_descriptor);
      free(tar_file_contents);
      free(tar_file_size);
      print_message(STDERR_FILENO, "my_tar: This does not look like a tar archive\n");
      print_message(STDERR_FILENO, "my_tar: Exiting with failure status due to previous errors\n");
    }
    else {
      printf("Code entered here\n");
      free(tar_file_contents);
      free(tar_file_size);
      Tar_archive__free(tar_archive);
    }
  }
  
  return 0;
}
