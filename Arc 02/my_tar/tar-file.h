#include "t_file_info.h"

#define BLOCK_SIZE 512
#define SIZE_OF_FIELD_SIZE 12
#define BLOCK_FACTOR 20

#ifndef TAR_HEADER_T
#define TAR_HEADER_T
typedef union {
  struct {        /* byte offset */
    char name[100];               /*   0 */
    char mode[8];                 /* 100 */
    char uid[8];                  /* 108 */
    char gid[8];                  /* 116 */
    char size[12];                /* 124 */
    char mtime[12];               /* 136 */
    char chksum[8];               /* 148 */
    char typeflag;                /* 156 */
    char linkname[100];           /* 157 */
    char magic[6];                /* 257 */
    char version[2];              /* 263 */
    char uname[32];               /* 265 */
    char gname[32];               /* 297 */
    char devmajor[8];             /* 329 */
    char devminor[8];             /* 337 */
    char prefix[155];             /* 345 */
  };
  char block[BLOCK_SIZE];
} tar_header_t;
#endif

#ifndef TAR_FILE
#define TAR_FILE
typedef struct Tar_file {
  tar_header_t header;
  string_t content;
  struct Tar_file* next_file;
  struct Tar_file* prev_file;
} Tar_file;
#endif

typedef tar_header_t *tar_header_ptr;

int fill_tar_header(tar_header_ptr tar_file_header, file_info f_info);
Tar_file* create_tar_file();
void Tar_file__free(Tar_file* self);
int Tar_file__push_content(Tar_file* this, string_t content, int content_size);
int Tar_file__in_archive(Tar_file *this, char *filename);