#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./helpers.h"
#include "./tar-file.h"
#include "./t_file_info.h"

int fill_tar_header(tar_header_ptr tar_file_header, file_info f_info){
  char *mode = octal_string(f_info->mode, 8);
  char *uid = octal_string(f_info->uid, 8);
  char *gid = octal_string(f_info->gid, 8);
  char *size = octal_string(f_info->size, 12);
  char *mtime = octal_string(f_info->mtime, 12);
  char *devmajor = octal_string(f_info->devmajor, 8);
  char *devminor = octal_string(f_info->devminor, 8);
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
  tar_file_header->typeflag = f_info->typeflag;
  strncpy(tar_file_header->magic, f_info->magic, 6);
  strncpy(tar_file_header->version, f_info->version, 2);
  strncpy(tar_file_header->uname, f_info->uname, 32);
  strncpy(tar_file_header->gname, f_info->gname, 32);
  strncpy(tar_file_header->devmajor, devmajor, 8);
  strncpy(tar_file_header->devminor, devminor, 8);
  strncpy(tar_file_header->prefix, f_info->prefix, 155);
  
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

//main function for testing above functions
int main() {
  Tar_file *t_file = create_tar_file();
  file_info file_1 = t_file_constructor();
  t_file_initialize(file_1);
  file_1 = get_file_info(file_1, "test-3.txt");
  fill_tar_header(&t_file->header, file_1);

  FILE *file_ptr = fopen("tar-test2.txt", "w");
  fwrite(&t_file->header, 1, BLOCK_SIZE, file_ptr);
  fclose(file_ptr);
  printf("Entry Name: %s\n", t_file->header.name);
  printf("file mode: %s\n", t_file->header.mode);
  printf("uid: %s\n", t_file->header.uid);
  printf("gid: %s\n", t_file->header.gid);
  printf("size: %s\n", t_file->header.size);
  printf("modification time: %s\n", t_file->header.mtime);
  printf("Checksum: %s\n", t_file->header.chksum);
  printf("Typeflag: %c\n", t_file->header.typeflag);
  printf("Link Name: %s\n", t_file->header.linkname);
  printf("magic: %s\n", t_file->header.magic);
  printf("version: %s\n", t_file->header.version);
  printf("User name: %s\n", t_file->header.uname);
  printf("Group name: %s\n", t_file->header.gname);
  printf("major: %s\n", t_file->header.devmajor);
  printf("minor: %s\n", t_file->header.devminor);
  printf("prefix: %s\n", t_file->header.prefix);
  
  return 0;
}