#include "./create_archive.h"

int update_archive(char *tar_filename, Array *filenames);
int append_archive(char *tar_filename, Array *filenames, bool update_flag);