#include "./helpers.h"
#include "./tar-file.h"

#ifndef TAR_ARCHIVE
#define TAR_ARCHIVE
typedef struct {
  Tar_file* first_file;
} Tar_archive;
#endif

Tar_archive* read_archive(string_t filename);
void Tar_archive__free(Tar_archive* self);