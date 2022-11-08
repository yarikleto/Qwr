#include <unistd.h>

#include "./arguments.h"
#include "./helpers.h"
#include "./tar-archive.h"
#include "./tar-file.h"

int main (int argc, char** argv) {
  arguments_t* arguments = parse_arguments(argc, argv);

  if (validate_arguments(arguments, argc) > 0) return 1;

  if (arguments->create_flag) {
    // int file_descriptor = STDOUT_FILENO;
    // if (arguments->output_file_flag) {
    //   file_descriptor = open(arguments->output_file_flag, O_WRONLY | O_TRUNC | O_CREAT | S_IRUSR | S_IWUSR);
    //   if (file_descriptor < 0) {
    //     print_message(STDOUT_FILENO, "my_tar: Error opening archive: Failed to create/trunc '");
    //     print_message(STDOUT_FILENO, arguments->output_file_flag);
    //     print_message(STDOUT_FILENO, "'\n");
    //     return 1;
    //   }
    // }

    // if (file_descriptor != STDOUT_FILENO) close(file_descriptor);
  }

  if (arguments->list_flag) {
    Tar_archive* tar_archive = read_archive(arguments->output_file_flag);
    if (tar_archive == NULL) return 1;

    Tar_archive__print_files(tar_archive);
  }

  if (arguments->extract_flag) {
    Tar_archive* tar_archive = read_archive(arguments->output_file_flag);
    if (tar_archive == NULL) return 1;

    // TODO: debug an archive
    // {
    //   Tar_file* file = tar_archive->first_file;

    //   while (file) {
    //     printf("------------------------\n");
    //     printf("Name: %s\n", file->header.name);
    //     printf("Size: %d\n", oct_str_to_bytes(file->header.size, SIZE_OF_FIELD_SIZE));
    //     printf("Content length: %d\n", get_str_length(file->content));
    //     printf("Type: %d\n", file->header.typeflag);
    //     printf("Content: %s\n", file->content);
    //     printf("------------------------\n");
    //     file = file->next_file;
    //   }
    // }
  }
}
