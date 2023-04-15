#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <utime.h>

#include "tar-archive.h"
#include "array.h"
#include "dir_ops.h"

int extract_file(Tar_file *archive_member) {
  unlink(archive_member->header.name);
  int mode = oct_2_dec(my_atoi(archive_member->header.mode));
  struct utimbuf timebuf;
  timebuf.modtime = long_oct_2_dec(my_atol(archive_member->header.mtime));
  timebuf.actime = timebuf.modtime;
  int file_descriptor = open(archive_member->header.name, O_RDWR | O_CREAT, mode);
  write(file_descriptor, archive_member->content, 
        oct_2_dec(my_atoi(archive_member->header.size)));
  utime(archive_member->header.name, &timebuf);
  close(file_descriptor);
  return 0;
}

Tar_file *extract_directory_contents(Tar_file *archive_dir) {
  char *archive_dir_name = strdup(archive_dir->header.name);
  archive_dir_name = add_forward_slash(archive_dir_name);
  int mode = oct_2_dec(my_atoi(archive_dir->header.mode));
  struct utimbuf dir_timebuf;
  struct utimbuf subdir_timebuf;
  dir_timebuf.modtime = long_oct_2_dec(my_atol(archive_dir->header.mtime));
  dir_timebuf.actime = dir_timebuf.modtime;

  if(in_directory(archive_dir_name) > 0) {
    mkdir(archive_dir_name, mode);
  }
  
  Tar_file *current_file = archive_dir->next_file;
  for(;current_file != NULL && 
      strncmp(current_file->header.name, archive_dir_name, strlen(archive_dir_name)) == 0;
      current_file = current_file->next_file) {
    
    if(current_file->header.typeflag == DIRTYPE) {
      mode = oct_2_dec(my_atoi(current_file->header.mode));
      mkdir(current_file->header.name, mode);
      subdir_timebuf.modtime = long_oct_2_dec(my_atol(current_file->header.mtime));
      subdir_timebuf.actime = subdir_timebuf.modtime;
      utime(current_file->header.name, &subdir_timebuf);
    }
    else {
      extract_file(current_file);
    }
  }

  free(archive_dir_name);
  return current_file;
}

int extract_archive(char *tar_filename, Array *filenames) {
  Tar_archive* tar_archive = read_archive(tar_filename);
  
  if (tar_archive == NULL) {
    return 1;
  }

  //Extract all archive members
  if(filenames->size == 0) {
    for(Tar_file *current_file = tar_archive->first_file; current_file != NULL; 
        current_file = current_file->next_file) {
      if(current_file->header.typeflag == REGTYPE || current_file->header.typeflag == SYMTYPE) {
        extract_file(current_file);
      }
      else if(current_file->header.typeflag == DIRTYPE) {
        current_file = extract_directory_contents(current_file);
        if(current_file == NULL) {
          break;
        }
      }
    }
    Tar_archive__free(tar_archive);
    return 0;
  }

  //Extract the specified files or directories
  else {
    for(int i = 0; i < filenames->size; i++) {
      for(Tar_file *current_file = tar_archive->first_file; current_file != NULL; 
          current_file = current_file->next_file) {
        int file_in_archive = strncmp(current_file->header.name, 
                                      filenames->items[i], 
                                      strlen(current_file->header.name));

        //Extract a single regular file
        if(file_in_archive == 0 && current_file->header.typeflag == REGTYPE) {
          extract_file(current_file);
          break;
        }
        //Extract directory and its contents
        else if(file_in_archive == 0 && current_file->header.typeflag == DIRTYPE) {
          current_file = extract_directory_contents(current_file);
          break;
        }

        else if(current_file->next_file != NULL) {
          continue;
        }

        else {
          print_message(STDERR_FILENO, "my_tar: ");
          print_message(STDERR_FILENO, filenames->items[i]);
          print_message(STDERR_FILENO, ": Not found in archive\n");
          print_message(STDERR_FILENO, 
                  "my_tar: Exiting with failure status due to previous errors\n");
        }
      }
    }
  }
  Tar_archive__free(tar_archive);
  return 0;
}
