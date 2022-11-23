#include "./arguments.h"
#include "./helpers.h"
#include "./tar-archive.h"
#include "./tar-file.h"
#include "./t_file_info.h"

int create_header(tar_header_ptr tar_file_header, char *filename);
int read_file_contents(string_t content, char *filename, char *file_size);
Tar_file *build_tar_file(Tar_file *this, char *filename, Tar_file *next, Tar_file *prev);
Tar_file *load_from_filenames(Tar_file *this, Array *filenames);
int create_archive(char *tar_filename, Array *filenames);
