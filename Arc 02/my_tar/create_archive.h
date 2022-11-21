#include "./arguments.h"
#include "./helpers.h"
#include "./tar-archive.h"
#include "./tar-file.h"
#include "./t_file_info.h"

int create_header(tar_header_ptr tar_file_header, char *filename);
int load_from_filenames(Tar_file *this, Array *filenames);
int create_archive(char *tar_filename, Array *filenames);
