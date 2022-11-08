#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "./helpers.h"
#include "./tar-file.h"

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