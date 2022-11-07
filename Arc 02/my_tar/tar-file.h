#define BLOCK_SIZE 512
#define SIZE_OF_FIELD_SIZE 12

#ifndef POSIX_TAR_HEADER_T
#define POSIX_TAR_HEADER_T
typedef union {
  union {
    // Pre-POSIX.1-1988 format
    struct {
        char name[100];             // file name
        char mode[8];               // permissions
        char uid[8];                // user id (octal)
        char gid[8];                // group id (octal)
        char size[12];              // size (octal)
        char mtime[12];             // modification time (octal)
        char check[8];              // sum of unsigned characters in block, with spaces in the check field while calculation is done (octal)
        char link;                  // link indicator
        char link_name[100];        // name of linked file
    };

    // UStar format (POSIX IEEE P1003.1)
    struct {
        char __offset__[156];       // first 156 octets of Pre-POSIX.1-1988 format
        char type;                  // file type
        char also_link_name[100];   // name of linked file
        char ustar[8];              // ustar\000
        char owner[32];             // user name (string)
        char group[32];             // group name (string)
        char major[8];              // device major number
        char minor[8];              // device minor number
        char prefix[155];
    };
  };

  char block[BLOCK_SIZE];
} posix_tar_header_t;
#endif

#ifndef TAR_FILE
#define TAR_FILE
typedef struct Tar_file {
  posix_tar_header_t header;
  string_t content;
  struct Tar_file* next_file;
  struct Tar_file* prev_file;
} Tar_file;
#endif

Tar_file* create_tar_file();
void Tar_file__free(Tar_file* self);
int Tar_file__push_content(Tar_file* this, string_t content, int content_size);
int Tar_file__get_file_type(Tar_file* self);