#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "./arguments.h"
#include "./helpers.h"
#include "./tar-archive.h"
#include "./tar-file.h"
#include "./create_archive.h"
#include "./update_archive.h"
#include "./extract_archive.h"

int main (int argc, char** argv) {
  arguments_t* arguments = parse_arguments(argc, argv);
  Tar_file *files = NULL;

  if (validate_arguments(arguments, argc) > 0) {
    free_arguments(arguments);
    return 1;
  }

  //Tar mode: -c Create a new archive
  if (arguments->create_flag) {
    if(validate_filestat(arguments->included_files) > 0) {
      return 1;
    }
    files = load_from_filenames(files, arguments->included_files);
    create_archive(files, arguments->output_file_flag);
    Tar_file__free(files);
  }

  //Tar mode: -t List the contents in the archive
  if (arguments->list_flag) {
    Tar_archive* tar_archive = read_archive(arguments->output_file_flag);
    if (tar_archive == NULL){
      print_message(STDERR_FILENO, "my_tar: This does not look like a tar archive\n");
      print_message(STDERR_FILENO, "my_tar: Exiting with failure status due to previous errors\n");
      free_arguments(arguments);
      return 1;
    }
    Tar_archive__print_files(tar_archive);
    Tar_archive__free(tar_archive);
  }

  //Tar mode: -r and -u
  //Append new entries to the archive. When update_flag is true, append new 
  //entry only if it is newer than its corresponding archive member
  if (arguments->append_flag || arguments->update_flag) {
    append_archive(arguments->output_file_flag, 
                  arguments->included_files, arguments->update_flag);
  }

  //Tar mode: -x extract file from the archive
  if (arguments->extract_flag) {
    extract_archive(arguments->output_file_flag, arguments->included_files);
  }

  free_arguments(arguments);
  return 0;
}
