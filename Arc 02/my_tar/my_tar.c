#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "./arguments.h"
#include "./helpers.h"
#include "./tar-archive.h"

int main (int argc, char** argv) {
  arguments_t* arguments = parse_arguments(argc, argv);

  if (validate_arguments(arguments, argc) > 0) return 1;

  //Debug printf's
  printf("Arguments size: %d\n", arguments->included_files->size);
  if(arguments->included_files->items != NULL){
    for(int i = 0; arguments->included_files->items[i] != NULL;i++) {
      printf("%s\n", arguments->included_files->items[i]);
    }
  }

  if (arguments->create_flag) {
    int file_descriptor = STDOUT_FILENO;
    if (arguments->output_file_flag) {
      file_descriptor = open(arguments->output_file_flag, O_WRONLY | O_TRUNC | O_CREAT | S_IRUSR | S_IWUSR);
      if (file_descriptor < 0) {
        print_message(STDOUT_FILENO, "my_tar: Error opening archive: Failed to create/trunc '");
        print_message(STDOUT_FILENO, arguments->output_file_flag);
        print_message(STDOUT_FILENO, "'\n");
        free_arguments(arguments);
        return 1;
      }
    }

    if (file_descriptor != STDOUT_FILENO) close(file_descriptor);
  }

  if (arguments->extract_flag) {
    Tar_archive* tar_archive = read_archive(arguments->output_file_flag);
    if (tar_archive == NULL) {
      Tar_archive__free(tar_archive);
      return 1;
    }
    Tar_archive__free(tar_archive);
  }

  free_arguments(arguments);
}
