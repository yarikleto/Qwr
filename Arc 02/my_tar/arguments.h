#include <stdbool.h>

#include "./helpers.h"

#ifndef ARGUMENTS_T
#define ARGUMENTS_T
typedef struct {
  // create a new archive
  bool create_flag; // -c
  //  append files to the end of an archive
  bool append_flag; // -r
  // show a list of files and folders in the archive
  bool list_flag; // -t
  // Like -r, but new entries are added only if they have a modification date newer than the corresponding entry in the archive.
  // Note that this only works on uncompressed archives stored in regular files.  The -f option is required.
  bool update_flag; // -u
  // Extract to disk from the archive.
  // If a file with the same name appears more than once in the archive, each copy will be extracted, with later copies overwriting (replacing)
  // earlier copies.
  bool extract_flag; // -x
  // Read the archive from or write the archive to the specified file. The filename can be standard input or standard output.
  char* output_file_flag; // -f

  array_of_str_t included_files;
} arguments_t;
#endif



arguments_t* parse_arguments(int argc, char** argv);
void free_arguments(arguments_t* arguments);
int validate_arguments(arguments_t* arguments, int argc);