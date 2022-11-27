#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>

#include "./arguments.h"
#include "./helpers.h"
#include "./tar-archive.h"
#include "./tar-file.h"

int main (int argc, char** argv) {
  arguments_t* arguments = parse_arguments(argc, argv);

  if (validate_arguments(arguments, argc) > 0) return 1;

  if (arguments->create_flag) {
    int file_descriptor = STDOUT_FILENO;
    Tar_archive* tar_archive = create_archive();

    if (arguments->output_file_flag) {
      file_descriptor = open(arguments->output_file_flag, O_WRONLY | O_TRUNC | O_CREAT | S_IRWXU);
      if (file_descriptor < 0) {
        print_message(STDOUT_FILENO, "my_tar: Error opening archive: Failed to create/trunc '");
        print_message(STDOUT_FILENO, arguments->output_file_flag);
        print_message(STDOUT_FILENO, "'\n");
        return 1;
      }
    }

    for (int i = 0; i < arguments->included_files->size; ++i) {
      string_t file_path = arguments->included_files->items[i];

      struct stat filestat;
      if (stat(file_path, &filestat) < 0) {
        print_message(STDOUT_FILENO, "tar: '");
        print_message(STDOUT_FILENO, file_path);
        print_message(STDOUT_FILENO, "' : Cannot stat\n");
        return 1;
      }

      Tar_file* active_file = NULL;
      if (active_file) {
        active_file->next_file = create_tar_file();
        active_file->next_file->prev_file = active_file;
        active_file = active_file->next_file;
      } else {
        active_file = create_tar_file();
        tar_archive->first_file = active_file;
      }

      memory_copy(
        active_file->header.name,
        S_ISDIR(filestat.st_mode) ? concat_strings(file_path, "/", -1) : file_path,
        SIZE_OF_FIELD_NAME
      );

      printf("Mode: %d\n", (filestat.st_mode & S_IRUSR) == S_IRUSR);
      // active_file->header.mode

    }

    Tar_archive__save(tar_archive, file_descriptor);
    if (file_descriptor != STDOUT_FILENO) close(file_descriptor);
  }

  if (arguments->list_flag) {
    Tar_archive* tar_archive = read_archive(arguments->output_file_flag);
    if (tar_archive == NULL) return 1;

    Tar_archive__print_files(tar_archive);
  }

  if (arguments->extract_flag) {
    Tar_archive* tar_archive = read_archive(arguments->output_file_flag);
    if (tar_archive == NULL) return 1;

    // !!!! For the debug purpose
    {
      Tar_file* file = tar_archive->first_file;

      while (file) {
        printf("------------------------\n");
        print_block(&file->header, BLOCK_SIZE, '^');
        // printf("Name: %s\n", file->header.name);
        // printf("Mode: %d\n", oct_str_to_bytes(file->header.mode, 8));
        // printf("Size: %d\n", oct_str_to_bytes(file->header.size, SIZE_OF_FIELD_SIZE));
        // printf("Content length: %d\n", get_str_length(file->content));
        // printf("Type: %d\n", file->header.typeflag - '0');
        // printf("Content: %s\n", file->content);
        printf("------------------------\n");
        file = file->next_file;
      }
    }
  }
}
