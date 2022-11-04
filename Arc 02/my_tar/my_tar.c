#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>

#include "./arguments.h"
#include "./helpers.h"
#include "./my_tar.h"

int main (int argc, char** argv) {
  arguments_t* arguments = parse_arguments(argc, argv);

  if (validate_arguments(arguments, argc) > 0) return 1;

  if (arguments->create_flag) {
    int file_descriptor = STDOUT_FILENO;
    if (arguments->output_file_flag) {
      file_descriptor = open(arguments->output_file_flag, O_WRONLY | O_TRUNC | O_CREAT | S_IRUSR | S_IWUSR);
      if (file_descriptor < 0) {
        print_message(STDOUT_FILENO, "my_tar: Error opening archive: Failed to create/trunc '");
        print_message(STDOUT_FILENO, arguments->output_file_flag);
        print_message(STDOUT_FILENO, "'\n");
        return 1;
      }
    }

    if (file_descriptor != STDOUT_FILENO) close(file_descriptor);
  }

  if (arguments->extract_flag) {
    int file_descriptor = open(arguments->output_file_flag, O_RDONLY);
    if (file_descriptor < 0) {
      print_message(STDOUT_FILENO, "my_tar: Error opening archive: Failed to open '");
      print_message(STDOUT_FILENO, arguments->output_file_flag);
      print_message(STDOUT_FILENO, "'\n");
      return 1;
    }
    // struct stat filestat;
    // if (fstat(file_descriptor, &filestat) < 0) {
    //   print_message(STDOUT_FILENO, "tar: '");
    //   print_message(STDOUT_FILENO, arguments->output_file_flag);
    //   print_message(STDOUT_FILENO, "' : Cannot stat\n");
    //   return 1;
    // }

    posix_header_t tar_header;
    if (read(file_descriptor, &tar_header, BLOCK_SIZE) < BLOCK_SIZE) {
      print_message(STDOUT_FILENO, "my_tar: Error header reading: '");
      print_message(STDOUT_FILENO, arguments->output_file_flag);
      print_message(STDOUT_FILENO, "'\n");
      return 1;
    }

    printf("name: %s\n", tar_header.name);

    close(file_descriptor);
  }
}
