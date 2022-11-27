#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./helpers.h"
#include "./tar-file.h"
#include "./t_file_info.h"

char *calculate_checksum(tar_header_ptr tar_header) {
  char *checksum;
  int ascii_sum = 0;
  char *real_checksum = calloc(8, sizeof(char));

  for(int i = 0; i < BLOCK_SIZE - 12; i++) {
    ascii_sum += tar_header->block[i];
  }
  checksum = octal_string(ascii_sum, 7);
  strcpy(real_checksum, checksum);
  real_checksum[7] = ' ';
  free(checksum);

  return real_checksum;
}

int fill_tar_header(tar_header_ptr tar_file_header, file_info f_info){
  char *mode = octal_string(f_info->mode, 8);
  char *uid = octal_string(f_info->uid, 8);
  char *gid = octal_string(f_info->gid, 8);
  char *size = octal_string(f_info->size, 12);
  char *mtime = octal_string(f_info->mtime, 12);
  char devmajor[8] = {0};
  char devminor[8] = {0};
  char *checksum;
  
  if(f_info == NULL) {
    return 1;
  }
  strncpy(tar_file_header->name, f_info->name, 100);
  strncpy(tar_file_header->mode, mode, 8);
  strncpy(tar_file_header->uid, uid, 8);
  strncpy(tar_file_header->gid, gid, 8);
  strncpy(tar_file_header->size, size, 12);
  strncpy(tar_file_header->mtime, mtime, 12);
  memory_copy(tar_file_header->chksum, "        ", 8);
  tar_file_header->typeflag = f_info->typeflag;
  strncpy(tar_file_header->linkname, f_info->linkname, 100);
  memory_copy(tar_file_header->magic, "ustar ", 6);
  strncpy(tar_file_header->version, " ", 2);
  strncpy(tar_file_header->uname, f_info->uname, 32);
  strncpy(tar_file_header->gname, f_info->gname, 32);
  strncpy(tar_file_header->devmajor, devmajor, 8);
  strncpy(tar_file_header->devminor, devminor, 8);
  strncpy(tar_file_header->prefix, f_info->prefix, 155);
  checksum = calculate_checksum(tar_file_header);
  memory_copy(tar_file_header->chksum, checksum, 8);

  free(mode);
  free(uid);
  free(gid);
  free(size);
  free(mtime);
  free(checksum);
  
  return 0;
}

Tar_file* create_tar_file() {
  Tar_file* tar_file = malloc(sizeof(Tar_file));
  tar_file->content = NULL;
  tar_file->next_file = NULL;
  tar_file->prev_file = NULL;

  return tar_file;
}

int Tar_file__push_content(Tar_file* this, string_t content, int content_size) {
  string_t new_content = concat_strings(this->content, content, content_size);
  if (!new_content) return 1;

  if (this->content) free(this->content);
  this->content = new_content;

  return 0;
}

void Tar_file__free(Tar_file* this) {
  if (this == NULL) return;

  Tar_file__free(this->next_file);
  free(this->content);
  free(this);
}

int Tar_file__get_file_type(Tar_file* this) {
  return this->header.typeflag - '0';
}

//Find archive member in the archive; return 0 if found; 1 otherwise
int Tar_file__in_archive(Tar_file *this, char *filename) {
  for(Tar_file *current_file = this; current_file != NULL;
      current_file = current_file->next_file) {
    if(strcmp(filename, current_file->header.name) == 0) {
      return 0;
    }
  }
  return 1;
}

//main function for testing above functions
// int main(int argc, char **argv) {
//   Tar_file *t_file = create_tar_file();
//   file_info file_1 = t_file_constructor();
//   t_file_initialize(file_1);
//   file_1 = get_file_info(file_1, argv[1]);
//   fill_tar_header(&t_file->header, file_1);

//   if(Tar_file__in_archive(t_file, "test-3.txt") == 0) {
//     printf("test-3.txt is in the archive");
//   }
//   t_file_destructor(file_1);
//   Tar_file__free(t_file);
  
//   return 0;
// }